//
//  DepthBuffer.h
//  RPG 3D
//
//  Created by Rémi on 20/08/13.
//
//

#ifndef __RPG_3D__DepthBuffer__
#define __RPG_3D__DepthBuffer__

#include "GL.h"
#include "Geometry.h"
#include "Texture.h"
#include <vector>
#include <stdexcept>
#include "RenderTarget.h"

class DepthBuffer : public RenderTarget {
public:
    DepthBuffer(ivec2 const &size, GLsizei depth);
    ~DepthBuffer();

    // Makes a new texture duplicating the data
    Texture clone() const;
    Texture &get() {
        return _depthTexture;
    }

    void resize(ivec2 const size) override;
    GLuint identifier() const override {
        return _id;
    }

private:
    GLuint _id = 0;
    GLsizei _depth;
    Texture _depthTexture;
};

#endif /* defined(__RPG_3D__DepthBuffer__) */
