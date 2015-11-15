//
//  Framebuffer.cpp
//  RPG 3D
//
//  Created by Rémi on 29/06/13.
//
//

#include "Framebuffer.h"
#include "Shader.h"
#include "VertexManager.h"
#include <stdexcept>
#include <iostream>

namespace CoreGL {

    Framebuffer::Framebuffer(ivec2 const &size, GLint samples, bool stencil)
            : RenderTarget(size)
            , _colorBuffers()
            , _samples(samples)
            , _stencil(stencil) {
        GLint maxSize = 0;
        glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxSize);

        if(std::max(size.x, size.y) > maxSize) {
            std::cerr << "FBO size too big (" << maxSize << ") !" << std::endl;
            throw std::out_of_range("FBO size invalid");
        }

        glGenRenderbuffers(1, &_renderBuffer);
        glGenFramebuffers(1, &_id);

        this->resize(size);
    }

    Framebuffer::~Framebuffer() {
        if(CoreGL::initialized()) {
            glDeleteFramebuffers(1, &_id);
            glDeleteRenderbuffers(1, &_renderBuffer);
        }
    }

    Texture Framebuffer::clone(int colorBuffer) const {
        Texture const &tex = this->colorBuffers()[colorBuffer];

        Texture newTex(nullptr, tex.size(), 0, 0, false);
        VertexManager::flush();
        glBindFramebuffer(GL_FRAMEBUFFER, _id);

        glBindTexture(GL_TEXTURE_2D, newTex.tex());
        glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, tex.size().x, tex.size().y);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, RenderTarget::top().identifier());

        return newTex;
    }

    void Framebuffer::resize(ivec2 const size, GLsizei samples) {
        this->RenderTarget::resize(size);
        _samples = samples;

        _colorBuffers.clear();
        _colorBuffers.emplace_back(nullptr, size, 4, samples, false);

        glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
        if(_samples > 1)
            glRenderbufferStorageMultisample(GL_RENDERBUFFER,
                                             _samples,
                                             _stencil ? GL_DEPTH24_STENCIL8 : GL_DEPTH_COMPONENT24,
                                             size.x,
                                             size.y);
        else
            glRenderbufferStorage(GL_RENDERBUFFER,
                                  _stencil ? GL_DEPTH24_STENCIL8 : GL_DEPTH_COMPONENT24,
                                  size.x,
                                  size.y);

        glBindFramebuffer(GL_FRAMEBUFFER, _id);
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               GL_COLOR_ATTACHMENT0,
                               _samples > 1 ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D,
                               _colorBuffers[0].tex(),
                               0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                  _stencil ? GL_DEPTH_STENCIL_ATTACHMENT : GL_DEPTH_ATTACHMENT,
                                  GL_RENDERBUFFER,
                                  _renderBuffer);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "FBO could not be created : " << glCheckFramebufferStatus(GL_FRAMEBUFFER)
                      << " !" << std::endl;
            throw std::runtime_error("Unable to create Framebuffer Object");
        }
    }
}
