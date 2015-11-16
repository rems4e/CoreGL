//
//  Shader.cpp
//  Projet2MIC
//
//  Créé par Marc Promé et Rémi Saurel.
//  Ce fichier et son contenu sont librement distribuables, modifiables et utilisables pour toute
//  œuvre non commerciale,
//  à condition d'en citer les auteurs.
//

#include "Shader.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "VertexManager.h"
#include "GLBuffer.h"
#include "RenderTarget.h"
#include <stdexcept>
#include "CoreGL.h"

using namespace std::string_literals;

namespace CoreGL {

    namespace ContextManager {
        void initDraw();
        void init(std::unique_ptr<GLContext> context);
    }

    namespace ShaderPrivate {
        void init();
        void frameConstantsUpdate();
    }

    struct ShaderProgram::Pimpl {
        friend void ShaderPrivate::init();
        friend void ShaderPrivate::frameConstantsUpdate();

    public:
        Pimpl(ShaderProgram &that);
        ~Pimpl();

        void init(std::string const &vert,
                  std::string const &frag,
                  std::vector<PreprocessorDefine> const &preprocessorDefines = {});

        static ShaderProgram &orthoTex();

        void setUniform(char const *uniform, GLint v);

        void setUniform(char const *uniform, float v);
        void setUniform(char const *uniform, vec2 const &vec);
        void setUniform(char const *uniform, vec3 const &vec);
        void setUniform(char const *uniform, vec4 const &vec);

        void setUniform(char const *uniform, mat3 const &mat);
        void setUniform(char const *uniform, mat4 const &mat);

        void setTexture(char const *name, Texture const &tex);

        void pushBuffer(std::string const &uniformBlockName, std::shared_ptr<UniformBuffer> const &buffer);

        static void modelViewUpdate();
        static void projectionUpdate();

        void bind();
        static void unbind();

        static ShaderProgram &current();

        std::string name() const;

    private:
        enum ShaderType { VertexShader, FragmentShader, ShaderTypesCount };
        static GLenum shaderTypesMatch(ShaderType val);

        struct Sampler {
            GLenum _type;
            std::string _name;
            GLint _textureUnit;

            std::weak_ptr<Texture::TextureBase> _boundTexture;
        };

        struct Shader {
            GLint _id;
            GLenum _type;
            std::string _file;
            std::vector<Sampler> _samplers;
        };
        struct ShaderDeleter {
            void operator()(Shader *);
        };

        static GLint compile(std::string const &source, GLenum type, std::string const &fichier);
        static void link(GLint prog, std::string const &fichier);

        static std::string loadShader(std::string const &chemin,
                                      GLenum type,
                                      std::vector<Sampler> &samplers,
                                      std::vector<PreprocessorDefine> const &preprocessorDefines);
        static std::string preprocess(std::string source,
                                      std::string const &shaderPath,
                                      std::vector<PreprocessorDefine> const &preprocessorDefines);
        static std::string resolveIncludes(std::string source, std::string shaderPath);
        static void getSamplers(std::string const &shaderSource,
                                GLenum shaderType,
                                std::string const &shaderPath,
                                std::vector<Sampler> &samplers);

        GLint uniformLocation(char const *param) const;
        GLint uniformBlockLocation(char const *uniformBlockName) const;
        static void init();

        static void frameConstantsUpdate();

        ShaderProgram &_that;
        GLint _id;
        std::shared_ptr<Shader> _shaders[ShaderTypesCount] = {{nullptr, ShaderDeleter()},
                                                              {nullptr, ShaderDeleter()}};
        std::vector<Sampler> _samplers;

        mutable std::unordered_map<std::string, GLint> _parametres;

        // std::pair<uniform block index, bufferBound, buffer>
        std::vector<std::tuple<GLuint, bool, std::shared_ptr<UniformBuffer>>> _buffers;

        // std::pair<buffer index, age of binding>
        static std::vector<std::pair<UniformBuffer *, float>> _uniformBlockBindings;

        static GLsizei _textureUnits;

        static std::shared_ptr<UniformBuffer> _frameConstantsBuffer;
        static std::unordered_map<std::string, std::weak_ptr<Shader>> _sharedShaders[ShaderTypesCount];
        static std::unique_ptr<ShaderProgram> _blur;
        static std::unique_ptr<ShaderProgram> _orthoTex;

