#include "Shader.h"

Shader::Shader(const GLchar* IncVertPath, const GLchar* IncFragPath)
{
    sShaderFile = IncVertPath;
    string sVertCode, sFragCode;

    ifstream rVertShaderFile, rFragShaderFile;

    rVertShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    rFragShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    try
    {
        rVertShaderFile.open(IncVertPath);
        rFragShaderFile.open(IncFragPath);

        stringstream rVertShaderStream, rFragShaderStream;

        rVertShaderStream << rVertShaderFile.rdbuf();
        rFragShaderStream << rFragShaderFile.rdbuf();

        rVertShaderFile.close();
        rFragShaderFile.close();

        sVertCode = rVertShaderStream.str();
        sFragCode = rFragShaderStream.str();
    }
    catch (ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }

    const GLchar* cVertShaderCode = sVertCode.c_str();
    const GLchar* cFragShaderCode = sFragCode.c_str();

    GLuint iVertShaderRef, iFragShaderRef;
    
    
    CompileShader(iVertShaderRef, cVertShaderCode, ShaderCompilationType::VertexShader);
    CompileShader(iFragShaderRef, cFragShaderCode, ShaderCompilationType::FragmentShader);

    CreateShaderProg(iVertShaderRef, iFragShaderRef);
}

void Shader::CompileShader(GLuint& IniShaderRef, const GLchar* IncShaderCode, ShaderCompilationType InFShaderType)
{
    GLint iSuccess;
    GLchar cInfoLog[512];

    switch (InFShaderType)
    {
        case ShaderCompilationType::VertexShader:
            IniShaderRef = glCreateShader(GL_VERTEX_SHADER);
            break;

        case ShaderCompilationType::FragmentShader:
            IniShaderRef = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }
    
    glShaderSource(IniShaderRef, 1, &IncShaderCode, NULL);
    glCompileShader(IniShaderRef);

    glGetShaderiv(IniShaderRef, GL_COMPILE_STATUS, &iSuccess);

    if (!iSuccess)
    {
        glGetShaderInfoLog(IniShaderRef, 512, NULL, cInfoLog);
        cout << "FILE::" << sShaderFile << endl;
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << cInfoLog << endl;
    }
}

void Shader::CreateShaderProg(GLuint& IniVertShaderRef, GLuint& IniFragShaderRef)
{
    GLint iSuccess;
    GLchar cInfoLog[512];

    ShaderProgRef = glCreateProgram();
    glAttachShader(ShaderProgRef, IniVertShaderRef);
    glAttachShader(ShaderProgRef, IniFragShaderRef);
    glLinkProgram(ShaderProgRef);

    glGetProgramiv(ShaderProgRef, GL_LINK_STATUS, &iSuccess);

    if (!iSuccess)
    {
        glGetProgramInfoLog(ShaderProgRef, 512, NULL, cInfoLog);
        cout << "ERROR:SHADER::PROGRAM::LINKING_FAILED\n" << cInfoLog << endl;
    }

    glDeleteShader(IniVertShaderRef);
    glDeleteShader(IniFragShaderRef);
}