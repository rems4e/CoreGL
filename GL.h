//
//  GL.h
//  CoreGL
//
//  Created by Rémi on 19/08/12.
//
//

#ifndef COREGL_GL_H
#define COREGL_GL_H

#ifdef __cplusplus
extern "C" void myGlewInit();
#endif // __cplusplus

#include "platform.h"

#define DEBUG_GL

#ifndef COREGL_GL_C

#ifndef DEBUG_GL

#include <GL/glew.h>

#else // DEBUG_GL

#ifdef __MACOSX__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#elif defined(__WIN32__)
#include <GL/glew.h>
#else
#define GL_GLEXT_LEGACY
#include <GL/gl.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glext.h>
#endif // __MACOSX__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define glVertexAttribDivisor _gl_debug_error_glVertexAttribDivisor
void _gl_debug_error_glVertexAttribDivisor(GLuint index, GLuint divisor);

#define glGenSamplers _gl_debug_error_glGenSamplers
void _gl_debug_error_glGenSamplers(GLsizei count, GLuint *samplers);

#define glSamplerParameteri _gl_debug_error_glSamplerParameteri
void _gl_debug_error_glSamplerParameteri(GLuint sampler, GLenum pname, GLint param);

#define glSamplerParameterf _gl_debug_error_glSamplerParameterf
void _gl_debug_error_glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param);

#define glBindSampler _gl_debug_error_glBindSampler
void _gl_debug_error_glBindSampler(GLuint unit, GLuint sampler);

#define glCullFace _gl_debug_error_glCullFace
void _gl_debug_error_glCullFace(GLenum mode);

#define glFrontFace _gl_debug_error_glFrontFace
void _gl_debug_error_glFrontFace(GLenum mode);

#define glHint _gl_debug_error_glHint
void _gl_debug_error_glHint(GLenum target, GLenum mode);

#define glLineWidth _gl_debug_error_glLineWidth
void _gl_debug_error_glLineWidth(GLfloat width);

#define glPointSize _gl_debug_error_glPointSize
void _gl_debug_error_glPointSize(GLfloat size);

#define glPolygonMode _gl_debug_error_glPolygonMode
void _gl_debug_error_glPolygonMode(GLenum face, GLenum mode);

#define glScissor _gl_debug_error_glScissor
void _gl_debug_error_glScissor(GLint x, GLint y, GLsizei width, GLsizei height);

#define glTexParameterf _gl_debug_error_glTexParameterf
void _gl_debug_error_glTexParameterf(GLenum target, GLenum pname, GLfloat param);

#define glTexParameterfv _gl_debug_error_glTexParameterfv
void _gl_debug_error_glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params);

#define glTexParameteri _gl_debug_error_glTexParameteri
void _gl_debug_error_glTexParameteri(GLenum target, GLenum pname, GLint param);

#define glTexParameteriv _gl_debug_error_glTexParameteriv
void _gl_debug_error_glTexParameteriv(GLenum target, GLenum pname, const GLint *params);

#define glTexImage1D _gl_debug_error_glTexImage1D
void _gl_debug_error_glTexImage1D(GLenum target,
                                  GLint level,
                                  GLint internalformat,
                                  GLsizei width,
                                  GLint border,
                                  GLenum format,
                                  GLenum type,
                                  const GLvoid *pixels);

#define glTexImage2D _gl_debug_error_glTexImage2D
void _gl_debug_error_glTexImage2D(GLenum target,
                                  GLint level,
                                  GLint internalformat,
                                  GLsizei width,
                                  GLsizei height,
                                  GLint border,
                                  GLenum format,
                                  GLenum type,
                                  const GLvoid *pixels);

#define glDrawBuffer _gl_debug_error_glDrawBuffer
void _gl_debug_error_glDrawBuffer(GLenum mode);

#define glClear _gl_debug_error_glClear
void _gl_debug_error_glClear(GLbitfield mask);

#define glClearColor _gl_debug_error_glClearColor
void _gl_debug_error_glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

#define glClearStencil _gl_debug_error_glClearStencil
void _gl_debug_error_glClearStencil(GLint s);

#define glClearDepth _gl_debug_error_glClearDepth
void _gl_debug_error_glClearDepth(GLclampd depth);

#define glStencilMask _gl_debug_error_glStencilMask
void _gl_debug_error_glStencilMask(GLuint mask);

#define glColorMask _gl_debug_error_glColorMask
void _gl_debug_error_glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

#define glDepthMask _gl_debug_error_glDepthMask
void _gl_debug_error_glDepthMask(GLboolean flag);

#define glDisable _gl_debug_error_glDisable
void _gl_debug_error_glDisable(GLenum cap);

#define glEnable _gl_debug_error_glEnable
void _gl_debug_error_glEnable(GLenum cap);

#define glFinish _gl_debug_error_glFinish
void _gl_debug_error_glFinish(void);

#define glFlush _gl_debug_error_glFlush
void _gl_debug_error_glFlush(void);

#define glBlendFunc _gl_debug_error_glBlendFunc
void _gl_debug_error_glBlendFunc(GLenum sfactor, GLenum dfactor);

#define glLogicOp _gl_debug_error_glLogicOp
void _gl_debug_error_glLogicOp(GLenum opcode);

#define glStencilFunc _gl_debug_error_glStencilFunc
void _gl_debug_error_glStencilFunc(GLenum func, GLint ref, GLuint mask);

#define glStencilOp _gl_debug_error_glStencilOp
void _gl_debug_error_glStencilOp(GLenum fail, GLenum zfail, GLenum zpass);

#define glDepthFunc _gl_debug_error_glDepthFunc
void _gl_debug_error_glDepthFunc(GLenum func);

#define glPixelStoref _gl_debug_error_glPixelStoref
void _gl_debug_error_glPixelStoref(GLenum pname, GLfloat param);

#define glPixelStorei _gl_debug_error_glPixelStorei
void _gl_debug_error_glPixelStorei(GLenum pname, GLint param);

#define glReadBuffer _gl_debug_error_glReadBuffer
void _gl_debug_error_glReadBuffer(GLenum mode);

#define glReadPixels _gl_debug_error_glReadPixels
void _gl_debug_error_glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);

#define glGetBooleanv _gl_debug_error_glGetBooleanv
void _gl_debug_error_glGetBooleanv(GLenum pname, GLboolean *params);

#define glGetDoublev _gl_debug_error_glGetDoublev
void _gl_debug_error_glGetDoublev(GLenum pname, GLdouble *params);

#define glGetFloatv _gl_debug_error_glGetFloatv
void _gl_debug_error_glGetFloatv(GLenum pname, GLfloat *params);

