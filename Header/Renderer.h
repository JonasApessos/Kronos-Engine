#pragma once
#include <GL/glew.h>
#include "Primitives.h"
#include "Log.h"
#include "Standard.h"
#include "Vertex.h"

using KronosPrim::uint8, KronosPrim::uint16, KronosPrim::uint32;

enum EGLEnable : uint16
{
	EGLE_Blend = GL_BLEND,
	EGLE_ClipDistance = GL_CLIP_DISTANCE0,
	EGLE_ColorLogicOP = GL_COLOR_LOGIC_OP,
	EGLE_CullFace = GL_CULL_FACE,
	EGLE_DebugOutput = GL_DEBUG_OUTPUT,
	EGLE_DebugOutputSynchronous = GL_DEBUG_OUTPUT_SYNCHRONOUS,
	EGLE_DepthClamp = GL_DEPTH_CLAMP,
	EGLE_DepthTest = GL_DEPTH_TEST,
	EGLE_Dither = GL_DITHER,
	EGLE_FramebufferSRGB = GL_FRAMEBUFFER_SRGB,
	EGLE_LineSmooth = GL_LINE_SMOOTH,
	EGLE_Multisample = GL_MULTISAMPLE,
	EGLE_PolygonOffsetFill = GL_POLYGON_OFFSET_FILL,
	EGLE_PolygonOffsetLine = GL_POLYGON_OFFSET_LINE,
	EGLE_PolygonOffsetPoint = GL_POLYGON_OFFSET_POINT,
	EGLE_PolygonSmooth = GL_POLYGON_SMOOTH,
	EGLE_PrimitiveRestart = GL_PRIMITIVE_RESTART,
	EGLE_PrimitiveRestartFixedIndex = GL_PRIMITIVE_RESTART_FIXED_INDEX,
	EGLE_RasterizerDiscard = GL_RASTERIZER_DISCARD,
	EGLE_SampleAlphaToCoverage = GL_SAMPLE_ALPHA_TO_COVERAGE,
	EGLE_SampleAlphaToOne = GL_SAMPLE_ALPHA_TO_ONE,
	EGLE_SampleCoverage = GL_SAMPLE_COVERAGE,
	EGLE_SampleShading = GL_SAMPLE_SHADING,
	EGLE_SampleMask = GL_SAMPLE_MASK,
	EGLE_ScissorTest = GL_SCISSOR_TEST,
	EGLE_StencilTest = GL_STENCIL_TEST,
	EGLE_TextureCubemapSeamles = GL_TEXTURE_CUBE_MAP_SEAMLESS,
	EGLE_ProgramPointSize = GL_PROGRAM_POINT_SIZE
};

enum EGLDrawBuffer : uint16
{
	EGLDB_None = GL_NONE,
	EGLDB_FrontLeft = GL_FRONT_LEFT,
	EGLDB_FrontRight = GL_FRONT_RIGHT,
	EGLDB_BackLeft = GL_BACK_LEFT,
	EGLDB_BackRight = GL_BACK_RIGHT,
	EGLDB_Front = GL_FRONT,
	EGLDB_Back = GL_BACK,
	EGLDB_Left = GL_LEFT,
	EGLDB_Right = GL_RIGHT,
	EGLDB_FrontAndBack = GL_FRONT_AND_BACK,
};

enum EGLFunc : uint16
{
	EGLDF_Never = GL_NEVER,
	EGLDF_Less = GL_LESS,
	EGLDF_Equal = GL_EQUAL,
	EGLDF_LEqual = GL_LEQUAL,
	EGLDF_Greater = GL_GREATER,
	EGLDF_NotEqual = GL_NOTEQUAL,
	EGLDF_GEqual = GL_GEQUAL,
	EGLDF_Always = GL_ALWAYS
};

enum EGLCullFace : uint16
{
	EGLCF_Back = GL_BACK,
	EGLCF_Face = GL_CULL_FACE,
	EGLCF_FrontAndBack = GL_FRONT_AND_BACK
};

enum EGLStencilOp : uint16
{
	EGLSO_Keep = GL_KEEP,
	EGLSO_Zero = GL_ZERO,
	EGLSO_Replace = GL_REPLACE,
	EGLSO_Incr = GL_INCR,
	EGLSO_IncrWrap = GL_INCR_WRAP,
	EGLSO_Decr = GL_DECR,
	EGLSO_DecrWrap = GL_DECR_WRAP,
	EGLSO_Invert = GL_INVERT
};

enum EGLPolygonMode : uint16
{
	EGLP_Point = GL_POINT,
	EGLP_Line = GL_LINE,
	EGLP_Fill = GL_FILL
};

enum EGLClearBuffer : uint16
{
	EGLC_ColorBufferBit = GL_COLOR_BUFFER_BIT,
	EGLC_DepthBufferBit = GL_DEPTH_BUFFER_BIT,
	EGLC_StencilBufferBit = GL_STENCIL_BUFFER_BIT
};

enum EViewMode : uint8
{
	EVM_Solid = 0,
	EVM_Unlit = 1,
	EVM_Wireframe = 2,
	EVM_Color = 3,
	EVM_Shadow = 4,
	EVM_Preview = 5
};

class Renderer
{
public:
	Renderer();

	~Renderer();

	void Initialize();

	bool EnableMode(EGLEnable IneEnable, bool InbEnable);

	inline void Clear();

	inline void EnableDepthMask(bool InbEnable);

	inline bool IsModeEnabled(EGLEnable IneEnable);

	inline void SetCullFace(EGLCullFace IneCullFace);

	inline void SetStencilMask(uint32 IniStencilMask);

