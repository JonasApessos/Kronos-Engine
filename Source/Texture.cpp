#include "Texture.h"

bool Texture::bInvertYOnLoad = true;

Texture::Texture(
    int IniWidth,
    int IniHeight,
    ETextureType IneTextureType,
    ETextureDataType IneTextureDataType,
    ETextureSlot IneTextureSlot,
    ETextureFormat IneTextureFormat) : 
    eTextureType(IneTextureType), 
    eTextureDataType(IneTextureDataType), 
    eTextureSlot(IneTextureSlot)
{
    glGenTextures(1, &iTextureId);
    glBindTexture(static_cast<GLenum>(eTextureDataType), GetId());

    switch (eTextureDataType)
    {
        case ETextureDataType::ETDT_Texture1D:
            glTexImage1D(static_cast<GLenum>(eTextureDataType),
                0,
                static_cast<GLint>(IneTextureFormat),
                static_cast<GLint>(iWidth),
                0,
                static_cast<GLint>(IneTextureFormat),
                GL_UNSIGNED_BYTE,
                NULL);

            break;

        case ETextureDataType::ETDT_Texture2D:
            glTexImage2D((GLenum)eTextureDataType,
                0,
                (GLint)IneTextureFormat,
                (GLint)iWidth,
                (GLint)iHeight,
                0,
                (GLint)IneTextureFormat,
                GL_UNSIGNED_BYTE,
                NULL);

            break;

        case ETextureDataType::ETDT_Texture3D:
            glTexImage3D((GLenum)eTextureDataType,
                0,
                (GLint)IneTextureFormat,
                (GLint)iWidth,
                (GLint)iHeight,
                0,
                0,
                (GLint)IneTextureFormat,
                GL_UNSIGNED_BYTE,
                NULL);

            break;
    }

    //glGenerateMipmap((GLenum)eTextureDataType);
    SetTextureWrap(ETextureWrap::ETW_Clip);
    SetTextureMinMagFilter(ETextureMinFilter::ETMF_Linear, ETextureMagFilter::ETMF_Linear);

    Active();
}

Texture::Texture(const char* IncImagePath, ETextureType IneTextureType, ETextureDataType IneTextureDataType, ETextureSlot IneTextureSlot, ETextureFormat IneTextureFormat, ETextureFormat IneInternalFormat) : eTextureDataType(IneTextureDataType), eTextureSlot(IneTextureSlot)
{
    stbi_set_flip_vertically_on_load(bInvertYOnLoad);

    PixelData = stbi_load(IncImagePath, &iWidth, &iHeight, &iChannels, 0);

    if (PixelData)
    {
        SetTextureType(IneTextureType);
        eTextureDataType = IneTextureDataType;
        eTextureSlot = IneTextureSlot;

        Active();

        glGenTextures(1, &iTextureId);
        glBindTexture((GLenum)eTextureDataType, iTextureId);

        switch (eTextureDataType)
        {
            case ETextureDataType::ETDT_Texture1D:
                glTexImage1D((GLenum)eTextureDataType, 0, (GLint)IneInternalFormat, iWidth, 0, (GLint)IneTextureFormat, GL_UNSIGNED_BYTE, PixelData);
                break;

            case ETextureDataType::ETDT_Texture2D:
                glTexImage2D((GLenum)eTextureDataType, 0, (GLint)IneInternalFormat, iWidth, iHeight, 0, (GLint)IneTextureFormat, GL_UNSIGNED_BYTE, PixelData);
                break;

            case ETextureDataType::ETDT_Texture3D:
                glTexImage3D((GLenum)eTextureDataType, 0, (GLint)IneInternalFormat, iWidth, iHeight, 0, 0, (GLint)IneTextureFormat, GL_UNSIGNED_BYTE, PixelData);
                break;
        }

        if (bGenerateMipMap)
        {
            glGenerateMipmap((GLenum)eTextureDataType);

            SetTextureWrap(ETextureWrap::ETW_Repeat);
            SetTextureMinMagFilter(ETextureMinFilter::ETMF_Linear, ETextureMagFilter::ETMF_Linear);
        }
    }
    else
        cerr << "Failed to load image" << endl;

    stbi_image_free(PixelData);
}