#define glGetIntegerv _gl_debug_error_glGetIntegerv
void _gl_debug_error_glGetIntegerv(GLenum pname, GLint *params);

#define glGetString _gl_debug_error_glGetString
const GLubyte *_gl_debug_error_glGetString(GLenum name);

#define glGetTexImage _gl_debug_error_glGetTexImage
void _gl_debug_error_glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);

#define glGetTexParameterfv _gl_debug_error_glGetTexParameterfv
void _gl_debug_error_glGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params);

#define glGetTexParameteriv _gl_debug_error_glGetTexParameteriv
void _gl_debug_error_glGetTexParameteriv(GLenum target, GLenum pname, GLint *params);

#define glGetTexLevelParameterfv _gl_debug_error_glGetTexLevelParameterfv
void _gl_debug_error_glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params);

#define glGetTexLevelParameteriv _gl_debug_error_glGetTexLevelParameteriv
void _gl_debug_error_glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params);

#define glIsEnabled _gl_debug_error_glIsEnabled
GLboolean _gl_debug_error_glIsEnabled(GLenum cap);

#define glDepthRange _gl_debug_error_glDepthRange
void _gl_debug_error_glDepthRange(GLclampd near, GLclampd far);

#define glViewport _gl_debug_error_glViewport
void _gl_debug_error_glViewport(GLint x, GLint y, GLsizei width, GLsizei height);

#define glDrawArrays _gl_debug_error_glDrawArrays
void _gl_debug_error_glDrawArrays(GLenum mode, GLint first, GLsizei count);

#define glDrawElements _gl_debug_error_glDrawElements
void _gl_debug_error_glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);

#define glPolygonOffset _gl_debug_error_glPolygonOffset
void _gl_debug_error_glPolygonOffset(GLfloat factor, GLfloat units);

#define glCopyTexImage1D _gl_debug_error_glCopyTexImage1D
void _gl_debug_error_glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);

#define glCopyTexImage2D _gl_debug_error_glCopyTexImage2D
void _gl_debug_error_glCopyTexImage2D(GLenum target,
                                      GLint level,
                                      GLenum internalformat,
                                      GLint x,
                                      GLint y,
                                      GLsizei width,
                                      GLsizei height,
                                      GLint border);

#define glCopyTexSubImage1D _gl_debug_error_glCopyTexSubImage1D
void _gl_debug_error_glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);

#define glCopyTexSubImage2D _gl_debug_error_glCopyTexSubImage2D
void _gl_debug_error_glCopyTexSubImage2D(GLenum target,
                                         GLint level,
                                         GLint xoffset,
                                         GLint yoffset,
                                         GLint x,
                                         GLint y,
                                         GLsizei width,
                                         GLsizei height);

#define glTexSubImage1D _gl_debug_error_glTexSubImage1D
void _gl_debug_error_glTexSubImage1D(GLenum target,
                                     GLint level,
                                     GLint xoffset,
                                     GLsizei width,
                                     GLenum format,
                                     GLenum type,
                                     const GLvoid *pixels);

#define glTexSubImage2D _gl_debug_error_glTexSubImage2D
void _gl_debug_error_glTexSubImage2D(GLenum target,
                                     GLint level,
                                     GLint xoffset,
                                     GLint yoffset,
                                     GLsizei width,
                                     GLsizei height,
                                     GLenum format,
                                     GLenum type,
                                     const GLvoid *pixels);

#define glBindTexture _gl_debug_error_glBindTexture
void _gl_debug_error_glBindTexture(GLenum target, GLuint texture);

#define glDeleteTextures _gl_debug_error_glDeleteTextures
void _gl_debug_error_glDeleteTextures(GLsizei n, const GLuint *textures);

#define glGenTextures _gl_debug_error_glGenTextures
void _gl_debug_error_glGenTextures(GLsizei n, GLuint *textures);

#define glIsTexture _gl_debug_error_glIsTexture
GLboolean _gl_debug_error_glIsTexture(GLuint texture);

#define glBlendColor _gl_debug_error_glBlendColor
void _gl_debug_error_glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

#define glBlendEquation _gl_debug_error_glBlendEquation
void _gl_debug_error_glBlendEquation(GLenum mode);

#define glDrawRangeElements _gl_debug_error_glDrawRangeElements
void _gl_debug_error_glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);

#define glTexImage3D _gl_debug_error_glTexImage3D
void _gl_debug_error_glTexImage3D(GLenum target,
                                  GLint level,
                                  GLint internalformat,
                                  GLsizei width,
                                  GLsizei height,
                                  GLsizei depth,
                                  GLint border,
                                  GLenum format,
                                  GLenum type,
                                  const GLvoid *pixels);

#define glTexSubImage3D _gl_debug_error_glTexSubImage3D
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
                                     const GLvoid *pixels);

#define glCopyTexSubImage3D _gl_debug_error_glCopyTexSubImage3D
void _gl_debug_error_glCopyTexSubImage3D(GLenum target,
                                         GLint level,
                                         GLint xoffset,
                                         GLint yoffset,
                                         GLint zoffset,
                                         GLint x,
                                         GLint y,
                                         GLsizei width,
                                         GLsizei height);

#define glActiveTexture _gl_debug_error_glActiveTexture
void _gl_debug_error_glActiveTexture(GLenum texture);

#define glSampleCoverage _gl_debug_error_glSampleCoverage
void _gl_debug_error_glSampleCoverage(GLclampf value, GLboolean invert);

#define glCompressedTexImage3D _gl_debug_error_glCompressedTexImage3D
void _gl_debug_error_glCompressedTexImage3D(GLenum target,
                                            GLint level,
                                            GLenum internalformat,
                                            GLsizei width,
                                            GLsizei height,
                                            GLsizei depth,
                                            GLint border,
                                            GLsizei imageSize,
                                            const GLvoid *data);

#define glCompressedTexImage2D _gl_debug_error_glCompressedTexImage2D
void _gl_debug_error_glCompressedTexImage2D(GLenum target,
                                            GLint level,
                                            GLenum internalformat,
                                            GLsizei width,
                                            GLsizei height,
                                            GLint border,
                                            GLsizei imageSize,
                                            const GLvoid *data);

#define glCompressedTexImage1D _gl_debug_error_glCompressedTexImage1D
void _gl_debug_error_glCompressedTexImage1D(GLenum target,
                                            GLint level,
                                            GLenum internalformat,
                                            GLsizei width,
                                            GLint border,
                                            GLsizei imageSize,
                                            const GLvoid *data);

#define glCompressedTexSubImage3D _gl_debug_error_glCompressedTexSubImage3D
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
                                               const GLvoid *data);

