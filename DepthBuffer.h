//
//  DepthBuffer.h
//  CoreGL
//
//  Created by Rémi on 20/08/13.
//
//

#ifndef COREGL_DEPTH_BUFFER_H
#define COREGL_DEPTH_BUFFER_H

#include "GL.h"
#include "Geometry.h"
#include "Texture.h"
#include <vector>
#include <stdexcept>
#include "RenderTarget.h"


namespace CoreGL {
    /**
     * A RenderTarget wrapping a depth texture of the specified size and precision.
     * Pay attention to the available precision, typically 2, 3 or 4 bytes (16, 24 or 32 bits).
     */
    class DepthBuffer : public RenderTarget {
    public:
        /**
         * @param size The dimensions of the underlying texture.
         * @param precision The precision in bytes of the depth buffer, typically 2, 3 or 4. Maps to
         * the
         * depth texture's depth.
         */
        DepthBuffer(ivec2 const &size, GLsizei precision);
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
}

#endif /* defined(__RPG_3D__DepthBuffer__) */
