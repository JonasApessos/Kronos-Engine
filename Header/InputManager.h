#pragma once

#include <vector>
#include <map>

#include "Primitives.h"
#include "InputHandler.h"
#include "Window.h"

using std::map, std::vector, std::to_string;

using KronosPrim::uint64, KronosPrim::uint8;

/** @enum EGLFWInputKey
* 	@brief enum for glfw input key map
*/
enum class EGLFWInputKey : int32
{
	EGLFWIK_Unknown = GLFW_KEY_UNKNOWN,
	EGLFWIK_Space = GLFW_KEY_SPACE,
	EGLFWIK_Apostrophe = GLFW_KEY_APOSTROPHE,
	EGLFWIK_Comma = GLFW_KEY_COMMA,
	EGLFWIK_Minus = GLFW_KEY_MINUS,
	EGLFWIK_Period = GLFW_KEY_PERIOD,
	EGLFWIK_Slash = GLFW_KEY_SLASH,
	EGLFWIK_0 = GLFW_KEY_0,
	EGLFWIK_1 = GLFW_KEY_1,
	EGLFWIK_2 = GLFW_KEY_2,
	EGLFWIK_3 = GLFW_KEY_3,
	EGLFWIK_4 = GLFW_KEY_4,
	EGLFWIK_5 = GLFW_KEY_5,
	EGLFWIK_6 = GLFW_KEY_6,
	EGLFWIK_7 = GLFW_KEY_7,
	EGLFWIK_8 = GLFW_KEY_8,
	EGLFWIK_9 = GLFW_KEY_9,
	EGLFWIK_Semicolon = GLFW_KEY_SEMICOLON,
	EGLFWIK_Equal = GLFW_KEY_EQUAL,
	EGLFWIK_A = GLFW_KEY_A,
	EGLFWIK_B = GLFW_KEY_B,
	EGLFWIK_C = GLFW_KEY_C,
	EGLFWIK_D = GLFW_KEY_D,
	EGLFWIK_E = GLFW_KEY_E,
	EGLFWIK_F = GLFW_KEY_F,
	EGLFWIK_G = GLFW_KEY_G,
	EGLFWIK_H = GLFW_KEY_H,
	EGLFWIK_I = GLFW_KEY_I,
	EGLFWIK_J = GLFW_KEY_J,
	EGLFWIK_K = GLFW_KEY_K,
	EGLFWIK_L = GLFW_KEY_L,
	EGLFWIK_M = GLFW_KEY_M,
	EGLFWIK_N = GLFW_KEY_N,
	EGLFWIK_O = GLFW_KEY_O,
	EGLFWIK_P = GLFW_KEY_P,
	EGLFWIK_Q = GLFW_KEY_Q,
	EGLFWIK_R = GLFW_KEY_R,
	EGLFWIK_S = GLFW_KEY_S,
	EGLFWIK_T = GLFW_KEY_T,
	EGLFWIK_U = GLFW_KEY_U,
	EGLFWIK_V = GLFW_KEY_V,
	EGLFWIK_W = GLFW_KEY_W,
	EGLFWIK_X = GLFW_KEY_X,
	EGLFWIK_Y = GLFW_KEY_Y,
	EGLFWIK_Z = GLFW_KEY_Z,
	EGLFWIK_LeftBracket = GLFW_KEY_LEFT_BRACKET,
	EGLFWIK_BackSlash = GLFW_KEY_BACKSLASH,
	EGLFWIK_RightBracket = GLFW_KEY_RIGHT_BRACKET,
	EGLFWIK_GraveAccent = GLFW_KEY_GRAVE_ACCENT,
	EGLFWIK_World1 = GLFW_KEY_WORLD_1,
	EGLFWIK_World2 = GLFW_KEY_WORLD_2,
	EGLFWIK_Escape = GLFW_KEY_ESCAPE,
	EGLFWIK_Enter = GLFW_KEY_ENTER,
	EGLFWIK_Tab = GLFW_KEY_TAB,
	EGLFWIK_Backspace = GLFW_KEY_BACKSPACE,
	EGLFWIK_Insert = GLFW_KEY_INSERT,
	EGLFWIK_Delete = GLFW_KEY_DELETE,
	EGLFWIK_Right = GLFW_KEY_RIGHT,
	EGLFWIK_Left = GLFW_KEY_LEFT,
	EGLFWIK_Down = GLFW_KEY_DOWN,
	EGLFWIK_Up = GLFW_KEY_UP,
	EGLFWIK_PageUp = GLFW_KEY_PAGE_UP,
	EGLFWIK_PageDown = GLFW_KEY_PAGE_DOWN,
	EGLFWIK_Home = GLFW_KEY_HOME,
	EGLFWIK_End = GLFW_KEY_END,
	EGLFWIK_CapsLock = GLFW_KEY_CAPS_LOCK,
	EGLFWIK_ScrollLock = GLFW_KEY_SCROLL_LOCK,
	EGLFWIK_NumLock = GLFW_KEY_NUM_LOCK,
	EGLFWIK_PrintScreen = GLFW_KEY_PRINT_SCREEN,
	EGLFWIK_Pause = GLFW_KEY_PAUSE,
	EGLFWIK_F1 = GLFW_KEY_F1,
	EGLFWIK_F2 = GLFW_KEY_F2,
	EGLFWIK_F3 = GLFW_KEY_F3,
	EGLFWIK_F4 = GLFW_KEY_F4,
	EGLFWIK_F5 = GLFW_KEY_F5,
	EGLFWIK_F6 = GLFW_KEY_F6,
	EGLFWIK_F7 = GLFW_KEY_F7,
	EGLFWIK_F8 = GLFW_KEY_F8,
	EGLFWIK_F9 = GLFW_KEY_F9,
	EGLFWIK_F10 = GLFW_KEY_F10,
	EGLFWIK_F11 = GLFW_KEY_F11,
	EGLFWIK_F12 = GLFW_KEY_F12,
	EGLFWIK_F13 = GLFW_KEY_F13,
	EGLFWIK_F14 = GLFW_KEY_F14,
	EGLFWIK_F15 = GLFW_KEY_F15,
	EGLFWIK_F16 = GLFW_KEY_F16,
	EGLFWIK_F17 = GLFW_KEY_F17,
	EGLFWIK_F18 = GLFW_KEY_F18,
	EGLFWIK_F19 = GLFW_KEY_F19,
	EGLFWIK_F20 = GLFW_KEY_F20,
	EGLFWIK_F21 = GLFW_KEY_F21,
	EGLFWIK_F22 = GLFW_KEY_F22,
	EGLFWIK_F23 = GLFW_KEY_F23,
	EGLFWIK_F24 = GLFW_KEY_F24,
	EGLFWIK_F25 = GLFW_KEY_F25,
	EGLFWIK_KP0 = GLFW_KEY_KP_0,
	EGLFWIK_KP1 = GLFW_KEY_KP_1,
	EGLFWIK_KP2 = GLFW_KEY_KP_2,
	EGLFWIK_KP3 = GLFW_KEY_KP_3,
	EGLFWIK_KP4 = GLFW_KEY_KP_4,
	EGLFWIK_KP5 = GLFW_KEY_KP_5,
	EGLFWIK_KP6 = GLFW_KEY_KP_6,
	EGLFWIK_KP7 = GLFW_KEY_KP_7,
	EGLFWIK_KP8 = GLFW_KEY_KP_8,
	EGLFWIK_KP9 = GLFW_KEY_KP_9,
	EGLFWIK_KPDecimal = GLFW_KEY_KP_DECIMAL,
	EGLFWIK_KPDivide = GLFW_KEY_KP_DIVIDE,
	EGLFWIK_KPMultiply = GLFW_KEY_KP_MULTIPLY,
	EGLFWIK_KPSubtract = GLFW_KEY_KP_SUBTRACT,
	EGLFWIK_KPAdd = GLFW_KEY_KP_ADD,
	EGLFWIK_KPEnter = GLFW_KEY_KP_ENTER,
	EGLFWIK_KPEqual = GLFW_KEY_KP_EQUAL,
	EGLFWIK_LeftShift = GLFW_KEY_LEFT_SHIFT,
	EGLFWIK_LeftControl = GLFW_KEY_LEFT_CONTROL,
	EGLFWIK_LeftAlt = GLFW_KEY_LEFT_ALT,
	EGLFWIK_LeftSuper = GLFW_KEY_LEFT_SUPER,
	EGLFWIK_RightShift = GLFW_KEY_RIGHT_SHIFT,
	EGLFWIK_RightControl = GLFW_KEY_RIGHT_CONTROL,
	EGLFWIK_RightAlt = GLFW_KEY_RIGHT_ALT,
	EGLFWIK_RightSuper = GLFW_KEY_RIGHT_SUPER,
	EGLFWIK_Menu = GLFW_KEY_MENU,
	EGLFWIK_Last = GLFW_KEY_LAST
};