        static ShaderProgram *_current;
    };

    void ShaderPrivate::init() {
        ShaderProgram::Pimpl::init();
    }

    void ShaderPrivate::frameConstantsUpdate() {
        ShaderProgram::Pimpl::frameConstantsUpdate();
    }

    ShaderProgram::ShaderProgram(std::string const &vert,
                                 std::string const &frag,
                                 std::vector<PreprocessorDefine> const &preprocessorDefines)
            : _pimpl(std::make_unique<ShaderProgram::Pimpl>(*this)) {
        _pimpl->init(vert, frag, preprocessorDefines);
    }

    ShaderProgram::~ShaderProgram() = default;

    ShaderProgram &ShaderProgram::orthoTex() {
        return Pimpl::orthoTex();
    }
    void ShaderProgram::setUniform(char const *uniform, GLint v) {
        return _pimpl->setUniform(uniform, v);
    }
    void ShaderProgram::setUniform(char const *uniform, float v) {
        return _pimpl->setUniform(uniform, v);
    }
    void ShaderProgram::setUniform(char const *uniform, vec2 const &vec) {
        return _pimpl->setUniform(uniform, vec);
    }
    void ShaderProgram::setUniform(char const *uniform, vec3 const &vec) {
        return _pimpl->setUniform(uniform, vec);
    }
    void ShaderProgram::setUniform(char const *uniform, vec4 const &vec) {
        return _pimpl->setUniform(uniform, vec);
    }
    void ShaderProgram::setUniform(char const *uniform, mat3 const &mat) {
        return _pimpl->setUniform(uniform, mat);
    }
    void ShaderProgram::setUniform(char const *uniform, mat4 const &mat) {
        return _pimpl->setUniform(uniform, mat);
    }
    void ShaderProgram::setTexture(char const *name, Texture const &tex) {
        return _pimpl->setTexture(name, tex);
    }
    void ShaderProgram::pushBuffer(std::string const &uniformBlockName,
                                   std::shared_ptr<UniformBuffer> const &buffer) {
        return _pimpl->pushBuffer(uniformBlockName, buffer);
    }
    void ShaderProgram::modelViewUpdate() {
        return Pimpl::modelViewUpdate();
    }
    void ShaderProgram::projectionUpdate() {
        return Pimpl::projectionUpdate();
    }
    void ShaderProgram::bind() {
        return _pimpl->bind();
    }
    void ShaderProgram::unbind() {
        return Pimpl::unbind();
    }
    ShaderProgram &ShaderProgram::current() {
        return Pimpl::current();
    }
    std::string ShaderProgram::name() const {
        return _pimpl->name();
    }


    std::vector<std::pair<UniformBuffer *, float>> ShaderProgram::Pimpl::_uniformBlockBindings;
    std::shared_ptr<UniformBuffer> ShaderProgram::Pimpl::_frameConstantsBuffer = nullptr;

    std::unordered_map<std::string, std::weak_ptr<ShaderProgram::Pimpl::Shader>>
    ShaderProgram::Pimpl::_sharedShaders[ShaderProgram::Pimpl::ShaderTypesCount];

    GLsizei ShaderProgram::Pimpl::_textureUnits = 0;

    std::unique_ptr<ShaderProgram> ShaderProgram::Pimpl::_blur = nullptr;
    std::unique_ptr<ShaderProgram> ShaderProgram::Pimpl::_orthoTex = nullptr;
    ShaderProgram *ShaderProgram::Pimpl::_current = nullptr;

    GLenum ShaderProgram::Pimpl::shaderTypesMatch(ShaderType val) {
        switch(val) {
            case VertexShader:
                return GL_VERTEX_SHADER;
            case FragmentShader:
                return GL_FRAGMENT_SHADER;
            case ShaderTypesCount:
                return 0;
        }

        return 0;
    }

    ShaderProgram::Pimpl::Pimpl(ShaderProgram &that)
            : _that(that) {}

