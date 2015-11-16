//
//  Texture.cpp
//  Projet2MIC
//
//  Created by Rémi on 17/08/12.
//  Copyright (c) 2012 Rémi Saurel. All rights reserved.
//

#include "Texture.h"
#include "CoreGL.h"
#include "Shader.h"
#include <iostream>

template <>
struct std::hash<std::pair<GLenum, CoreGL::Texture::Sampling>> {
    size_t operator()(std::pair<GLenum, CoreGL::Texture::Sampling> const &tex) const noexcept;
};

namespace CoreGL {

    struct Texture::TextureBase final {
        inline TextureBase(GLubyte const *pixels, ivec2 const &size, int depth, GLsizei samples, bool bgr, bool depthTexture) {
            this->load(pixels, size, depth, samples, bgr, depthTexture);
        }

        inline TextureBase(GLenum target, Sampling sampling)
                : _target(target)
                , _sampling(sampling)
                , _depth(4)
                , _size{} {
            glGenTextures(1, &_tex);
        }

        ~TextureBase();
        void load(GLubyte const *pixels, ivec2 const &size, int depth, GLsizei samples, bool bgr, bool depthTexture);

        std::unique_ptr<GLubyte[]> pixels() const;

        GLuint _tex = 0;
        GLenum _target = GL_TEXTURE_2D;
        Texture::Sampling _sampling;
        ivec2 _size;
        int _depth = 4;
        bool _depthTexture = false;

        static std::unordered_map<std::pair<GLenum, Texture::Sampling>, GLuint> _samplers;
        static GLfloat _anisotropy;

        static GLuint getSampler(GLenum target, Texture::Sampling sampling) {
            GLuint &sampler = _samplers[std::make_pair(target, sampling)];
            if(sampler == 0) {
                glGenSamplers(1, &sampler);
                switch(target) {
                    case GL_TEXTURE_2D: {
                        switch(sampling) {
                            case StandardSampling:
                                glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
                                glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
                                glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                                glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                                glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, _anisotropy);
                                break;
                            case DepthSampling:
                                glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                                glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                                glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                                glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                                glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
                                glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
                                break;
                            case SamplingModesCount:
                                break;
                        }
                        break;
                    }
                    case GL_TEXTURE_CUBE_MAP: {
                        switch(sampling) {
                            case StandardSampling:
                                glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                                glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                                glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                                glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                                glSamplerParameteri(sampler, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                                break;
                            case DepthSampling:
                                glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                                glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                                glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                                glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                                glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
                                glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
                                break;
                            case SamplingModesCount:
                                break;
                        }
                    }
                    case GL_TEXTURE_2D_ARRAY: {
                        switch(sampling) {
                            case DepthSampling:
                                glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                                glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                                glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                                glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                                glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
                                glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
                            case StandardSampling:
                            case SamplingModesCount:
                                break;
                        }
                    }
                }
            }

            return sampler;
        }
    };

    using TextureBase = Texture::TextureBase;
}

size_t std::hash<std::pair<GLenum, CoreGL::Texture::Sampling>>::
operator()(std::pair<GLenum, CoreGL::Texture::Sampling> const &tex) const noexcept {
    static std::hash<uint64_t> hash;
    return hash(tex.second + (tex.first << CoreGL::Texture::SamplingModesCount));
}

namespace CoreGL {

    std::unordered_map<std::pair<GLenum, Texture::Sampling>, GLuint> TextureBase::_samplers;

    GLfloat TextureBase::_anisotropy = 1.0f;

    TextureBase::~TextureBase() {
        if(CoreGL::initialized())
            glDeleteTextures(1, &_tex);
    }

