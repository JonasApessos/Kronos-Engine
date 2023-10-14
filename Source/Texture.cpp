#include "Texture.h"


bool Texture::bInvertYOnLoad = true;

Texture::Texture(
    int32 IniWidth,
    int32 IniHeight,
    ETextureType IneTextureType,
    EGLTextureDataType IneTextureDataType,
    EGLTextureSlot IneTextureSlot,
    EGLTextureFormat IneTextureFormat) : 
    iWidth(IniWidth),
    iHeight(IniHeight),
    eTextureType(IneTextureType), 
    eTextureDataType(IneTextureDataType), 
    eTextureSlot(IneTextureSlot),
    eTextureFormat(IneTextureFormat),
    eTextureInternalFormat(IneTextureFormat)
{
    Initialization();
}

Texture::Texture(
    char const* IncImagePath,
    ETextureType IneTextureType,
    EGLTextureDataType IneTextureDataType,
    EGLTextureSlot IneTextureSlot,
    EGLTextureFormat IneTextureFormat) :
    sPath(IncImagePath),
    eTextureType(IneTextureType),
    eTextureDataType(IneTextureDataType),
    eTextureSlot(IneTextureSlot),
    eTextureFormat(IneTextureFormat),
    eTextureInternalFormat(IneTextureFormat)
{
    stbi_set_flip_vertically_on_load(bInvertYOnLoad);

    PixelData = stbi_load(sPath.c_str(), &iWidth, &iHeight, &iChannels, 0);

    if (PixelData)
        Initialization();
    else
        rLog->WriteAndDisplay("Failed to load image");

    stbi_image_free(PixelData);
}

Texture::Texture(
    char const* IncImagePath,
    ETextureType IneTextureType,
    EGLTextureDataType IneTextureDataType,
    EGLTextureSlot IneTextureSlot,
    EGLTextureFormat IneTextureFormat,
    EGLTextureFormat IneInternalFormat) : 
    sPath(IncImagePath),
    eTextureType(IneTextureType),
    eTextureDataType(IneTextureDataType),
    eTextureSlot(IneTextureSlot),
    eTextureFormat(IneTextureFormat),
    eTextureInternalFormat(IneInternalFormat)
{
    stbi_set_flip_vertically_on_load(bInvertYOnLoad);

    PixelData = stbi_load(sPath.c_str(), &iWidth, &iHeight, &iChannels, 0);

    if (PixelData)
        Initialization();
    else
        rLog->WriteAndDisplay("Failed to load image");

    stbi_image_free(PixelData);
}

Texture::Texture(
    char const* IncImagePath,
    ETextureType IneTextureType,
    EGLTextureDataType IneTextureDataType,
    EGLTextureSlot IneTextureSlot) :
    sPath(IncImagePath),
    eTextureDataType(IneTextureDataType),
    eTextureSlot(IneTextureSlot),
    eTextureType(IneTextureType)
{
    stbi_set_flip_vertically_on_load(bInvertYOnLoad);

    PixelData = stbi_load(sPath.c_str(), &iWidth, &iHeight, &iChannels, 0);

    if (PixelData)
    {
        switch (iChannels)
        {
        case 1:
            eTextureFormat = EGLTextureFormat::EGLTF_RED;
            break;

        case 3:
            eTextureFormat = EGLTextureFormat::EGLTF_RGB;
            break;

        case 4:
            eTextureFormat = EGLTextureFormat::EGLTF_RGBA;
            break;
        }

        Initialization();
    }
    else
    {
        if(rLog != nullptr)
            rLog->WriteAndDisplay("Failed to load image");
    }

    stbi_image_free(PixelData);
}

Texture::Texture(
    char const* IncImagePath,
    aiTextureType IneTextureType,
    EGLTextureDataType IneTextureDataType,
    EGLTextureSlot IneTextureSlot) :
    sPath(IncImagePath),
    eTextureDataType(IneTextureDataType),
    eTextureSlot(IneTextureSlot),
    eTextureType(static_cast<ETextureType>(IneTextureType))
{
    stbi_set_flip_vertically_on_load(bInvertYOnLoad);

    PixelData = stbi_load(sPath.c_str(), &iWidth, &iHeight, &iChannels, 0);

    if (PixelData)
    {
        switch (iChannels)
        {
        case 1:
            eTextureFormat = EGLTextureFormat::EGLTF_RED;
            break;

        case 3:
            eTextureFormat = EGLTextureFormat::EGLTF_RGB;
            break;

        case 4:
            eTextureFormat = EGLTextureFormat::EGLTF_RGBA;
            break;
        }

        Initialization();
    }
    else
    {
        if(rLog != nullptr)
            rLog->WriteAndDisplay("Failed to load image");
    }

    stbi_image_free(PixelData);
}

