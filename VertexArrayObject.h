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

class VertexArrayObject {
public:
    // Creates empty VAO with blank state
    VertexArrayObject();
    // Destroys VAO if there is a valid GL context in use
    ~VertexArrayObject();

    // Binds the VAO to be used by the GL. For drawing only, changing its state requires beginEditing();
    void bind();
    static void unbind();

    // If the currently bound VAO is in editing mode, we can bind a VBO (to update its content and so on). Otherwise the
    // changes are propably unwanted
    static bool canBindBufferSafely();

    void beginEditing();
    void endEditing();
    bool isEditing() const;

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

#endif /* defined(__RPG_3D__VertexArrayObject__) */
