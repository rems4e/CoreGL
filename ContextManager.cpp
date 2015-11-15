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
#include "Screen.h"
#include <map>

using namespace Units::UnitsLiterals;

namespace CoreGL {

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

        std::uint64_t _lastObserverId = 1;
        std::map<std::uint64_t, ResolutionObserverRAII *> _resolutionObservers;

        void init(std::unique_ptr<GLContext> context);

        void clean();
    }

    ResolutionObserverRAII::ResolutionObserverRAII(std::function<void()> f)
            : _observerFun(std::move(f))
            , _id(ContextManager::_lastObserverId++) {
        ContextManager::_resolutionObservers[_id] = this;
    }

    ResolutionObserverRAII::~ResolutionObserverRAII() {
        if(_id != 0) {
            ContextManager::_resolutionObservers.erase(_id);
        }
    }

    ResolutionObserverRAII::ResolutionObserverRAII(ResolutionObserverRAII &&observer) {
        *this = std::move(observer);
    }

    ResolutionObserverRAII &ResolutionObserverRAII::operator=(ResolutionObserverRAII &&observer) {
        _id = observer._id;
        observer._id = 0;

        _observerFun = std::move(_observerFun);
        observer._observerFun = nullptr;

        return *this;
    }

    void ResolutionObserverRAII::notify() {
        if(_observerFun) {
            _observerFun();
        }
    }

    void ContextManager::init(std::unique_ptr<GLContext> context) {
        if(CoreGL::initialized())
            return;

        try {
            context->init();
        } catch(std::exception const &e) {
            std::cerr << "Unable to init GL context!\n" << e.what() << std::endl;
            throw;
        }

        _context = std::move(context);

        myGlewInit();

        _screen = std::make_unique<Screen>();
        _renderTarget = std::make_unique<Framebuffer>(_context->size(), 0, false);
        RenderTarget::push(*_screen);
        RenderTarget::push(*_renderTarget);

        ShaderPrivate::init();
        VertexManager::init();

        _context->updateResolution();

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

        ShaderProgram::orthoTex().bind();

        {
            std::array<GLubyte, 4> const data = {0, 0, 0, 255};
            _emptyTex = std::make_unique<Texture>(data.data(), vec2{1, 1}, 4, 1, false);
        }

        ShaderPrivate::frameConstantsUpdate();

        resetPointer();
        setPointerVisibility(false);
        _context->showWindow();
    }

    void ContextManager::clean() {
        _context = nullptr;
    }

    void ContextManager::updateResolution() {
        _context->updateResolution();

        _frequence = {};

        _screen->resize(_context->size());
        _renderTarget->resize(_context->size());

        for(auto obs : _resolutionObservers) {
            obs.second->notify();
        }
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
        ShaderProgram::orthoTex().bind();

        VertexManager::pushTex(renderTarget, vec2{}, true);
        VertexManager::flush();
        _renderTarget->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
                             RenderTarget::MODELVIEW_BIT | RenderTarget::VIEWPORT_BIT);

        if(_cursorVisible) {
            VertexManager::pushTex(*_cursor, CoreGL::eventManager().mousePosition() - _distanceToCross);
        }

        VertexManager::flush();

        _context->swapBuffers();

        _screen->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | RenderTarget::MODELVIEW_BIT |
                       RenderTarget::VIEWPORT_BIT);

        ShaderPrivate::frameConstantsUpdate();

        RenderTarget::push(*_renderTarget);
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

    bool ContextManager::pointerVisible() {
        return _cursorVisible;
    }

    void ContextManager::setPointerVisibility(bool af) {
        _cursorVisible = af;
    }

    Texture const &ContextManager::pointer() {
        return *_cursor;
    }

    void ContextManager::setPointer(Texture const &tex, ivec2 const &distanceToCross) {
        _cursor = std::make_unique<Texture>(tex);
        _distanceToCross = distanceToCross;
    }

    void ContextManager::resetPointer() {
        _cursor = std::make_unique<Texture>(*_emptyTex);
        _distanceToCross = {};
    }

    Texture const &ContextManager::emptyTex() {
        return *_emptyTex;
    }

    std::vector<ivec2> ContextManager::availableResolutions(bool fullScreen) {
        return _context->availableResolutions(fullScreen);
    }
}