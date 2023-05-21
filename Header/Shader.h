#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>

#include "Primitives.h"

#include "Log.h"

using KronosPrim::int32, KronosPrim::uint32, KronosPrim::uint8;
using glm::vec3, glm::mat2, glm::mat3, glm::mat4;
using std::cout, std::string, std::ifstream, std::stringstream;

enum EShaderCompilationType : uint8
{
    ESCT_Vertex = 0,
    ESCT_Fragment = 1,
    ESCT_Geometry = 2,
    ESCT_Tessellation = 3,
    ESCT_Mesh = 4,
    ESCT_Raytracing = 5,
    ESCT_Compute = 6
};

class Shader
{

public:
    uint32 iShaderProgID = 0;

    string sShaderFile;

    Shader(const char* IncVertPath, const char* IncFragPath);
    
    ~Shader();

    inline void Use();
    void CompileShader(uint32& IniShaderID, const char* IncShaderCode, EShaderCompilationType IneShaderType);
    void CreateShaderProg(uint32& IniVertShaderID, uint32& IniFragShaderID);

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
    Log* rLog = new Log("LogShader");

private:

};

inline void Shader::SetBool(const string& InsName, bool InbValue) const
{
    glUniform1i(glGetUniformLocation(iShaderProgID, InsName.c_str()), InbValue);
}

inline void Shader::SetInt(const string& InsName, int32 IniValue) const
{
    glUniform1i(glGetUniformLocation(iShaderProgID, InsName.c_str()), IniValue);
}

inline void Shader::SetFloat(const string& InsName, float InfValue) const
{
    glUniform1f(glGetUniformLocation(iShaderProgID, InsName.c_str()), InfValue);
}

inline void Shader::SetVec2(const string& InsName, float InfUniform) const
{
    glUniform2f(glGetUniformLocation(iShaderProgID, InsName.c_str()), InfUniform, InfUniform);
}

inline void Shader::SetVec2(const string& InsName, float InfX, float InfY) const
{
    glUniform2f(glGetUniformLocation(iShaderProgID, InsName.c_str()), InfX, InfY);
}

inline void Shader::SetVec3(const string& InsName, vec3& InfValue) const
{
    glUniform3fv(glGetUniformLocation(iShaderProgID, InsName.c_str()), 1, &InfValue[0]);
}

inline void Shader::SetVec3(const string& InsName, float InfUniform) const
{
    glUniform3f(glGetUniformLocation(iShaderProgID, InsName.c_str()), InfUniform, InfUniform, InfUniform);
}

inline void Shader::SetVec3(const string& InsName, float InfX, float InfY, float InfZ) const
{
    glUniform3f(glGetUniformLocation(iShaderProgID, InsName.c_str()), InfX, InfY, InfZ);
}

inline void Shader::SetMat2(const string& InsName, mat2& InrValue) const
{
    glUniformMatrix2fv(glGetUniformLocation(iShaderProgID, InsName.c_str()), 1, GL_FALSE, &InrValue[0][0]);
}

inline void Shader::SetMat3(const string& InsName, mat3& InrValue) const
{
    glUniformMatrix3fv(glGetUniformLocation(iShaderProgID, InsName.c_str()), 1, GL_FALSE, &InrValue[0][0]);
}

inline void Shader::SetMat4(const string& InsName, mat4& InrValue) const
{
    glUniformMatrix4fv(glGetUniformLocation(iShaderProgID, InsName.c_str()), 1, GL_FALSE, &InrValue[0][0]);
}

inline void Shader::Use() { glUseProgram(iShaderProgID); }

#endif