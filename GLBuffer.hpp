//
//  GLBuffer.hpp
//  CoreGL
//
//  Created by Rémi on 02/07/13.
//
//

#include "CoreGL.h"
#include "VertexArrayObject.h"

namespace CoreGL {

    template <GLenum Target>
    GLBufferTarget<Target>::~GLBufferTarget() {
        if(CoreGL::initialized()) {
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
}
