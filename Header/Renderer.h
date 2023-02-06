#pragma once
#include <GL/glew.h>
#include "Primitives.h"

using KronosPrim::uint16;

enum EGLEnable : uint16
{
	EGLE_Blend = GL_BLEND,
	EGLE_ClipDistance = GL_CLIP_DISTANCE0,
	EGLE_ColorLogicOP = GL_COLOR_LOGIC_OP,
	EGLE_CullFace = GL_CULL_FACE,
	EGLE_DebugOutput = GL_DEBUG_OUTPUT,
	EGLE_DebugOutputSynchronous = GL_DEBUG_OUTPUT_SYNCHRONOUS,
	EGLE_DepthClamp = GL_DEPTH_CLAMP,
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
	EGLE_TextureCubeMapSeamlles = GL_TEXTURE_CUBE_MAP_SEAMLESS,
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

enum EGLDepthFunc : uint16
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

enum ECullFace : uint16
{
	ECF_CullBack = GL_BACK,
	ECF_CullFace = GL_CULL_FACE,
	ECF_CullFrontAndBack = GL_FRONT_AND_BACK
};

class Renderer
{
public:
	Renderer();

	~Renderer();

	void Initialize();


	void SetViewMode();

	inline void Enable(const EGLEnable InrFlag);

	inline void SetDepthFunc(const EGLDepthFunc InrFlag);

	inline void GetViewMode() const;

	inline void GetDepthFunc() const;
	inline void GetEnabledState() const;
	inline void GetCullFace() const;
	inline void GetDrawBuffer() const;

protected:

private:
};


inline void Renderer::SetViewMode() { }

inline void Renderer::Enable(const EGLEnable InrFlag) { glEnable(InrFlag); }

inline void Renderer::SetDepthFunc(const EGLDepthFunc InrFlag) { glDepthFunc(InrFlag); }



inline void Renderer::GetViewMode() const { }

inline void Renderer::GetDepthFunc() const { }

inline void Renderer::GetEnabledState() const { }

inline void Renderer::GetCullFace() const { }

inline void Renderer::GetDrawBuffer() const { }

