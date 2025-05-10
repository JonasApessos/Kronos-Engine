#pragma once

#include <iostream>

#include "assimp/scene.h"
#include <stb/stb_image.h>

#include "Primitives.h"
#include "Standard.h"

#include "Log.h"

using std::cout, std::string, std::cerr, std::to_string;
using KronosPrim::uint32, KronosPrim::int32, KronosPrim::uint32;


/** @enum EGLTextureParameter
	@brief opengl enum texture parameter*/
enum class EGLTextureParameter:uint32
{
    EGLTP_DepthStencilTextureMode = GL_DEPTH_STENCIL_TEXTURE_MODE,
    EGLTP_BaseLevel = GL_TEXTURE_BASE_LEVEL,
    EGLTP_CompareFunc = GL_TEXTURE_COMPARE_FUNC,
    EGLTP_CompoareMode = GL_TEXTURE_COMPARE_MODE,
    EGLTP_LodBias = GL_TEXTURE_LOD_BIAS,
    EGLTP_MinFilter = GL_TEXTURE_MIN_FILTER,
    EGLTP_MagFilter = GL_TEXTURE_MAG_FILTER,
    EGLTP_MinLod = GL_TEXTURE_MIN_LOD,
    EGLTP_MaxLod = GL_TEXTURE_MAX_LOD,
    EGLTP_MaxLevel = GL_TEXTURE_MAX_LEVEL,
    EGLTP_SwizzleR = GL_TEXTURE_SWIZZLE_R,
    EGLTP_SwizzleG = GL_TEXTURE_SWIZZLE_G,
    EGLTP_SwizzleB = GL_TEXTURE_SWIZZLE_B,
    EGLTP_SwizzleA = GL_TEXTURE_SWIZZLE_A,
    EGLTP_WrapS = GL_TEXTURE_WRAP_S,
    EGLTP_WrapT = GL_TEXTURE_WRAP_T,
    EGLTP_WrapR = GL_TEXTURE_WRAP_R,
    EGLTP_BorderColor = GL_TEXTURE_BORDER_COLOR,
    EGLTP_SwizzleRGBA = GL_TEXTURE_SWIZZLE_RGBA
};

/** @enum EGLTextureWrap
	@brief opengl enum texture wrap type*/
enum class EGLTextureWrap:uint32
{
    EGLTW_Repeat = GL_REPEAT,
    EGLTW_Mirror = GL_MIRRORED_REPEAT,
    EGLTW_Clip = GL_CLAMP_TO_EDGE,
    EGLTW_Border = GL_CLAMP_TO_BORDER
};

/** @enum EGLTextureMagFilter
	@brief opengl texture filter*/
enum class EGLTextureMagFilter:uint32
{
    EGLTMF_Linear = GL_LINEAR,
    EGLTMF_Nearest = GL_NEAREST
};

/** @enum EGLTextureMinFilter
	@brief opengl mipmap filter*/
enum class EGLTextureMinFilter:uint32
{
    EGLTMF_Linear = GL_LINEAR,
    EGLTMF_Nearest = GL_NEAREST,
    EGLTMF_NearestMipMapLinear = GL_NEAREST_MIPMAP_LINEAR,
    EGLTMF_NearestMipMapNearest = GL_NEAREST_MIPMAP_NEAREST,
    EGLTMF_LinearMipMapNearest = GL_LINEAR_MIPMAP_NEAREST,
    EGLTMF_LinearMipMapLinear = GL_LINEAR_MIPMAP_LINEAR
};

/** @enum EGLTextureSlot
	@brief opengl Texture slot*/
enum EGLTextureSlot:uint32
{
    EGLTS_Slot0 = GL_TEXTURE0,
    EGLTS_Slot1 = GL_TEXTURE1,
    EGLTS_Slot2 = GL_TEXTURE2,
    EGLTS_Slot3 = GL_TEXTURE3,
    EGLTS_Slot4 = GL_TEXTURE4,
    EGLTS_Slot5 = GL_TEXTURE5,
    EGLTS_Slot6 = GL_TEXTURE6,
    EGLTS_Slot7 = GL_TEXTURE7,
    EGLTS_Slot8 = GL_TEXTURE8,
    EGLTS_Slot9 = GL_TEXTURE9,
    EGLTS_Slot10 = GL_TEXTURE10,
    EGLTS_Slot11 = GL_TEXTURE11,
    EGLTS_Slot12 = GL_TEXTURE12,
    EGLTS_Slot13 = GL_TEXTURE13,
    EGLTS_Slot14 = GL_TEXTURE14,
    EGLTS_Slot15 = GL_TEXTURE15
};

