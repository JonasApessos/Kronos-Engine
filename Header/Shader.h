#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

enum class ShaderCompilationType : GLuint
{
    VertexShader = 0,
    FragmentShader = 1
};

class Shader
{

public:
    GLuint ShaderProgID = 0;

    string sShaderFile;

    Shader(const GLchar* IncVertPath, const GLchar* IncFragPath);
    
    ~Shader();

    inline void Use();
    void CompileShader(GLuint& ShaderID, const GLchar* IncShaderCode, ShaderCompilationType InFShaderType);
    void CreateShaderProg(GLuint& IniVertShaderID, GLuint& IniFragShaderID);

    inline void SetBool(const string& InsName, bool InbValue) const;
    inline void SetInt(const string& InsName, int32 IniValue) const;
    inline void SetFloat(const string& InsName, float InfVaule) const;
    inline void SetVec2(const string& InsName, float InfUniform) const;
    inline void SetVec2(const string& InsName, float InfX, float InfY) const;
    inline void SetVec3(const string& InsName, vec3& InfValue) const;
    inline void SetVec3(const string& InsName, float InfX, float InfY, float InfZ) const;
    inline void SetVec3(const string& InsName, float InfUniform) const;
    inline void SetMat2(const string& InsName, mat2& InfValue) const;
    inline void SetMat3(const string& InsName, mat3& InfValue) const;
    inline void SetMat4(const string& InsName, mat4& InfVaule) const;

protected:

private:

};

inline void Shader::SetBool(const string& InsName, bool InbValue) const
{
    glUniform1i(glGetUniformLocation(ShaderProgID, InsName.c_str()), (GLboolean)InbValue);
}

inline void Shader::SetInt(const string& InsName, int32 IniValue) const
{
    glUniform1i(glGetUniformLocation(ShaderProgID, InsName.c_str()), (GLint)IniValue);
}

inline void Shader::SetFloat(const string& InsName, float InfValue) const
{
    glUniform1f(glGetUniformLocation(ShaderProgID, InsName.c_str()), (GLfloat)InfValue);
}

inline void Shader::SetVec2(const string& InsName, float InfUniform) const
{
    glUniform2f(glGetUniformLocation(ShaderProgID, InsName.c_str()), (GLfloat)InfUniform, (GLfloat)InfUniform);
}

inline void Shader::SetVec2(const string& InsName, float InfX, float InfY) const
{
    glUniform2f(glGetUniformLocation(ShaderProgID, InsName.c_str()), (GLfloat)InfX, (GLfloat)InfY);
}

inline void Shader::SetVec3(const string& InsName, vec3& InfValue) const
{
    glUniform3fv(glGetUniformLocation(ShaderProgID, InsName.c_str()), 1, &InfValue[0]);
}

inline void Shader::SetVec3(const string& InsName, float InfUniform) const
{
    glUniform3f(glGetUniformLocation(ShaderProgID, InsName.c_str()), (GLfloat)InfUniform, (GLfloat)InfUniform, (GLfloat)InfUniform);
}

inline void Shader::SetVec3(const string& InsName, float InfX, float InfY, float InfZ) const
{
    glUniform3f(glGetUniformLocation(ShaderProgID, InsName.c_str()), (GLfloat)InfX, (GLfloat)InfY, (GLfloat)InfZ);
}

inline void Shader::SetMat2(const string& InsName, mat2& InrValue) const
{
    glUniformMatrix2fv(glGetUniformLocation(ShaderProgID, InsName.c_str()), 1, GL_FALSE, &InrValue[0][0]);
}

inline void Shader::SetMat3(const string& InsName, mat3& InrValue) const
{
    glUniformMatrix3fv(glGetUniformLocation(ShaderProgID, InsName.c_str()), 1, GL_FALSE, &InrValue[0][0]);
}

inline void Shader::SetMat4(const string& InsName, mat4& InrValue) const
{
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgID, InsName.c_str()), 1, GL_FALSE, &InrValue[0][0]);
}

inline void Shader::Use()
{
    glUseProgram(ShaderProgID);
}

#endif