    void ShaderProgram::Pimpl::init(std::string const &vert,
                                    std::string const &frag,
                                    std::vector<PreprocessorDefine> const &preprocessorDefines) {
        std::string prepDefines(" ");
        for(auto const &def : preprocessorDefines) {
            prepDefines += def.first + " " + def.second;
        }

        std::string const *shaderPath[ShaderTypesCount] = {nullptr};
        shaderPath[VertexShader] = &vert;
        shaderPath[FragmentShader] = &frag;

        for(int shaderType = 0; shaderType < ShaderTypesCount; ++shaderType) {
            if(shaderPath[shaderType] && !shaderPath[shaderType]->empty()) {
                _shaders[shaderType] =
                _sharedShaders[shaderType][*shaderPath[shaderType] + prepDefines].lock();

                if(!_shaders[shaderType]) {
                    _shaders[shaderType] = std::make_unique<Shader>();

                    _sharedShaders[shaderType][vert + prepDefines] = _shaders[shaderType];

                    _shaders[shaderType]->_type =
                    ShaderProgram::Pimpl::shaderTypesMatch(static_cast<ShaderType>(shaderType));
                    _shaders[shaderType]->_file = *shaderPath[shaderType];
                    std::string source = ShaderProgram::Pimpl::loadShader(*shaderPath[shaderType],
                                                                          _shaders[shaderType]->_type,
                                                                          _shaders[shaderType]->_samplers,
                                                                          preprocessorDefines);

                    _shaders[shaderType]->_id =
                    ShaderProgram::Pimpl::compile(source, _shaders[shaderType]->_type, *shaderPath[shaderType]);
                }
            }
        }

        // Concatenation of all shader stages' texture samplers
        for(int i = 0; i < ShaderTypesCount; ++i) {
            if(_shaders[i])
                _samplers.insert(_samplers.end(), _shaders[i]->_samplers.begin(), _shaders[i]->_samplers.end());
        }

        // Removing duplicates accros different shader stages.
        std::sort(_samplers.begin(),
                  _samplers.end(),
                  [](Sampler const &s1, Sampler const &s2) { return s1._name < s2._name; });
        _samplers.erase(std::unique(_samplers.begin(),
                                    _samplers.end(),
                                    [](Sampler const &s1, Sampler const &s2) {
                                        return s1._name == s2._name;
                                    }),
                        _samplers.end());

        _id = glCreateProgram();

        if(_samplers.size() > _textureUnits) {
            std::cerr << "Too much texture units used at the same time in shader {" << vert << ", " << frag
                      << "} (" << _samplers.size() << ", max is " << _textureUnits << ")." << std::endl;
            throw std::runtime_error("Shader uses too mush texture units at a time");
        }

        for(int i = 0; i < ShaderTypesCount; ++i) {
            if(_shaders[i])
                glAttachShader(_id, _shaders[i]->_id);
        }

        try {
            ShaderProgram::Pimpl::link(_id, frag);
        } catch(std::runtime_error &e) {
            std::cerr << "Shader linking error : " + vert + " " + frag << std::endl;
            throw;
        }

        this->pushBuffer("FrameConstants", _frameConstantsBuffer);
        if(std::get<0>(_buffers.front()) != GL_INVALID_INDEX) {
            glUniformBlockBinding(_id, std::get<0>(_buffers.front()), 0);

            glBindBufferBase(GL_UNIFORM_BUFFER, 0, _frameConstantsBuffer->identifier());
        }

        GLint textureUnit = 0;
        for(Sampler &s : _samplers) {
            s._textureUnit = textureUnit++;
            this->setUniform(s._name.c_str(), s._textureUnit);
        }
    }

    ShaderProgram::Pimpl::~Pimpl() {
        // No need to release OpenGL data if the context is already gone
        if(CoreGL::initialized()) {
            if(_current == &_that) {
                ShaderProgram::Pimpl::unbind();
            }

            for(int i = 0; i < ShaderTypesCount; ++i) {
                if(_shaders[i])
                    glDetachShader(_id, _shaders[i]->_id);
            }
            glDeleteProgram(_id);
        }
    }

    void ShaderProgram::Pimpl::ShaderDeleter::operator()(ShaderProgram::Pimpl::Shader *prog) {
        if(prog) {
            for(int i = 0; i < ShaderTypesCount; ++i) {
                if(ShaderProgram::Pimpl::shaderTypesMatch(static_cast<ShaderType>(i)) == prog->_type) {
                    ShaderProgram::Pimpl::_sharedShaders[i].erase(prog->_file);
                    break;
                }
            }
            glDeleteShader(prog->_id);

            delete prog;
        }
    }

