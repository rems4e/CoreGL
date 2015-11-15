//
//  GLBuffer.hpp
//  RPG 3D
//
//  Created by Rémi on 02/07/13.
//
//

#include "ContextManager.h"
#include "VertexArrayObject.h"

template <GLenum Target>
GLBufferTarget<Target>::~GLBufferTarget() {
    if(ContextManager::hasGLContext()) {
        VertexArrayObject::unbind();
        glBindBuffer(Target, 0);
        glDeleteBuffers(1, &_identifier);
    }
}

template <GLenum Target>
void GLBufferTarget<Target>::bind() {
    if(Target == GL_ARRAY_BUFFER || Target == GL_ELEMENT_ARRAY_BUFFER) {
        if(!VertexArrayObject::canBindBufferSafely())
            VertexArrayObject::unbind();
    }

    glBindBuffer(Target, _identifier);
}