/** @enum EGLTextureDataType
	@brief opengl texture data type*/
enum class EGLTextureDataType:uint32
{
    EGLTDT_Texture1D = GL_TEXTURE_1D,
    EGLTDT_Texture1DArray = GL_TEXTURE_1D_ARRAY,
    EGLTDT_Texture2D = GL_TEXTURE_2D,
    EGLTDT_Texture2DArray = GL_TEXTURE_2D_ARRAY,
    EGLTDT_Texture2DMultisample = GL_TEXTURE_2D_MULTISAMPLE,
    EGLTDT_Texture2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
    EGLTDT_Texture3D = GL_TEXTURE_3D,
    EGLTDT_TextureCubeMap = GL_TEXTURE_CUBE_MAP,
    EGLTDT_TextureCubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
};

/** @enum ETextureType
	@brief Assimp imported texture type*/
enum class ETextureType:uint32
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

/** @enum EGLTextureFormat
	@brief opengl texture channel format*/
enum class EGLTextureFormat:uint32
{
    EGLTF_RED = GL_RED,
    EGLTF_GREEN = GL_GREEN,
    EGLTF_BLUE = GL_BLUE,
    EGLTF_ALPHA = GL_ALPHA,
    EGLTF_RGB = GL_RGB,
    EGLTF_RGBA = GL_RGBA
};

/** @class Texture
*   @brief handles textures*/
class Texture
{
public:
    bool bGenerateMipMap = true;
    static bool bInvertYOnLoad;

    uint32 iTextureId = 0;

    int32 iWidth = 1024, iHeight = static_cast<int32>(static_cast<float>(iWidth) * (9/16)), iChannels = 0;

    string sPath;

    Texture(char const* IncImagePath, ETextureType IneTextureType, EGLTextureDataType IneTextureDataType, EGLTextureSlot IneTextureSlot, EGLTextureFormat IneTextureFormat);
    Texture(char const* IncImagePath, ETextureType IneTextureType, EGLTextureDataType IneTextureDataType, EGLTextureSlot IneTextureSlot, EGLTextureFormat IneTextureFormat, EGLTextureFormat IneInternalFormat);
    Texture(char const* IncImagePath, ETextureType IneTextureType, EGLTextureDataType IneTextureDataType, EGLTextureSlot IneTextureSlot);
    Texture(char const* IncImagePath, aiTextureType IneTextureType, EGLTextureDataType IneTextureDataType, EGLTextureSlot IneTextureSlot);
    Texture(int32 IniWidth, int32 IniHeight, ETextureType IneTextureType, EGLTextureDataType IneTextureDataType, EGLTextureSlot IneTextureSlot, EGLTextureFormat IneTextureFormat);
    Texture(Texture const&);
    Texture(Texture&& InrTexture);
    

    Texture operator=(Texture&& InrTexture);
    Texture operator=(Texture const& InrTexture);

    ~Texture();


    //Set
    inline void SetId(uint32 IniTextureId);

    inline void SetTextureWrap(EGLTextureWrap IneTextureWrapS, EGLTextureWrap IneTextureWrapT);
    inline void SetTextureWrap(EGLTextureWrap IneTextureWrap);
    inline void SetTextureWrapS(EGLTextureWrap IneTextureWrap);
    inline void SetTextureWrapT(EGLTextureWrap IneTextureWrap);

    inline void SetTextureType(ETextureType IneTextureType);
    inline void SetTextureType(aiTextureType IneTextureType);

    inline void SetTextureMinMagFilter(EGLTextureMinFilter IneTextureMinFilter, EGLTextureMagFilter IneTextureMagFilter);
    inline void SetTextureMinFilter(EGLTextureMinFilter IneTextureFilter);
    inline void SetTextureMagFilter(EGLTextureMagFilter IneTextureFilter);

    //Get
    constexpr inline uint32 GetId() const;

    inline EGLTextureWrap GetTextureWrapS() const;
    inline EGLTextureWrap GetTextureWrapT() const;

    inline EGLTextureMinFilter GetTextureMinFilter() const;
    inline EGLTextureMagFilter GetTextureMagFilter() const;

    inline EGLTextureSlot GetTextureSlot() const;
    inline ETextureType GetTextureType() const;
    inline EGLTextureDataType GetTextureDataType() const;