#define glCompressedTexSubImage2D _gl_debug_error_glCompressedTexSubImage2D
void _gl_debug_error_glCompressedTexSubImage2D(GLenum target,
                                               GLint level,
                                               GLint xoffset,
                                               GLint yoffset,
                                               GLsizei width,
                                               GLsizei height,
                                               GLenum format,
                                               GLsizei imageSize,
                                               const GLvoid *data);

#define glCompressedTexSubImage1D _gl_debug_error_glCompressedTexSubImage1D
void _gl_debug_error_glCompressedTexSubImage1D(GLenum target,
                                               GLint level,
                                               GLint xoffset,
                                               GLsizei width,
                                               GLenum format,
                                               GLsizei imageSize,
                                               const GLvoid *data);

#define glGetCompressedTexImage _gl_debug_error_glGetCompressedTexImage
void _gl_debug_error_glGetCompressedTexImage(GLenum target, GLint level, GLvoid *img);

#define glBlendFuncSeparate _gl_debug_error_glBlendFuncSeparate
void _gl_debug_error_glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);

#define glMultiDrawArrays _gl_debug_error_glMultiDrawArrays
void _gl_debug_error_glMultiDrawArrays(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);

#define glMultiDrawElements _gl_debug_error_glMultiDrawElements
void _gl_debug_error_glMultiDrawElements(GLenum mode,
                                         const GLsizei *count,
                                         GLenum type,
                                         const GLvoid *const *indices,
                                         GLsizei primcount);

#define glPointParameterf _gl_debug_error_glPointParameterf
void _gl_debug_error_glPointParameterf(GLenum pname, GLfloat param);

#define glPointParameterfv _gl_debug_error_glPointParameterfv
void _gl_debug_error_glPointParameterfv(GLenum pname, const GLfloat *params);

#define glPointParameteri _gl_debug_error_glPointParameteri
void _gl_debug_error_glPointParameteri(GLenum pname, GLint param);

#define glPointParameteriv _gl_debug_error_glPointParameteriv
void _gl_debug_error_glPointParameteriv(GLenum pname, const GLint *params);

#define glGenQueries _gl_debug_error_glGenQueries
void _gl_debug_error_glGenQueries(GLsizei n, GLuint *ids);

#define glDeleteQueries _gl_debug_error_glDeleteQueries
void _gl_debug_error_glDeleteQueries(GLsizei n, const GLuint *ids);

#define glIsQuery _gl_debug_error_glIsQuery
GLboolean _gl_debug_error_glIsQuery(GLuint id);

#define glBeginQuery _gl_debug_error_glBeginQuery
void _gl_debug_error_glBeginQuery(GLenum target, GLuint id);

#define glEndQuery _gl_debug_error_glEndQuery
void _gl_debug_error_glEndQuery(GLenum target);

#define glGetQueryiv _gl_debug_error_glGetQueryiv
void _gl_debug_error_glGetQueryiv(GLenum target, GLenum pname, GLint *params);

#define glGetQueryObjectiv _gl_debug_error_glGetQueryObjectiv
void _gl_debug_error_glGetQueryObjectiv(GLuint id, GLenum pname, GLint *params);

#define glGetQueryObjectuiv _gl_debug_error_glGetQueryObjectuiv
void _gl_debug_error_glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint *params);

#define glBindBuffer _gl_debug_error_glBindBuffer
void _gl_debug_error_glBindBuffer(GLenum target, GLuint buffer);

#define glDeleteBuffers _gl_debug_error_glDeleteBuffers
void _gl_debug_error_glDeleteBuffers(GLsizei n, const GLuint *buffers);

#define glGenBuffers _gl_debug_error_glGenBuffers
void _gl_debug_error_glGenBuffers(GLsizei n, GLuint *buffers);

#define glIsBuffer _gl_debug_error_glIsBuffer
GLboolean _gl_debug_error_glIsBuffer(GLuint buffer);

#define glBufferData _gl_debug_error_glBufferData
void _gl_debug_error_glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);

#define glBufferSubData _gl_debug_error_glBufferSubData
void _gl_debug_error_glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);

#define glGetBufferSubData _gl_debug_error_glGetBufferSubData
void _gl_debug_error_glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data);

#define glMapBuffer _gl_debug_error_glMapBuffer
GLvoid *_gl_debug_error_glMapBuffer(GLenum target, GLenum access);

#define glUnmapBuffer _gl_debug_error_glUnmapBuffer
GLboolean _gl_debug_error_glUnmapBuffer(GLenum target);

#define glGetBufferParameteriv _gl_debug_error_glGetBufferParameteriv
void _gl_debug_error_glGetBufferParameteriv(GLenum target, GLenum pname, GLint *params);

#define glGetBufferPointerv _gl_debug_error_glGetBufferPointerv
void _gl_debug_error_glGetBufferPointerv(GLenum target, GLenum pname, GLvoid **params);

#define glBlendEquationSeparate _gl_debug_error_glBlendEquationSeparate
void _gl_debug_error_glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);

#define glDrawBuffers _gl_debug_error_glDrawBuffers
void _gl_debug_error_glDrawBuffers(GLsizei n, const GLenum *bufs);

#define glStencilOpSeparate _gl_debug_error_glStencilOpSeparate
void _gl_debug_error_glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);

#define glStencilFuncSeparate _gl_debug_error_glStencilFuncSeparate
void _gl_debug_error_glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);

#define glStencilMaskSeparate _gl_debug_error_glStencilMaskSeparate
void _gl_debug_error_glStencilMaskSeparate(GLenum face, GLuint mask);

#define glAttachShader _gl_debug_error_glAttachShader
void _gl_debug_error_glAttachShader(GLuint program, GLuint shader);

#define glBindAttribLocation _gl_debug_error_glBindAttribLocation
void _gl_debug_error_glBindAttribLocation(GLuint program, GLuint index, const GLchar *name);

#define glCompileShader _gl_debug_error_glCompileShader
void _gl_debug_error_glCompileShader(GLuint shader);

#define glCreateProgram _gl_debug_error_glCreateProgram
GLuint _gl_debug_error_glCreateProgram(void);

#define glCreateShader _gl_debug_error_glCreateShader
GLuint _gl_debug_error_glCreateShader(GLenum type);

#define glDeleteProgram _gl_debug_error_glDeleteProgram
void _gl_debug_error_glDeleteProgram(GLuint program);

#define glDeleteShader _gl_debug_error_glDeleteShader
void _gl_debug_error_glDeleteShader(GLuint shader);

#define glDetachShader _gl_debug_error_glDetachShader
void _gl_debug_error_glDetachShader(GLuint program, GLuint shader);