    void TextureBase::load(GLubyte const *img, ivec2 const &size, int depth, GLsizei samples, bool bgr, bool depthTexture) {
        glGenTextures(1, &_tex);

        _size = size;

        if(samples > 1) {
            _target = GL_TEXTURE_2D_MULTISAMPLE;
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _tex);
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,
                                    samples,
                                    GL_RGBA8,
                                    static_cast<GLsizei>(size.x),
                                    static_cast<GLsizei>(size.y),
                                    GL_TRUE);
            _depth = 4;
        } else {
            _target = GL_TEXTURE_2D;
            glBindTexture(GL_TEXTURE_2D, _tex);

            if(depthTexture) {
                _depthTexture = true;
                _sampling = DepthSampling;

                _depth = depth;
                switch(depth) {
                    case 2:
                        depth = GL_DEPTH_COMPONENT16;
                        break;
                    case 3:
                        depth = GL_DEPTH_COMPONENT24;
                        break;
                    case 4:
                        depth = GL_DEPTH_COMPONENT32;
                        break;
                    default:
                        std::cerr << "Invalid depth for texture : " << depth << std::endl;
                        throw std::runtime_error("Invalid depth for texture!");
                }

                glTexImage2D(GL_TEXTURE_2D, 0, depth, size.x, size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            } else {
                _depth = 4;

                GLenum format = bgr ? GL_BGRA : GL_RGBA;

                if(depth == 3) {
                    if(bgr)
                        format = GL_BGR;
                    else
                        format = GL_RGB;
                } else if(depth == 1) {
                    format = GL_RED;
                }

                _sampling = StandardSampling;

                glTexImage2D(GL_TEXTURE_2D,
                             0,
                             GL_RGBA,
                             static_cast<GLsizei>(size.x),
                             static_cast<GLsizei>(size.y),
                             0,
                             format,
                             GL_UNSIGNED_BYTE,
                             img);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    std::unique_ptr<GLubyte[]> TextureBase::pixels() const {
        auto pix = std::make_unique<GLubyte[]>(_size.x * _size.y * 4);
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pix[0]);

        return pix;
    }

    Texture::Texture(GLubyte const *pixels, ivec2 const &size, int depth, GLsizei samples, bool bgr, bool depthTexture) {
        _base = std::make_unique<TextureBase>(pixels, size, depth, samples, bgr, depthTexture);
    }

    Texture::Texture(GLenum target, Sampling sampling) {
        _base = std::make_unique<TextureBase>(target, sampling);
    }

    Texture::Texture(Texture const &img) {
        _base = img._base;
    }

    void Texture::setAnisotropy(GLfloat anisotropy) {
        TextureBase::_anisotropy = anisotropy;
        glSamplerParameterf(TextureBase::getSampler(GL_TEXTURE_2D, StandardSampling),
                            GL_TEXTURE_MAX_ANISOTROPY_EXT,
                            anisotropy);
    }

    Texture Texture::clone() const {
        auto old = this->pixels();
        auto newBitmap = std::make_unique<GLubyte[]>(_base->_size.x * _base->_size.y * _base->_depth);
        for(int row = 0; row < _base->_size.y; ++row) {
            std::memcpy(&newBitmap[0] + row * _base->_size.x * _base->_depth,
                        &old[0] + (_base->_size.y - row - 1) * _base->_size.x * _base->_depth,
                        _base->_size.x * _base->_depth);
        }
        old.release();
        return Texture(newBitmap.get(), _base->_size, _base->_depth, 0, false, _base->_depthTexture);
    }

    GLuint Texture::sampler() const {
        return TextureBase::getSampler(_base->_target, _base->_sampling);
    }

    ivec2 const &Texture::size() const {
        return _base->_size;
    }

    std::unique_ptr<GLubyte[]> Texture::pixels() const {
        return _base->pixels();
    }

    GLuint Texture::tex() const {
        return _base->_tex;
    }

    GLenum Texture::target() const {
        return _base->_target;
    }

    bool operator==(Texture const &t1, Texture const &t2) {
        return t1._base->_tex == t2._base->_tex;
    }

    bool operator!=(Texture const &t1, Texture const &t2) {
        return !(t1 == t2);
    }
}
