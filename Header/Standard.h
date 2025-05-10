#pragma once

#include "Primitives.h"

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "Log.h"

using KronosPrim::uint32;

enum class EGLFWError: uint32
{
	EGLFWE_NoError = GLFW_NO_ERROR,
	EGLFWE_NotInitialized = GLFW_NOT_INITIALIZED,
	EGLFWE_NoCurrentContext = GLFW_NO_CURRENT_CONTEXT,
	EGLFWE_InvalidEnum = GLFW_INVALID_ENUM,
	EGLFWE_InvalidValue = GLFW_INVALID_VALUE,
	EGLFWE_OutOfMemory = GLFW_OUT_OF_MEMORY,
	EGLFWE_ApiUnavailable = GLFW_API_UNAVAILABLE,
	EGLFWE_VersionUnavailable = GLFW_VERSION_UNAVAILABLE,
	EGLFWE_PlatformError = GLFW_PLATFORM_ERROR,
	EGLFWE_FormatUnavailable = GLFW_FORMAT_UNAVAILABLE,
	EGLFWE_NoWindowContext = GLFW_NO_WINDOW_CONTEXT,
	EGLFWE_CursorUnavailable = GLFW_CURSOR_UNAVAILABLE,
	EGLFWE_FeatureUnavailable = GLFW_FEATURE_UNAVAILABLE,
	EGLFWE_FeatureUnimplemented = GLFW_FEATURE_UNIMPLEMENTED,
	EGLFWE_PlatformUnavailable = GLFW_PLATFORM_UNAVAILABLE
};

/** @enum EGLError
	@brief opengl error flags*/
enum class EGLError : uint32
{
	EGLE_NoError = GL_NO_ERROR,
	EGLE_InvalidEnum = GL_INVALID_ENUM,
	EGLE_InvalidValue = GL_INVALID_VALUE,
	EGLE_InvalidOperation = GL_INVALID_OPERATION,
	EGLE_InvalidFramebufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION,
	EGLE_OutOfMemory = GL_OUT_OF_MEMORY,
	EGLE_StackUnderflow = GL_STACK_UNDERFLOW,
	EGLE_StackOverflow = GL_STACK_OVERFLOW
};

string GLFWErrorToString(uint32 IniErrorCode);

bool GLError(uint32 IniGLError);

void DisplayAllGLError();