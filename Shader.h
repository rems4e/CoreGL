//
//  Shader.h
//  CoreGL
//
//  Created by Rémi Saurel on 11/04/12.
//  Additional contributor (2012): Marc Promé
//

#ifndef COREGL_SHADER_H
#define COREGL_SHADER_H

#include <unordered_map>
#include <string>
#include "Geometry.h"
#include "ContextManager.h"
#include "GL.h"
#include <functional>
#include <list>

namespace CoreGL {

    class UniformBuffer;

    /**
     * A class simplifying the use of GLSL shaders and programs.
     * #include instructions are emulated in the compiled shaders, the path of the #included files
     * is resolved relatively to each source code file's location.
     */
    class ShaderProgram {
    public:
        /**
         * A key-value pair representing the preprocessor instruction #define pair.first
         * pair.second.
         * Passing around one ore more of those in a ShaderProgram constructor allows for easy
         * runtime customization of the actual shader being compiled.
         */
        using PreprocessorDefine = std::pair<std::string, std::string>;

        /**
         * Creates an OpenGL shader program composed of a vertex shader stage and a fragment shader
         * stage. The preprocessor defines are inserted in the shaders source code before invoking
         * the GLSL compiler.
         * @param vert The path to the vertex shader source code.
         * @param frag The path to the fragment shader source code.
         * @param preprocessorDefines The preprocessor defines that will be added to both shader
         * stages' source codes before compilation.
         */
        ShaderProgram(std::string const &vert,
                      std::string const &frag,
                      std::vector<PreprocessorDefine> const &preprocessorDefines = {});
        ~ShaderProgram();

        /**
         * A basic shader consisting of a vertex shader performing no projection of the passed
         * vertices, and a fragment shader only fetching the texels of the active texture without
         * computations.
         * It is used among others for simple billboards drawing.
         */
        static ShaderProgram &orthoTex();

        /**
         * Update a uniform value. The uniform's name is given by the first parameter, the value by
         * the second one.
         * For better performance, cache the uniform's name pointer value and reuse it instead of
         * the same string value stored in another memory location, for example by declaring a
         * constant char const* for each uniform and reuse that constant.
         * Be careful that each uniform update has to bind() the shader program, with all its side
         * effects on rendering and performance implications.
         */
        void setUniform(char const *uniform, GLint v);

        void setUniform(char const *uniform, float v);
        void setUniform(char const *uniform, vec2 const &vec);
        void setUniform(char const *uniform, vec3 const &vec);
        void setUniform(char const *uniform, vec4 const &vec);

        void setUniform(char const *uniform, mat3 const &mat);
        void setUniform(char const *uniform, mat4 const &mat);

        void setTexture(char const *name, Texture const &tex);

        /**
         * Associates a UniformBuffer to the shader. Each associated buffer will be explicitely
         * update()d upon the shader program's binding.
         */
        void pushBuffer(std::string const &uniformBlockName, std::shared_ptr<UniformBuffer> const &buffer);
        template <typename... Args>
        void emplaceBuffer(std::string const &uniformBlockName, Args... args) {
            auto buffer = std::make_shared<UniformBuffer>(args...);
            this->pushBuffer(uniformBlockName, buffer);
        }

        /**
         * Updates the modelView matrix of the current shader to the one stored in the currently
         * active render target.
         */
        static void modelViewUpdate();

        /**
         * Updates the projection matrix of the current shader to the one stored in the currently
         * active render target.
         */
        static void projectionUpdate();

        /**
         * Sets the current instance as the active OpenGL shader program. This will cause the date
         * of the uniform buffers associated with the program to be update()d, i.e. the data will be
         * copied to the video memory.
         */
        void bind();

        /**
         * Sets the orthoTex() shader program as the active one.
         */
        static void unbind();

        /**
         * The shader currently in use.
         */
        static ShaderProgram &current();

        /**
         * An implementation-define string that uniquely identifies the shader by its sources'
         * paths.
         * Note that two shaders may be considered equal regarding this method, but may behave
         * completely different because of the preprocessor defines.
         */
        std::string name() const;


        struct Pimpl;

    private:
        std::unique_ptr<Pimpl> _pimpl;
    };
}

#endif
