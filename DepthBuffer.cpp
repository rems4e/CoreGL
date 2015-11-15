//
//  DepthBuffer.cpp
//  RPG 3D
//
//  Created by Rémi on 20/08/13.
//
//

#include "DepthBuffer.h"
#include "Shader.h"
#include "VertexManager.h"
#include <stdexcept>
#include <iostream>

namespace CoreGL {

DepthBuffer::DepthBuffer(ivec2 const &size, GLsizei depth)
        : RenderTarget(size), _depth(depth), _depthTexture(nullptr, size, _depth, 0, false, true) {
    GLint maxSize = 0;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxSize);

    if(std::max(size.x, size.y) > maxSize) {
        std::cerr << "FBO size too big (" << maxSize << ") !" << std::endl;
        throw std::out_of_range("FBO size invalid");
    }

    glGenFramebuffers(1, &_id);

    this->resize(size);
}

DepthBuffer::~DepthBuffer() {
    if(CoreGL::initialized()) {
        glDeleteFramebuffers(1, &_id);
    }
}

Texture DepthBuffer::clone() const {
    Texture newTex(nullptr, _depthTexture.size(), _depth, 0, false, true);
    VertexManager::flush();
    glBindFramebuffer(GL_FRAMEBUFFER, _id);

    glBindTexture(GL_TEXTURE_2D, newTex.tex());
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, _depthTexture.size().x, _depthTexture.size().y);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, RenderTarget::top().identifier());

    return newTex;
}

void DepthBuffer::resize(ivec2 const size) {
    this->RenderTarget::resize(size);

    _depthTexture = Texture(nullptr, size, _depth, 0, false, true);

    glBindFramebuffer(GL_FRAMEBUFFER, _id);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _depthTexture.tex(), 0);

    glDrawBuffer(GL_NONE); // No color buffer is drawn to.

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "FBO could not be created : " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << " !" << std::endl;
        throw std::runtime_error("Unable to create Framebuffer Object");
    }
}

}
