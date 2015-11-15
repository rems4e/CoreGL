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

namespace CoreGL {

    /**
     * A general-purpose type-safe OpengL buffer class.
     * It may contain vertices, normals, pixels, indexes, numeric data…
     */
    class GLBuffer {
    public:
        template <typename T>
        using ForPointers = std::enable_if_t<std::is_pointer<T>::value, void>;

        template <typename T>
        using NotForPointers = std::enable_if_t<!std::is_pointer<T>::value, void>;

        /**
         * The OpenGL target of the buffer, differenciating an uniform buffer from an index buffer,
         * for instance.
         */
        virtual GLenum target() const = 0;

        /**
         * The size in bytes of the underlying memory buffer.
         */
        virtual GLsizei size() const = 0;

        /**
         * Binds the buffer with on its target on the OpenGL driver side.
         */
        virtual void bind() = 0;

        /**
         * Sends the data to the OpenGL driver.
         * When used on an "unbuffered" buffer, this is the no-op, as the data is always sent as
         * during the setData operations.
         */
        virtual void update() = 0;

        /**
         * These methods are meant for copying the data pointed to by ptr, using various sizes and
         * offsets (offset is 0 when unspecified).
         * The update variants will send allways send the data to the OpenGL driver, whereas the
         * non-update variants will only send the data to the driver when used in an "unbuffered"
         * subclass of GLBuffer.
         */
        virtual void setData(GLubyte const *ptr, size_t size) {
            this->setData(ptr, 0, size);
        }
        virtual void setData(GLubyte const *ptr, size_t offset, size_t size) = 0;
        virtual void setDataAndUpdate(GLubyte const *ptr, size_t size) {
            this->setDataAndUpdate(ptr, 0, size);
        }
        void setDataAndUpdate(GLubyte const *ptr, size_t offset, size_t size) {
            this->setData(ptr, offset, size);
            this->update();
        }
        template <typename T>
        ForPointers<T> setData(T ptr, size_t size) {
            this->setData(reinterpret_cast<GLubyte const *>(ptr), size);
        }
        template <typename T>
        ForPointers<T> setData(T ptr, size_t offset, size_t size) {
            this->setData(reinterpret_cast<GLubyte const *>(ptr), offset, size);
        }
        template <typename T>
        ForPointers<T> setDataAndUpdate(T ptr, size_t size) {
            this->setDataAndUpdate(reinterpret_cast<GLubyte const *>(ptr), size);
        }
        template <typename T>
        ForPointers<T> setDataAndUpdate(T ptr, size_t offset, size_t size) {
            this->setDataAndUpdate(reinterpret_cast<GLubyte const *>(ptr), offset, size);
        }


        /**
         * These methods are meant for copying the provided data, using various sizes and
         * offsets (offset is 0 when unspecified).
         * The update variants will send allways send the data to the OpenGL driver, whereas the
         * non-update variants will only send the data to the driver when used in an "unbuffered"
         * subclass of GLBuffer.
         */
        template <typename T>
        NotForPointers<T> setData(T const &data, size_t size) {
            this->setData(reinterpret_cast<GLubyte const *>(&data), size);
        }
        template <typename T>
        NotForPointers<T> setData(T const &data, size_t offset, size_t size) {
            this->setData(reinterpret_cast<GLubyte const *>(&data), offset, size);
        }
        template <typename T>
        NotForPointers<T> setDataAndUpdate(T const &data, size_t size) {
            this->setDataAndUpdate(reinterpret_cast<GLubyte const *>(&data), size);
        }
        template <typename T>
        NotForPointers<T> setDataAndUpdate(T const &data, size_t offset, size_t size) {
            this->setDataAndUpdate(reinterpret_cast<GLubyte const *>(&data), offset, size);
        }

        /**
         * The value identifying the buffer on the OpenGL side.
         */
        GLuint identifier() const {
            return _identifier;
        }

    protected:
        GLuint _identifier = 0;
    };

    /**
     * A helper class with no particular behavior except for storing the buffer target and size.
     */
    template <GLenum Target>
    class GLBufferTarget : public GLBuffer {
    public:
        using GLBuffer::setData;

        GLBufferTarget(GLsizei size)
                : _size(size) {
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


    /**
     * An invocation of one variant of the GLBufferedBuffer's setData methods will result in no data
     * being sent to the OpenGL. You either need to call one of the setDataAndUpdate variants, or
     * explicitely call the update method.
     * On the other hand, you will always be able to quickly query the data contained in the buffer,
     * and no copy other that the one you make will be involved.
     */
    template <GLenum Target>
    class GLBufferedBuffer : public GLBufferTarget<Target> {
    public:
        using GLBuffer::setData;

        GLBufferedBuffer(GLsizei size, GLubyte const *data, GLenum usage)
                : GLBufferTarget<Target>(size)
                , _buffer(size) {
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
                glBufferSubData(Target,
                                _editedRange.first,
                                _editedRange.second - _editedRange.first,
                                &_buffer[_editedRange.first]);
                _editedRange = std::make_pair(GLBufferTarget<Target>::_size, 0);
            }
        }

        void setData(GLubyte const *data, size_t offset, size_t size) override {
            std::memcpy(&_buffer[offset], data, size);
            _editedRange = std::make_pair(std::min(_editedRange.first, offset),
                                          std::max(_editedRange.second, size + offset));
        }

        /**
         * Retrieves the data cached in the buffer.
         * Be careful that if one of the setData methods has been called and not subsequent call to
         * update was made, then the data returned here will not reflect the data present in the
         * OpenGL driver.
         */
        GLubyte const *data() const {
            return &_buffer[0];
        }

    private:
        std::vector<GLubyte> _buffer;
        std::pair<size_t, size_t> _editedRange;
    };

    /**
     * A GLUnbufferedBuffer has the opposite behavior of GLBufferedBuffer regarding when the data is
     * sent to the OpenGL driver: every setData methods will behave exactly as their
     * setDataAndUpdate counterpart.
     * This immediate copy means that there are no quick way of retrieving the data conained in the
     * GL buffer.
     */
    template <GLenum Target>
    class GLUnbufferedBuffer : public GLBufferTarget<Target> {
    public:
        using GLBuffer::setData;

        GLUnbufferedBuffer(GLsizei size, GLubyte const *data, GLenum usage)
                : GLBufferTarget<Target>(size) {
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

    /**
     * A buffered GLBuffer specifically meant for containg shaders' uniform buffers.
     */
    class UniformBuffer : public GLBufferedBuffer<GL_UNIFORM_BUFFER> {
    public:
        using GLBuffer::setData;

        UniformBuffer(GLsizei size, GLubyte *data)
                : GLBufferedBuffer<GL_UNIFORM_BUFFER>(size, data, GL_STREAM_DRAW) {}

        virtual ~UniformBuffer() = default;

        /**
         * The binding ID of the buffer in the shader.
         */
        GLint bindingPoint() const {
            return _bindingPoint;
        }

        void setBindingPoint(GLint bindingPoint) {
            _bindingPoint = bindingPoint;
        }

    private:
        GLint _bindingPoint = -1;
    };

    using VertexBuffer = GLUnbufferedBuffer<GL_ARRAY_BUFFER>;
    using IndexBuffer = GLUnbufferedBuffer<GL_ELEMENT_ARRAY_BUFFER>;
}

template <>
struct std::hash<CoreGL::GLBuffer> {
    size_t operator()(CoreGL::GLBuffer const &buf) const noexcept {
        return std::hash<GLuint>()(buf.identifier());
    }
};

#include "GLBuffer.hpp"

#endif /* defined(__RPG_3D__GLBuffer__) */
