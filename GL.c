//
//  GL.c
//  CoreGL
//
//  Created by Rémi on 29/06/13.
//
//

// For DEBUG_GL
#define COREGL_GL_C
#include "GL.h"
#undef COREGL_GL_C

#include <stdio.h>
#include <GL/glew.h>

void myGlewInit() {
#ifdef DEBUG_GL
    printf("Initializing GLEW, GL_DEBUG on\n");
#endif // DEBUG_GL

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if(err != GLEW_OK) {
        printf("%s", (char const *)glewGetErrorString(err));
    }
    glGetError();
}

#ifdef DEBUG_GL

#define TOSTRING(x) #x

void CHECK_GL_ERROR(char const *fonction) {
    GLenum __error = glGetError();
    if(__error) {
        char const *txt = "other error";
        switch(__error) {
            case GL_INVALID_ENUM:
                txt = TOSTRING(GL_INVALID_ENUM);
                break;
            case GL_INVALID_OPERATION:
                txt = TOSTRING(GL_INVALID_OPERATION);
                break;
            case GL_INVALID_VALUE:
                txt = TOSTRING(GL_INVALID_VALUE);
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                txt = TOSTRING(GL_INVALID_FRAMEBUFFER_OPERATION);
                break;
            default:
                break;
        }
        printf("OpenGL error 0x%04X (%s) in %s\n", __error, txt, fonction);
        glGetError();
    }
}