/** @enum EGLFWMouseKey
* 	@brief enum for glfw input Mouse map*/
enum class EGLFWMouseKey : int32
{
	EGLFWMK_Button1 = GLFW_MOUSE_BUTTON_1,
	EGLFWMK_Button2 = GLFW_MOUSE_BUTTON_2,
	EGLFWMK_Button3 = GLFW_MOUSE_BUTTON_3,
	EGLFWMK_Button4 = GLFW_MOUSE_BUTTON_4,
	EGLFWMK_Button5 = GLFW_MOUSE_BUTTON_5,
	EGLFWMK_Button6 = GLFW_MOUSE_BUTTON_6,
	EGLFWMK_Button7 = GLFW_MOUSE_BUTTON_7,
	EGLFWMK_Button8 = GLFW_MOUSE_BUTTON_8,
	EGLFWMK_Left = GLFW_MOUSE_BUTTON_LEFT,
	EGLFWMK_Middle = GLFW_MOUSE_BUTTON_MIDDLE,
	EGLFWMK_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
	EGLFWMK_Last = GLFW_MOUSE_BUTTON_LAST
};

/** @enum EGLFWGamepadKey
* 	@brief enum for glfw input Gamepad map*/
enum class EGLFWGamepadKey : int32
{
	EGLFWGK_A = GLFW_GAMEPAD_BUTTON_A,
	EGLFWGK_B = GLFW_GAMEPAD_BUTTON_B,
	EGLFWGK_Back = GLFW_GAMEPAD_BUTTON_BACK,
	EGLFWGK_Circle = GLFW_GAMEPAD_BUTTON_CIRCLE,
	EGLFWGK_Cross = GLFW_GAMEPAD_BUTTON_CROSS,
	EGLFWGK_Square = GLFW_GAMEPAD_BUTTON_SQUARE,
	EGLFWGK_Triangle = GLFW_GAMEPAD_BUTTON_TRIANGLE,
	EGLFWGK_DPadDown = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
	EGLFWGK_DPadLeft = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
	EGLFWGK_DPadRight = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
	EGLFWGK_DPadUp = GLFW_GAMEPAD_BUTTON_DPAD_UP,
	EGLFWGK_Guide = GLFW_GAMEPAD_BUTTON_GUIDE,
	EGLFWGK_LeftBumper = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
	EGLFWGK_RightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
	EGLFWGK_LeftThump = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
	EGLFWGK_RightThump = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
	EGLFWGK_Start = GLFW_GAMEPAD_BUTTON_START,
	EGLFWGK_Last = GLFW_GAMEPAD_BUTTON_LAST
};

