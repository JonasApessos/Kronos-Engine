#include "Standard.h"


Log rGLLog = Log("LogOpenGL");


bool GLError(uint16 IniGLError)
{
	switch (IniGLError)
	{
	case EGLError::EGLE_NoError:
		rGLLog.WriteAndDisplay("No errors detected", ELogSeverity::ELS_Info);
		return false;
	case EGLError::EGLE_InvalidEnum:
		rGLLog.WriteAndDisplay("unacceptable value has been parsed", ELogSeverity::ELS_Error);
		break;
	case EGLError::EGLE_InvalidValue:
		rGLLog.WriteAndDisplay("numeric argument is out of range", ELogSeverity::ELS_Error);
		break;
	case EGLError::EGLE_InvalidOperation:
		rGLLog.WriteAndDisplay("Specific operation not allowed in current state", ELogSeverity::ELS_Error);
		break;
	case EGLError::EGLE_InvalidFramebufferOperation:
		rGLLog.WriteAndDisplay("Framebuffer object not completed", ELogSeverity::ELS_Error);
		break;
	case EGLError::EGLE_OutOfMemory:
		rGLLog.WriteAndDisplay("Not enought memory to execute command", ELogSeverity::ELS_Critical);
		break;
	case EGLError::EGLE_StackUnderflow:
		rGLLog.WriteAndDisplay("attemped operation that could cause an underflow", ELogSeverity::ELS_Critical);
		break;
	case EGLError::EGLE_StackOverflow:
		rGLLog.WriteAndDisplay("attemped operation that could cause an overflow", ELogSeverity::ELS_Critical);
		break;
	default:
		rGLLog.WriteAndDisplay("Multyple Errors Detected", ELogSeverity::ELS_Critical);
	}

	return true;
}


void DisplayAllGLError()
{
	GLenum ErrorCode = glGetError();

	do
	{
		GLError(ErrorCode);
	} while (ErrorCode = glGetError());
}