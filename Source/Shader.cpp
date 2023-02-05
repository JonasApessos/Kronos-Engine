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
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ - " << e.what() << "\n";
    }

    const GLchar* cVertShaderCode = sVertCode.c_str();
    const GLchar* cFragShaderCode = sFragCode.c_str();

    GLuint iVertShaderRef, iFragShaderRef;
    
    
    CompileShader(iVertShaderRef, cVertShaderCode, ShaderCompilationType::VertexShader);
    CompileShader(iFragShaderRef, cFragShaderCode, ShaderCompilationType::FragmentShader);

    CreateShaderProg(iVertShaderRef, iFragShaderRef);
}

Shader::~Shader()
{
    if (glIsShader(ShaderProgID))
    {

    }
}

void Shader::CompileShader(GLuint& IniShaderID, const GLchar* IncShaderCode, ShaderCompilationType InFShaderType)
{
    GLint iSuccess;
    GLchar cInfoLog[512];

    switch (InFShaderType)
    {
        case ShaderCompilationType::VertexShader:
            IniShaderID = glCreateShader(GL_VERTEX_SHADER);
            break;

        case ShaderCompilationType::FragmentShader:
            IniShaderID = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }
    
    glShaderSource(IniShaderID, 1, &IncShaderCode, NULL);
    glCompileShader(IniShaderID);

    glGetShaderiv(IniShaderID, GL_COMPILE_STATUS, &iSuccess);

    if (!iSuccess)
    {
        glGetShaderInfoLog(IniShaderID, 512, NULL, cInfoLog);
        cout << "FILE::" << sShaderFile << endl;
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << cInfoLog << endl;
    }
}

void Shader::CreateShaderProg(GLuint& IniVertShaderID, GLuint& IniFragShaderID)
{
    GLint iSuccess;
    GLchar cInfoLog[512];

    ShaderProgID = glCreateProgram();
    glAttachShader(ShaderProgID, IniVertShaderID);
    glAttachShader(ShaderProgID, IniFragShaderID);
    glLinkProgram(ShaderProgID);

    glGetProgramiv(ShaderProgID, GL_LINK_STATUS, &iSuccess);

    if (!iSuccess)
    {
        glGetProgramInfoLog(ShaderProgID, 512, NULL, cInfoLog);
        cout << "ERROR:SHADER::PROGRAM::LINKING_FAILED\n" << cInfoLog << endl;
    }

    glDeleteShader(IniVertShaderID);
    glDeleteShader(IniFragShaderID);
}