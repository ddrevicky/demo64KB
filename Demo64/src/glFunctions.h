#pragma once

#include "Def.h"

typedef void (GLAPIENTRY *PFGLFINISH)();
typedef void (GLAPIENTRY *PFGLCLEARCOLOR)(float r, float g, float b, float a);	
typedef void (GLAPIENTRY *PFGLCLEAR)(unsigned int mask);
typedef void (GLAPIENTRY * PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint* arrays);
typedef void (GLAPIENTRY *PFNGLBINDVERTEXARRAY) (GLuint arr);
typedef void (GLAPIENTRY * PFNGLGENBUFFERS) (GLsizei n, GLuint* buffers);
typedef void (GLAPIENTRY * PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (GLAPIENTRY * PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void (GLAPIENTRY * PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef GLuint(GLAPIENTRY * PFNGLCREATESHADERPROC) (GLenum type);
typedef void (GLAPIENTRY * PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void (GLAPIENTRY * PFNGLCOMPILESHADERPROC) (GLuint shaderObj);
typedef GLuint(GLAPIENTRY * PFNGLCREATEPROGRAMPROC) (void);
typedef void (GLAPIENTRY * PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (GLAPIENTRY * PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (GLAPIENTRY * PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (GLAPIENTRY * PFNGLUSEPROGRAMPROC) (GLuint program);
typedef GLint(GLAPIENTRY * PFNGLGETUNIFORMLOCATIONARBPROC) (GLhandleARB programObj, const GLchar* name);
typedef void (GLAPIENTRY * PFNGLUNIFORM1FARBPROC) (GLint location, GLfloat v0);
typedef void (GLAPIENTRY * PFNGLUNIFORM2FARBPROC) (GLint location, GLfloat v0, GLfloat v1);
typedef void (GLAPIENTRY * PFNGLUNIFORM3FARBPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (GLAPIENTRY * PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void (GLAPIENTRY * PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);

typedef void (GLAPIENTRY * PFNGLDRAWELEMENTS) (GLenum mode, GLsizei count, GLenum type, const void *indices);

extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFGLCLEARCOLOR glClearColor;
extern PFGLCLEAR glClear;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLBINDVERTEXARRAY glBindVertexArray;
extern PFNGLGENBUFFERS glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocation;
extern PFNGLUNIFORM1FARBPROC glUniform1f;
extern PFNGLUNIFORM2FARBPROC glUniform2f;
extern PFNGLUNIFORM3FARBPROC glUniform3f;
extern PFNGLDRAWELEMENTS glDrawElements;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFGLFINISH glFinish;