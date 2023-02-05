#pragma once

#include <iostream>

#include <GL/glew.h>
#include "assimp/scene.h"

#include "stb_image.h"

#include "Primitives.h"

using namespace std;

enum class ETextureParameter:GLenum
{
    ETP_DepthStencilTextureMode = GL_DEPTH_STENCIL_TEXTURE_MODE,
    ETP_BaseLevel = GL_TEXTURE_BASE_LEVEL,
    ETP_CompareFunc = GL_TEXTURE_COMPARE_FUNC,
    ETP_CompoareMode = GL_TEXTURE_COMPARE_MODE,
    ETP_LodBias = GL_TEXTURE_LOD_BIAS,
    ETP_MinFilter = GL_TEXTURE_MIN_FILTER,
    ETP_MagFilter = GL_TEXTURE_MAG_FILTER,
    ETP_MinLod = GL_TEXTURE_MIN_LOD,
    ETP_MaxLod = GL_TEXTURE_MAX_LOD,
    ETP_MaxLevel = GL_TEXTURE_MAX_LEVEL,
    ETP_SwizzleR = GL_TEXTURE_SWIZZLE_R,
    ETP_SwizzleG = GL_TEXTURE_SWIZZLE_G,
    ETP_SwizzleB = GL_TEXTURE_SWIZZLE_B,
    ETP_SwizzleA = GL_TEXTURE_SWIZZLE_A,
    ETP_WrapS = GL_TEXTURE_WRAP_S,
    ETP_WrapT = GL_TEXTURE_WRAP_T,
    ETP_WrapR = GL_TEXTURE_WRAP_R,
    ETP_BorderColor = GL_TEXTURE_BORDER_COLOR,
    ETP_SwizzleRGBA = GL_TEXTURE_SWIZZLE_RGBA
};

enum class ETextureWrap:GLenum
{
    ETW_Repeat = GL_REPEAT,
    ETW_Mirror = GL_MIRRORED_REPEAT,
    ETW_Clip = GL_CLAMP_TO_EDGE,
    ETW_Border = GL_CLAMP_TO_BORDER
};

enum class ETextureMagFilter:GLenum
{
    ETMF_Linear = GL_LINEAR,
    ETMF_Nearest = GL_NEAREST
};

enum class ETextureMinFilter:GLenum
{
    ETMF_Linear = GL_LINEAR,
    ETMF_Nearest = GL_NEAREST,
    ETMF_NearestMipMapLinear = GL_NEAREST_MIPMAP_LINEAR,
    ETMF_NearestMipMapNearest = GL_NEAREST_MIPMAP_NEAREST,
    ETMF_LinearMipMapNearest = GL_LINEAR_MIPMAP_NEAREST,
    ETMF_LinearMipMapLinear = GL_LINEAR_MIPMAP_LINEAR
};

enum class ETextureSlot:GLenum
{
    ETS_Slot0 = GL_TEXTURE0,
    ETS_Slot1 = GL_TEXTURE1,
    ETS_Slot2 = GL_TEXTURE2,
    ETS_Slot3 = GL_TEXTURE3,
    ETS_Slot4 = GL_TEXTURE4,
    ETS_Slot5 = GL_TEXTURE5,
    ETS_Slot6 = GL_TEXTURE6,
    ETS_Slot7 = GL_TEXTURE7,
    ETS_Slot8 = GL_TEXTURE8,
    ETS_Slot9 = GL_TEXTURE9,
    ETS_Slot10 = GL_TEXTURE10,
    ETS_Slot11 = GL_TEXTURE11,
    ETS_Slot12 = GL_TEXTURE12,
    ETS_Slot13 = GL_TEXTURE13,
    ETS_Slot14 = GL_TEXTURE14,
    ETS_Slot15 = GL_TEXTURE15
};

enum class ETextureDataType:GLenum
{
    ETDT_Texture1D = GL_TEXTURE_1D,
    ETDT_Texture1DArray = GL_TEXTURE_1D_ARRAY,
    ETDT_Texture2D = GL_TEXTURE_2D,
    ETDT_Texture2DArray = GL_TEXTURE_2D_ARRAY,
    ETDT_Texture2DMultisample = GL_TEXTURE_2D_MULTISAMPLE,
    ETDT_Texture2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
    ETDT_Texture3D = GL_TEXTURE_3D,
    ETDT_TextureCubeMap = GL_TEXTURE_CUBE_MAP,
    ETDT_TextureCubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
};

