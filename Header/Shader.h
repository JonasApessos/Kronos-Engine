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

using KronosPrim::int32, KronosPrim::uint32;
using glm::vec3, glm::mat2, glm::mat3, glm::mat4;
using std::cout, std::string, std::ifstream, std::stringstream;

enum EShaderCompilationType : uint32
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

    Shader(char const* IncVertPath, char const* IncFragPath);
    
    ~Shader();

    inline void Use();
    void CompileShader(uint32& IniShaderID, char const* IncShaderCode, EShaderCompilationType IneShaderType);
    void CreateShaderProg(uint32& IniVertShaderID, uint32& IniFragShaderID);

    inline void SetBool(string const& InsName, bool InbValue) const;
    inline void SetInt(string const& InsName, int32 IniValue) const;
    inline void SetFloat(string const& InsName, float InfVaule) const;
    inline void SetVec2(string const& InsName, float InfUniform) const;
    inline void SetVec2(string const& InsName, float InfX, float InfY) const;
    inline void SetVec3(string const& InsName, vec3& InfValue) const;
    inline void SetVec3(string const& InsName, float InfX, float InfY, float InfZ) const;
    inline void SetVec3(string const& InsName, float InfUniform) const;
    inline void SetMat2(string const& InsName, mat2& InfValue) const;
    inline void SetMat3(string const& InsName, mat3& InfValue) const;
    inline void SetMat4(string const& InsName, mat4& InfVaule) const;

protected:
    Log* rLog = new Log("LogShader");

private:

};

inline void Shader::SetBool(string const& InsName, bool InbValue) const
{
    glUniform1i(glGetUniformLocation(iShaderProgID, InsName.c_str()), InbValue);
}

inline void Shader::SetInt(string const& InsName, int32 IniValue) const
{
    glUniform1i(glGetUniformLocation(iShaderProgID, InsName.c_str()), IniValue);
}

inline void Shader::SetFloat(string const& InsName, float InfValue) const
{
    glUniform1f(glGetUniformLocation(iShaderProgID, InsName.c_str()), InfValue);
}

inline void Shader::SetVec2(string const& InsName, float InfUniform) const
{
    glUniform2f(glGetUniformLocation(iShaderProgID, InsName.c_str()), InfUniform, InfUniform);
}

inline void Shader::SetVec2(string const& InsName, float InfX, float InfY) const
{
    glUniform2f(glGetUniformLocation(iShaderProgID, InsName.c_str()), InfX, InfY);
}

inline void Shader::SetVec3(string const& InsName, vec3& InfValue) const
{
    glUniform3fv(glGetUniformLocation(iShaderProgID, InsName.c_str()), 1, &InfValue[0]);
}

inline void Shader::SetVec3(string const& InsName, float InfUniform) const
{
    glUniform3f(glGetUniformLocation(iShaderProgID, InsName.c_str()), InfUniform, InfUniform, InfUniform);
}

inline void Shader::SetVec3(string const& InsName, float InfX, float InfY, float InfZ) const
{
    glUniform3f(glGetUniformLocation(iShaderProgID, InsName.c_str()), InfX, InfY, InfZ);
}

inline void Shader::SetMat2(string const& InsName, mat2& InrValue) const
{
    glUniformMatrix2fv(glGetUniformLocation(iShaderProgID, InsName.c_str()), 1, GL_FALSE, &InrValue[0][0]);
}

inline void Shader::SetMat3(string const& InsName, mat3& InrValue) const
{
    glUniformMatrix3fv(glGetUniformLocation(iShaderProgID, InsName.c_str()), 1, GL_FALSE, &InrValue[0][0]);
}

inline void Shader::SetMat4(string const& InsName, mat4& InrValue) const
{
    glUniformMatrix4fv(glGetUniformLocation(iShaderProgID, InsName.c_str()), 1, GL_FALSE, &InrValue[0][0]);
}

inline void Shader::Use() { glUseProgram(iShaderProgID); }

#endif