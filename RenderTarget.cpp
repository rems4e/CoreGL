//
//  RenderTarget.cpp
//  RPG 3D
//
//  Created by Rémi on 17/07/13.
//
//

#include "RenderTarget.h"
#include "VertexManager.h"
#include "Shader.h"

namespace CoreGL {

    std::stack<RenderTarget *> RenderTarget::_renderTargets;

    RenderTarget::RenderTarget(ivec2 const &size)
            : _size(size) {
        _modelView.emplace(1.0f);
        _viewports.emplace(vec2(0, 0), vec2(_size.x, _size.y));
    }

    RenderTarget::~RenderTarget() {}

    RenderTarget &RenderTarget::top() {
        return *_renderTargets.top();
    }

    void RenderTarget::push(RenderTarget &f) {
        _renderTargets.push(&f);
        f.bind();
    }

    void RenderTarget::pop() {
        _renderTargets.pop();

        RenderTarget::top().bind();
    }

    void RenderTarget::bind() {
        VertexManager::flush();
        this->setViewport(this->viewport());

        glBindFramebuffer(GL_FRAMEBUFFER, this->identifier());
    }

    void RenderTarget::clear(GLbitfield mask) {
        glBindFramebuffer(GL_FRAMEBUFFER, this->identifier());
        glClear(mask & ~(RenderTarget::VIEWPORT_BIT) & ~(RenderTarget::MODELVIEW_BIT));
        glBindFramebuffer(GL_FRAMEBUFFER, RenderTarget::top().identifier());

        if((mask | RenderTarget::VIEWPORT_BIT) == mask) {
            while(_viewports.size() > 0)
                _viewports.pop();
            _viewports.emplace(vec2(0), vec2(_size));

            Rectangle const &nouveau = RenderTarget::viewport();
            this->setViewport(nouveau);
        }

        if((mask | RenderTarget::MODELVIEW_BIT) == mask) {
            while(_modelView.size() > 1) {
                _modelView.pop();
            }
        }
    }

    vec2 RenderTarget::scale() {
        ivec2 const &size = this->size();
        return vec2(size.x / 800.0f, size.y / 600.0f);
    }

    float RenderTarget::minScale() {
        vec2 scale = this->scale();
        return std::min(scale.x, scale.y);
    }

    Rectangle const &RenderTarget::viewport() {
        return _viewports.top();
    }

    void RenderTarget::setViewport(Rectangle const &rect) {
        glViewport(rect.left, this->size().y - rect.top - rect.height, rect.width, rect.height);
    }

    void RenderTarget::pushViewport(Rectangle const &r, bool intersection) {
        VertexManager::flush();

        if(intersection)
            _viewports.push(r.intersection(RenderTarget::viewport()));
        else
            _viewports.push(r);
        Rectangle const &nouveau = RenderTarget::viewport();
        this->setViewport(nouveau);
    }

    void RenderTarget::popViewport() {
        VertexManager::flush();

        _viewports.pop();
        Rectangle const &nouveau = RenderTarget::viewport();
        this->setViewport(nouveau);
    }

    void RenderTarget::pushTransformation(mat4 const &transfo) {
        _modelView.push(_modelView.top() * transfo);
        ShaderProgram::modelViewUpdate();
    }

    void RenderTarget::popTransformations(int nbSupr) {
        while(nbSupr--)
            _modelView.pop();
        ShaderProgram::modelViewUpdate();
    }

    mat4 const &RenderTarget::projection() {
        return _projection;
    }

    mat4 const &RenderTarget::modelView() {
        return _modelView.top();
    }

    void RenderTarget::setProjection(mat4 const &projection) {
        _projection = projection;

        ShaderProgram::projectionUpdate();
    }
}
