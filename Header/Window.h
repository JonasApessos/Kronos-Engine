#pragma once

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Standard.h"
#include "Primitives.h"
#include "Log.h"
#include "InputManager.h"

using KronosPrim::uint32;

/** @enum EGLFWHints
*   @brief GLFW window hint flags*/
enum class EGLFWHints : uint32
{
	EGLFWH_REDBits = GLFW_RED_BITS,
	EGLFWH_GreenBits = GLFW_GREEN_BITS,
	EGLFWH_BlueBits = GLFW_BLUE_BITS,
	EGLFWH_AlphaBits = GLFW_ALPHA_BITS,
	EGLFWH_DepthBits = GLFW_DEPTH_BITS,
	EGLFWH_StencilBits = GLFW_STENCIL_BITS,
	EGLFWH_AccumRedBits = GLFW_ACCUM_RED_BITS,
	EGLFWH_AccumGreenBits = GLFW_ACCUM_GREEN_BITS,
	EGLFWH_AccumBlueBits = GLFW_ACCUM_BLUE_BITS,
	EGLFWH_AccumAlphaBits = GLFW_ACCUM_ALPHA_BITS,
	EGLFWH_AuxBuffers = GLFW_AUX_BUFFERS,
	EGLFWH_Stereo = GLFW_STEREO,
	EGLFWH_Samples = GLFW_SAMPLES,
	EGLFWH_SRGBCapable = GLFW_SRGB_CAPABLE,
	EGLFWH_DoubleBuffer = GLFW_DOUBLEBUFFER,
	EGLFWH_RefreshRate = GLFW_REFRESH_RATE,
	EGLFWH_ClientApi = GLFW_CLIENT_API,
	EGLFWH_ContextCreationApi = GLFW_CONTEXT_CREATION_API,
	EGLFWH_ContextVersionMajor = GLFW_CONTEXT_VERSION_MAJOR,
	EGLFWH_ContextVersionMinor = GLFW_CONTEXT_VERSION_MINOR,
	EGLFWH_VersionMajor = GLFW_VERSION_MAJOR,
	EGLFWH_VersionMinor = GLFW_VERSION_MINOR,
	EGLFWH_OpenglForwardCompat = GLFW_OPENGL_FORWARD_COMPAT,
	EGLFWH_OpenglDebugContext = GLFW_OPENGL_DEBUG_CONTEXT,
	EGLFWH_OpenglProfile = GLFW_OPENGL_PROFILE,
	EGLFWH_ContextRobustness = GLFW_CONTEXT_ROBUSTNESS,
	EGLFWH_ContextReleaseBehavior = GLFW_CONTEXT_RELEASE_BEHAVIOR,
	EGLFWH_ContextNoError = GLFW_CONTEXT_NO_ERROR,
	EGLFWH_CocoaRetinaFramebuffer = GLFW_COCOA_RETINA_FRAMEBUFFER,
	EGLFWH_CocoaFrameName = GLFW_COCOA_FRAME_NAME,
	EGLFWH_CocoaGraphicsSwitching = GLFW_COCOA_GRAPHICS_SWITCHING,
	EGLFWH_X11ClassName = GLFW_X11_CLASS_NAME,
	EGLFWH_X11InstanceName = GLFW_X11_INSTANCE_NAME

};

/** @enum EGLFWError
*   @brief GLFW error types*/
enum class EGLFWError : uint32
{
	EGLFWE_NoError = GLFW_NO_ERROR,
	EGLFWE_NotInit = GLFW_NOT_INITIALIZED,
	EGLFWE_NoCurrentContext = GLFW_NO_CURRENT_CONTEXT,
	EGLFWE_InvalidEnum = GLFW_INVALID_ENUM,
	EGLFWE_InvaludValue = GLFW_INVALID_VALUE,
	EGLFWE_OutOfMemory = GLFW_OUT_OF_MEMORY,
	EGLFWE_ApiUnavailable = GLFW_API_UNAVAILABLE,
	EGLFWE_VersionUnavailable = GLFW_VERSION_UNAVAILABLE,
	EGLFWE_PlatformError = GLFW_PLATFORM_ERROR,
	EGLFWE_FormatUnavailable = GLFW_FORMAT_UNAVAILABLE,
	EGLFWE_NoWindowContect = GLFW_NO_WINDOW_CONTEXT
};

/** @class Window
*   @brief unified window system using glfw library*/
class Window
{
public:
	bool bIsAspectLocked = true;

	Window(int32 IniWidth, int32 IniHeight, string const& InsTitle);
	Window(Window&& InrWindow) noexcept;
	Window(Window const& InrWindow) noexcept;

	~Window();

	Window& operator=(Window const& InrWindow) noexcept;
	Window& operator=(Window&& InrWindow) noexcept;

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
	float iRatioX = 16.0f, iRatioY = 9.0f;
	int32 iWidth = 1280, iHeight = iWidth * static_cast<int32>(iRatioY / iRatioX);

	string sTitle = "";

	Log rLog = Log("LogWindow");

	GLFWwindow* rWindow = nullptr;
	GLFWmonitor* rMonitor = nullptr;
	GLFWvidmode rVidMode;

	inline void CreateWindow();

	static void OnResize(GLFWwindow* InrWindow, int32 IniWidth, int32 IniHeight);

private:

	void Initialize();
};

inline void Window::CreateWindow()
{
	// Open a window and create its OpenGL context
	rWindow = glfwCreateWindow(static_cast<int>(iWidth), static_cast<int>(iHeight), sTitle.c_str(), NULL, NULL);
}

inline void Window::SetIsAspectLocked(bool InbIsApsectLocked) { bIsAspectLocked = InbIsApsectLocked; }

inline void Window::SetScreenSize(int32 IniWidth, int32 IniHeight) { iWidth = IniWidth; iHeight = IniHeight; }
inline void Window::SetWidth(int32 IniWidth) { ((IniWidth > 0) ? iWidth = IniWidth : iWidth = 1024); }
inline void Window::SetHeight(int32 IniHeight) { ((IniHeight > 0) ? iHeight = IniHeight : iHeight = static_cast<int32>(GetAspectRatioHeight() * static_cast<float>(GetWidth()))); }


inline bool Window::GetIsAspectLocked() const { return bIsAspectLocked; }

inline float Window::GetAspectRatioWidth() const { return iRatioX / iRatioY; }
inline float Window::GetAspectRatioHeight() const { return iRatioY / iRatioX; }

inline int32 Window::GetWidth() { int X,Y; glfwGetWindowSize(rWindow, &X, &Y); iWidth = X; iHeight = Y; return iWidth; }
inline int32 Window::GetHeight() { int X,Y; glfwGetWindowSize(rWindow, &X, &Y); iWidth = X; iHeight = Y; return iHeight; }

inline GLFWwindow* Window::GetWindow() const { return rWindow; }