#define glDisableVertexAttribArray _gl_debug_error_glDisableVertexAttribArray
void _gl_debug_error_glDisableVertexAttribArray(GLuint index);

#define glEnableVertexAttribArray _gl_debug_error_glEnableVertexAttribArray
void _gl_debug_error_glEnableVertexAttribArray(GLuint index);

#define glGetActiveAttrib _gl_debug_error_glGetActiveAttrib
void _gl_debug_error_glGetActiveAttrib(GLuint program,
                                       GLuint index,
                                       GLsizei bufSize,
                                       GLsizei *length,
                                       GLint *size,
                                       GLenum *type,
                                       GLchar *name);

#define glGetActiveUniform _gl_debug_error_glGetActiveUniform
void _gl_debug_error_glGetActiveUniform(GLuint program,
                                        GLuint index,
                                        GLsizei bufSize,
                                        GLsizei *length,
                                        GLint *size,
                                        GLenum *type,
                                        GLchar *name);

#define glGetAttachedShaders _gl_debug_error_glGetAttachedShaders
void _gl_debug_error_glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);

#define glGetAttribLocation _gl_debug_error_glGetAttribLocation
GLint _gl_debug_error_glGetAttribLocation(GLuint program, const GLchar *name);

#define glGetProgramiv _gl_debug_error_glGetProgramiv
void _gl_debug_error_glGetProgramiv(GLuint program, GLenum pname, GLint *params);

#define glGetProgramInfoLog _gl_debug_error_glGetProgramInfoLog
void _gl_debug_error_glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);

#define glGetShaderiv _gl_debug_error_glGetShaderiv
void _gl_debug_error_glGetShaderiv(GLuint shader, GLenum pname, GLint *params);

#define glGetShaderInfoLog _gl_debug_error_glGetShaderInfoLog
void _gl_debug_error_glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);

#define glGetShaderSource _gl_debug_error_glGetShaderSource
void _gl_debug_error_glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);

#define glGetUniformLocation _gl_debug_error_glGetUniformLocation
GLint _gl_debug_error_glGetUniformLocation(GLuint program, const GLchar *name);

#define glGetUniformfv _gl_debug_error_glGetUniformfv
void _gl_debug_error_glGetUniformfv(GLuint program, GLint location, GLfloat *params);

#define glGetUniformiv _gl_debug_error_glGetUniformiv
void _gl_debug_error_glGetUniformiv(GLuint program, GLint location, GLint *params);

#define glGetVertexAttribdv _gl_debug_error_glGetVertexAttribdv
void _gl_debug_error_glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble *params);

#define glGetVertexAttribfv _gl_debug_error_glGetVertexAttribfv
void _gl_debug_error_glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params);

#define glGetVertexAttribiv _gl_debug_error_glGetVertexAttribiv
void _gl_debug_error_glGetVertexAttribiv(GLuint index, GLenum pname, GLint *params);

#define glGetVertexAttribPointerv _gl_debug_error_glGetVertexAttribPointerv
void _gl_debug_error_glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid **pointer);

#define glIsProgram _gl_debug_error_glIsProgram
GLboolean _gl_debug_error_glIsProgram(GLuint program);

#define glIsShader _gl_debug_error_glIsShader
GLboolean _gl_debug_error_glIsShader(GLuint shader);

#define glLinkProgram _gl_debug_error_glLinkProgram
void _gl_debug_error_glLinkProgram(GLuint program);

#define glShaderSource _gl_debug_error_glShaderSource
void _gl_debug_error_glShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length);

#define glUseProgram _gl_debug_error_glUseProgram
void _gl_debug_error_glUseProgram(GLuint program);

#define glUniform1f _gl_debug_error_glUniform1f
void _gl_debug_error_glUniform1f(GLint location, GLfloat v0);

#define glUniform2f _gl_debug_error_glUniform2f
void _gl_debug_error_glUniform2f(GLint location, GLfloat v0, GLfloat v1);

#define glUniform3f _gl_debug_error_glUniform3f
void _gl_debug_error_glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);

#define glUniform4f _gl_debug_error_glUniform4f
void _gl_debug_error_glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

#define glUniform1i _gl_debug_error_glUniform1i
void _gl_debug_error_glUniform1i(GLint location, GLint v0);

#define glUniform2i _gl_debug_error_glUniform2i
void _gl_debug_error_glUniform2i(GLint location, GLint v0, GLint v1);

#define glUniform3i _gl_debug_error_glUniform3i
void _gl_debug_error_glUniform3i(GLint location, GLint v0, GLint v1, GLint v2);

#define glUniform4i _gl_debug_error_glUniform4i
void _gl_debug_error_glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);

#define glUniform1fv _gl_debug_error_glUniform1fv
void _gl_debug_error_glUniform1fv(GLint location, GLsizei count, const GLfloat *value);

#define glUniform2fv _gl_debug_error_glUniform2fv
void _gl_debug_error_glUniform2fv(GLint location, GLsizei count, const GLfloat *value);

#define glUniform3fv _gl_debug_error_glUniform3fv
void _gl_debug_error_glUniform3fv(GLint location, GLsizei count, const GLfloat *value);

#define glUniform4fv _gl_debug_error_glUniform4fv
void _gl_debug_error_glUniform4fv(GLint location, GLsizei count, const GLfloat *value);

#define glUniform1iv _gl_debug_error_glUniform1iv
void _gl_debug_error_glUniform1iv(GLint location, GLsizei count, const GLint *value);

#define glUniform2iv _gl_debug_error_glUniform2iv
void _gl_debug_error_glUniform2iv(GLint location, GLsizei count, const GLint *value);

#define glUniform3iv _gl_debug_error_glUniform3iv
void _gl_debug_error_glUniform3iv(GLint location, GLsizei count, const GLint *value);

#define glUniform4iv _gl_debug_error_glUniform4iv
void _gl_debug_error_glUniform4iv(GLint location, GLsizei count, const GLint *value);

#define glUniformMatrix2fv _gl_debug_error_glUniformMatrix2fv
void _gl_debug_error_glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

#define glUniformMatrix3fv _gl_debug_error_glUniformMatrix3fv
void _gl_debug_error_glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

#define glUniformMatrix4fv _gl_debug_error_glUniformMatrix4fv
void _gl_debug_error_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

#define glValidateProgram _gl_debug_error_glValidateProgram
void _gl_debug_error_glValidateProgram(GLuint program);

#define glVertexAttrib1d _gl_debug_error_glVertexAttrib1d
void _gl_debug_error_glVertexAttrib1d(GLuint index, GLdouble x);