    void ShaderProgram::Pimpl::init() {
        GLint val;
        glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &val);
        _uniformBlockBindings.resize(val);

        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &val);
        _textureUnits = val;

        _frameConstantsBuffer = std::make_unique<UniformBuffer>(sizeof(glm::vec2) + 3 * sizeof(float), nullptr);
        _uniformBlockBindings[0] = std::make_pair(_frameConstantsBuffer.get(), 0);
    }

    std::string ShaderProgram::Pimpl::name() const {
        std::string retour;
        for(int i = 0; i < ShaderTypesCount; ++i) {
            retour += ", ";
            if(_shaders[i])
                retour += _shaders[i]->_file;
            else
                retour += "<no shader>";
        }

        return "{"s + retour.substr(2) + "}";
    }

    ShaderProgram &ShaderProgram::Pimpl::orthoTex() {
        if(!_orthoTex) {
            _orthoTex =
            std::make_unique<ShaderProgram>(CoreGL::resourcesPath() + "shaders/2D.vert",
                                            CoreGL::resourcesPath() + "shaders/2D.frag");
        }

        return *_orthoTex;
    }

    void ShaderProgram::Pimpl::setUniform(char const *param, GLint v) {
        GLint loc = this->uniformLocation(param);
        if(loc == -1)
            return;

        if(_current != &_that) {
            this->bind();
        } else
            VertexManager::flush();

        glUniform1i(loc, v);
    }

    void ShaderProgram::Pimpl::setUniform(char const *param, float v) {
        GLint loc = this->uniformLocation(param);
        if(loc == -1)
            return;

        if(_current != &_that) {
            this->bind();
        } else
            VertexManager::flush();

        glUniform1f(loc, v);
    }

    void ShaderProgram::Pimpl::setUniform(char const *param, vec2 const &vec) {
        GLint loc = this->uniformLocation(param);
        if(loc == -1)
            return;

        if(_current != &_that) {
            this->bind();
        } else
            VertexManager::flush();

        glUniform2fv(loc, 1, &vec[0]);
    }

    void ShaderProgram::Pimpl::setUniform(char const *param, vec3 const &vec) {
        GLint loc = this->uniformLocation(param);
        if(loc == -1)
            return;

        if(_current != &_that) {
            this->bind();
        } else
            VertexManager::flush();

        glUniform3fv(loc, 1, &vec[0]);
    }

    void ShaderProgram::Pimpl::setUniform(char const *param, vec4 const &vec) {
        GLint loc = this->uniformLocation(param);
        if(loc == -1)
            return;

        if(_current != &_that) {
            this->bind();
        } else
            VertexManager::flush();

        glUniform4fv(loc, 1, &vec[0]);
    }

    void ShaderProgram::Pimpl::setUniform(char const *param, mat3 const &mat) {
        GLint loc = this->uniformLocation(param);
        if(loc == -1)
            return;

        if(_current != &_that) {
            this->bind();
        } else
            VertexManager::flush();

        glUniformMatrix3fv(loc, 1, GL_FALSE, &mat[0][0]);
    }

    void ShaderProgram::Pimpl::setUniform(char const *param, mat4 const &mat) {
        GLint loc = this->uniformLocation(param);
        if(loc == -1)
            return;

        if(_current != &_that) {
            this->bind();
        } else
            VertexManager::flush();

        glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
    }

    GLint ShaderProgram::Pimpl::uniformLocation(char const *param) const {
        GLint loc = -1;
        auto i = _parametres.find(param);
        if(i == _parametres.end()) {
            _parametres[param] = loc = glGetUniformLocation(_id, param);
        } else
            loc = i->second;

        return loc;
    }

    void ShaderProgram::Pimpl::setTexture(char const *name, Texture const &tex) {
        auto it = std::find_if(_samplers.begin(),
                               _samplers.end(),
                               [name](Sampler const &s) { return s._name == name; });
        if(it != _samplers.end()) {
            if(it->_boundTexture.expired() || it->_boundTexture.lock() != tex.textureBase()) {
                VertexManager::flush();
                it->_boundTexture = tex.textureBase();
            }

            glActiveTexture(GL_TEXTURE0 + it->_textureUnit);
            glBindTexture(tex.target(), tex.tex());
            glBindSampler(it->_textureUnit, tex.sampler());
            // FIXME: Remove after support of Sampler Objects
            // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,
            // Parametres::anisotropy());
        } else {
            std::cerr << "Invalid sampler name " << name << " in shader " << this->name() << std::endl;
            std::cerr << "{\n";
            for(auto &s : _samplers) {
                std::cerr << '\t' << s._name << '\n';
            }
            std::cerr << '}' << std::endl;
        }
    }

    void ShaderProgram::Pimpl::pushBuffer(std::string const &uniformBlockName,
                                          std::shared_ptr<UniformBuffer> const &buffer) {
        buffer->bind();
        GLuint index = glGetUniformBlockIndex(_id, uniformBlockName.c_str());
        _buffers.push_back(std::make_tuple(index, false, buffer));
    }

    void ShaderProgram::Pimpl::modelViewUpdate() {
        ShaderProgram &s = ShaderProgram::Pimpl::current();
        s.setUniform("_modelToCamera", RenderTarget::top().modelView());
        s.setUniform("_3x3ModelToCamera", mat3(RenderTarget::top().modelView()));
    }

    void ShaderProgram::Pimpl::projectionUpdate() {
        ShaderProgram &s = ShaderProgram::Pimpl::current();
        s.setUniform("_cameraToClip", RenderTarget::top().projection());
    }

    void ShaderProgram::Pimpl::frameConstantsUpdate() {
        _frameConstantsBuffer->setData(vec2(ContextManager::size()), 0, sizeof(glm::vec2));
        _frameConstantsBuffer->setData(CoreGL::timeSinceInit().toS(), sizeof(glm::vec2), sizeof(float));
        _frameConstantsBuffer->update();
    }

    void ShaderProgram::Pimpl::bind() {
        if(_current != &_that) {
            VertexManager::flush();
            _current = &_that;

            glUseProgram(_id);
            ShaderProgram::Pimpl::modelViewUpdate();
            ShaderProgram::Pimpl::projectionUpdate();

            for(auto i = _buffers.begin() + 1; i != _buffers.end(); ++i) {
                std::get<2>(*i)->update();

                if(std::get<2>(*i)->bindingPoint() == -1) {
                    // Look for the oldest binding
                    auto it = std::min_element(_uniformBlockBindings.begin() + 1,
                                               _uniformBlockBindings.end(),
                                               [](decltype(_uniformBlockBindings)::value_type const &p1,
                                                  decltype(_uniformBlockBindings)::value_type const &p2) {
                                                   return p1.second < p2.second;
                                               });
                    it->first = std::get<2>(*i).get();
                    it->second = CoreGL::timeSinceInit().toS();
                    std::get<2>(*i)->setBindingPoint(
                    static_cast<GLuint>(std::distance(_uniformBlockBindings.begin(), it)));
                } else {
                    _uniformBlockBindings[std::get<2>(*i)->bindingPoint()].second =
                    CoreGL::timeSinceInit().toS();
                }

                if(std::get<0>(*i) != GL_INVALID_INDEX && !std::get<1>(*i)) {
                    glUniformBlockBinding(_id, std::get<0>(*i), std::get<2>(*i)->bindingPoint());
                    glBindBufferBase(GL_UNIFORM_BUFFER,
                                     std::get<2>(*i)->bindingPoint(),
                                     std::get<2>(*i)->identifier());
                    std::get<1>(*i) = true;
                }
            }
        }
    }

    void ShaderProgram::Pimpl::unbind() {
        ShaderProgram::Pimpl::orthoTex().bind();
    }

    ShaderProgram &ShaderProgram::Pimpl::current() {
        return *_current;
    }

    std::string ShaderProgram::Pimpl::loadShader(std::string const &chemin,
                                                 GLenum type,
                                                 std::vector<Sampler> &samplers,
                                                 std::vector<PreprocessorDefine> const &preprocessorDefines) {
        std::ifstream fShad(chemin.c_str(), std::ios::in);
        if(!fShad) {
            std::cerr << "Shader doesn't exist : " << chemin << std::endl;
            throw std::runtime_error("Shader doesn't exist");
        }

        fShad.seekg(0, std::ios::end);
        int dimShad = static_cast<int>(fShad.tellg());
        std::string shadSource(dimShad, ';');
        fShad.seekg(0, std::ios::beg);
        fShad.read(&shadSource[0], dimShad);
        fShad.close();

        shadSource = ShaderProgram::Pimpl::preprocess(shadSource, chemin, preprocessorDefines);

        ShaderProgram::Pimpl::getSamplers(shadSource, type, chemin, samplers);

        return shadSource;
    }

    std::string ShaderProgram::Pimpl::preprocess(std::string shadSource,
                                                 std::string const &shaderPath,
                                                 std::vector<PreprocessorDefine> const &preprocessorDefines) {
        auto it = shadSource.find('\n');
        if(it == std::string::npos) {
            std::cerr << "Bad shader : " << shaderPath << std::endl;
            throw std::runtime_error("Bad shader content");
        }

        std::string defines;
        for(auto const &def : preprocessorDefines) {
            defines += "\n\n#define " + def.first + ' ' + def.second + '\n';
        }

        shadSource.insert(it, defines);

        shadSource = ShaderProgram::Pimpl::resolveIncludes(shadSource, shaderPath);

        return shadSource;
    }

    std::string ShaderProgram::Pimpl::resolveIncludes(std::string shadSource, std::string shaderPath) {
        auto separatorIndex = shaderPath.find_last_of("/");
        size_t correctedIndex = separatorIndex == std::string::npos ? -1 : separatorIndex;

        auto const parentDirectory = shaderPath.substr(0, correctedIndex + 1);
        shaderPath = shaderPath.substr(correctedIndex + 1);

        std::string::iterator it = shadSource.begin();
        char const *include = "#include";
        while((it = std::search(it, shadSource.end(), include, include + 8)) != shadSource.end()) {
            if(std::distance(shadSource.begin(), it) > 0 && *(it - 1) != '\n') {
                ++it;
                continue;
            }
            std::size_t itSauve = it - shadSource.begin();
            it += 8;
            while(it < shadSource.end() && std::isspace(*it)) {
                ++it;
            }
            if(it < shadSource.end() - 2) {
                if(*it != '"') {
                    std::cerr << "Shader preprocessing error (" << parentDirectory + shaderPath
                              << ") : Invalid Include path" << std::endl;
                    throw std::runtime_error("Shader syntax error");
                }
                ++it;
                auto it2 = it;
                while(it2 + 1 < shadSource.end()) {
                    ++it2;
                    if(*it2 == '"')
                        break;
                }

                std::string const currentPath = parentDirectory + std::string{it, it2};

                std::ifstream fInclude(currentPath, std::ios::in);
                if(!fInclude) {
                    std::cerr << "Shader preprocessing error (" << shaderPath
                              << ") : Included file doesn't exist : " << currentPath << std::endl;
                    throw std::runtime_error("Include path doesn't exist");
                }

                fInclude.seekg(0, std::ios::end);
                int dimInclude = static_cast<int>(fInclude.tellg());
                std::string includeSource(dimInclude, ' ');
                fInclude.seekg(0, std::ios::beg);
                fInclude.read(&includeSource[0], dimInclude);
                fInclude.close();

                shadSource.replace(shadSource.begin() + itSauve, it2 + 1, includeSource);
                it = shadSource.begin();
            } else {
                std::cerr << "Shader preprocessing error (" << shaderPath << ") : "
                          << "Invalid Include path" << std::endl;
                throw std::runtime_error("Shader syntax error");
            }
        }

        return shadSource;
    }

    void ShaderProgram::Pimpl::getSamplers(std::string const &shaderSource,
                                           GLenum shaderType,
                                           std::string const &shaderPath,
                                           std::vector<Sampler> &samplers) {
        if(shaderType == GL_FRAGMENT_SHADER) {
            auto it = shaderSource.begin();
            std::string pattern = "\nuniform sampler";
            while((it = std::search(it, shaderSource.end(), pattern.begin(), pattern.end())) !=
                  shaderSource.end()) {
                Sampler sampler;
                auto lastIt = it += std::string("\nuniform ").size();
                while(!std::isspace(*++it))
                    ;
                std::string samplerType(lastIt, it);
                if(samplerType == "sampler1D" || samplerType == "sampler1DShadow")
                    sampler._type = GL_TEXTURE_1D;
                else if(samplerType == "sampler1DArray" || samplerType == "sampler1DArrayShadow")
                    sampler._type = GL_TEXTURE_1D_ARRAY;
                else if(samplerType == "sampler2D" || samplerType == "sampler2DShadow")
                    sampler._type = GL_TEXTURE_2D;
                else if(samplerType == "sampler2DArray" || samplerType == "sampler2DArrayShadow")
                    sampler._type = GL_TEXTURE_2D_ARRAY;
                else if(samplerType == "sampler2DMS")
                    sampler._type = GL_TEXTURE_2D_MULTISAMPLE;
                else if(samplerType == "sampler2DMSArray")
                    sampler._type = GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
                else if(samplerType == "sampler3D")
                    sampler._type = GL_TEXTURE_3D;
                else if(samplerType == "samplerCube" || samplerType == "samplerCubeShadow")
                    sampler._type = GL_TEXTURE_CUBE_MAP;
                else if(samplerType == "sampler2DRect" || samplerType == "sampler2DRectShadow")
                    sampler._type = GL_TEXTURE_RECTANGLE;
                else {
                    std::cerr << "Shader preprocessing error (" << shaderPath << ") : "
                              << "Unhandled or invalid sampler type " << samplerType << "." << std::endl;
                    throw std::runtime_error("Shader syntax error");
                }

                while(std::isspace(*++it))
                    ;
                lastIt = it;

                while(*(it++) != ';')
                    ;
                while(isspace(*--it))
                    ;

                std::string textureName(lastIt, it);
                sampler._name = textureName;

                samplers.push_back(sampler);
            }
        }
    }

    GLint ShaderProgram::Pimpl::compile(std::string const &source, GLenum type, std::string const &fichier) {
        GLint shader = glCreateShader(type);

        const char *src = &source[0];
        glShaderSource(shader, 1, &src, nullptr);

        glCompileShader(shader);

        GLint etat = 0;

        GLint tailleLog = 0;
        std::unique_ptr<GLchar[]> log;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleLog);

        std::string str;
        if(tailleLog) {
            log = std::make_unique<GLchar[]>(tailleLog);
            glGetShaderInfoLog(shader, tailleLog, &tailleLog, log.get());
            log[tailleLog - 1] = '\0';

            str = log.get();
        }

