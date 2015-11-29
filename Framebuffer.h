//
//  Framebuffer.h
//  CoreGL
//
//  Created by Rémi on 29/06/13.
//
//

#ifndef COREGL_FRAMEBUFFER_H
#define COREGL_FRAMEBUFFER_H

#include "GL.h"
#include "Geometry.h"
#include "Texture.h"
#include <vector>
#include <stdexcept>
#include "RenderTarget.h"

namespace CoreGL {
    /**
     * A class wrapping a texture that can be directly rendered to.
     */
    class Framebuffer : public RenderTarget {
    public:
        /*
         * @param size The size of the underlying texture.
         * @param samples The multisampling level of the texture. A standard texture has a sampling
         * level of 1.
         * @param stencil Whether the framebuffer is meant for stencilling or not/
         */
        Framebuffer(ivec2 const &size, GLsizei samples, bool stencil);
        ~Framebuffer();

        // Makes a new texture duplicating the data
        Texture clone(int colorBuffer) const;

        std::vector<Texture> const &colorBuffers() const {
            return _colorBuffers;
        }

        void resize(ivec2 const size) override {
            this->resize(size, _samples);
        }
        void resize(ivec2 const size, GLsizei samples);
        GLuint identifier() const override {
            return _id;
        }

    private:
        GLuint _id = 0;

        std::vector<Texture> _colorBuffers;
        GLuint _renderBuffer = 0;

        GLsizei _samples;
        bool _stencil;
    };
}
#endif /* defined(__RPG_3D__Framebuffer__) */
