#pragma once

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Standard.h"
#include "Primitives.h"
#include "Log.h"
#include "InputManager.h"

using KronosPrim::uint32;

/** @enum EHints
*   @brief GLFW window hint flags*/
enum class ECanvasHints : uint32
{
	ECH_REDBits = GLFW_RED_BITS,
	ECH_GreenBits = GLFW_GREEN_BITS,
	ECH_BlueBits = GLFW_BLUE_BITS,
	ECH_AlphaBits = GLFW_ALPHA_BITS,
	ECH_DepthBits = GLFW_DEPTH_BITS,
	ECH_StencilBits = GLFW_STENCIL_BITS,
	ECH_AccumRedBits = GLFW_ACCUM_RED_BITS,
	ECH_AccumGreenBits = GLFW_ACCUM_GREEN_BITS,
	ECH_AccumBlueBits = GLFW_ACCUM_BLUE_BITS,
	ECH_AccumAlphaBits = GLFW_ACCUM_ALPHA_BITS,
	ECH_AuxBuffers = GLFW_AUX_BUFFERS,
	ECH_Stereo = GLFW_STEREO,
	ECH_Samples = GLFW_SAMPLES,
	ECH_SRGBCapable = GLFW_SRGB_CAPABLE,
	ECH_DoubleBuffer = GLFW_DOUBLEBUFFER,
	ECH_RefreshRate = GLFW_REFRESH_RATE,
	ECH_ClientApi = GLFW_CLIENT_API,
	ECH_ContextCreationApi = GLFW_CONTEXT_CREATION_API,
	ECH_ContextVersionMajor = GLFW_CONTEXT_VERSION_MAJOR,
	ECH_ContextVersionMinor = GLFW_CONTEXT_VERSION_MINOR,
	ECH_VersionMajor = GLFW_VERSION_MAJOR,
	ECH_VersionMinor = GLFW_VERSION_MINOR,
	ECH_OpenglForwardCompat = GLFW_OPENGL_FORWARD_COMPAT,
	ECH_OpenglDebugContext = GLFW_OPENGL_DEBUG_CONTEXT,
	ECH_OpenglProfile = GLFW_OPENGL_PROFILE,
	ECH_ContextRobustness = GLFW_CONTEXT_ROBUSTNESS,
	ECH_ContextReleaseBehavior = GLFW_CONTEXT_RELEASE_BEHAVIOR,
	ECH_ContextNoError = GLFW_CONTEXT_NO_ERROR,
	ECH_CocoaRetinaFramebuffer = GLFW_COCOA_RETINA_FRAMEBUFFER,
	ECH_CocoaFrameName = GLFW_COCOA_FRAME_NAME,
	ECH_CocoaGraphicsSwitching = GLFW_COCOA_GRAPHICS_SWITCHING,
	ECH_X11ClassName = GLFW_X11_CLASS_NAME,
	ECH_X11InstanceName = GLFW_X11_INSTANCE_NAME

};

/** @enum EError
*   @brief GLFW error types*/
enum class ECanvasError : uint32
{
	ECE_NoError = GLFW_NO_ERROR,
	ECE_NotInit = GLFW_NOT_INITIALIZED,
	ECE_NoCurrentContext = GLFW_NO_CURRENT_CONTEXT,
	ECE_InvalidEnum = GLFW_INVALID_ENUM,
	ECE_InvaludValue = GLFW_INVALID_VALUE,
	ECE_OutOfMemory = GLFW_OUT_OF_MEMORY,
	ECE_ApiUnavailable = GLFW_API_UNAVAILABLE,
	ECE_VersionUnavailable = GLFW_VERSION_UNAVAILABLE,
	ECE_PlatformError = GLFW_PLATFORM_ERROR,
	ECE_FormatUnavailable = GLFW_FORMAT_UNAVAILABLE,
	ECE_NoWindowContect = GLFW_NO_WINDOW_CONTEXT
};

/** @class Canvas
*   @brief unified window system using glfw library*/
class Canvas
{
public:
	bool bIsAspectLocked = true;

	Canvas(int32 IniWidth, int32 IniHeight, string const& InsTitle);
	Canvas(Canvas&& InrCanvas) noexcept;
	Canvas(Canvas const& InrCanvas) noexcept;

	~Canvas();

	Canvas& operator=(Canvas const& InrCanvas) noexcept;
	Canvas& operator=(Canvas&& InrCanvas) noexcept;

	void Destroy();

	inline void SetIsAspectLocked(bool InbIsAspectLocked);

	void SetAspect(float InfAspectScalar);
	void SetAspect(float IniAspectX, float IniAspectY);

	inline void SetScreenSize(int32 IniWidth, int32 IniHeight);
	inline void SetWidth(int32 IniWidth);
	inline void SetHeight(int32 IniHeight);

	inline bool GetIsAspectLocked() const;

	inline float GetAspectRatioWidth() const;
	inline float GetAspectRatioHeight() const;

	inline int32 GetWidth();
	inline int32 GetHeight();

	inline GLFWwindow* GetWindow() const;

protected:
	float fRatioX = 16.0f, fRatioY = 9.0f;
	int32 iWidth = 1280, iHeight = iWidth * static_cast<int32>(fRatioY / fRatioX);
	float fScaleX = 1.f, fScaleY = 1.f;

	string sTitle = "";

	Log rLog = Log("LogWindow");

	GLFWwindow* rWindow = nullptr;
	GLFWmonitor* rMonitor = nullptr;
	GLFWvidmode rVidMode;

	inline GLFWwindow* CreateWindow();

	static void OnResize(GLFWwindow* InrWindow, int32 IniWidth, int32 IniHeight);

private:

	void Init();
};

inline GLFWwindow* Canvas::CreateWindow()
{
	// Open a window and create its OpenGL context
	return glfwCreateWindow(static_cast<int>(iWidth), static_cast<int>(iHeight), sTitle.c_str(), NULL, NULL);
}

inline void Canvas::SetIsAspectLocked(bool InbIsApsectLocked) { bIsAspectLocked = InbIsApsectLocked; }

inline void Canvas::SetScreenSize(int32 IniWidth, int32 IniHeight) { iWidth = IniWidth; iHeight = IniHeight; }
inline void Canvas::SetWidth(int32 IniWidth) { iWidth = (IniWidth * IniWidth > 0) + (iWidth * IniWidth <= 0); }
inline void Canvas::SetHeight(int32 IniHeight) { iHeight = (IniHeight * IniHeight > 0) + static_cast<int32>(iWidth * (fRatioY / fRatioX) * IniHeight <= 0); }


inline bool Canvas::GetIsAspectLocked() const { return bIsAspectLocked; }

inline float Canvas::GetAspectRatioWidth() const { return fRatioX / fRatioY; }
inline float Canvas::GetAspectRatioHeight() const { return fRatioY / fRatioX; }

inline int32 Canvas::GetWidth() { glfwGetWindowSize(rWindow, &iWidth, &iHeight); return iWidth; }
inline int32 Canvas::GetHeight() { glfwGetWindowSize(rWindow, &iWidth, &iHeight); return iHeight; }

inline GLFWwindow* Canvas::GetWindow() const { return rWindow; }