/** @enum EGLFWJoysticKey
* 	@brief enum for glfw input Joystic map*/
enum class EGLFWJoysticKey : int32
{
	EGLFWJK_1 = GLFW_JOYSTICK_1,
	EGLFWJK_2 = GLFW_JOYSTICK_2,
	EGLFWJK_3 = GLFW_JOYSTICK_3,
	EGLFWJK_4 = GLFW_JOYSTICK_4,
	EGLFWJK_5 = GLFW_JOYSTICK_5,
	EGLFWJK_6 = GLFW_JOYSTICK_6,
	EGLFWJK_7 = GLFW_JOYSTICK_7,
	EGLFWJK_8 = GLFW_JOYSTICK_8,
	EGLFWJK_9 = GLFW_JOYSTICK_9,
	EGLFWJK_10 = GLFW_JOYSTICK_10,
	EGLFWJK_11 = GLFW_JOYSTICK_11,
	EGLFWJK_12 = GLFW_JOYSTICK_12,
	EGLFWJK_13 = GLFW_JOYSTICK_13,
	EGLFWJK_14 = GLFW_JOYSTICK_14,
	EGLFWJK_15 = GLFW_JOYSTICK_15,
	EGLFWJK_16 = GLFW_JOYSTICK_16,
	EGLFWJK_Last = GLFW_JOYSTICK_LAST,
};