#define glVertexAttrib1dv _gl_debug_error_glVertexAttrib1dv
void _gl_debug_error_glVertexAttrib1dv(GLuint index, const GLdouble *v);

#define glVertexAttrib1f _gl_debug_error_glVertexAttrib1f
void _gl_debug_error_glVertexAttrib1f(GLuint index, GLfloat x);

#define glVertexAttrib1fv _gl_debug_error_glVertexAttrib1fv
void _gl_debug_error_glVertexAttrib1fv(GLuint index, const GLfloat *v);

#define glVertexAttrib1s _gl_debug_error_glVertexAttrib1s
void _gl_debug_error_glVertexAttrib1s(GLuint index, GLshort x);

#define glVertexAttrib1sv _gl_debug_error_glVertexAttrib1sv
void _gl_debug_error_glVertexAttrib1sv(GLuint index, const GLshort *v);

#define glVertexAttrib2d _gl_debug_error_glVertexAttrib2d
void _gl_debug_error_glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y);

#define glVertexAttrib2dv _gl_debug_error_glVertexAttrib2dv
void _gl_debug_error_glVertexAttrib2dv(GLuint index, const GLdouble *v);

#define glVertexAttrib2f _gl_debug_error_glVertexAttrib2f
void _gl_debug_error_glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y);

#define glVertexAttrib2fv _gl_debug_error_glVertexAttrib2fv
void _gl_debug_error_glVertexAttrib2fv(GLuint index, const GLfloat *v);

#define glVertexAttrib2s _gl_debug_error_glVertexAttrib2s
void _gl_debug_error_glVertexAttrib2s(GLuint index, GLshort x, GLshort y);

#define glVertexAttrib2sv _gl_debug_error_glVertexAttrib2sv
void _gl_debug_error_glVertexAttrib2sv(GLuint index, const GLshort *v);

#define glVertexAttrib3d _gl_debug_error_glVertexAttrib3d
void _gl_debug_error_glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z);

#define glVertexAttrib3dv _gl_debug_error_glVertexAttrib3dv
void _gl_debug_error_glVertexAttrib3dv(GLuint index, const GLdouble *v);

#define glVertexAttrib3f _gl_debug_error_glVertexAttrib3f
void _gl_debug_error_glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);

#define glVertexAttrib3fv _gl_debug_error_glVertexAttrib3fv
void _gl_debug_error_glVertexAttrib3fv(GLuint index, const GLfloat *v);

#define glVertexAttrib3s _gl_debug_error_glVertexAttrib3s
void _gl_debug_error_glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z);

#define glVertexAttrib3sv _gl_debug_error_glVertexAttrib3sv
void _gl_debug_error_glVertexAttrib3sv(GLuint index, const GLshort *v);

#define glVertexAttrib4Nbv _gl_debug_error_glVertexAttrib4Nbv
void _gl_debug_error_glVertexAttrib4Nbv(GLuint index, const GLbyte *v);

#define glVertexAttrib4Niv _gl_debug_error_glVertexAttrib4Niv
void _gl_debug_error_glVertexAttrib4Niv(GLuint index, const GLint *v);

#define glVertexAttrib4Nsv _gl_debug_error_glVertexAttrib4Nsv
void _gl_debug_error_glVertexAttrib4Nsv(GLuint index, const GLshort *v);

#define glVertexAttrib4Nub _gl_debug_error_glVertexAttrib4Nub
void _gl_debug_error_glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);

#define glVertexAttrib4Nubv _gl_debug_error_glVertexAttrib4Nubv
void _gl_debug_error_glVertexAttrib4Nubv(GLuint index, const GLubyte *v);

#define glVertexAttrib4Nuiv _gl_debug_error_glVertexAttrib4Nuiv
void _gl_debug_error_glVertexAttrib4Nuiv(GLuint index, const GLuint *v);

#define glVertexAttrib4Nusv _gl_debug_error_glVertexAttrib4Nusv
void _gl_debug_error_glVertexAttrib4Nusv(GLuint index, const GLushort *v);

#define glVertexAttrib4bv _gl_debug_error_glVertexAttrib4bv
void _gl_debug_error_glVertexAttrib4bv(GLuint index, const GLbyte *v);

#define glVertexAttrib4d _gl_debug_error_glVertexAttrib4d
void _gl_debug_error_glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);

#define glVertexAttrib4dv _gl_debug_error_glVertexAttrib4dv
void _gl_debug_error_glVertexAttrib4dv(GLuint index, const GLdouble *v);

#define glVertexAttrib4f _gl_debug_error_glVertexAttrib4f
void _gl_debug_error_glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

#define glVertexAttrib4fv _gl_debug_error_glVertexAttrib4fv
void _gl_debug_error_glVertexAttrib4fv(GLuint index, const GLfloat *v);

#define glVertexAttrib4iv _gl_debug_error_glVertexAttrib4iv
void _gl_debug_error_glVertexAttrib4iv(GLuint index, const GLint *v);

#define glVertexAttrib4s _gl_debug_error_glVertexAttrib4s
void _gl_debug_error_glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);

#define glVertexAttrib4sv _gl_debug_error_glVertexAttrib4sv
void _gl_debug_error_glVertexAttrib4sv(GLuint index, const GLshort *v);

#define glVertexAttrib4ubv _gl_debug_error_glVertexAttrib4ubv
void _gl_debug_error_glVertexAttrib4ubv(GLuint index, const GLubyte *v);

#define glVertexAttrib4uiv _gl_debug_error_glVertexAttrib4uiv
void _gl_debug_error_glVertexAttrib4uiv(GLuint index, const GLuint *v);

#define glVertexAttrib4usv _gl_debug_error_glVertexAttrib4usv
void _gl_debug_error_glVertexAttrib4usv(GLuint index, const GLushort *v);

#define glVertexAttribPointer _gl_debug_error_glVertexAttribPointer
void _gl_debug_error_glVertexAttribPointer(GLuint index,
                                           GLint size,
                                           GLenum type,
                                           GLboolean normalized,
                                           GLsizei stride,
                                           const GLvoid *pointer);

#define glUniformMatrix2x3fv _gl_debug_error_glUniformMatrix2x3fv
void _gl_debug_error_glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

#define glUniformMatrix3x2fv _gl_debug_error_glUniformMatrix3x2fv
void _gl_debug_error_glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

#define glUniformMatrix2x4fv _gl_debug_error_glUniformMatrix2x4fv
void _gl_debug_error_glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

#define glUniformMatrix4x2fv _gl_debug_error_glUniformMatrix4x2fv
void _gl_debug_error_glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

#define glUniformMatrix3x4fv _gl_debug_error_glUniformMatrix3x4fv
void _gl_debug_error_glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

