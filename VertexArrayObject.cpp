//
//  VertexArrayObject.cpp
//  RPG 3D
//
//  Created by Rémi on 01/09/13.
//
//

#include "VertexArrayObject.h"
#include "ContextManager.h"

namespace CoreGL {

    VertexArrayObject *VertexArrayObject::_current = nullptr;

    VertexArrayObject::VertexArrayObject() {
        glGenVertexArrays(1, &_identifier);
    }

    VertexArrayObject::~VertexArrayObject() {
        if(_current == this)
            VertexArrayObject::unbind();
        if(ContextManager::hasGLContext())
            glDeleteVertexArrays(1, &_identifier);
    }

    void VertexArrayObject::bind() {
        if(_current != this) {
            _current = this;
            _isEditing = false;
            glBindVertexArray(_identifier);
        }
    }

    void VertexArrayObject::unbind() {
        _current = nullptr;
        if(ContextManager::hasGLContext())
            glBindVertexArray(0);
    }

    bool VertexArrayObject::canBindBufferSafely() {
        return _current ? _current->_isEditing : true;
    }

    void VertexArrayObject::beginEditing() {
        this->bind();
        _isEditing = true;
    }

    void VertexArrayObject::endEditing() {
        _isEditing = false;
    }

    bool VertexArrayObject::isEditing() const {
        return _current == this && _isEditing;
    }

    void VertexArrayObject::enableVertexAttribArray(GLuint index) {
        if(!this->isEditing())
            throw std::runtime_error("VAO must be unlocked before changing its state");
        glEnableVertexAttribArray(index);
    }

    void VertexArrayObject::disableVertexAttribArray(GLuint index) {
        if(!this->isEditing())
            throw std::runtime_error("VAO must be unlocked before changing its state");
        glDisableVertexAttribArray(index);
    }

    void VertexArrayObject::vertexAttribPointer(GLuint index,
                                                GLint size,
                                                GLenum type,
                                                GLboolean normalized,
                                                GLsizei stride,
                                                GLint offset) {
        if(!this->isEditing())
            throw std::runtime_error("VAO must be unlocked before changing its state");
        glVertexAttribPointer(index, size, type, normalized, stride, reinterpret_cast<void *>(offset));
    }

    void VertexArrayObject::vertexAttribDivisor(GLuint index, GLuint divisor) {
        if(!this->isEditing())
            throw std::runtime_error("VAO must be unlocked before changing its state");
        glVertexAttribDivisor(index, divisor);
    }

    void VertexArrayObject::vertexAttrib2f(GLuint index, GLfloat x, GLfloat y) {
        if(!this->isEditing())
            throw std::runtime_error("VAO must be unlocked before changing its state");
        glVertexAttrib2f(index, x, y);
    }

    void VertexArrayObject::vertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) {
        if(!this->isEditing())
            throw std::runtime_error("VAO must be unlocked before changing its state");
        glVertexAttrib3f(index, x, y, z);
    }

    void VertexArrayObject::vertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
        if(!this->isEditing())
            throw std::runtime_error("VAO must be unlocked before changing its state");
        glVertexAttrib4f(index, x, y, z, w);
    }
}