Texture::Texture(Texture const& InrTexture) :
    iTextureId(InrTexture.iTextureId),
    iWidth(InrTexture.iWidth),
    iHeight(InrTexture.iHeight),
    iChannels(InrTexture.iChannels),
    eTextureType(InrTexture.eTextureType),
    eTextureDataType(InrTexture.eTextureDataType),
    eTextureSlot(InrTexture.eTextureSlot),
    eTextureWrapS(InrTexture.eTextureWrapS),
    eTextureWrapT(InrTexture.eTextureWrapT),
    eTextureMinFilter(InrTexture.eTextureMinFilter),
    eTextureMagFilter(InrTexture.eTextureMagFilter)
{
    rLog = InrTexture.rLog;
}

Texture::Texture(Texture&& InrTexture) :
    iTextureId(InrTexture.iTextureId),
    iWidth(InrTexture.iWidth),
    iHeight(InrTexture.iHeight),
    iChannels(InrTexture.iChannels),
    eTextureType(InrTexture.eTextureType),
    eTextureDataType(InrTexture.eTextureDataType),
    eTextureSlot(InrTexture.eTextureSlot),
    eTextureWrapS(InrTexture.eTextureWrapS),
    eTextureWrapT(InrTexture.eTextureWrapT),
    eTextureMinFilter(InrTexture.eTextureMinFilter),
    eTextureMagFilter(InrTexture.eTextureMagFilter)
{
    rLog = InrTexture.rLog;

    InrTexture.rLog = nullptr;
}

Texture Texture::operator=(Texture&& InrTexture)
{
    if(this != &InrTexture)
    {
        iTextureId = InrTexture.iTextureId;
        iWidth = InrTexture.iWidth;
        iHeight = InrTexture.iHeight;
        iChannels = InrTexture.iChannels;
        eTextureType = InrTexture.eTextureType;
        eTextureDataType = InrTexture.eTextureDataType;
        eTextureSlot = InrTexture.eTextureSlot;
        eTextureWrapS = InrTexture.eTextureWrapS;
        eTextureWrapT = InrTexture.eTextureWrapT;
        eTextureMinFilter = InrTexture.eTextureMinFilter;
        eTextureMagFilter = InrTexture.eTextureMagFilter; 
        rLog = InrTexture.rLog;

        InrTexture.rLog = nullptr;
    }

    return InrTexture;
}

Texture Texture::operator=(Texture const& InrTexture)
{
    iTextureId = InrTexture.iTextureId;
    iWidth = InrTexture.iWidth;
    iHeight = InrTexture.iHeight;
    iChannels = InrTexture.iChannels;
    eTextureType = InrTexture.eTextureType;
    eTextureDataType = InrTexture.eTextureDataType;
    eTextureSlot = InrTexture.eTextureSlot;
    eTextureWrapS = InrTexture.eTextureWrapS;
    eTextureWrapT = InrTexture.eTextureWrapT;
    eTextureMinFilter = InrTexture.eTextureMinFilter;
    eTextureMagFilter = InrTexture.eTextureMagFilter; 
    rLog = InrTexture.rLog;

    return InrTexture;
}

Texture::~Texture()
{
    glDeleteTextures(1, &iTextureId);

    if(rLog != nullptr)
        delete rLog;
}

void Texture::Initialization()
{
    Active();

    glGenTextures(1, &iTextureId);
    glBindTexture(static_cast<GLenum>(eTextureDataType), iTextureId);

    switch (eTextureDataType)
    {
    case EGLTextureDataType::EGLTDT_Texture1D:
        glTexImage1D(
            static_cast<GLenum>(eTextureDataType),
            0,
            static_cast<GLint>(eTextureInternalFormat),
            iWidth,
            0,
            static_cast<GLint>(eTextureFormat),
            GL_UNSIGNED_BYTE,
            PixelData);
        break;

    case EGLTextureDataType::EGLTDT_Texture2D:
        glTexImage2D(
            static_cast<GLenum>(eTextureDataType),
            0,
            static_cast<GLint>(eTextureInternalFormat),
            iWidth,
            iHeight,
            0,
            static_cast<GLint>(eTextureFormat),
            GL_UNSIGNED_BYTE,
            PixelData);
        break;

    case EGLTextureDataType::EGLTDT_Texture3D:
        glTexImage3D(
            static_cast<GLenum>(eTextureDataType),
            0,
            static_cast<GLint>(eTextureInternalFormat),
            iWidth,
            iHeight,
            0,
            0,
            static_cast<GLint>(eTextureFormat),
            GL_UNSIGNED_BYTE,
            PixelData);
        break;

    default:
        glTexImage2D(
            static_cast<GLenum>(eTextureDataType),
            0,
            static_cast<GLint>(eTextureInternalFormat),
            iWidth,
            iHeight,
            0,
            static_cast<GLint>(eTextureFormat),
            GL_UNSIGNED_BYTE,
            PixelData);
    }

    if (bGenerateMipMap)
    {
        glGenerateMipmap(static_cast<GLenum>(eTextureDataType));

        SetTextureWrap(EGLTextureWrap::EGLTW_Repeat);
        SetTextureMinMagFilter(EGLTextureMinFilter::EGLTMF_Linear, EGLTextureMagFilter::EGLTMF_Linear);
    }
}