#define glUniformMatrix4x3fv _gl_debug_error_glUniformMatrix4x3fv
void _gl_debug_error_glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

#define glColorMaski _gl_debug_error_glColorMaski
void _gl_debug_error_glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);

#define glGetBooleani_v _gl_debug_error_glGetBooleani_v
void _gl_debug_error_glGetBooleani_v(GLenum target, GLuint index, GLboolean *data);

#define glGetIntegeri_v _gl_debug_error_glGetIntegeri_v
void _gl_debug_error_glGetIntegeri_v(GLenum target, GLuint index, GLint *data);

#define glEnablei _gl_debug_error_glEnablei
void _gl_debug_error_glEnablei(GLenum target, GLuint index);

#define glDisablei _gl_debug_error_glDisablei
void _gl_debug_error_glDisablei(GLenum target, GLuint index);

#define glIsEnabledi _gl_debug_error_glIsEnabledi
GLboolean _gl_debug_error_glIsEnabledi(GLenum target, GLuint index);

#define glBeginTransformFeedback _gl_debug_error_glBeginTransformFeedback
void _gl_debug_error_glBeginTransformFeedback(GLenum primitiveMode);

#define glEndTransformFeedback _gl_debug_error_glEndTransformFeedback
void _gl_debug_error_glEndTransformFeedback(void);

#define glBindBufferRange _gl_debug_error_glBindBufferRange
void _gl_debug_error_glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);

#define glBindBufferBase _gl_debug_error_glBindBufferBase
void _gl_debug_error_glBindBufferBase(GLenum target, GLuint index, GLuint buffer);

#define glTransformFeedbackVaryings _gl_debug_error_glTransformFeedbackVaryings
void _gl_debug_error_glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const *varyings, GLenum bufferMode);

#define glGetTransformFeedbackVarying _gl_debug_error_glGetTransformFeedbackVarying
void _gl_debug_error_glGetTransformFeedbackVarying(GLuint program,
                                                   GLuint index,
                                                   GLsizei bufSize,
                                                   GLsizei *length,
                                                   GLsizei *size,
                                                   GLenum *type,
                                                   GLchar *name);

#define glClampColor _gl_debug_error_glClampColor
void _gl_debug_error_glClampColor(GLenum target, GLenum clamp);

#define glBeginConditionalRender _gl_debug_error_glBeginConditionalRender
void _gl_debug_error_glBeginConditionalRender(GLuint id, GLenum mode);

#define glEndConditionalRender _gl_debug_error_glEndConditionalRender
void _gl_debug_error_glEndConditionalRender(void);

#define glVertexAttribIPointer _gl_debug_error_glVertexAttribIPointer
void _gl_debug_error_glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

#define glGetVertexAttribIiv _gl_debug_error_glGetVertexAttribIiv
void _gl_debug_error_glGetVertexAttribIiv(GLuint index, GLenum pname, GLint *params);

#define glGetVertexAttribIuiv _gl_debug_error_glGetVertexAttribIuiv
void _gl_debug_error_glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params);

#define glVertexAttribI1i _gl_debug_error_glVertexAttribI1i
void _gl_debug_error_glVertexAttribI1i(GLuint index, GLint x);

#define glVertexAttribI2i _gl_debug_error_glVertexAttribI2i
void _gl_debug_error_glVertexAttribI2i(GLuint index, GLint x, GLint y);

#define glVertexAttribI3i _gl_debug_error_glVertexAttribI3i
void _gl_debug_error_glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z);

#define glVertexAttribI4i _gl_debug_error_glVertexAttribI4i
void _gl_debug_error_glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w);

#define glVertexAttribI1ui _gl_debug_error_glVertexAttribI1ui
void _gl_debug_error_glVertexAttribI1ui(GLuint index, GLuint x);

#define glVertexAttribI2ui _gl_debug_error_glVertexAttribI2ui
void _gl_debug_error_glVertexAttribI2ui(GLuint index, GLuint x, GLuint y);

#define glVertexAttribI3ui _gl_debug_error_glVertexAttribI3ui
void _gl_debug_error_glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z);

#define glVertexAttribI4ui _gl_debug_error_glVertexAttribI4ui
void _gl_debug_error_glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);

#define glVertexAttribI1iv _gl_debug_error_glVertexAttribI1iv
void _gl_debug_error_glVertexAttribI1iv(GLuint index, const GLint *v);

#define glVertexAttribI2iv _gl_debug_error_glVertexAttribI2iv
void _gl_debug_error_glVertexAttribI2iv(GLuint index, const GLint *v);

#define glVertexAttribI3iv _gl_debug_error_glVertexAttribI3iv
void _gl_debug_error_glVertexAttribI3iv(GLuint index, const GLint *v);

#define glVertexAttribI4iv _gl_debug_error_glVertexAttribI4iv
void _gl_debug_error_glVertexAttribI4iv(GLuint index, const GLint *v);

#define glVertexAttribI1uiv _gl_debug_error_glVertexAttribI1uiv
void _gl_debug_error_glVertexAttribI1uiv(GLuint index, const GLuint *v);

#define glVertexAttribI2uiv _gl_debug_error_glVertexAttribI2uiv
void _gl_debug_error_glVertexAttribI2uiv(GLuint index, const GLuint *v);

#define glVertexAttribI3uiv _gl_debug_error_glVertexAttribI3uiv
void _gl_debug_error_glVertexAttribI3uiv(GLuint index, const GLuint *v);

#define glVertexAttribI4uiv _gl_debug_error_glVertexAttribI4uiv
void _gl_debug_error_glVertexAttribI4uiv(GLuint index, const GLuint *v);

#define glVertexAttribI4bv _gl_debug_error_glVertexAttribI4bv
void _gl_debug_error_glVertexAttribI4bv(GLuint index, const GLbyte *v);

#define glVertexAttribI4sv _gl_debug_error_glVertexAttribI4sv
void _gl_debug_error_glVertexAttribI4sv(GLuint index, const GLshort *v);

#define glVertexAttribI4ubv _gl_debug_error_glVertexAttribI4ubv
void _gl_debug_error_glVertexAttribI4ubv(GLuint index, const GLubyte *v);

#define glVertexAttribI4usv _gl_debug_error_glVertexAttribI4usv
void _gl_debug_error_glVertexAttribI4usv(GLuint index, const GLushort *v);

#define glGetUniformuiv _gl_debug_error_glGetUniformuiv
void _gl_debug_error_glGetUniformuiv(GLuint program, GLint location, GLuint *params);

#define glBindFragDataLocation _gl_debug_error_glBindFragDataLocation
void _gl_debug_error_glBindFragDataLocation(GLuint program, GLuint color, const GLchar *name);