    inline void Active() const;
    inline void Use() const;

protected:
    ETextureType eTextureType = ETextureType::ETT_Albedo;
    EGLTextureDataType eTextureDataType = EGLTextureDataType::EGLTDT_Texture2D;
    EGLTextureSlot eTextureSlot = EGLTextureSlot::EGLTS_Slot0;
    EGLTextureWrap eTextureWrapS = EGLTextureWrap::EGLTW_Repeat, eTextureWrapT = EGLTextureWrap::EGLTW_Repeat;
    EGLTextureMinFilter eTextureMinFilter = EGLTextureMinFilter::EGLTMF_NearestMipMapNearest;
    EGLTextureMagFilter eTextureMagFilter = EGLTextureMagFilter::EGLTMF_Nearest;
    EGLTextureFormat eTextureFormat = EGLTextureFormat::EGLTF_RGB;
    EGLTextureFormat eTextureInternalFormat = EGLTextureFormat::EGLTF_RGB;

    Log* rLog = new Log("LogTexture");

    void Initialization();

private:
    unsigned char* PixelData = NULL;
};



inline void Texture::SetId(uint32 IniId) { iTextureId = IniId; }

inline void Texture::SetTextureWrap(EGLTextureWrap IneTextureWrapS, EGLTextureWrap IneTextureWrapT)
{
    SetTextureWrapS(IneTextureWrapS);
    SetTextureWrapT(IneTextureWrapT);
}

inline void Texture::SetTextureWrap(EGLTextureWrap IneTextureWrap)
{
    SetTextureWrapS(IneTextureWrap);
    SetTextureWrapT(IneTextureWrap);
}

inline void Texture::SetTextureWrapS(EGLTextureWrap IneTextureWrap)
{
    eTextureWrapS = IneTextureWrap;

    glTexParameteri(static_cast<GLenum>(eTextureDataType),
    static_cast<GLenum>(EGLTextureParameter::EGLTP_WrapS),
    static_cast<GLint>(eTextureWrapS));
}

inline void Texture::SetTextureWrapT(EGLTextureWrap IneTextureWrap)
{
    eTextureWrapT = IneTextureWrap;

    glTexParameteri(static_cast<GLenum>(eTextureDataType),
    static_cast<GLenum>(EGLTextureParameter::EGLTP_WrapT),
    static_cast<GLint>(eTextureWrapT));
}

inline void Texture::SetTextureMinMagFilter(EGLTextureMinFilter IneTextureMinFilter, EGLTextureMagFilter IneTextureMagFilter)
{
    SetTextureMinFilter(IneTextureMinFilter);
    SetTextureMagFilter(IneTextureMagFilter);
}

inline void Texture::SetTextureMinFilter(EGLTextureMinFilter IneTextureFilter)
{
    eTextureMinFilter = IneTextureFilter;

    glTexParameteri(static_cast<GLenum>(eTextureDataType),
    static_cast<GLenum>(EGLTextureParameter::EGLTP_MinFilter),
    static_cast<GLint>(eTextureMinFilter));
}

inline void Texture::SetTextureMagFilter(EGLTextureMagFilter IneTextureFilter)
{
    eTextureMagFilter = IneTextureFilter;

    glTexParameteri(static_cast<GLenum>(eTextureDataType),
    static_cast<GLenum>(EGLTextureParameter::EGLTP_MagFilter),
    static_cast<GLint>(eTextureMagFilter));
}

inline void Texture::SetTextureType(ETextureType IneTextureType) { eTextureType = IneTextureType; }
inline void Texture::SetTextureType(aiTextureType InaiTextureType) { eTextureType = static_cast<ETextureType>(InaiTextureType); }

constexpr inline uint32 Texture::GetId() const { return iTextureId; }

inline EGLTextureWrap Texture::GetTextureWrapS() const { return eTextureWrapS; }
inline EGLTextureWrap Texture::GetTextureWrapT() const { return eTextureWrapT; }

inline EGLTextureMinFilter Texture::GetTextureMinFilter() const { return eTextureMinFilter; }
inline EGLTextureMagFilter Texture::GetTextureMagFilter() const { return eTextureMagFilter; }

inline EGLTextureSlot Texture::GetTextureSlot() const { return eTextureSlot; }

inline ETextureType Texture::GetTextureType() const { return eTextureType; }
inline EGLTextureDataType Texture::GetTextureDataType() const { return eTextureDataType; }

inline void Texture::Active() const { glActiveTexture(static_cast<GLenum>(eTextureSlot)); }

inline void Texture::Use() const { glBindTexture(static_cast<GLenum>(EGLTextureDataType::EGLTDT_Texture2D), iTextureId); }