enum class ETextureType:GLenum
{
    ETT_Diffuse = aiTextureType::aiTextureType_DIFFUSE,
    ETT_Albedo = aiTextureType::aiTextureType_BASE_COLOR,
    ETT_Specular = aiTextureType::aiTextureType_SPECULAR,
    ETT_Rougness = aiTextureType::aiTextureType_SHININESS,
    ETT_Metalness = aiTextureType::aiTextureType_METALNESS,
    ETT_Emissive = aiTextureType::aiTextureType_EMISSIVE,
    ETT_Reflection = aiTextureType::aiTextureType_REFLECTION,
    ETT_Height = aiTextureType::aiTextureType_HEIGHT,
    ETT_Normal = aiTextureType::aiTextureType_NORMALS,
    ETT_Displacement = aiTextureType::aiTextureType_DISPLACEMENT,
    ETT_Ambient = aiTextureType::aiTextureType_AMBIENT,
    ETT_AO = aiTextureType::aiTextureType_AMBIENT_OCCLUSION,
    ETT_Transmision = aiTextureType::aiTextureType_TRANSMISSION,
    ETT_Unknown = aiTextureType::aiTextureType_UNKNOWN,
    ETT_None = aiTextureType::aiTextureType_NONE,
    ETT_ClearCoat = aiTextureType::aiTextureType_CLEARCOAT,
    ETT_DiffuseRoughness = aiTextureType::aiTextureType_DIFFUSE_ROUGHNESS,
    ETT_Emission_Color = aiTextureType::aiTextureType_EMISSION_COLOR,
    ETT_Lightmap = aiTextureType::aiTextureType_LIGHTMAP,
    ETT_NormalCamera = aiTextureType::aiTextureType_NORMAL_CAMERA,
    ETT_Opacity = aiTextureType::aiTextureType_OPACITY,
    ETT_Sheen = aiTextureType::aiTextureType_SHEEN,
    ETT_RGB_Mask = 22,
    ETT_RGBA_Mask = 23
};

enum class ETextureFormat:GLenum
{
    ETF_RED = GL_RED,
    ETF_GREEN = GL_GREEN,
    ETF_BLUE = GL_BLUE,
    ETF_ALPHA = GL_ALPHA,
    ETF_RGB = GL_RGB,
    ETF_RGBA = GL_RGBA
};

class Texture
{
public:
    bool bGenerateMipMap = true;
    static bool bInvertYOnLoad;

    int32 iWidth = 0, iHeight = 0, iChannels = 0;

    string sPath;

    Texture(const char* IncImagePath, ETextureType IneTextureType, ETextureDataType IneTextureDataType, ETextureSlot IneTextureSlot, ETextureFormat IneTextureFormat, ETextureFormat IneInternalFormat);
    Texture(const char* IncImagePath, ETextureType IneTextureType, ETextureDataType IneTextureDataType, ETextureSlot IneTextureSlot);
    Texture(const char* IncImagePath, aiTextureType IneTextureType, ETextureDataType IneTextureDataType, ETextureSlot IneTextureSlot);
    Texture(int IniWidth, int IniHeight, ETextureType IneTextureType, ETextureDataType IneTextureDataType, ETextureSlot IneTextureSlot, ETextureFormat IneTextureFormat);



    inline void SetId(uint32 IniTextureId);

    inline void SetTextureWrap(ETextureWrap IneTextureWrapS, ETextureWrap IneTextureWrapT);
    inline void SetTextureWrap(ETextureWrap IneTextureWrap);
    inline void SetTextureWrapS(ETextureWrap IneTextureWrap);
    inline void SetTextureWrapT(ETextureWrap IneTextureWrap);

    inline void SetTextureType(ETextureType IneTextureType);
    void SetTextureType(aiTextureType IneTextureType);

    inline void SetTextureMinMagFilter(ETextureMinFilter IneTextureMinFilter, ETextureMagFilter IneTextureMagFilter);
    inline void SetTextureMinFilter(ETextureMinFilter IneTextureFilter);
    inline void SetTextureMagFilter(ETextureMagFilter IneTextureFilter);

    inline uint32 GetId() const;

    inline ETextureWrap GetTextureWrapS() const;
    inline ETextureWrap GetTextureWrapT() const;

