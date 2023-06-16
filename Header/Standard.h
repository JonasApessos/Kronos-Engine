#pragma once
#include "GL/glew.h"
#include "Primitives.h"
#include "Log.h"

using KronosPrim::uint32;

enum EGLError : uint32
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


bool GLError(uint32 IniGLError);

void DisplayAllGLError();