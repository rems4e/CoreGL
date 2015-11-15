//
//  GLBuffer.h
//  RPG 3D
//
//  Created by Rémi on 02/07/13.
//
//

#ifndef __RPG_3D__GLBuffer__
#define __RPG_3D__GLBuffer__

#include "GL.h"
#include <vector>
#include <functional>
#include <type_traits>
#include <type_traits>

namespace Ecran {
    bool GLContext();
}

class GLBuffer {
public:
    virtual GLenum target() const = 0;
    virtual GLsizei size() const = 0;
    virtual void bind() = 0;
    virtual void update() = 0;
    virtual void setData(GLubyte const *data, size_t size) {
        this->setData(data, 0, size);
    }
    virtual void setData(GLubyte const *data, size_t offset, size_t size) = 0;
    virtual void setDataAndUpdate(GLubyte const *data, size_t size) {
        this->setDataAndUpdate(data, 0, size);
    }
    void setDataAndUpdate(GLubyte const *data, size_t offset, size_t size) {
        this->setData(data, offset, size);
        this->update();
    }

    template <typename T>
    std::enable_if_t<std::is_pointer<T>::value, void> setData(T data, size_t size) {
        this->setData(reinterpret_cast<GLubyte const *>(data), size);
    }
    template <typename T>
    std::enable_if_t<std::is_pointer<T>::value, void> setData(T data, size_t offset, size_t size) {
        this->setData(reinterpret_cast<GLubyte const *>(data), offset, size);
    }
    template <typename T>
    std::enable_if_t<std::is_pointer<T>::value, void> setDataAndUpdate(T data, size_t size) {
        this->setDataAndUpdate(reinterpret_cast<GLubyte const *>(data), size);
    }
    template <typename T>
    std::enable_if_t<std::is_pointer<T>::value, void> setDataAndUpdate(T data, size_t offset, size_t size) {
        this->setDataAndUpdate(reinterpret_cast<GLubyte const *>(data), offset, size);
    }

    template <typename T>
    std::enable_if_t<!std::is_pointer<T>::value, void> setData(T const &data, size_t size) {
        this->setData(reinterpret_cast<GLubyte const *>(&data), size);
    }
    template <typename T>
    std::enable_if_t<!std::is_pointer<T>::value, void> setData(T const &data, size_t offset, size_t size) {
        this->setData(reinterpret_cast<GLubyte const *>(&data), offset, size);
    }
    template <typename T>
    std::enable_if_t<!std::is_pointer<T>::value, void> setDataAndUpdate(T const &data, size_t size) {
        this->setDataAndUpdate(reinterpret_cast<GLubyte const *>(&data), size);
    }
    template <typename T>
    std::enable_if_t<!std::is_pointer<T>::value, void> setDataAndUpdate(T const &data, size_t offset, size_t size) {
        this->setDataAndUpdate(reinterpret_cast<GLubyte const *>(&data), offset, size);
    }

    GLuint identifier() const {
        return _identifier;
    }

protected:
    GLuint _identifier = 0;
};

template <GLenum Target>
class GLBufferTarget : public GLBuffer {
public:
    using GLBuffer::setData;

    GLBufferTarget(GLsizei size) : _size(size) {
        glGenBuffers(1, &_identifier);
    }

    virtual ~GLBufferTarget();

    GLenum target() const override final {
        return Target;
    }

    GLsizei size() const override final {
        return _size;
    }

    void bind() override final;

protected:
    GLsizei const _size;
};

template <GLenum Target>
class GLBufferedBuffer : public GLBufferTarget<Target> {
public:
    using GLBuffer::setData;

    GLBufferedBuffer(GLsizei size, GLubyte const *data, GLenum usage) : GLBufferTarget<Target>(size), _buffer(size) {
        if(data)
            std::copy(data, data + size, &_buffer[0]);
        this->bind();
        glBufferData(Target, size, data, usage);
        _editedRange = std::make_pair(GLBufferTarget<Target>::_size, 0);
    }

    virtual ~GLBufferedBuffer() = default;

    void update() override {
        if(_editedRange != decltype(_editedRange)(GLBufferTarget<Target>::_size, 0)) {
            this->bind();
            glBufferSubData(Target, _editedRange.first, _editedRange.second - _editedRange.first, &_buffer[_editedRange.first]);
            _editedRange = std::make_pair(GLBufferTarget<Target>::_size, 0);
        }
    }

    void setData(GLubyte const *data, size_t offset, size_t size) override {
        std::memcpy(&_buffer[offset], data, size);
        _editedRange = std::make_pair(std::min(_editedRange.first, offset), std::max(_editedRange.second, size + offset));
    }

    GLubyte const *data() const {
        return _buffer;
    }

private:
    std::vector<GLubyte> _buffer;
    std::pair<size_t, size_t> _editedRange;
};

template <GLenum Target>
class GLUnbufferedBuffer : public GLBufferTarget<Target> {
public:
    using GLBuffer::setData;

    GLUnbufferedBuffer(GLsizei size, GLubyte const *data, GLenum usage) : GLBufferTarget<Target>(size) {
        this->bind();
        glBufferData(Target, size, data, usage);
    }

    virtual ~GLUnbufferedBuffer() = default;

    void update() override {}

    void setData(GLubyte const *data, size_t offset, size_t size) override {
        this->bind();
        glBufferSubData(Target, offset, size, reinterpret_cast<void const *>(data));
    }
};

class UniformBuffer : public GLBufferedBuffer<GL_UNIFORM_BUFFER> {
public:
    using GLBuffer::setData;

    UniformBuffer(GLsizei size, GLubyte *data) : GLBufferedBuffer<GL_UNIFORM_BUFFER>(size, data, GL_STREAM_DRAW) {}

    virtual ~UniformBuffer() = default;

    GLint bindingPoint() const {
        return _bindingPoint;
    }

    void setBindingPoint(GLint bindingPoint) {
        _bindingPoint = bindingPoint;
    }

private:
    GLint _bindingPoint = -1;
};

typedef GLUnbufferedBuffer<GL_ARRAY_BUFFER> VertexBuffer;
typedef GLUnbufferedBuffer<GL_ELEMENT_ARRAY_BUFFER> IndexBuffer;

template <>
struct std::hash<GLBuffer> {
    size_t operator()(GLBuffer const &buf) const noexcept {
        return std::hash<GLuint>()(buf.identifier());
    }
};

#include "GLBuffer.hpp"

#endif /* defined(__RPG_3D__GLBuffer__) */
