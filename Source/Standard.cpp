#include "Standard.h"

bool GLError(uint32 IniGLError)
{
	Log rGLLog("LogOpenGL");

	switch (IniGLError)
	{
	case static_cast<GLenum>(EGLError::EGLE_NoError):
		rGLLog.WriteAndDisplay("No errors detected", ELogSeverity::ELS_Info);
		return false;
	case static_cast<GLenum>(EGLError::EGLE_InvalidEnum):
		rGLLog.WriteAndDisplay("Unacceptable value has been parsed", ELogSeverity::ELS_Error);
		break;
	case static_cast<GLenum>(EGLError::EGLE_InvalidValue):
		rGLLog.WriteAndDisplay("Numeric argument is out of range", ELogSeverity::ELS_Error);
		break;
	case static_cast<GLenum>(EGLError::EGLE_InvalidOperation):
		rGLLog.WriteAndDisplay("Specific operation not allowed in current state", ELogSeverity::ELS_Error);
		break;
	case static_cast<GLenum>(EGLError::EGLE_InvalidFramebufferOperation):
		rGLLog.WriteAndDisplay("Framebuffer object not completed", ELogSeverity::ELS_Error);
		break;
	case static_cast<GLenum>(EGLError::EGLE_OutOfMemory):
		rGLLog.WriteAndDisplay("Not enought memory to execute command", ELogSeverity::ELS_Critical);
		break;
	case static_cast<GLenum>(EGLError::EGLE_StackUnderflow):
		rGLLog.WriteAndDisplay("Attemped operation that could cause an underflow", ELogSeverity::ELS_Critical);
		break;
	case static_cast<GLenum>(EGLError::EGLE_StackOverflow):
		rGLLog.WriteAndDisplay("Attemped operation that could cause an overflow", ELogSeverity::ELS_Critical);
		break;
	default:
		rGLLog.WriteAndDisplay("Multiple Errors Detected", ELogSeverity::ELS_Critical);
	}

	return true;
}


void DisplayAllGLError()
{
	GLenum ErrorCode = glGetError();

	do
	{
		GLError(ErrorCode);

	} while ((ErrorCode = glGetError()));
}