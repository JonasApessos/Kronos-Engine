#include "Shader.h"

Shader::Shader(char const* IncVertPath, char const* IncFragPath)
{
    sShaderFile = IncVertPath;
    string sVertCode, sFragCode;

    ifstream rVertShaderFile, rFragShaderFile;

    rVertShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    rFragShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    try
    {
        rShaderFile.SetFullPath(IncVertPath);

        sVertCode = rShaderFile.Read();

        rShaderFile.SetFullPath(IncFragPath);

        sFragCode = rShaderFile.Read();
    }
    catch (ifstream::failure e)
    {
        string sError = e.what();
        rLog.WriteAndDisplay("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ - " + sError, ELogSeverity::ELS_Error);
    }

    char const* cVertShaderCode = sVertCode.c_str();
    char const* cFragShaderCode = sFragCode.c_str();

    uint32 iVertShaderRef, iFragShaderRef;
    
    
    CompileShader(iVertShaderRef, cVertShaderCode, EShaderCompilationType::ESCT_Vertex);
    CompileShader(iFragShaderRef, cFragShaderCode, EShaderCompilationType::ESCT_Fragment);

    CreateShaderProg(iVertShaderRef, iFragShaderRef);
}

Shader::~Shader()
{
    if (glIsShader(iShaderProgID))
    {

    }
}

void Shader::CompileShader(uint32& IniShaderID, char const* IncShaderCode, EShaderCompilationType IneShaderType)
{
    int32 iSuccess;
    char cInfoLog[512];

    switch (IneShaderType)
    {
        case EShaderCompilationType::ESCT_Vertex:
            IniShaderID = glCreateShader(GL_VERTEX_SHADER);
            break;

        case EShaderCompilationType::ESCT_Fragment:
            IniShaderID = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }
    
    glShaderSource(IniShaderID, 1, &IncShaderCode, NULL);
    glCompileShader(IniShaderID);

    glGetShaderiv(IniShaderID, GL_COMPILE_STATUS, &iSuccess);

    if (!iSuccess)
    {
        glGetShaderInfoLog(IniShaderID, 512, NULL, cInfoLog);

        string sInfoLog = cInfoLog;

        rLog.WriteAndDisplay("FILE::" + sShaderFile);
        rLog.WriteAndDisplay("ERROR::SHADER::VERTEX::COMPILATION_FAILED: " + sInfoLog, ELogSeverity::ELS_Error);
    }
}

void Shader::CreateShaderProg(uint32& IniVertShaderID, uint32& IniFragShaderID)
{
    GLint iSuccess;
    char cInfoLog[512];

    iShaderProgID = glCreateProgram();
    glAttachShader(iShaderProgID, IniVertShaderID);
    glAttachShader(iShaderProgID, IniFragShaderID);
    glLinkProgram(iShaderProgID);

    glGetProgramiv(iShaderProgID, GL_LINK_STATUS, &iSuccess);

    if (!iSuccess)
    {
        glGetProgramInfoLog(iShaderProgID, 512, NULL, cInfoLog);

        string sInfoLog = cInfoLog;

        rLog.WriteAndDisplay("ERROR:SHADER::PROGRAM::LINKING_FAILED: " + sInfoLog, ELogSeverity::ELS_Error);
    }

    glDeleteShader(IniVertShaderID);
    glDeleteShader(IniFragShaderID);
}