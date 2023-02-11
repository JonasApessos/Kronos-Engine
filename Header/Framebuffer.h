#pragma once
#include <GL/glew.h>
#include <iostream>
#include "Log.h"

#include "Primitives.h"
#include "Texture.h"

using KronosPrim::int32, KronosPrim::uint32, KronosPrim::uint16;
using std::cout, std::cerr, std::to_string;

class Log;

enum EFramebufferStatus : uint16
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

enum EFramebufferOp : uint16
{
	EFO_Draw = GL_DRAW_FRAMEBUFFER,
	EFO_Read = GL_READ_FRAMEBUFFER,
	EFO_FrameBuffer = GL_FRAMEBUFFER
};

enum EFramebufferAttach : uint16
{
	EFA_Color = GL_COLOR_ATTACHMENT0,
	EFA_Depth = GL_DEPTH_ATTACHMENT,
	EFA_Stencil = GL_STENCIL_ATTACHMENT,
	EFA_DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT,
};

enum EFrambufferCubemap : uint16
{
	EFC_TexturePosX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	EFC_TextureNegX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	EFC_TexturePosY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	EFC_TextureNegY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	EFC_TexturePosZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	EFC_TextureNegZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

enum EFramebufferTex : uint16
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

	Texture* rTexture;

	Framebuffer(EFramebufferOp IneFrameBufferOp, EFramebufferAttach IneFramebufferAttach, EFramebufferTex IneFramebufferTex, Texture* InrTexture, int32 IniLevel);
	
	~Framebuffer();

	void Destroy();
	
	
protected:
	Log rLog;

private:

};

