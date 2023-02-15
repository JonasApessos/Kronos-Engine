#include "Texture.h"

bool Texture::bInvertYOnLoad = true;

Texture::Texture(
    int32 IniWidth,
    int32 IniHeight,
    ETextureType IneTextureType,
    ETextureDataType IneTextureDataType,
    ETextureSlot IneTextureSlot,
    ETextureFormat IneTextureFormat) : 
    iWidth(IniWidth),
    iHeight(IniHeight),
    eTextureType(IneTextureType), 
    eTextureDataType(IneTextureDataType), 
    eTextureSlot(IneTextureSlot),
    eTextureFormat(IneTextureFormat),
    eTextureInternalFormat(IneTextureFormat)
{
    rLog = Log("LogTexture");

    Initialization();
}

Texture::Texture(
    const char* IncImagePath,
    ETextureType IneTextureType,
    ETextureDataType IneTextureDataType,
    ETextureSlot IneTextureSlot,
    ETextureFormat IneTextureFormat,
    ETextureFormat IneInternalFormat) : 
    sPath(IncImagePath),
    eTextureType(IneTextureType),
    eTextureDataType(IneTextureDataType),
    eTextureSlot(IneTextureSlot),
    eTextureFormat(IneTextureFormat),
    eTextureInternalFormat(IneInternalFormat)
{
    rLog = Log("LogTexture");

    stbi_set_flip_vertically_on_load(bInvertYOnLoad);

    PixelData = stbi_load(sPath.c_str(), &iWidth, &iHeight, &iChannels, 0);

    if (PixelData)
        Initialization();
    else
        rLog.WriteAndDisplay("Failed to load image");

    stbi_image_free(PixelData);
}

Texture::Texture(
    const char* IncImagePath,
    ETextureType IneTextureType,
    ETextureDataType IneTextureDataType,
    ETextureSlot IneTextureSlot) :
    sPath(IncImagePath),
    eTextureDataType(IneTextureDataType),
    eTextureSlot(IneTextureSlot),
    eTextureType(IneTextureType)
{
    rLog = Log("LogTexture");

    stbi_set_flip_vertically_on_load(bInvertYOnLoad);

    PixelData = stbi_load(sPath.c_str(), &iWidth, &iHeight, &iChannels, 0);

    if (PixelData)
    {
        switch (iChannels)
        {
        case 1:
            eTextureFormat = ETextureFormat::ETF_RED;
            break;

        case 3:
            eTextureFormat = ETextureFormat::ETF_RGB;
            break;

        case 4:
            eTextureFormat = ETextureFormat::ETF_RGBA;
            break;
        }

        Initialization();
    }
    else
        rLog.WriteAndDisplay("Failed to load image");

    stbi_image_free(PixelData);
}

Texture::Texture(
    const char* IncImagePath,
    aiTextureType IneTextureType,
    ETextureDataType IneTextureDataType,
    ETextureSlot IneTextureSlot) :
    sPath(IncImagePath),
    eTextureDataType(IneTextureDataType),
    eTextureSlot(IneTextureSlot),
    eTextureType(static_cast<ETextureType>(IneTextureType))
{
    rLog = Log("LogTexture");

    stbi_set_flip_vertically_on_load(bInvertYOnLoad);

    PixelData = stbi_load(sPath.c_str(), &iWidth, &iHeight, &iChannels, 0);

    if (PixelData)
    {
        switch (iChannels)
        {
        case 1:
            eTextureFormat = ETextureFormat::ETF_RED;
            break;

        case 3:
            eTextureFormat = ETextureFormat::ETF_RGB;
            break;

        case 4:
            eTextureFormat = ETextureFormat::ETF_RGBA;
            break;
        }

        Initialization();
    }
    else
        rLog.WriteAndDisplay("Failed to load image");

    stbi_image_free(PixelData);
}

Texture::Texture(const Texture& InrTexture) :
    eTextureDataType(InrTexture.eTextureDataType),
    eTextureMagFilter(InrTexture.eTextureMagFilter),
    eTextureMinFilter(InrTexture.eTextureMinFilter),
    eTextureSlot(InrTexture.eTextureSlot),
    eTextureType(InrTexture.eTextureType),
    eTextureWrapS(InrTexture.eTextureWrapS),
    eTextureWrapT(InrTexture.eTextureWrapT),
    iChannels(InrTexture.iChannels),
    iHeight(InrTexture.iHeight),
    iWidth(InrTexture.iWidth),
    iTextureId(InrTexture.iTextureId)
{
    rLog = InrTexture.rLog;
}

Texture::Texture(Texture&& InrTexture) :
    eTextureDataType(InrTexture.eTextureDataType),
    eTextureMagFilter(InrTexture.eTextureMagFilter),
    eTextureMinFilter(InrTexture.eTextureMinFilter),
    eTextureSlot(InrTexture.eTextureSlot),
    eTextureType(InrTexture.eTextureType),
    eTextureWrapS(InrTexture.eTextureWrapS),
    eTextureWrapT(InrTexture.eTextureWrapT),
    iChannels(InrTexture.iChannels),
    iHeight(InrTexture.iHeight),
    iWidth(InrTexture.iWidth),
    iTextureId(InrTexture.iTextureId)
{
    rLog = InrTexture.rLog;
}

Texture Texture::operator=(const Texture&& InrTexture)
{
    eTextureDataType = InrTexture.eTextureDataType;
    eTextureMagFilter = InrTexture.eTextureMagFilter;
    eTextureMinFilter = InrTexture.eTextureMinFilter;
    eTextureSlot = InrTexture.eTextureSlot;
    eTextureType = InrTexture.eTextureType;
    eTextureWrapS = InrTexture.eTextureWrapS;
    eTextureWrapT = InrTexture.eTextureWrapT;
    iChannels = InrTexture.iChannels;
    iHeight = InrTexture.iHeight;
    iWidth = InrTexture.iWidth;
    iTextureId = InrTexture.iTextureId;
    rLog = InrTexture.rLog;

    return InrTexture;
}

Texture::~Texture()
{

}

void Texture::Initialization()
{
    Active();

    glGenTextures(1, &iTextureId);
    glBindTexture(static_cast<GLenum>(eTextureDataType), iTextureId);

    switch (eTextureDataType)
    {
    case ETextureDataType::ETDT_Texture1D:
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

    case ETextureDataType::ETDT_Texture2D:
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

    case ETextureDataType::ETDT_Texture3D:
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

        SetTextureWrap(ETextureWrap::ETW_Repeat);
        SetTextureMinMagFilter(ETextureMinFilter::ETMF_Linear, ETextureMagFilter::ETMF_Linear);
    }
}