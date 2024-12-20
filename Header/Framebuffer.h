#pragma once
#include <iostream>

#include "Primitives.h"
#include "Standard.h"
#include "Log.h"
#include "Texture.h"

using KronosPrim::int32, KronosPrim::uint32;
using std::cout, std::cerr, std::to_string;

/** @enum EGLFramebufferStatus
* 	@brief enum for opengl framebuffer status*/
enum class EGLFramebufferStatus : uint32
{
	EGLFS_Complete = GL_FRAMEBUFFER_COMPLETE,
	EGLFS_Undefined = GL_FRAMEBUFFER_UNDEFINED,
	EGLFS_IncompleteAttachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
	EGLFS_IncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
	EGLFS_IncompleteDrawBuffer = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
	EGLFS_IncompleteReadBuffer = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
	EGLFS_Unsupported = GL_FRAMEBUFFER_UNSUPPORTED,
	EGLFS_IncompleteMultisample = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
	EGLFS_IncompleteLayerTargets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
};

/** @enum EGLFramebufferOp
* 	@brief enum for opengl framebuffer operation*/
enum class EGLFramebufferOp : uint32
{
	EGLFO_Draw = GL_DRAW_FRAMEBUFFER,
	EGLFO_Read = GL_READ_FRAMEBUFFER,
	EGLFO_FrameBuffer = GL_FRAMEBUFFER
};

/** @enum EGLFramebufferAttach
* 	@brief enum for opengl framebuffer attachment type*/
enum class EGLFramebufferAttach : uint32
{
	EGLFA_Color = GL_COLOR_ATTACHMENT0,
	EGLFA_Depth = GL_DEPTH_ATTACHMENT,
	EGLFA_Stencil = GL_STENCIL_ATTACHMENT,
	EGLFA_DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT,
};

/** @enum EGLFrambufferCubemap
* 	@brief enum for opengl framebuffer Cubemap coord*/
enum class EGLFrambufferCubemap : uint32
{
	EGLFC_TexturePosX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	EGLFC_TextureNegX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	EGLFC_TexturePosY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	EGLFC_TextureNegY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	EGLFC_TexturePosZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	EGLFC_TextureNegZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

/** @enum EGLFramebufferTex
* 	@brief enum for opengl framebuffer texture type*/
enum class EGLFramebufferTex : uint32
{
	EGLFT_Texture1D = GL_TEXTURE_1D,
	EGLFT_Texture2D = GL_TEXTURE_2D,
	EGLFT_Texture3D = GL_TEXTURE_3D,
	EGLFT_TextureRect = GL_TEXTURE_RECTANGLE,	
	EGLFT_Texture2DMultisample = GL_TEXTURE_2D_MULTISAMPLE
};

/** @class Framebuffer
* 	@brief class that handles opengl framebuffers*/
class Framebuffer
{
public:
	uint32 iFrameBufferID = 0;

	EGLFramebufferOp eFramebufferOp = EGLFramebufferOp::EGLFO_FrameBuffer;
	EGLFramebufferAttach eFramebufferAttach = EGLFramebufferAttach::EGLFA_Color;
	EGLFramebufferTex eFramebufferTex = EGLFramebufferTex::EGLFT_Texture2D;

	int32 iLevel = 0;

	Framebuffer(EGLFramebufferOp IneFrameBufferOp, EGLFramebufferAttach IneFramebufferAttach, EGLFramebufferTex IneFramebufferTex, Texture* InrTexture, int32 IniLevel);
	Framebuffer(Framebuffer const& InrFramebuffer);
	Framebuffer(Framebuffer&& InrFramebuffer) noexcept;

	Framebuffer& operator=(Framebuffer&& InrFramebuffer) noexcept;

	~Framebuffer();

	void Destroy();

	void RecreateBuffer();

	void CheckFramebufferState();

	//Set
	inline void SetLevel(int32 IniLevel) noexcept;

	inline void SetTexture(Texture* InrTexture) noexcept;

	inline void SetFramebufferOp(EGLFramebufferOp IneFramebufferOp) noexcept;
	inline void SetFramebufferAttach(EGLFramebufferAttach IneFramebufferAttach) noexcept;
	inline void SetFramebufferTex(EGLFramebufferTex IneFramebufferTex) noexcept;

	//Get
	constexpr inline int32 GetLevel() const noexcept;

	constexpr inline Texture& GetTexture() const noexcept;

	constexpr inline EGLFramebufferOp GetFramebufferOp() const noexcept;
	constexpr inline EGLFramebufferAttach GetFramebufferAttach() const noexcept;
	constexpr inline EGLFramebufferTex GetFramebufferTex() const noexcept;
	
	
protected:
	Log rLog = Log("LogFrameBuffer");

	Texture* rTexture;

	void CreateBuffer();

private:

};


inline void Framebuffer::SetLevel(int32 IniLevel) noexcept { iLevel = IniLevel; }
inline void Framebuffer::SetTexture(Texture* InrTexture) noexcept { rTexture = InrTexture; }
inline void Framebuffer::SetFramebufferOp(EGLFramebufferOp IneFramebufferOp) noexcept { eFramebufferOp = IneFramebufferOp; }
inline void Framebuffer::SetFramebufferAttach(EGLFramebufferAttach IneFramebufferAttach) noexcept { eFramebufferAttach = IneFramebufferAttach; }
inline void Framebuffer::SetFramebufferTex(EGLFramebufferTex IneFramebufferTex) noexcept { eFramebufferTex = IneFramebufferTex; }

constexpr int32 Framebuffer::GetLevel() const noexcept { return iLevel; }
constexpr inline Texture& Framebuffer::GetTexture() const noexcept { return *rTexture; }
constexpr inline EGLFramebufferOp Framebuffer::GetFramebufferOp() const noexcept { return eFramebufferOp; }
constexpr inline EGLFramebufferAttach Framebuffer::GetFramebufferAttach() const noexcept { return eFramebufferAttach; }
constexpr inline EGLFramebufferTex Framebuffer::GetFramebufferTex() const noexcept { return eFramebufferTex; }