void _gl_debug_error_glVertexAttribDivisor(GLuint index, GLuint divisor) {
    glVertexAttribDivisor(index, divisor);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGenSamplers(GLsizei count, GLuint *samplers) {
    glGenSamplers(count, samplers);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glSamplerParameteri(GLuint sampler, GLenum pname, GLint param) {
    glSamplerParameteri(sampler, pname, param);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param) {
    glSamplerParameterf(sampler, pname, param);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBindSampler(GLuint unit, GLuint sampler) {
    glBindSampler(unit, sampler);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCullFace(GLenum mode) {
    glCullFace(mode);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glFrontFace(GLenum mode) {
    glFrontFace(mode);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glHint(GLenum target, GLenum mode) {
    glHint(target, mode);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glLineWidth(GLfloat width) {
    glLineWidth(width);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glPointSize(GLfloat size) {
    glPointSize(size);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glPolygonMode(GLenum face, GLenum mode) {
    glPolygonMode(face, mode);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    glScissor(x, y, width, height);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexParameterf(GLenum target, GLenum pname, GLfloat param) {
    glTexParameterf(target, pname, param);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params) {
    glTexParameterfv(target, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexParameteri(GLenum target, GLenum pname, GLint param) {
    glTexParameteri(target, pname, param);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexParameteriv(GLenum target, GLenum pname, const GLint *params) {
    glTexParameteriv(target, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexImage1D(GLenum target,
                                  GLint level,
                                  GLint internalformat,
                                  GLsizei width,
                                  GLint border,
                                  GLenum format,
                                  GLenum type,
                                  const GLvoid *pixels) {
    glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexImage2D(GLenum target,
                                  GLint level,
                                  GLint internalformat,
                                  GLsizei width,
                                  GLsizei height,
                                  GLint border,
                                  GLenum format,
                                  GLenum type,
                                  const GLvoid *pixels) {
    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDrawBuffer(GLenum mode) {
    glDrawBuffer(mode);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glClear(GLbitfield mask) {
    glClear(mask);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glClearColor(red, green, blue, alpha);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glClearStencil(GLint s) {
    glClearStencil(s);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glClearDepth(GLclampd depth) {
    glClearDepth(depth);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glStencilMask(GLuint mask) {
    glStencilMask(mask);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    glColorMask(red, green, blue, alpha);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDepthMask(GLboolean flag) {
    glDepthMask(flag);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDisable(GLenum cap) {
    glDisable(cap);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glEnable(GLenum cap) {
    glEnable(cap);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glFinish(void) {
    glFinish();
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glFlush(void) {
    glFlush();
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBlendFunc(GLenum sfactor, GLenum dfactor) {
    glBlendFunc(sfactor, dfactor);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glLogicOp(GLenum opcode) {
    glLogicOp(opcode);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glStencilFunc(GLenum func, GLint ref, GLuint mask) {
    glStencilFunc(func, ref, mask);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
    glStencilOp(fail, zfail, zpass);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDepthFunc(GLenum func) {
    glDepthFunc(func);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glPixelStoref(GLenum pname, GLfloat param) {
    glPixelStoref(pname, param);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glPixelStorei(GLenum pname, GLint param) {
    glPixelStorei(pname, param);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glReadBuffer(GLenum mode) {
    glReadBuffer(mode);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels) {
    glReadPixels(x, y, width, height, format, type, pixels);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetBooleanv(GLenum pname, GLboolean *params) {
    glGetBooleanv(pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetDoublev(GLenum pname, GLdouble *params) {
    glGetDoublev(pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetFloatv(GLenum pname, GLfloat *params) {
    glGetFloatv(pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetIntegerv(GLenum pname, GLint *params) {
    glGetIntegerv(pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

const GLubyte *_gl_debug_error_glGetString(GLenum name) {
    const GLubyte *var = glGetString(name);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels) {
    glGetTexImage(target, level, format, type, pixels);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params) {
    glGetTexParameterfv(target, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetTexParameteriv(GLenum target, GLenum pname, GLint *params) {
    glGetTexParameteriv(target, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params) {
    glGetTexLevelParameterfv(target, level, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params) {
    glGetTexLevelParameteriv(target, level, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLboolean _gl_debug_error_glIsEnabled(GLenum cap) {
    GLboolean var = glIsEnabled(cap);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glDepthRange(GLclampd near, GLclampd far) {
    glDepthRange(near, far);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    glViewport(x, y, width, height);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDrawArrays(GLenum mode, GLint first, GLsizei count) {
    glDrawArrays(mode, first, count);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) {
    glDrawElements(mode, count, type, indices);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glPolygonOffset(GLfloat factor, GLfloat units) {
    glPolygonOffset(factor, units);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) {
    glCopyTexImage1D(target, level, internalformat, x, y, width, border);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCopyTexImage2D(GLenum target,
                                      GLint level,
                                      GLenum internalformat,
                                      GLint x,
                                      GLint y,
                                      GLsizei width,
                                      GLsizei height,
                                      GLint border) {
    glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
    glCopyTexSubImage1D(target, level, xoffset, x, y, width);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCopyTexSubImage2D(GLenum target,
                                         GLint level,
                                         GLint xoffset,
                                         GLint yoffset,
                                         GLint x,
                                         GLint y,
                                         GLsizei width,
                                         GLsizei height) {
    glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexSubImage1D(GLenum target,
                                     GLint level,
                                     GLint xoffset,
                                     GLsizei width,
                                     GLenum format,
                                     GLenum type,
                                     const GLvoid *pixels) {
    glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexSubImage2D(GLenum target,
                                     GLint level,
                                     GLint xoffset,
                                     GLint yoffset,
                                     GLsizei width,
                                     GLsizei height,
                                     GLenum format,
                                     GLenum type,
                                     const GLvoid *pixels) {
    glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBindTexture(GLenum target, GLuint texture) {
    glBindTexture(target, texture);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDeleteTextures(GLsizei n, const GLuint *textures) {
    glDeleteTextures(n, textures);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGenTextures(GLsizei n, GLuint *textures) {
    glGenTextures(n, textures);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLboolean _gl_debug_error_glIsTexture(GLuint texture) {
    GLboolean var = glIsTexture(texture);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glBlendColor(red, green, blue, alpha);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBlendEquation(GLenum mode) {
    glBlendEquation(mode);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices) {
    glDrawRangeElements(mode, start, end, count, type, indices);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexImage3D(GLenum target,
                                  GLint level,
                                  GLint internalformat,
                                  GLsizei width,
                                  GLsizei height,
                                  GLsizei depth,
                                  GLint border,
                                  GLenum format,
                                  GLenum type,
                                  const GLvoid *pixels) {
    glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexSubImage3D(GLenum target,
                                     GLint level,
                                     GLint xoffset,
                                     GLint yoffset,
                                     GLint zoffset,
                                     GLsizei width,
                                     GLsizei height,
                                     GLsizei depth,
                                     GLenum format,
                                     GLenum type,
                                     const GLvoid *pixels) {
    glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCopyTexSubImage3D(GLenum target,
                                         GLint level,
                                         GLint xoffset,
                                         GLint yoffset,
                                         GLint zoffset,
                                         GLint x,
                                         GLint y,
                                         GLsizei width,
                                         GLsizei height) {
    glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glActiveTexture(GLenum texture) {
    glActiveTexture(texture);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glSampleCoverage(GLclampf value, GLboolean invert) {
    glSampleCoverage(value, invert);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCompressedTexImage3D(GLenum target,
                                            GLint level,
                                            GLenum internalformat,
                                            GLsizei width,
                                            GLsizei height,
                                            GLsizei depth,
                                            GLint border,
                                            GLsizei imageSize,
                                            const GLvoid *data) {
    glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCompressedTexImage2D(GLenum target,
                                            GLint level,
                                            GLenum internalformat,
                                            GLsizei width,
                                            GLsizei height,
                                            GLint border,
                                            GLsizei imageSize,
                                            const GLvoid *data) {
    glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCompressedTexImage1D(GLenum target,
                                            GLint level,
                                            GLenum internalformat,
                                            GLsizei width,
                                            GLint border,
                                            GLsizei imageSize,
                                            const GLvoid *data) {
    glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCompressedTexSubImage3D(GLenum target,
                                               GLint level,
                                               GLint xoffset,
                                               GLint yoffset,
                                               GLint zoffset,
                                               GLsizei width,
                                               GLsizei height,
                                               GLsizei depth,
                                               GLenum format,
                                               GLsizei imageSize,
                                               const GLvoid *data) {
    glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCompressedTexSubImage2D(GLenum target,
                                               GLint level,
                                               GLint xoffset,
                                               GLint yoffset,
                                               GLsizei width,
                                               GLsizei height,
                                               GLenum format,
                                               GLsizei imageSize,
                                               const GLvoid *data) {
    glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCompressedTexSubImage1D(GLenum target,
                                               GLint level,
                                               GLint xoffset,
                                               GLsizei width,
                                               GLenum format,
                                               GLsizei imageSize,
                                               const GLvoid *data) {
    glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetCompressedTexImage(GLenum target, GLint level, GLvoid *img) {
    glGetCompressedTexImage(target, level, img);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {
    glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glMultiDrawArrays(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount) {
    glMultiDrawArrays(mode, first, count, primcount);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glMultiDrawElements(GLenum mode, const GLsizei *count, GLenum type, const GLvoid **indices, GLsizei primcount) {
    glMultiDrawElements(mode, count, type, indices, primcount);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glPointParameterf(GLenum pname, GLfloat param) {
    glPointParameterf(pname, param);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glPointParameterfv(GLenum pname, const GLfloat *params) {
    glPointParameterfv(pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glPointParameteri(GLenum pname, GLint param) {
    glPointParameteri(pname, param);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glPointParameteriv(GLenum pname, const GLint *params) {
    glPointParameteriv(pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGenQueries(GLsizei n, GLuint *ids) {
    glGenQueries(n, ids);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDeleteQueries(GLsizei n, const GLuint *ids) {
    glDeleteQueries(n, ids);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLboolean _gl_debug_error_glIsQuery(GLuint id) {
    GLboolean var = glIsQuery(id);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glBeginQuery(GLenum target, GLuint id) {
    glBeginQuery(target, id);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glEndQuery(GLenum target) {
    glEndQuery(target);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetQueryiv(GLenum target, GLenum pname, GLint *params) {
    glGetQueryiv(target, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetQueryObjectiv(GLuint id, GLenum pname, GLint *params) {
    glGetQueryObjectiv(id, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint *params) {
    glGetQueryObjectuiv(id, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBindBuffer(GLenum target, GLuint buffer) {
    glBindBuffer(target, buffer);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDeleteBuffers(GLsizei n, const GLuint *buffers) {
    glDeleteBuffers(n, buffers);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGenBuffers(GLsizei n, GLuint *buffers) {
    glGenBuffers(n, buffers);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLboolean _gl_debug_error_glIsBuffer(GLuint buffer) {
    GLboolean var = glIsBuffer(buffer);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) {
    glBufferData(target, size, data, usage);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data) {
    glBufferSubData(target, offset, size, data);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data) {
    glGetBufferSubData(target, offset, size, data);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLvoid *_gl_debug_error_glMapBuffer(GLenum target, GLenum access) {
    GLvoid *var = glMapBuffer(target, access);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


GLboolean _gl_debug_error_glUnmapBuffer(GLenum target) {
    GLboolean var = glUnmapBuffer(target);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glGetBufferParameteriv(GLenum target, GLenum pname, GLint *params) {
    glGetBufferParameteriv(target, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetBufferPointerv(GLenum target, GLenum pname, GLvoid **params) {
    glGetBufferPointerv(target, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) {
    glBlendEquationSeparate(modeRGB, modeAlpha);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDrawBuffers(GLsizei n, const GLenum *bufs) {
    glDrawBuffers(n, bufs);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
    glStencilOpSeparate(face, sfail, dpfail, dppass);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) {
    glStencilFuncSeparate(face, func, ref, mask);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glStencilMaskSeparate(GLenum face, GLuint mask) {
    glStencilMaskSeparate(face, mask);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glAttachShader(GLuint program, GLuint shader) {
    glAttachShader(program, shader);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBindAttribLocation(GLuint program, GLuint index, const GLchar *name) {
    glBindAttribLocation(program, index, name);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCompileShader(GLuint shader) {
    glCompileShader(shader);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLuint _gl_debug_error_glCreateProgram(void) {
    GLuint var = glCreateProgram();
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


GLuint _gl_debug_error_glCreateShader(GLenum type) {
    GLuint var = glCreateShader(type);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glDeleteProgram(GLuint program) {
    glDeleteProgram(program);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDeleteShader(GLuint shader) {
    glDeleteShader(shader);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDetachShader(GLuint program, GLuint shader) {
    glDetachShader(program, shader);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDisableVertexAttribArray(GLuint index) {
    glDisableVertexAttribArray(index);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glEnableVertexAttribArray(GLuint index) {
    glEnableVertexAttribArray(index);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetActiveAttrib(GLuint program,
                                       GLuint index,
                                       GLsizei bufSize,
                                       GLsizei *length,
                                       GLint *size,
                                       GLenum *type,
                                       GLchar *name) {
    glGetActiveAttrib(program, index, bufSize, length, size, type, name);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetActiveUniform(GLuint program,
                                        GLuint index,
                                        GLsizei bufSize,
                                        GLsizei *length,
                                        GLint *size,
                                        GLenum *type,
                                        GLchar *name) {
    glGetActiveUniform(program, index, bufSize, length, size, type, name);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders) {
    glGetAttachedShaders(program, maxCount, count, shaders);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLint _gl_debug_error_glGetAttribLocation(GLuint program, const GLchar *name) {
    GLint var = glGetAttribLocation(program, name);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glGetProgramiv(GLuint program, GLenum pname, GLint *params) {
    glGetProgramiv(program, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    glGetProgramInfoLog(program, bufSize, length, infoLog);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetShaderiv(GLuint shader, GLenum pname, GLint *params) {
    glGetShaderiv(shader, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    glGetShaderInfoLog(shader, bufSize, length, infoLog);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source) {
    glGetShaderSource(shader, bufSize, length, source);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLint _gl_debug_error_glGetUniformLocation(GLuint program, const GLchar *name) {
    GLint var = glGetUniformLocation(program, name);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glGetUniformfv(GLuint program, GLint location, GLfloat *params) {
    glGetUniformfv(program, location, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetUniformiv(GLuint program, GLint location, GLint *params) {
    glGetUniformiv(program, location, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble *params) {
    glGetVertexAttribdv(index, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params) {
    glGetVertexAttribfv(index, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetVertexAttribiv(GLuint index, GLenum pname, GLint *params) {
    glGetVertexAttribiv(index, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid **pointer) {
    glGetVertexAttribPointerv(index, pname, pointer);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLboolean _gl_debug_error_glIsProgram(GLuint program) {
    GLboolean var = glIsProgram(program);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


GLboolean _gl_debug_error_glIsShader(GLuint shader) {
    GLboolean var = glIsShader(shader);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glLinkProgram(GLuint program) {
    glLinkProgram(program);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glShaderSource(GLuint shader, GLsizei count, const GLchar **string, const GLint *length) {
    glShaderSource(shader, count, string, length);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUseProgram(GLuint program) {
    glUseProgram(program);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform1f(GLint location, GLfloat v0) {
    glUniform1f(location, v0);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform2f(GLint location, GLfloat v0, GLfloat v1) {
    glUniform2f(location, v0, v1);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    glUniform3f(location, v0, v1, v2);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    glUniform4f(location, v0, v1, v2, v3);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform1i(GLint location, GLint v0) {
    glUniform1i(location, v0);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform2i(GLint location, GLint v0, GLint v1) {
    glUniform2i(location, v0, v1);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform3i(GLint location, GLint v0, GLint v1, GLint v2) {
    glUniform3i(location, v0, v1, v2);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    glUniform4i(location, v0, v1, v2, v3);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform1fv(GLint location, GLsizei count, const GLfloat *value) {
    glUniform1fv(location, count, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform2fv(GLint location, GLsizei count, const GLfloat *value) {
    glUniform2fv(location, count, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform3fv(GLint location, GLsizei count, const GLfloat *value) {
    glUniform3fv(location, count, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform4fv(GLint location, GLsizei count, const GLfloat *value) {
    glUniform4fv(location, count, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform1iv(GLint location, GLsizei count, const GLint *value) {
    glUniform1iv(location, count, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform2iv(GLint location, GLsizei count, const GLint *value) {
    glUniform2iv(location, count, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform3iv(GLint location, GLsizei count, const GLint *value) {
    glUniform3iv(location, count, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform4iv(GLint location, GLsizei count, const GLint *value) {
    glUniform4iv(location, count, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix2fv(location, count, transpose, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix3fv(location, count, transpose, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix4fv(location, count, transpose, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glValidateProgram(GLuint program) {
    glValidateProgram(program);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib1d(GLuint index, GLdouble x) {
    glVertexAttrib1d(index, x);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib1dv(GLuint index, const GLdouble *v) {
    glVertexAttrib1dv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib1f(GLuint index, GLfloat x) {
    glVertexAttrib1f(index, x);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib1fv(GLuint index, const GLfloat *v) {
    glVertexAttrib1fv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib1s(GLuint index, GLshort x) {
    glVertexAttrib1s(index, x);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib1sv(GLuint index, const GLshort *v) {
    glVertexAttrib1sv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y) {
    glVertexAttrib2d(index, x, y);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib2dv(GLuint index, const GLdouble *v) {
    glVertexAttrib2dv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y) {
    glVertexAttrib2f(index, x, y);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib2fv(GLuint index, const GLfloat *v) {
    glVertexAttrib2fv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib2s(GLuint index, GLshort x, GLshort y) {
    glVertexAttrib2s(index, x, y);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib2sv(GLuint index, const GLshort *v) {
    glVertexAttrib2sv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) {
    glVertexAttrib3d(index, x, y, z);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib3dv(GLuint index, const GLdouble *v) {
    glVertexAttrib3dv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) {
    glVertexAttrib3f(index, x, y, z);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib3fv(GLuint index, const GLfloat *v) {
    glVertexAttrib3fv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z) {
    glVertexAttrib3s(index, x, y, z);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib3sv(GLuint index, const GLshort *v) {
    glVertexAttrib3sv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4Nbv(GLuint index, const GLbyte *v) {
    glVertexAttrib4Nbv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4Niv(GLuint index, const GLint *v) {
    glVertexAttrib4Niv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4Nsv(GLuint index, const GLshort *v) {
    glVertexAttrib4Nsv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) {
    glVertexAttrib4Nub(index, x, y, z, w);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4Nubv(GLuint index, const GLubyte *v) {
    glVertexAttrib4Nubv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4Nuiv(GLuint index, const GLuint *v) {
    glVertexAttrib4Nuiv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4Nusv(GLuint index, const GLushort *v) {
    glVertexAttrib4Nusv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4bv(GLuint index, const GLbyte *v) {
    glVertexAttrib4bv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    glVertexAttrib4d(index, x, y, z, w);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4dv(GLuint index, const GLdouble *v) {
    glVertexAttrib4dv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glVertexAttrib4f(index, x, y, z, w);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4fv(GLuint index, const GLfloat *v) {
    glVertexAttrib4fv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4iv(GLuint index, const GLint *v) {
    glVertexAttrib4iv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) {
    glVertexAttrib4s(index, x, y, z, w);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4sv(GLuint index, const GLshort *v) {
    glVertexAttrib4sv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4ubv(GLuint index, const GLubyte *v) {
    glVertexAttrib4ubv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4uiv(GLuint index, const GLuint *v) {
    glVertexAttrib4uiv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttrib4usv(GLuint index, const GLushort *v) {
    glVertexAttrib4usv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribPointer(GLuint index,
                                           GLint size,
                                           GLenum type,
                                           GLboolean normalized,
                                           GLsizei stride,
                                           const GLvoid *pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix2x3fv(location, count, transpose, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix3x2fv(location, count, transpose, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix2x4fv(location, count, transpose, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix4x2fv(location, count, transpose, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix3x4fv(location, count, transpose, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix4x3fv(location, count, transpose, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) {
    glColorMaski(index, r, g, b, a);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetBooleani_v(GLenum target, GLuint index, GLboolean *data) {
    glGetBooleani_v(target, index, data);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetIntegeri_v(GLenum target, GLuint index, GLint *data) {
    glGetIntegeri_v(target, index, data);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glEnablei(GLenum target, GLuint index) {
    glEnablei(target, index);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDisablei(GLenum target, GLuint index) {
    glDisablei(target, index);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLboolean _gl_debug_error_glIsEnabledi(GLenum target, GLuint index) {
    GLboolean var = glIsEnabledi(target, index);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glBeginTransformFeedback(GLenum primitiveMode) {
    glBeginTransformFeedback(primitiveMode);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glEndTransformFeedback(void) {
    glEndTransformFeedback();
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) {
    glBindBufferRange(target, index, buffer, offset, size);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBindBufferBase(GLenum target, GLuint index, GLuint buffer) {
    glBindBufferBase(target, index, buffer);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar **varyings, GLenum bufferMode) {
    glTransformFeedbackVaryings(program, count, varyings, bufferMode);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetTransformFeedbackVarying(GLuint program,
                                                   GLuint index,
                                                   GLsizei bufSize,
                                                   GLsizei *length,
                                                   GLsizei *size,
                                                   GLenum *type,
                                                   GLchar *name) {
    glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glClampColor(GLenum target, GLenum clamp) {
    glClampColor(target, clamp);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBeginConditionalRender(GLuint id, GLenum mode) {
    glBeginConditionalRender(id, mode);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glEndConditionalRender(void) {
    glEndConditionalRender();
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
    glVertexAttribIPointer(index, size, type, stride, pointer);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetVertexAttribIiv(GLuint index, GLenum pname, GLint *params) {
    glGetVertexAttribIiv(index, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params) {
    glGetVertexAttribIuiv(index, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI1i(GLuint index, GLint x) {
    glVertexAttribI1i(index, x);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI2i(GLuint index, GLint x, GLint y) {
    glVertexAttribI2i(index, x, y);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z) {
    glVertexAttribI3i(index, x, y, z);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w) {
    glVertexAttribI4i(index, x, y, z, w);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI1ui(GLuint index, GLuint x) {
    glVertexAttribI1ui(index, x);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI2ui(GLuint index, GLuint x, GLuint y) {
    glVertexAttribI2ui(index, x, y);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z) {
    glVertexAttribI3ui(index, x, y, z);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) {
    glVertexAttribI4ui(index, x, y, z, w);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI1iv(GLuint index, const GLint *v) {
    glVertexAttribI1iv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI2iv(GLuint index, const GLint *v) {
    glVertexAttribI2iv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI3iv(GLuint index, const GLint *v) {
    glVertexAttribI3iv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI4iv(GLuint index, const GLint *v) {
    glVertexAttribI4iv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI1uiv(GLuint index, const GLuint *v) {
    glVertexAttribI1uiv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI2uiv(GLuint index, const GLuint *v) {
    glVertexAttribI2uiv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI3uiv(GLuint index, const GLuint *v) {
    glVertexAttribI3uiv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI4uiv(GLuint index, const GLuint *v) {
    glVertexAttribI4uiv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI4bv(GLuint index, const GLbyte *v) {
    glVertexAttribI4bv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI4sv(GLuint index, const GLshort *v) {
    glVertexAttribI4sv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI4ubv(GLuint index, const GLubyte *v) {
    glVertexAttribI4ubv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glVertexAttribI4usv(GLuint index, const GLushort *v) {
    glVertexAttribI4usv(index, v);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetUniformuiv(GLuint program, GLint location, GLuint *params) {
    glGetUniformuiv(program, location, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBindFragDataLocation(GLuint program, GLuint color, const GLchar *name) {
    glBindFragDataLocation(program, color, name);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLint _gl_debug_error_glGetFragDataLocation(GLuint program, const GLchar *name) {
    GLint var = glGetFragDataLocation(program, name);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glUniform1ui(GLint location, GLuint v0) {
    glUniform1ui(location, v0);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform2ui(GLint location, GLuint v0, GLuint v1) {
    glUniform2ui(location, v0, v1);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) {
    glUniform3ui(location, v0, v1, v2);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    glUniform4ui(location, v0, v1, v2, v3);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform1uiv(GLint location, GLsizei count, const GLuint *value) {
    glUniform1uiv(location, count, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform2uiv(GLint location, GLsizei count, const GLuint *value) {
    glUniform2uiv(location, count, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform3uiv(GLint location, GLsizei count, const GLuint *value) {
    glUniform3uiv(location, count, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniform4uiv(GLint location, GLsizei count, const GLuint *value) {
    glUniform4uiv(location, count, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexParameterIiv(GLenum target, GLenum pname, const GLint *params) {
    glTexParameterIiv(target, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexParameterIuiv(GLenum target, GLenum pname, const GLuint *params) {
    glTexParameterIuiv(target, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetTexParameterIiv(GLenum target, GLenum pname, GLint *params) {
    glGetTexParameterIiv(target, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint *params) {
    glGetTexParameterIuiv(target, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value) {
    glClearBufferiv(buffer, drawbuffer, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value) {
    glClearBufferuiv(buffer, drawbuffer, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value) {
    glClearBufferfv(buffer, drawbuffer, value);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) {
    glClearBufferfi(buffer, drawbuffer, depth, stencil);
    CHECK_GL_ERROR(__FUNCTION__);
}

const GLubyte *_gl_debug_error_glGetStringi(GLenum name, GLuint index) {
    const GLubyte *var = glGetStringi(name, index);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei primcount) {
    glDrawArraysInstanced(mode, first, count, primcount);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount) {
    glDrawElementsInstanced(mode, count, type, indices, primcount);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer) {
    glTexBuffer(target, internalformat, buffer);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glPrimitiveRestartIndex(GLuint index) {
    glPrimitiveRestartIndex(index);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data) {
    glGetInteger64i_v(target, index, data);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params) {
    glGetBufferParameteri64v(target, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) {
    glFramebufferTexture(target, attachment, texture, level);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLboolean _gl_debug_error_glIsRenderbuffer(GLuint renderbuffer) {
    GLboolean var = glIsRenderbuffer(renderbuffer);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glBindRenderbuffer(GLenum target, GLuint renderbuffer) {
    glBindRenderbuffer(target, renderbuffer);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers) {
    glDeleteRenderbuffers(n, renderbuffers);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGenRenderbuffers(GLsizei n, GLuint *renderbuffers) {
    glGenRenderbuffers(n, renderbuffers);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
    glRenderbufferStorage(target, internalformat, width, height);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params) {
    glGetRenderbufferParameteriv(target, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLboolean _gl_debug_error_glIsFramebuffer(GLuint framebuffer) {
    GLboolean var = glIsFramebuffer(framebuffer);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glBindFramebuffer(GLenum target, GLuint framebuffer) {
    glBindFramebuffer(target, framebuffer);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers) {
    glDeleteFramebuffers(n, framebuffers);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGenFramebuffers(GLsizei n, GLuint *framebuffers) {
    glGenFramebuffers(n, framebuffers);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLenum _gl_debug_error_glCheckFramebufferStatus(GLenum target) {
    GLenum var = glCheckFramebufferStatus(target);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glFramebufferTexture1D(target, attachment, textarget, texture, level);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glFramebufferTexture3D(GLenum target,
                                            GLenum attachment,
                                            GLenum textarget,
                                            GLuint texture,
                                            GLint level,
                                            GLint zoffset) {
    glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params) {
    glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGenerateMipmap(GLenum target) {
    glGenerateMipmap(target);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBlitFramebuffer(GLint srcX0,
                                       GLint srcY0,
                                       GLint srcX1,
                                       GLint srcY1,
                                       GLint dstX0,
                                       GLint dstY0,
                                       GLint dstX1,
                                       GLint dstY1,
                                       GLbitfield mask,
                                       GLenum filter) {
    glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glRenderbufferStorageMultisample(GLenum target,
                                                      GLsizei samples,
                                                      GLenum internalformat,
                                                      GLsizei width,
                                                      GLsizei height) {
    glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) {
    glFramebufferTextureLayer(target, attachment, texture, level, layer);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLvoid *_gl_debug_error_glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) {
    GLvoid *var = glMapBufferRange(target, offset, length, access);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length) {
    glFlushMappedBufferRange(target, offset, length);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glBindVertexArray(GLuint array) {
    glBindVertexArray(array);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDeleteVertexArrays(GLsizei n, const GLuint *arrays) {
    glDeleteVertexArrays(n, arrays);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGenVertexArrays(GLsizei n, GLuint *arrays) {
    glGenVertexArrays(n, arrays);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLboolean _gl_debug_error_glIsVertexArray(GLuint array) {
    GLboolean var = glIsVertexArray(array);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar **uniformNames, GLuint *uniformIndices) {
    glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetActiveUniformsiv(GLuint program,
                                           GLsizei uniformCount,
                                           const GLuint *uniformIndices,
                                           GLenum pname,
                                           GLint *params) {
    glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetActiveUniformName(GLuint program,
                                            GLuint uniformIndex,
                                            GLsizei bufSize,
                                            GLsizei *length,
                                            GLchar *uniformName) {
    glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLuint _gl_debug_error_glGetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName) {
    GLuint var = glGetUniformBlockIndex(program, uniformBlockName);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params) {
    glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetActiveUniformBlockName(GLuint program,
                                                 GLuint uniformBlockIndex,
                                                 GLsizei bufSize,
                                                 GLsizei *length,
                                                 GLchar *uniformBlockName) {
    glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) {
    glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glCopyBufferSubData(GLenum readTarget,
                                         GLenum writeTarget,
                                         GLintptr readOffset,
                                         GLintptr writeOffset,
                                         GLsizeiptr size) {
    glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, GLvoid *indices, GLint basevertex) {
    glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDrawRangeElementsBaseVertex(GLenum mode,
                                                   GLuint start,
                                                   GLuint end,
                                                   GLsizei count,
                                                   GLenum type,
                                                   GLvoid *indices,
                                                   GLint basevertex) {
    glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glDrawElementsInstancedBaseVertex(GLenum mode,
                                                       GLsizei count,
                                                       GLenum type,
                                                       const GLvoid *indices,
                                                       GLsizei primcount,
                                                       GLint basevertex) {
    glDrawElementsInstancedBaseVertex(mode, count, type, indices, primcount, basevertex);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glMultiDrawElementsBaseVertex(GLenum mode,
                                                   const GLsizei *count,
                                                   GLenum type,
                                                   const void *const *indices,
                                                   GLsizei primcount,
                                                   const GLint *basevertex) {
    glMultiDrawElementsBaseVertex(mode, count, type, indices, primcount, basevertex);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glProvokingVertex(GLenum mode) {
    glProvokingVertex(mode);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLsync _gl_debug_error_glFenceSync(GLenum condition, GLbitfield flags) {
    GLsync var = glFenceSync(condition, flags);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


GLboolean _gl_debug_error_glIsSync(GLsync sync) {
    GLboolean var = glIsSync(sync);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glDeleteSync(GLsync sync) {
    glDeleteSync(sync);
    CHECK_GL_ERROR(__FUNCTION__);
}

GLenum _gl_debug_error_glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) {
    GLenum var = glClientWaitSync(sync, flags, timeout);
    CHECK_GL_ERROR(__FUNCTION__);
    return var;
}


void _gl_debug_error_glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) {
    glWaitSync(sync, flags, timeout);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetInteger64v(GLenum pname, GLint64 *params) {
    glGetInteger64v(pname, params);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values) {
    glGetSynciv(sync, pname, bufSize, length, values);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexImage2DMultisample(GLenum target,
                                             GLsizei samples,
                                             GLint internalformat,
                                             GLsizei width,
                                             GLsizei height,
                                             GLboolean fixedsamplelocations) {
    glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glTexImage3DMultisample(GLenum target,
                                             GLsizei samples,
                                             GLint internalformat,
                                             GLsizei width,
                                             GLsizei height,
                                             GLsizei depth,
                                             GLboolean fixedsamplelocations) {
    glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glGetMultisamplefv(GLenum pname, GLuint index, GLfloat *val) {
    glGetMultisamplefv(pname, index, val);
    CHECK_GL_ERROR(__FUNCTION__);
}

void _gl_debug_error_glSampleMaski(GLuint index, GLbitfield mask) {
    glSampleMaski(index, mask);
    CHECK_GL_ERROR(__FUNCTION__);
}

#endif