#include "glFunctions.h"
#include "Graphics.h"
#include "UtilMesh.h"
#include "glFunctions.h"
#include "Maths.h"
#include "PlatformFunctions.h"
#include "Def.h"
#include <Windows.h>

extern FILEREAD(Win32FileRead);
extern FILERELEASE(Win32FileRelease);

void Graphics::InitScreenQuadModel(Model *model, Mesh mesh)
{
	glGenVertexArrays(1, &model->vao);
	glBindVertexArray(model->vao);

	glGenBuffers(1, &model->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertexCount*mesh.vertexStride, mesh.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &model->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indexCount * sizeof(uint32), mesh.indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, mesh.vertexStride, 0);

	model->indexCount = mesh.indexCount;

	UtilMesh::Free(mesh);
	glBindVertexArray(0);
}

GLuint Graphics::CreateShader(GLenum shaderType, wchar_t *shaderSourceFile)
{
	GLuint shader = glCreateShader(shaderType);

	File shaderFile = {};
	shaderFile = Win32FileRead(shaderSourceFile);
	glShaderSource(shader, 1, (GLchar **)&shaderFile.data, (GLint *)&shaderFile.size);
	glCompileShader(shader);
	Win32FileRelease(shaderFile);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		OutputDebugStringA(buffer);
	}

	return shader;
}

GLuint Graphics::CreateShaderFromString(GLenum shaderType, const char *shaderString)
{
	GLuint shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &shaderString, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		OutputDebugStringA(buffer);
	}

	return shader;
}

void Graphics::CreateProgram(GLuint *program, wchar_t *vertexShaderFile, wchar_t *fragmentShaderFile)
{
	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderFile);
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderFile);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	*program = shaderProgram;
}

void Graphics::CreateProgram(GLuint *program, const char* vertexShaderString, const char* fragmentShaderString)
{
	GLuint vertexShader = CreateShaderFromString(GL_VERTEX_SHADER, vertexShaderString);
	GLuint fragmentShader = CreateShaderFromString(GL_FRAGMENT_SHADER, fragmentShaderString);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	*program = shaderProgram;
}

void Graphics::ClearScreen()
{
	glClearColor(1, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::UseProgram(GLuint program)
{
	glUseProgram(program);
}

void Graphics::RenderModel(Model *model)
{
	glBindVertexArray(model->vao);
	glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Graphics::SetUniform1f(GLuint program, float value, GLchar *uniformName)
{
	glUseProgram(program);
	GLint floatUniform = glGetUniformLocation(program, uniformName);
	glUniform1f(floatUniform, value);
}

void Graphics::SetUniform2f(GLuint program, float v1, float v2, GLchar *uniformName)
{
	glUseProgram(program);
	GLint floatUniform = glGetUniformLocation(program, uniformName);
	glUniform2f(floatUniform, v1, v2);
}

void Graphics::SetUniform3f(GLuint program, Vector3 v, GLchar *uniformName)
{
	glUseProgram(program);
	GLint floatUniform = glGetUniformLocation(program, uniformName);
	glUniform3f(floatUniform, v.x, v.y, v.z);
}