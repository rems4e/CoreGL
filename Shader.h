//
//  Shader.h
//  Projet2MIC
//
//  Créé par Marc Promé et Rémi Saurel.
//  Ce fichier et son contenu sont librement distribuables, modifiables et utilisables pour toute
//  œuvre non commerciale,
//  à condition d'en citer les auteurs.
//

#ifndef Projet2MIC_Shader_h
#define Projet2MIC_Shader_h

#include <unordered_map>
#include <string>
#include "Geometry.h"
#include "ContextManager.h"
#include "GL.h"
#include <functional>
#include <list>

namespace CoreGL {

    class UniformBuffer;

    class Shader {
    public:
        using PreprocessorDefine = std::pair<std::string, std::string>;
        Shader(std::string const &vert,
               std::string const &frag,
               std::vector<PreprocessorDefine> const &preprocessorDefines = {});
        ~Shader();

        static Shader &orthoTex();

        static Shader &blur(float radius);

        void setUniform(char const *uniform, GLint v);

        void setUniform(char const *uniform, float v);
        void setUniform(char const *uniform, vec2 const &vec);
        void setUniform(char const *uniform, vec3 const &vec);
        void setUniform(char const *uniform, vec4 const &vec);

        void setUniform(char const *uniform, mat3 const &mat);
        void setUniform(char const *uniform, mat4 const &mat);

        void setTexture(char const *name, Texture const &tex);

        void pushBuffer(std::string const &uniformBlockName, std::shared_ptr<UniformBuffer> const &buffer);
        template <typename... Args>
        void emplaceBuffer(std::string const &uniformBlockName, Args... args) {
            auto buffer = std::make_shared<UniformBuffer>(args...);
            this->pushBuffer(uniformBlockName, buffer);
        }

        static void modelViewUpdate();
        static void projectionUpdate();

        void bind();
        static void unbind();

        static Shader &current();

        std::string name() const;


        struct Pimpl;

    private:
        std::unique_ptr<Pimpl> _pimpl;
    };
}

#endif
