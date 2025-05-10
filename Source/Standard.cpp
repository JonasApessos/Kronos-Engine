#include "Standard.h"

string GLFWErrorToString(uint32 IniErrorCode)
{
	switch(static_cast<EGLFWError>(IniErrorCode))
	{
		case EGLFWError::EGLFWE_NoError:
			return "No Error";
			break;
		
		case EGLFWError::EGLFWE_NotInitialized:
			return "Not Initialized";
			break;
		
		case EGLFWError::EGLFWE_NoCurrentContext:
			return "No Current Context";
			break;

		case EGLFWError::EGLFWE_InvalidEnum:
			return "Invalid Enum";
			break;
		
		case EGLFWError::EGLFWE_InvalidValue:
			return "Invalid Value";
			break;
		
		case EGLFWError::EGLFWE_OutOfMemory:
			return "Out Of Memory";
			break;
		
		case EGLFWError::EGLFWE_ApiUnavailable:
			return "API Unavailable";
			break;

		case EGLFWError::EGLFWE_VersionUnavailable:
			return "Version Unavailable";
			break;
		
		case EGLFWError::EGLFWE_PlatformError:
			return "Platform Error";
			break;
		
		case EGLFWError::EGLFWE_FormatUnavailable:
			return "Format Unavailable";
			break;
		
		case EGLFWError::EGLFWE_NoWindowContext:
			return "No Window Context";
			break;
		
		case EGLFWError::EGLFWE_CursorUnavailable:
			return "Cursor Unavailable";
			break;
		
		case EGLFWError::EGLFWE_FeatureUnavailable:
			return "Feature Unavailable";
			break;
		
		case EGLFWError::EGLFWE_FeatureUnimplemented:
			return "FeatureUnimplemented";
			break;

		case EGLFWError::EGLFWE_PlatformUnavailable:
			return "Platform Unavaulable";
			break;
		
		default:
			return "Unknown";
			break;
	}
}

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