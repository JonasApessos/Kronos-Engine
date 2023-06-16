#pragma once
#include <GL/glew.h>
#include <iostream>
#include "Primitives.h"
#include "Log.h"
#include "Standard.h"
#include "Texture.h"

using KronosPrim::int32, KronosPrim::uint32;
using std::cout, std::cerr, std::to_string;

class Log;

enum EFramebufferStatus : uint32
{
	EFS_Complete = GL_FRAMEBUFFER_COMPLETE,
	EFS_Undefined = GL_FRAMEBUFFER_UNDEFINED,
	EFS_IncompleteAttachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
	EFS_IncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
	EFS_IncompleteDrawBuffer = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
	EFS_IncompleteReadBuffer = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
	EFS_Unsupported = GL_FRAMEBUFFER_UNSUPPORTED,
	EFS_IncompleteMultisample = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
	EFS_IncompleteLayerTargets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
};

enum EFramebufferOp : uint32
{
	EFO_Draw = GL_DRAW_FRAMEBUFFER,
	EFO_Read = GL_READ_FRAMEBUFFER,
	EFO_FrameBuffer = GL_FRAMEBUFFER
};

enum EFramebufferAttach : uint32
{
	EFA_Color = GL_COLOR_ATTACHMENT0,
	EFA_Depth = GL_DEPTH_ATTACHMENT,
	EFA_Stencil = GL_STENCIL_ATTACHMENT,
	EFA_DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT,
};

enum EFrambufferCubemap : uint32
{
	EFC_TexturePosX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	EFC_TextureNegX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	EFC_TexturePosY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	EFC_TextureNegY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	EFC_TexturePosZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	EFC_TextureNegZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

enum EFramebufferTex : uint32
{
	EFT_Texture1D = GL_TEXTURE_1D,
	EFT_Texture2D = GL_TEXTURE_2D,
	EFT_Texture3D = GL_TEXTURE_3D,
	EFT_TextureRect = GL_TEXTURE_RECTANGLE,	
	EFT_Texture2DMultisample = GL_TEXTURE_2D_MULTISAMPLE
};

class Framebuffer
{
public:
	uint32 iFrameBufferID = 0;
	int32 iLevel = 0;

	EFramebufferOp eFramebufferOp = EFramebufferOp::EFO_FrameBuffer;
	EFramebufferAttach eFramebufferAttach = EFramebufferAttach::EFA_Color;
	EFramebufferTex eFramebufferTex = EFramebufferTex::EFT_Texture2D;

	Framebuffer(EFramebufferOp IneFrameBufferOp, EFramebufferAttach IneFramebufferAttach, EFramebufferTex IneFramebufferTex, Texture* InrTexture, int32 IniLevel);
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

	inline void SetFramebufferOp(EFramebufferOp IneFramebufferOp) noexcept;
	inline void SetFramebufferAttach(EFramebufferAttach IneFramebufferAttach) noexcept;
	inline void SetFramebufferTex(EFramebufferTex IneFramebufferTex) noexcept;

	//Get
	constexpr inline int32 GetLevel() const noexcept;

	constexpr inline Texture& GetTexture() const noexcept;

	constexpr inline EFramebufferOp GetFramebufferOp() const noexcept;
	constexpr inline EFramebufferAttach GetFramebufferAttach() const noexcept;
	constexpr inline EFramebufferTex GetFramebufferTex() const noexcept;
	
	
protected:
	Log* rLog = new Log("LogFrameBuffer");

	Texture* rTexture;

	void CreateBuffer();

private:

};


inline void Framebuffer::SetLevel(int32 IniLevel) noexcept { iLevel = IniLevel; }
inline void Framebuffer::SetTexture(Texture* InrTexture) noexcept { rTexture = InrTexture; }
inline void Framebuffer::SetFramebufferOp(EFramebufferOp IneFramebufferOp) noexcept { eFramebufferOp = IneFramebufferOp; }
inline void Framebuffer::SetFramebufferAttach(EFramebufferAttach IneFramebufferAttach) noexcept { eFramebufferAttach = IneFramebufferAttach; }
inline void Framebuffer::SetFramebufferTex(EFramebufferTex IneFramebufferTex) noexcept { eFramebufferTex = IneFramebufferTex; }

constexpr int32 Framebuffer::GetLevel() const noexcept { return iLevel; }
constexpr inline Texture& Framebuffer::GetTexture() const noexcept { return *rTexture; }
constexpr inline EFramebufferOp Framebuffer::GetFramebufferOp() const noexcept { return eFramebufferOp; }
constexpr inline EFramebufferAttach Framebuffer::GetFramebufferAttach() const noexcept { return eFramebufferAttach; }
constexpr inline EFramebufferTex Framebuffer::GetFramebufferTex() const noexcept { return eFramebufferTex; }