#ifdef DEVELOPPEMENT
        if(tailleLog > 0)
            std::cerr << "Shader compilation log (" << fichier << ") : " << str << std::endl;
#endif

        glGetShaderiv(shader, GL_COMPILE_STATUS, &etat);
        if(etat != GL_TRUE) {
            std::cerr << "Shader compilation error." << std::endl;
#ifdef DEVELOPPEMENT

            std::cerr << "Preprocessed shader source : \n";
            auto const vec = source.split('\n');
            for(auto const &line : vec) {
                std::cerr << (&line - &vec[0] + 1) << "|\t" << line << '\n';
            }
            std::cerr << std::endl;
#endif
            throw std::runtime_error("Shader compilation error");
        }

        return shader;
    }

    void ShaderProgram::Pimpl::link(GLint prog, std::string const &fichier) {
        glLinkProgram(prog);

        GLint etat = 0;

        GLint tailleLog = 0;
        std::unique_ptr<GLchar[]> log;

        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &tailleLog);

        std::string str;
        if(tailleLog) {
            log = std::make_unique<GLchar[]>(tailleLog);

            glGetProgramInfoLog(prog, tailleLog, &tailleLog, log.get());
            log[tailleLog - 1] = '\0';

            str = log.get();
        }

#ifdef DEVELOPPEMENT
        if(tailleLog > 0)
            std::cerr << "Shader linking log (" << fichier << ") : " << str << std::endl;
#endif

        glGetProgramiv(prog, GL_LINK_STATUS, &etat);
        if(etat != GL_TRUE) {
            std::cerr << "Shader linking error." << std::endl;
            throw std::runtime_error("Shader linking error");
        }
    }
}