Texture::Texture(const char* IncImagePath, ETextureType IneTextureType, ETextureDataType IneTextureDataType, ETextureSlot IneTextureSlot) : eTextureDataType(IneTextureDataType), eTextureSlot(IneTextureSlot)
{
    stbi_set_flip_vertically_on_load(bInvertYOnLoad);

    PixelData = stbi_load(IncImagePath, &iWidth, &iHeight, &iChannels, 0);

    if (PixelData)
    {
        ETextureFormat eFormat = ETextureFormat::ETF_RED;

        eTextureDataType = IneTextureDataType;
        eTextureSlot = IneTextureSlot;

        SetTextureType(IneTextureType);

        switch (iChannels)
        {
        case 1:
            eFormat = ETextureFormat::ETF_RED;
            break;

        case 3:
            eFormat = ETextureFormat::ETF_RGB;
            break;

        case 4:
            eFormat = ETextureFormat::ETF_RGBA;
            break;
        }

        Active();

        glGenTextures(1, &iTextureId);
        glBindTexture((GLenum)eTextureDataType, iTextureId);



        switch (eTextureDataType)
        {
        case ETextureDataType::ETDT_Texture1D:
            glTexImage1D((GLenum)eTextureDataType, 0, (GLint)eFormat, iWidth, 0, (GLint)eFormat, GL_UNSIGNED_BYTE, PixelData);
            break;

        case ETextureDataType::ETDT_Texture2D:
            glTexImage2D((GLenum)eTextureDataType, 0, (GLint)eFormat, iWidth, iHeight, 0, (GLint)eFormat, GL_UNSIGNED_BYTE, PixelData);
            break;

        case ETextureDataType::ETDT_Texture3D:
            glTexImage3D((GLenum)eTextureDataType, 0, (GLint)eFormat, iWidth, iHeight, 0, 0, (GLint)eFormat, GL_UNSIGNED_BYTE, PixelData);
            break;
        }

        if (bGenerateMipMap)
        {
            glGenerateMipmap((GLenum)eTextureDataType);

            SetTextureWrap(ETextureWrap::ETW_Repeat);
            SetTextureMinMagFilter(ETextureMinFilter::ETMF_Linear, ETextureMagFilter::ETMF_Linear);
        }
    }
    else
        cerr << "Failed to load image" << endl;

    stbi_image_free(PixelData);
}

Texture::Texture(const char* IncImagePath, aiTextureType IneTextureType, ETextureDataType IneTextureDataType, ETextureSlot IneTextureSlot) : eTextureDataType(IneTextureDataType), eTextureSlot(IneTextureSlot)
{
    stbi_set_flip_vertically_on_load(bInvertYOnLoad);

    PixelData = stbi_load(IncImagePath, &iWidth, &iHeight, &iChannels, 0);

    if (PixelData)
    {
        ETextureFormat eFormat = ETextureFormat::ETF_RED;

        eTextureDataType = IneTextureDataType;
        eTextureSlot = IneTextureSlot;

        SetTextureType(IneTextureType);

        switch (iChannels)
        {
        case 1:
            eFormat = ETextureFormat::ETF_RED;
            break;

        case 3:
            eFormat = ETextureFormat::ETF_RGB;
            break;

        case 4:
            eFormat = ETextureFormat::ETF_RGBA;
            break;
        }

        Active();

        glGenTextures(1, &iTextureId);
        glBindTexture((GLenum)eTextureDataType, iTextureId);



        switch (eTextureDataType)
        {
        case ETextureDataType::ETDT_Texture1D:
            glTexImage1D((GLenum)eTextureDataType, 0, (GLint)eFormat, iWidth, 0, (GLint)eFormat, GL_UNSIGNED_BYTE, PixelData);
            break;

        case ETextureDataType::ETDT_Texture2D:
            glTexImage2D((GLenum)eTextureDataType, 0, (GLint)eFormat, iWidth, iHeight, 0, (GLint)eFormat, GL_UNSIGNED_BYTE, PixelData);
            break;

        case ETextureDataType::ETDT_Texture3D:
            glTexImage3D((GLenum)eTextureDataType, 0, (GLint)eFormat, iWidth, iHeight, 0, 0, (GLint)eFormat, GL_UNSIGNED_BYTE, PixelData);
            break;
        }

        if (bGenerateMipMap)
        {
            glGenerateMipmap((GLenum)eTextureDataType);

            SetTextureWrap(ETextureWrap::ETW_Repeat);
            SetTextureMinMagFilter(ETextureMinFilter::ETMF_Linear, ETextureMagFilter::ETMF_Linear);
        }
    }
    else
        cerr << "Failed to load image" << endl;

    stbi_image_free(PixelData);
}

void Texture::SetTextureType(aiTextureType IneTextureType)
{
    switch (IneTextureType)
    {
    case aiTextureType::aiTextureType_DIFFUSE:
        eTextureType = ETextureType::ETT_Albedo;
        break;

    case aiTextureType::aiTextureType_NORMALS:
        eTextureType = ETextureType::ETT_Normal;
        break;

    case aiTextureType::aiTextureType_SPECULAR:
        eTextureType = ETextureType::ETT_Specular;
        break;

    case aiTextureType::aiTextureType_METALNESS:
        eTextureType = ETextureType::ETT_Metalness;
        break;

    case aiTextureType::aiTextureType_AMBIENT:
        eTextureType = ETextureType::ETT_AO;
        break;

    case aiTextureType::aiTextureType_EMISSIVE:
        eTextureType = ETextureType::ETT_Emissive;
        break;

    case aiTextureType::aiTextureType_HEIGHT:
        eTextureType = ETextureType::ETT_Height;
        break;

    case aiTextureType::aiTextureType_TRANSMISSION:
        eTextureType = ETextureType::ETT_Transmision;
        break;

    case aiTextureType::aiTextureType_UNKNOWN:
        eTextureType = ETextureType::ETT_Unknown;
        break;

    case aiTextureType::aiTextureType_NONE:
        eTextureType = ETextureType::ETT_None;
        break;
        
    default:
        eTextureType = ETextureType::ETT_Unknown;
        cout << "Unknown Texture " << IneTextureType << endl;
        break;
    }
}