	inline void SetStencilFunc(EGLFunc IneFunc, int32 IniRef);
	inline void SetStencilFunc(EGLFunc IneFunc, int32 IniRef, uint32 IniMask);

	inline void SetStencilOp(EGLStencilOp IneStencilOp);
	inline void SetStencilOp(EGLStencilOp IneStencilOpFail, EGLStencilOp IneStencilOpZFail, EGLStencilOp IneStencilOpPass);

	inline void SetPolygonMode(EGLCullFace IneCullFace, EGLPolygonMode InePolygoneMode);

	inline void SetDepthFunc(const EGLFunc InrFlag);

	inline void SetClearBuffer(uint16 IniClearFlag);

	inline void SetClearColor(float InfRGB, float InfAlpha);
	inline void SetClearColor(float InfR, float InfG, float InfB, float InfAlpha);
	inline void SetClearColor(const vec3& InrColor, float InfAlpha);

	inline EViewMode GetViewMode() const;

	inline EGLCullFace GetCullFace() const;
	inline EGLDrawBuffer GetDrawBuffer() const;

	

protected:
	//TODO: Set it as a pointer, as in the future there will be a factory class making those!
	Log rLog;

private:
	
	uint16 iClearBufferBit = EGLClearBuffer::EGLC_ColorBufferBit;

	uint32 iStencilMask = 0xFF;

	EGLCullFace eCullFace = EGLCullFace::EGLCF_Back;
	EGLDrawBuffer eDrawBuffer = EGLDrawBuffer::EGLDB_Front;
	EGLFunc eDepthFunc = EGLFunc::EGLDF_Less;
	EGLFunc eStencilFunc = EGLFunc::EGLDF_GEqual;
	EGLStencilOp eStencilOp = EGLStencilOp::EGLSO_Keep;
	EGLPolygonMode ePolygonMode = EGLPolygonMode::EGLP_Fill;
	EViewMode eViewMode = EViewMode::EVM_Solid;

};

inline void Renderer::EnableDepthMask(bool InbEnable) { glDepthMask(static_cast<GLboolean>(InbEnable)); }

inline void Renderer::Clear() { glClear(iClearBufferBit); }

inline bool Renderer::IsModeEnabled(EGLEnable IneEnable) { return static_cast<bool>(static_cast<GLenum>(glIsEnabled(IneEnable))); }

inline void Renderer::SetCullFace(EGLCullFace IneCullFace) { eCullFace = IneCullFace;  glCullFace(static_cast<GLenum>(eCullFace)); }

inline void Renderer::SetStencilMask(uint32 IniStencilMask) { iStencilMask = IniStencilMask;  glStencilMask(static_cast<GLuint>(iStencilMask)); }

inline void Renderer::SetStencilFunc(EGLFunc IneFunc, int32 IniRef)
{
	glStencilFunc(static_cast<GLenum>(IneFunc), static_cast<GLint>(IniRef), static_cast<GLuint>(iStencilMask));
}

inline void Renderer::SetStencilFunc(EGLFunc IneFunc, int32 IniRef, uint32 IniMask) 
{ 
	glStencilFunc(static_cast<GLenum>(IneFunc), static_cast<GLint>(IniRef), static_cast<GLuint>(IniMask)); 
}

inline void Renderer::SetStencilOp(EGLStencilOp IneStencilOp)
{
	eStencilOp = IneStencilOp;
	glStencilOp(static_cast<GLenum>(eStencilOp), static_cast<GLenum>(eStencilOp), static_cast<GLenum>(eStencilOp));
}

inline void Renderer::SetStencilOp(EGLStencilOp IneStencilOpFail, EGLStencilOp IneStencilOpZFail, EGLStencilOp IneStencilOpPass) 
{ 
	eStencilOp = IneStencilOpPass;

	glStencilOp(static_cast<GLenum>(IneStencilOpFail), static_cast<GLenum>(IneStencilOpZFail), static_cast<GLenum>(eStencilOp));
}

inline void Renderer::SetPolygonMode(EGLCullFace IneCullFace, EGLPolygonMode InePolygoneMode)
{
	ePolygonMode = InePolygoneMode;
	glPolygonMode(static_cast<GLenum>(IneCullFace), static_cast<GLenum>(InePolygoneMode));
}


inline void Renderer::SetClearColor(float InfRGB, float InfAlpha) 
{ 
	glClearColor(static_cast<GLclampf>(InfRGB), static_cast<GLclampf>(InfRGB), static_cast<GLclampf>(InfRGB), static_cast<GLclampf>(InfAlpha));
}
inline void Renderer::SetClearColor(float InfR, float InfG, float InfB, float InfAlpha) 
{ 
	glClearColor(static_cast<GLclampf>(InfR), static_cast<GLclampf>(InfG), static_cast<GLclampf>(InfB), static_cast<GLclampf>(InfAlpha));
}
inline void Renderer::SetClearColor(const vec3& InrColor, float InfAlpha) 
{ 
	glClearColor(static_cast<GLclampf>(InrColor.r), static_cast<GLclampf>(InrColor.g), static_cast<GLclampf>(InrColor.b), static_cast<GLclampf>(InfAlpha));
}

inline void Renderer::SetDepthFunc(const EGLFunc IneFunc) { glDepthFunc(IneFunc); }
inline void Renderer::SetClearBuffer(uint16 IniClearFlag) { iClearBufferBit = IniClearFlag; }

inline EViewMode Renderer::GetViewMode() const { return eViewMode;  }

inline EGLCullFace Renderer::GetCullFace() const { return eCullFace; }

inline EGLDrawBuffer Renderer::GetDrawBuffer() const { return eDrawBuffer; }