    inline ETextureMinFilter GetTextureMinFilter() const;
    inline ETextureMagFilter GetTextureMagFilter() const;

    inline ETextureSlot GetTextureSlot() const;
    inline ETextureType GetTextureType() const;
    inline ETextureDataType GetTextureDataType() const;

    inline void Active();
    inline void Use();

protected:
    ETextureType eTextureType = ETextureType::ETT_Albedo;
    ETextureDataType eTextureDataType = ETextureDataType::ETDT_Texture2D;
    ETextureSlot eTextureSlot = ETextureSlot::ETS_Slot0;
    ETextureWrap eTextureWrapS = ETextureWrap::ETW_Repeat, eTextureWrapT = ETextureWrap::ETW_Repeat;
    ETextureMinFilter eTextureMinFilter = ETextureMinFilter::ETMF_NearestMipMapNearest;
    ETextureMagFilter eTextureMagFilter = ETextureMagFilter::ETMF_Nearest;

private:
    uint32 iTextureId = 0;

    unsigned char* PixelData = NULL;
};



inline void Texture::SetId(uint32 IniId)
{
    iTextureId = IniId;
}

inline void Texture::SetTextureWrap(ETextureWrap IneTextureWrapS, ETextureWrap IneTextureWrapT)
{
    SetTextureWrapS(IneTextureWrapS);
    SetTextureWrapT(IneTextureWrapT);
}

inline void Texture::SetTextureWrap(ETextureWrap IneTextureWrap)
{
    SetTextureWrapS(IneTextureWrap);
    SetTextureWrapT(IneTextureWrap);
}

inline void Texture::SetTextureWrapS(ETextureWrap IneTextureWrap)
{
    eTextureWrapS = IneTextureWrap;

    glTexParameteri(static_cast<GLenum>(eTextureDataType), static_cast<GLenum>(ETextureParameter::ETP_WrapS), static_cast<GLint>(eTextureWrapS));
}

inline void Texture::SetTextureWrapT(ETextureWrap IneTextureWrap)
{
    eTextureWrapT = IneTextureWrap;

    glTexParameteri(static_cast<GLenum>(eTextureDataType), static_cast<GLenum>(ETextureParameter::ETP_WrapT), static_cast<GLint>(eTextureWrapT));
}

inline void Texture::SetTextureMinMagFilter(ETextureMinFilter IneTextureMinFilter, ETextureMagFilter IneTextureMagFilter)
{
    SetTextureMinFilter(IneTextureMinFilter);
    SetTextureMagFilter(IneTextureMagFilter);
}

inline void Texture::SetTextureMinFilter(ETextureMinFilter IneTextureFilter)
{
    eTextureMinFilter = IneTextureFilter;

    glTexParameteri(static_cast<GLenum>(eTextureDataType), static_cast<GLenum>(ETextureParameter::ETP_MinFilter), static_cast<GLint>(eTextureMinFilter));
}

inline void Texture::SetTextureMagFilter(ETextureMagFilter IneTextureFilter)
{
    eTextureMagFilter = IneTextureFilter;

    glTexParameteri(static_cast<GLenum>(eTextureDataType), static_cast<GLenum>(ETextureParameter::ETP_MagFilter), static_cast<GLint>(eTextureMagFilter));
}

inline void Texture::SetTextureType(ETextureType IneTextureType)
{
    eTextureType = IneTextureType;
}

inline uint32 Texture::GetId() const { return iTextureId; }

inline ETextureWrap Texture::GetTextureWrapS() const { return eTextureWrapS; }
inline ETextureWrap Texture::GetTextureWrapT() const { return eTextureWrapT; }

inline ETextureMinFilter Texture::GetTextureMinFilter() const { return eTextureMinFilter; }
inline ETextureMagFilter Texture::GetTextureMagFilter() const { return eTextureMagFilter; }

inline ETextureSlot Texture::GetTextureSlot() const { return eTextureSlot; }

inline ETextureType Texture::GetTextureType() const { return eTextureType; }
inline ETextureDataType Texture::GetTextureDataType() const { return eTextureDataType; }

inline void Texture::Active() { glActiveTexture(static_cast<GLenum>(eTextureSlot)); }

inline void Texture::Use() { glBindTexture(static_cast<GLenum>(ETextureDataType::ETDT_Texture2D), iTextureId); }