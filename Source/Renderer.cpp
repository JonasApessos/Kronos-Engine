#include "Renderer.h"


Renderer::Renderer()
{
	Initialize();
}

Renderer::~Renderer()
{

}

void Renderer::Initialize()
{
}

void Renderer::EnableMode(EGLEnable IneEnable, bool InbEnable)
{
	if (InbEnable && !IsModeEnabled(IneEnable))
	{
		glEnable(static_cast<GLenum>(IneEnable));
		
		rLog.WriteAndDisplay("Mode " + TransModeToStr(IneEnable)  + " is Enabled");
	}
	else if (!InbEnable && IsModeEnabled(IneEnable))
	{
		glDisable(static_cast<GLenum>(IneEnable));

		rLog.WriteAndDisplay("Mode " + TransModeToStr(IneEnable)  + " is Disabled");
	}
	else
	{
		string sTemp = (IsModeEnabled(IneEnable) ? "Enabled" : "Disabled");

		rLog.WriteAndDisplay("Mode " + TransModeToStr(IneEnable)  + " is already " + sTemp);
	}

	DisplayAllGLError();
}

string Renderer::TransModeToStr(EGLEnable IneEnable)
{
	switch(IneEnable)
	{
		case EGLEnable::EGLE_Blend:
			return "GL_BLEND";

		case EGLEnable::EGLE_ClipDistance:
			return "GL_CLIP_DISTANCE";

		case EGLEnable::EGLE_ColorLogicOP:
			return "GL_COLOR_LOGIC_OP";

		case EGLEnable::EGLE_CullFace:
			return "GL_CULL_FACE";

		case EGLEnable::EGLE_DebugOutput:
			return "GL_DEBUG_OUTPUT";

		case EGLEnable::EGLE_DebugOutputSynchronous:
			return "GL_DEBUG_OUTPUT_SYNCHRONOUS";

		case EGLEnable::EGLE_DepthClamp:
			return "GL_DEPTH_CLAMP";

		case EGLEnable::EGLE_DepthTest:
			return "GL_DEPTH_TEST";

		case EGLEnable::EGLE_Dither:
			return "GL_DITHER";

		case EGLEnable::EGLE_FramebufferSRGB:
			return "GL_FRAMEBUFFER_SRGB";

		case EGLEnable::EGLE_LineSmooth:
			return "GL_LINE_SMOOTH";

		case EGLEnable::EGLE_Multisample:
			return "GL_MULTISAMPLE";

		case EGLEnable::EGLE_PolygonOffsetFill:
			return "GL_POLYGON_OFFSET_FILL";

		case EGLEnable::EGLE_PolygonOffsetLine:
			return "GL_POLYGON_OFFSET_LINE";

		case EGLEnable::EGLE_PolygonOffsetPoint:
			return "GL_POLYGON_OFFSET_POINT";

		case EGLEnable::EGLE_PolygonSmooth:
			return "GL_POLYGON_SMOOTH";

		case EGLEnable::EGLE_PrimitiveRestart:
			return "GL_PRIMITIVE_RESTART";

		case EGLEnable::EGLE_PrimitiveRestartFixedIndex:
			return "GL_PRIMITIVE_RESTART_FIXED_INDEX";

		case EGLEnable::EGLE_ProgramPointSize:
			return "GL_PROGRAM_POINT_SIZE";

		case EGLEnable::EGLE_RasterizerDiscard:
			return "GL_RASTERIZER_DISCARD";

		case EGLEnable::EGLE_SampleAlphaToCoverage:
			return "GL_SAMPLE_ALPHA_TO_COVERAGE";

		case EGLEnable::EGLE_SampleAlphaToOne:
			return "GL_SAMPLE_ALPHA_TO_ONE";

		case EGLEnable::EGLE_SampleCoverage:
			return "GL_SAMPLE_COVERAGE";

		case EGLEnable::EGLE_SampleMask:
			return "GL_SAMPLE_MASK";

		case EGLEnable::EGLE_SampleShading:
			return "GL_SAMPLE_SHADING";

		case EGLEnable::EGLE_ScissorTest:
			return "GL_SCISSOR_TEST";

		case EGLEnable::EGLE_StencilTest:
			return "GL_STENCIL_TEST";

		case EGLEnable::EGLE_TextureCubemapSeamless:
			return "GL_TEXTURE_CUBEMAP_SEAMPLESS";
	}

	return "Unknown GL Command";
}