/** @enum EGLFWModKey
* 	@brief enum for glfw input Mod map*/
enum class EGLFWModKey : int32
{
	EGLFWMK_Shift = GLFW_MOD_SHIFT,
	EGLFWMK_Control = GLFW_MOD_CONTROL,
	EGLFWMK_Alt = GLFW_MOD_ALT,
	EGLFWMK_Super = GLFW_MOD_SUPER,
	EGLFWMK_CapsLock = GLFW_MOD_CAPS_LOCK,
	EGLFWMK_NumLock = GLFW_MOD_NUM_LOCK
};

/** @enum EGLFWInputState
* 	@brief enum for glfw key state*/
enum class EGLFWInputState : int32
{
	EGLFWIS_Release = GLFW_RELEASE,
	EGLFWIS_Press = GLFW_PRESS,
	EGLFWIS_Repeat = GLFW_REPEAT
};

/** @enum EDeviceType
* 	@brief enum for input Device type*/
enum class EDeviceType : uint8
{
	EDT_Keyboard = 0,
	EDT_Mouse = 1,
	EDT_Joystic = 2,
	EDT_Gamepad = 3,
	EDT_Unknown = 4
};

/** @struct SKeyInputFrame
* 	@brief structure for keyboard input frame
*	capture input event per frame
*/
struct SKeyInputFrame
{
	bool IsInputConsumed = true;
	EGLFWInputKey eKeyPressed;
	uint32 iScanCode;
	EGLFWInputState eAction;
	EGLFWModKey iMods;
};

/** @struct SMouseMotionInputFrame
* 	@brief structure for Mouse motion input frame
*	capture input event per frame
*/
struct SMouseMotionInputFrame
{
	bool IsInputConsumed = true;
	double dXPos, dYPos;
};

/** @struct SMouseScrollInputFrame
* 	@brief structure for Mouse scroll input frame
*	capture input event per frame
*/
struct SMouseScrollInputFrame
{
	bool IsInputConsumed = true;
	double dScrollX, dScrollY;
};

/** @struct SMouseKeyInputFrame
* 	@brief structure for Mouse key input frame
*	capture input event per frame
*/
struct SMouseKeyInputFrame
{
	bool IsInputConsumed = true;
	EGLFWMouseKey eMouseKey;
	EGLFWInputState eInputState;
	EGLFWModKey iMods;
};

/** @struct SInputInfo
* 	@brief structure for input info bridge.
*	This structure serves as a bridge between
*	Input Frames and callback functions
*/
struct SInputInfo
{
	string sName;
	int32 iInputKey;
	int32 iInputState;
	int32 iInputMod;
	void (*rCallback)();

	SInputInfo(string InsName,
	int32 IniInputKey,
	int32 IniInputState,
	int32 IniInputMod,
	void (*InrCallback)()) :
	sName(InsName),
	iInputKey(IniInputKey),
	iInputState(IniInputState),
	iInputMod(IniInputMod),
	rCallback(*InrCallback) {}
};

