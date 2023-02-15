#pragma once
#include "GL/glew.h"
#include "Primitives.h"
#include "Log.h"

using KronosPrim::uint16;

enum EGLError : uint16
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


bool GLError(uint16 IniGLError);

void DisplayAllGLError();