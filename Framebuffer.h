//
//  Framebuffer.h
//  RPG 3D
//
//  Created by Rémi on 29/06/13.
//
//

#ifndef __RPG_3D__Framebuffer__
#define __RPG_3D__Framebuffer__

#include "GL.h"
#include "Geometry.h"
#include "Texture.h"
#include <vector>
#include <stdexcept>
#include "RenderTarget.h"

class Framebuffer : public RenderTarget {
public:
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

#endif /* defined(__RPG_3D__Framebuffer__) */
