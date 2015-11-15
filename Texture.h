//
//  Texture.h
//  Projet2MIC
//
//  Created by Rémi on 17/08/12.
//  Copyright (c) 2012 Rémi Saurel. All rights reserved.
//

#ifndef EN_TETE_TEXTURE
#define EN_TETE_TEXTURE

#include "GL.h"
#include <string>
#include "Geometry.h"
#include <unordered_map>
#include <list>
#include <memory>

namespace CoreGL {
    class Texture final {
        friend bool operator==(Texture const &t1, Texture const &t2);
        friend bool operator!=(Texture const &t1, Texture const &t2);

    public:
        enum Sampling { StandardSampling, DepthSampling, NumSampling };

        // On créé un image à partir d'un tableau 2D de pixels, rangés un rang après l'autre, avec
        // 'profondeur' octet pour
        // chaque pixel.
        Texture(GLubyte const *pixels, ivec2 const &size, int depth, GLsizei samples, bool bgr, bool depthTexture = false);
        Texture(GLenum target, Sampling sampling = StandardSampling);

        // Les texels sont partagés entre l'ancienne et la nouvelle texture pour la copie et
        // l'affectation
        Texture(Texture const &img);

        ~Texture() = default;

        friend void swap(Texture &t1, Texture &t2) {
            using std::swap;
            swap(t1._base, t2._base);
        }

        // new deep copy of the texture
        Texture clone() const;

        ivec2 const &size() const;

        std::unique_ptr<GLubyte[]> pixels() const;

        // Fichier de l'image ou chaîne vide si l'image a été générée à partir d'une matrice de
        // pixels
        std::string const &file() const;

        GLuint tex() const;
        GLenum target() const;

        struct TextureBase;
        std::shared_ptr<TextureBase> const &textureBase() const {
            return _base;
        }

        GLuint sampler() const;

        static void setAnisotropy(GLfloat anisotropy);

    private:
        struct SharedTextureDeleter {
            void operator()(TextureBase *tex);
        };
        std::shared_ptr<TextureBase> _base = {nullptr, SharedTextureDeleter()};
    };
}

#endif
