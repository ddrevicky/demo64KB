#pragma once
#include "Def.h"

struct Mesh;
struct Vector3;
struct Matrix4x4;

struct Model
{
	uint32 vao;
	uint32 vbo;
	uint32 ibo;

	uint32 indexCount;
};

namespace Graphics
{
	void InitModel(Model *model, Mesh mesh);
	void InitScreenQuadModel(Model *model, Mesh mesh);
	GLuint CreateShader(GLenum shaderType, wchar_t *shaderSourceFile);
	GLuint CreateShaderFromString(GLenum shaderType, const char *shaderString);
	void CreateProgram(GLuint *program, wchar_t *vertexShaderFile, wchar_t *fragmentShaderFile);
	void CreateProgram(GLuint *program, const char* vertexShaderString, const char* fragmentShaderString);

	void ClearScreen();
	void UseProgram(GLuint program);
	void RenderModel(Model *model);
	void SetUniform1f(GLuint program, float value, GLchar *uniformName);
	void SetUniform2f(GLuint program, float v1, float v2, GLchar *uniformName);
	void SetUniform3f(GLuint program, Vector3 v, GLchar *uniformName);
}