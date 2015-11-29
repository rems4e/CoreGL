//
//  Texture.h
//  CoreGL
//
//  Created by Rémi on 17/08/12.
//

#ifndef COREGL_TEXTURE_H
#define COREGL_TEXTURE_H

#include "GL.h"
#include <string>
#include "Geometry.h"
#include <unordered_map>
#include <list>
#include <memory>

namespace CoreGL {
    /**
     * A texture class, that can be used to contain numeric data, picture elements, depth samples…
     */
    class Texture final {
        friend bool operator==(Texture const &t1, Texture const &t2);
        friend bool operator!=(Texture const &t1, Texture const &t2);

    public:
        /**
         * The sampling mode used to fetch the texels.
         * Standard sampling is using a trilinear filtering method, for GL_TEXTURE_2D and
         * GL_TEXTURE_CUBE_MAP, and linear sampling for GL_TEXTURE_2D_ARRAY.
         * Depth sampling always uses the nearest texel.
         */
        enum Sampling { StandardSampling, DepthSampling, SamplingModesCount };

        /**
         * Creates a GL_TEXTURE_2D with the specified image data, multisampling level and color
         * components layout.
         * @param pixels The image data, in a planar array of size.x × size.y × depth bytes. May not
         * be null.
         * @param size The {width, height} size of the desired texture.
         * @param depth The count of bytes per pixel. Possible values are 1, 3 or 4 (greyscale, RGB
         * or RGBA) for color textures, or 1, 2 or 3 (8, 16 or 24 bits) for depth textures.
         * @param samples The level of multisampling. A value of 1 means no multisampling (standard
         * texture), and > 1 means a multisampled texture.
         * @param bgr If true, the pixel layout is BGR or BGRA depending on the depth. If false, the
         * pixel layout is RGB or RGBA.
         * @param depthTexture Whether the texture is mean for depth samples or not.
         */
        Texture(GLubyte const *pixels, ivec2 const &size, int depth, GLsizei samples, bool bgr, bool depthTexture = false);

        /*
         * Creates a texture mapped to the given target and sampling mode.
         */
        Texture(GLenum target, Sampling sampling = StandardSampling);

        /**
         * Texels are shared, as the underlying GL texture of the copy will be the same as the
         * original.
         */
        Texture(Texture const &img);

        ~Texture() = default;

        friend void swap(Texture &t1, Texture &t2) {
            using std::swap;
            swap(t1._base, t2._base);
        }

        /**
         * Creates a deep copy of the texture, effectively creating a new one with the same
         * parameters and copying the texels.
         */
        Texture clone() const;

        /**
         * The size in pixels of the texture. Only relevent for 2D textures, and textures created
         * with the constructor overload that takes pixel data as initializer. When a texture is
         * resized externally, this value is not updated.
         */
        ivec2 const &size() const;

        /**
         * Returns a copy of the pixel data of the picture. The pixel layout is RGBA, 4 bytes per
         * pixel.
         */
        std::unique_ptr<GLubyte[]> pixels() const;

        /**
         * The OpenGL identifier of the texture.
         */
        GLuint tex() const;

        /**
         * The OpenGL target of the texture.
         */
        GLenum target() const;

        struct TextureBase;
        std::shared_ptr<TextureBase> const &textureBase() const {
            return _base;
        }

        /**
         * The OpenGL sampler identifier of the texture.
         */
        GLuint sampler() const;

        /**
         * Changes the anisotropic filtering level of the textures.
         */
        static void setAnisotropy(GLfloat anisotropy);

    private:
        std::shared_ptr<TextureBase> _base;
    };
}

#endif