#define glGetFragDataLocation _gl_debug_error_glGetFragDataLocation
GLint _gl_debug_error_glGetFragDataLocation(GLuint program, const GLchar *name);

#define glUniform1ui _gl_debug_error_glUniform1ui
void _gl_debug_error_glUniform1ui(GLint location, GLuint v0);

#define glUniform2ui _gl_debug_error_glUniform2ui
void _gl_debug_error_glUniform2ui(GLint location, GLuint v0, GLuint v1);

#define glUniform3ui _gl_debug_error_glUniform3ui
void _gl_debug_error_glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2);

#define glUniform4ui _gl_debug_error_glUniform4ui
void _gl_debug_error_glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);

#define glUniform1uiv _gl_debug_error_glUniform1uiv
void _gl_debug_error_glUniform1uiv(GLint location, GLsizei count, const GLuint *value);

#define glUniform2uiv _gl_debug_error_glUniform2uiv
void _gl_debug_error_glUniform2uiv(GLint location, GLsizei count, const GLuint *value);

#define glUniform3uiv _gl_debug_error_glUniform3uiv
void _gl_debug_error_glUniform3uiv(GLint location, GLsizei count, const GLuint *value);

#define glUniform4uiv _gl_debug_error_glUniform4uiv
void _gl_debug_error_glUniform4uiv(GLint location, GLsizei count, const GLuint *value);

#define glTexParameterIiv _gl_debug_error_glTexParameterIiv
void _gl_debug_error_glTexParameterIiv(GLenum target, GLenum pname, const GLint *params);

#define glTexParameterIuiv _gl_debug_error_glTexParameterIuiv
void _gl_debug_error_glTexParameterIuiv(GLenum target, GLenum pname, const GLuint *params);

#define glGetTexParameterIiv _gl_debug_error_glGetTexParameterIiv
void _gl_debug_error_glGetTexParameterIiv(GLenum target, GLenum pname, GLint *params);

#define glGetTexParameterIuiv _gl_debug_error_glGetTexParameterIuiv
void _gl_debug_error_glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint *params);

#define glClearBufferiv _gl_debug_error_glClearBufferiv
void _gl_debug_error_glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value);

#define glClearBufferuiv _gl_debug_error_glClearBufferuiv
void _gl_debug_error_glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value);

#define glClearBufferfv _gl_debug_error_glClearBufferfv
void _gl_debug_error_glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value);

#define glClearBufferfi _gl_debug_error_glClearBufferfi
void _gl_debug_error_glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);

#define glGetStringi _gl_debug_error_glGetStringi
const GLubyte *_gl_debug_error_glGetStringi(GLenum name, GLuint index);

#define glDrawArraysInstanced _gl_debug_error_glDrawArraysInstanced
void _gl_debug_error_glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei primcount);

#define glDrawElementsInstanced _gl_debug_error_glDrawElementsInstanced
void _gl_debug_error_glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount);

#define glTexBuffer _gl_debug_error_glTexBuffer
void _gl_debug_error_glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer);

#define glPrimitiveRestartIndex _gl_debug_error_glPrimitiveRestartIndex
void _gl_debug_error_glPrimitiveRestartIndex(GLuint index);

#define glGetInteger64i_v _gl_debug_error_glGetInteger64i_v
void _gl_debug_error_glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data);

#define glGetBufferParameteri64v _gl_debug_error_glGetBufferParameteri64v
void _gl_debug_error_glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params);

#define glFramebufferTexture _gl_debug_error_glFramebufferTexture
void _gl_debug_error_glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level);

#define glIsRenderbuffer _gl_debug_error_glIsRenderbuffer
GLboolean _gl_debug_error_glIsRenderbuffer(GLuint renderbuffer);

#define glBindRenderbuffer _gl_debug_error_glBindRenderbuffer
void _gl_debug_error_glBindRenderbuffer(GLenum target, GLuint renderbuffer);

#define glDeleteRenderbuffers _gl_debug_error_glDeleteRenderbuffers
void _gl_debug_error_glDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers);

#define glGenRenderbuffers _gl_debug_error_glGenRenderbuffers
void _gl_debug_error_glGenRenderbuffers(GLsizei n, GLuint *renderbuffers);

#define glRenderbufferStorage _gl_debug_error_glRenderbufferStorage
void _gl_debug_error_glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);

#define glGetRenderbufferParameteriv _gl_debug_error_glGetRenderbufferParameteriv
void _gl_debug_error_glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params);

#define glIsFramebuffer _gl_debug_error_glIsFramebuffer
GLboolean _gl_debug_error_glIsFramebuffer(GLuint framebuffer);

#define glBindFramebuffer _gl_debug_error_glBindFramebuffer
void _gl_debug_error_glBindFramebuffer(GLenum target, GLuint framebuffer);

#define glDeleteFramebuffers _gl_debug_error_glDeleteFramebuffers
void _gl_debug_error_glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers);

#define glGenFramebuffers _gl_debug_error_glGenFramebuffers
void _gl_debug_error_glGenFramebuffers(GLsizei n, GLuint *framebuffers);

#define glCheckFramebufferStatus _gl_debug_error_glCheckFramebufferStatus
GLenum _gl_debug_error_glCheckFramebufferStatus(GLenum target);

#define glFramebufferTexture1D _gl_debug_error_glFramebufferTexture1D
void _gl_debug_error_glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);

#define glFramebufferTexture2D _gl_debug_error_glFramebufferTexture2D
void _gl_debug_error_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);

#define glFramebufferTexture3D _gl_debug_error_glFramebufferTexture3D
void _gl_debug_error_glFramebufferTexture3D(GLenum target,
                                            GLenum attachment,
                                            GLenum textarget,
                                            GLuint texture,
                                            GLint level,
                                            GLint zoffset);

#define glFramebufferRenderbuffer _gl_debug_error_glFramebufferRenderbuffer
void _gl_debug_error_glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);

#define glGetFramebufferAttachmentParameteriv _gl_debug_error_glGetFramebufferAttachmentParameteriv
void _gl_debug_error_glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params);

#define glGenerateMipmap _gl_debug_error_glGenerateMipmap
void _gl_debug_error_glGenerateMipmap(GLenum target);

#define glBlitFramebuffer _gl_debug_error_glBlitFramebuffer
void _gl_debug_error_glBlitFramebuffer(GLint srcX0,
                                       GLint srcY0,
                                       GLint srcX1,
                                       GLint srcY1,
                                       GLint dstX0,
                                       GLint dstY0,
                                       GLint dstX1,
                                       GLint dstY1,
                                       GLbitfield mask,
                                       GLenum filter);

