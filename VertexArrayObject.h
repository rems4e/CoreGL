//
//  VertexArrayObject.h
//  RPG 3D
//
//  Created by Rémi on 01/09/13.
//
//

#ifndef __RPG_3D__VertexArrayObject__
#define __RPG_3D__VertexArrayObject__

#include "GL.h"

namespace CoreGL {

    /**
     * A class managing the drawn vertices's components such as color, normal, tangent…
     *
     * In order to call the enable/disable/vertexAttrib* methods, the VAO must be unlocked by a call
     * to the beginEditing methods. A corresponding call to endEnditing has to be made before
     * issuing actual drawing commands. This prevents accidental modifications of the current VAO,
     *when modifying another one was what was wanted.
     */
    class VertexArrayObject {
    public:
        /**
         * Creates an empty VAO with blank state
         */
        VertexArrayObject();
        ~VertexArrayObject();

        // Binds the VAO to be used by the GL. For drawing only, changing its state requires
        // beginEditing();
        /**
         * Sets the VAO as the active one for the next drawing commands. This does
         */
        void bind();
        static void unbind();

        /**
         * If the currently bound VAO is in editing mode, we can bind a VBO (to update its content
         * and so on). Otherwise the changes are probably unwanted.
         */
        static bool canBindBufferSafely();

        /**
         * Starts, stops and queries the editing mode of the object.
         */
        void beginEditing();
        void endEditing();
        bool isEditing() const;

        /**
         * Small wrappers to the OpenGL version of these functions.
         * It enables asserting that the VAO is actually in editing mode.
         */
        void enableVertexAttribArray(GLuint index);
        void disableVertexAttribArray(GLuint index);
        void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLint offset);
        void vertexAttribDivisor(GLuint index, GLuint divisor);

        void vertexAttrib2f(GLuint index, GLfloat x, GLfloat y);
        void vertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);
        void vertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

    private:
        GLuint _identifier;
        bool _isEditing = false;

        static VertexArrayObject *_current;
    };
}

#endif /* defined(__RPG_3D__VertexArrayObject__) */
