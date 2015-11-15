//
//  Affichage.cpp
//  Projet2MIC
//
//  Created by Rémi on 12/08/12.
//  Copyright (c) 2012 Rémi Saurel. All rights reserved.
//

#include "ContextManager.h"
#include <algorithm>
#include "Shader.h"
#include <stack>
#include <cmath>
#include "VertexManager.h"
#include "GL.h"
#include "Framebuffer.h"
#include "CoreGL.h"
#include <si-units/TimePoint.h>
#include <array>

using namespace Units::UnitsLiterals;

namespace VertexManager {
    void init();
}

namespace ShaderPrivate {
    void init();
    void frameConstantsUpdate();
}

namespace ContextManager {
    std::unique_ptr<GLContext> _context;
    std::unique_ptr<Texture> _emptyTex;

    std::unique_ptr<Texture> _cursor;
    bool _cursorVisible;
    ivec2 _distanceToCross;

    Units::Frequency _frequence;
    Units::Frequency _frequenceInstantanee;

    std::unique_ptr<Screen> _screen;
    std::unique_ptr<Framebuffer> _renderTarget;
    GLsizei _maxSamples = 0;
    GLfloat _maxAnisotropy = 0;

    ObserverID _lastObserverId = 0;
    std::list<std::pair<std::function<void()>, ObserverID>> _resolutionObservers;

    void clean();
    void flush();
    void initDraw();

    void init(std::unique_ptr<GLContext> context);
}

void ContextManager::init(std::unique_ptr<GLContext> context) {
    if(ContextManager::hasGLContext())
        return;

    try {
        context->init();
    } catch(std::exception const &e) {
        std::cerr << "Unable to init GL context!\n" << e.what() << std::endl;
        throw;
    }

    _context = std::move(context);

    myGlewInit();

    glGetIntegerv(GL_MAX_SAMPLES, &_maxSamples);
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &_maxAnisotropy);

    _context->setSamples(glm::clamp(_context->samples(), 1, _maxSamples));

    _context->setAnisotropy(glm::clamp(_context->anisotropy(), 1.0f, _maxAnisotropy));
    Texture::setAnisotropy(_context->anisotropy());

    _screen = std::make_unique<Screen>();
    _renderTarget = std::make_unique<Framebuffer>(_context->size(), 0, false);
    RenderTarget::push(*_screen);
    RenderTarget::push(*_renderTarget);

    ShaderPrivate::init();
    VertexManager::init();

    _context->changeResolution(_context->size(), _context->fullScreen(), _context->vsync());

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _context->swapBuffers();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    glDepthRange(0.0f, 1.0f);

    Shader::orthoTex().bind();

    {
        std::array<GLubyte, 4> const data = {0, 0, 0, 255};
        _emptyTex = std::make_unique<Texture>(data.data(), vec2{1, 1}, 4, 1, false);
    }

    ShaderPrivate::frameConstantsUpdate();

    resetCursor();
    setCursorVisibility(false);
    _context->showWindow();
}

void ContextManager::clean() {
    _context = nullptr;
}

void ContextManager::changeResolution(ivec2 const &resolution, bool fullScreen, bool vsync, GLsizei samples, GLfloat anisotropy) {
    _context->changeResolution(resolution, fullScreen, vsync);

    _frequence = {};

    _screen->resize(resolution);
    _renderTarget->resize(resolution);

    for(auto obs : _resolutionObservers) {
        obs.first();
    }
}

bool ContextManager::hasGLContext() {
    return _context != nullptr;
}

GLsizei ContextManager::maxSamples() {
    return _maxSamples;
}

GLfloat ContextManager::maxAnisotropy() {
    return _maxAnisotropy;
}

void ContextManager::addResolutionObserver(std::function<void()> const &f, ObserverID &observerID) {
    _resolutionObservers.emplace_back(f, ++_lastObserverId);
    observerID = _resolutionObservers.back().second;
}

void ContextManager::removeResolutionObserver(ObserverID const &observer) {
    _resolutionObservers.remove_if([&observer](decltype(_resolutionObservers)::value_type const &obs) {
        return obs.second == observer;
    });
}

Texture ContextManager::currentDisplay() {
    return _renderTarget->clone(0);
}

void ContextManager::flush() {
    static Units::TimePoint const start;
    static Units::TimePoint h, h1;
    static size_t c = 0;
    ++c;
    auto now = Units::TimePoint::now();
    _frequenceInstantanee = 1.0f / (now - h1);
    h1 = now;
    if(now - h >= 3_s) {
        _frequence = c / (now - h);
        c = 0;
        h = now;
    }

    Texture const &renderTarget = _renderTarget->colorBuffers()[0];

    RenderTarget::pop();
    Shader::orthoTex().bind();

    VertexManager::pushTex(renderTarget, vec2{}, true);
    VertexManager::flush();
    _renderTarget->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | RenderTarget::MODELVIEW_BIT |
                         RenderTarget::VIEWPORT_BIT);

    if(_cursorVisible) {
        VertexManager::pushTex(*_cursor, CoreGL::eventManager().cursorPosition() - _distanceToCross);
    }

    VertexManager::flush();

    _context->swapBuffers();

    _screen->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | RenderTarget::MODELVIEW_BIT |
                   RenderTarget::VIEWPORT_BIT);

    RenderTarget::push(*_renderTarget);
}

void ContextManager::initDraw() {
    ShaderPrivate::frameConstantsUpdate();
}

Rectangle ContextManager::bounds() {
    return Rectangle(vec2{}, vec2(ContextManager::size()));
}

ivec2 ContextManager::size() {
    return _context->size();
}

float ContextManager::ratio() {
    return float(ContextManager::size().x) / float(ContextManager::size().y);
}

bool ContextManager::fullScreen() {
    return _context->fullScreen();
}

Units::Frequency ContextManager::averagRefreshRate() {
    return _frequence;
}

Units::Frequency ContextManager::instantRefreshRate() {
    return _frequenceInstantanee;
}

bool ContextManager::cursorVisible() {
    return _cursorVisible;
}

void ContextManager::setCursorVisibility(bool af) {
    _cursorVisible = af;
}

Texture const &ContextManager::cursor() {
    return *_cursor;
}

void ContextManager::setCursor(Texture const &tex, ivec2 const &distanceToCross) {
    _cursor = std::make_unique<Texture>(tex);
    _distanceToCross = distanceToCross;
}

void ContextManager::resetCursor() {
    _cursor = std::make_unique<Texture>(*_emptyTex);
    _distanceToCross = {};
}

Texture &ContextManager::emptyTex() {
    return *_emptyTex;
}

std::vector<ivec2> ContextManager::availableResolutions(bool fullScreen) {
    return _context->availableResolutions(fullScreen);
}