#define glRenderbufferStorageMultisample _gl_debug_error_glRenderbufferStorageMultisample
void _gl_debug_error_glRenderbufferStorageMultisample(GLenum target,
                                                      GLsizei samples,
                                                      GLenum internalformat,
                                                      GLsizei width,
                                                      GLsizei height);

#define glFramebufferTextureLayer _gl_debug_error_glFramebufferTextureLayer
void _gl_debug_error_glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);

#define glMapBufferRange _gl_debug_error_glMapBufferRange
GLvoid *_gl_debug_error_glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);

#define glFlushMappedBufferRange _gl_debug_error_glFlushMappedBufferRange
void _gl_debug_error_glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length);

#define glBindVertexArray _gl_debug_error_glBindVertexArray
void _gl_debug_error_glBindVertexArray(GLuint array);

#define glDeleteVertexArrays _gl_debug_error_glDeleteVertexArrays
void _gl_debug_error_glDeleteVertexArrays(GLsizei n, const GLuint *arrays);

#define glGenVertexArrays _gl_debug_error_glGenVertexArrays
void _gl_debug_error_glGenVertexArrays(GLsizei n, GLuint *arrays);

#define glIsVertexArray _gl_debug_error_glIsVertexArray
GLboolean _gl_debug_error_glIsVertexArray(GLuint array);

#define glGetUniformIndices _gl_debug_error_glGetUniformIndices
void _gl_debug_error_glGetUniformIndices(GLuint program,
                                         GLsizei uniformCount,
                                         const GLchar *const *uniformNames,
                                         GLuint *uniformIndices);

#define glGetActiveUniformsiv _gl_debug_error_glGetActiveUniformsiv
void _gl_debug_error_glGetActiveUniformsiv(GLuint program,
                                           GLsizei uniformCount,
                                           const GLuint *uniformIndices,
                                           GLenum pname,
                                           GLint *params);

#define glGetActiveUniformName _gl_debug_error_glGetActiveUniformName
void _gl_debug_error_glGetActiveUniformName(GLuint program,
                                            GLuint uniformIndex,
                                            GLsizei bufSize,
                                            GLsizei *length,
                                            GLchar *uniformName);

#define glGetUniformBlockIndex _gl_debug_error_glGetUniformBlockIndex
GLuint _gl_debug_error_glGetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName);

#define glGetActiveUniformBlockiv _gl_debug_error_glGetActiveUniformBlockiv
void _gl_debug_error_glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);

#define glGetActiveUniformBlockName _gl_debug_error_glGetActiveUniformBlockName
void _gl_debug_error_glGetActiveUniformBlockName(GLuint program,
                                                 GLuint uniformBlockIndex,
                                                 GLsizei bufSize,
                                                 GLsizei *length,
                                                 GLchar *uniformBlockName);

#define glUniformBlockBinding _gl_debug_error_glUniformBlockBinding
void _gl_debug_error_glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);

#define glCopyBufferSubData _gl_debug_error_glCopyBufferSubData
void _gl_debug_error_glCopyBufferSubData(GLenum readTarget,
                                         GLenum writeTarget,
                                         GLintptr readOffset,
                                         GLintptr writeOffset,
                                         GLsizeiptr size);

#define glDrawElementsBaseVertex _gl_debug_error_glDrawElementsBaseVertex
void _gl_debug_error_glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex);

#define glDrawRangeElementsBaseVertex _gl_debug_error_glDrawRangeElementsBaseVertex
void _gl_debug_error_glDrawRangeElementsBaseVertex(GLenum mode,
                                                   GLuint start,
                                                   GLuint end,
                                                   GLsizei count,
                                                   GLenum type,
                                                   const GLvoid *indices,
                                                   GLint basevertex);

#define glDrawElementsInstancedBaseVertex _gl_debug_error_glDrawElementsInstancedBaseVertex
void _gl_debug_error_glDrawElementsInstancedBaseVertex(GLenum mode,
                                                       GLsizei count,
                                                       GLenum type,
                                                       const GLvoid *indices,
                                                       GLsizei primcount,
                                                       GLint basevertex);

#define glMultiDrawElementsBaseVertex _gl_debug_error_glMultiDrawElementsBaseVertex
void _gl_debug_error_glMultiDrawElementsBaseVertex(GLenum mode,
                                                   const GLsizei *count,
                                                   GLenum type,
                                                   const void *const *indices,
                                                   GLsizei primcount,
                                                   const GLint *basevertex);

#define glProvokingVertex _gl_debug_error_glProvokingVertex
void _gl_debug_error_glProvokingVertex(GLenum mode);

#define glFenceSync _gl_debug_error_glFenceSync
GLsync _gl_debug_error_glFenceSync(GLenum condition, GLbitfield flags);

#define glIsSync _gl_debug_error_glIsSync
GLboolean _gl_debug_error_glIsSync(GLsync sync);

#define glDeleteSync _gl_debug_error_glDeleteSync
void _gl_debug_error_glDeleteSync(GLsync sync);

#define glClientWaitSync _gl_debug_error_glClientWaitSync
GLenum _gl_debug_error_glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout);

#define glWaitSync _gl_debug_error_glWaitSync
void _gl_debug_error_glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout);

#define glGetInteger64v _gl_debug_error_glGetInteger64v
void _gl_debug_error_glGetInteger64v(GLenum pname, GLint64 *params);

#define glGetSynciv _gl_debug_error_glGetSynciv
void _gl_debug_error_glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);

#define glTexImage2DMultisample _gl_debug_error_glTexImage2DMultisample
void _gl_debug_error_glTexImage2DMultisample(GLenum target,
                                             GLsizei samples,
                                             GLint internalformat,
                                             GLsizei width,
                                             GLsizei height,
                                             GLboolean fixedsamplelocations);

#define glTexImage3DMultisample _gl_debug_error_glTexImage3DMultisample
void _gl_debug_error_glTexImage3DMultisample(GLenum target,
                                             GLsizei samples,
                                             GLint internalformat,
                                             GLsizei width,
                                             GLsizei height,
                                             GLsizei depth,
                                             GLboolean fixedsamplelocations);

#define glGetMultisamplefv _gl_debug_error_glGetMultisamplefv
void _gl_debug_error_glGetMultisamplefv(GLenum pname, GLuint index, GLfloat *val);

#define glSampleMaski _gl_debug_error_glSampleMaski
void _gl_debug_error_glSampleMaski(GLuint index, GLbitfield mask);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // DEBUG_GL

#endif // GL_C

#endif // RPG_RD_GL_h