/** @class InputManager
*   @brief Singleton class that manages keyboard input*/
class InputManager
{
public:

	InputManager(InputManager const&) = delete;
	InputManager(InputManager&&) = delete;

	InputManager& operator=(InputManager const&) = delete;
	InputManager& operator=(InputManager&&) = delete;

	static InputManager* GetInstance();

	static inline void SetCurrentWindow(GLFWwindow* InrWindowP);

	static inline GLFWwindow* GetCurrentWindow();
	static inline SKeyInputFrame GetKeyInputFrame();
	static inline SMouseKeyInputFrame GetMouseKeyInputFrame();
	static inline SMouseMotionInputFrame GetMouseMotionInputFrame();
	static inline SMouseScrollInputFrame GetMouseScrollInputFrame();

	static void BindInput(string const& InsName, EGLFWInputKey IneInputKey, EGLFWInputState IneInputState, void (*InrCallback)());
	static void BindInput(string const& InsName, EGLFWMouseKey IneInputMouseKey, EGLFWInputState IneInputState, void (*InrCallback)());
	static void BindInput(string const& InsName, EDeviceType IneDeviceType, void (*InrCallback)());

	static void ProcessInput();

protected:
	static SKeyInputFrame rKeyInputFrame;
	static SMouseKeyInputFrame rMouseInputFrame;
	static SMouseMotionInputFrame rMouseMotionInputFrame;
	static SMouseScrollInputFrame rMouseScrollInputFrame;

	static void CallKeyInputList(vector<SInputInfo> const& InsInputInfo);
	static void CallMousePosList(vector<SInputInfo> const& InsInputInfo);
	static void CallMouseButtonInputList(vector<SInputInfo> const& InsInputInfo);
	static void CallScrollInputList(vector<SInputInfo> const& InsInputInfo);
	//static void CallCursorEnterList(vector<SInputInfo> const& InsInputInfo);
	
	static void OnKey(GLFWwindow* InrWindow, int IniKeyCode, int IniScanCode, int IniAction, int IniMods);
	static void OnMousePos(GLFWwindow* InrWindow, double IndPosX, double IndPosY);
	static void OnMouseButton(GLFWwindow* InrWindow, int IniButton, int IniAction, int IniMods);
	static void OnScroll(GLFWwindow* InrWindow, double IndOffsetX, double IndOffsetY);
	//static void OnCursorEnter(GLFWwindow* InrWindow, int IniEntered);
private:
	//incremental id, there is no recycling.
	static uint64 iInputHandlerID;

	static map<EDeviceType, vector<SInputInfo>> rKeyboardKeyList;

	static GLFWwindow* rCurrentWindowInput;

	static InputManager* rInputManager;

	static Log rLog;

	InputManager();
};

inline void InputManager::SetCurrentWindow(GLFWwindow* InrWindowP) 
{ 
	rCurrentWindowInput = InrWindowP; 
	
	if(rCurrentWindowInput != nullptr)
	{
		glfwSetKeyCallback(rCurrentWindowInput, InputManager::OnKey);
		glfwSetCursorPosCallback(rCurrentWindowInput, InputManager::OnMousePos);
		//glfwSetCursorEnterCallback(rCurrentWindowInput, InputManager::OnCursorEnter);
		glfwSetMouseButtonCallback(rCurrentWindowInput, InputManager::OnMouseButton);
		glfwSetScrollCallback(rCurrentWindowInput, InputManager::OnScroll);
	}

}

inline GLFWwindow* InputManager::GetCurrentWindow() { return rCurrentWindowInput; }

inline SKeyInputFrame InputManager::GetKeyInputFrame() { return rKeyInputFrame; }
inline SMouseKeyInputFrame InputManager::GetMouseKeyInputFrame() { return rMouseInputFrame; }
inline SMouseMotionInputFrame InputManager::GetMouseMotionInputFrame() { return rMouseMotionInputFrame; }
inline SMouseScrollInputFrame InputManager::GetMouseScrollInputFrame() { return rMouseScrollInputFrame; }