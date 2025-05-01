#pragma once

#include <thread>
#include <functional>
#include <vector>
#include <map>

#include "Primitives.h"
#include "InputHandler.h"
#include "Window.h"

using std::map, std::vector, std::to_string, std::thread;

using KronosPrim::uint64, KronosPrim::uint8;

/** @enum EGLFWInputKey
* 	@brief enum for glfw input key map
*/
enum class EInputKey : int32
{
	EIK_Unknown = GLFW_KEY_UNKNOWN,
	EIK_Space = GLFW_KEY_SPACE,
	EIK_Apostrophe = GLFW_KEY_APOSTROPHE,
	EIK_Comma = GLFW_KEY_COMMA,
	EIK_Minus = GLFW_KEY_MINUS,
	EIK_Period = GLFW_KEY_PERIOD,
	EIK_Slash = GLFW_KEY_SLASH,
	EIK_0 = GLFW_KEY_0,
	EIK_1 = GLFW_KEY_1,
	EIK_2 = GLFW_KEY_2,
	EIK_3 = GLFW_KEY_3,
	EIK_4 = GLFW_KEY_4,
	EIK_5 = GLFW_KEY_5,
	EIK_6 = GLFW_KEY_6,
	EIK_7 = GLFW_KEY_7,
	EIK_8 = GLFW_KEY_8,
	EIK_9 = GLFW_KEY_9,
	EIK_Semicolon = GLFW_KEY_SEMICOLON,
	EIK_Equal = GLFW_KEY_EQUAL,
	EIK_A = GLFW_KEY_A,
	EIK_B = GLFW_KEY_B,
	EIK_C = GLFW_KEY_C,
	EIK_D = GLFW_KEY_D,
	EIK_E = GLFW_KEY_E,
	EIK_F = GLFW_KEY_F,
	EIK_G = GLFW_KEY_G,
	EIK_H = GLFW_KEY_H,
	EIK_I = GLFW_KEY_I,
	EIK_J = GLFW_KEY_J,
	EIK_K = GLFW_KEY_K,
	EIK_L = GLFW_KEY_L,
	EIK_M = GLFW_KEY_M,
	EIK_N = GLFW_KEY_N,
	EIK_O = GLFW_KEY_O,
	EIK_P = GLFW_KEY_P,
	EIK_Q = GLFW_KEY_Q,
	EIK_R = GLFW_KEY_R,
	EIK_S = GLFW_KEY_S,
	EIK_T = GLFW_KEY_T,
	EIK_U = GLFW_KEY_U,
	EIK_V = GLFW_KEY_V,
	EIK_W = GLFW_KEY_W,
	EIK_X = GLFW_KEY_X,
	EIK_Y = GLFW_KEY_Y,
	EIK_Z = GLFW_KEY_Z,
	EIK_LeftBracket = GLFW_KEY_LEFT_BRACKET,
	EIK_BackSlash = GLFW_KEY_BACKSLASH,
	EIK_RightBracket = GLFW_KEY_RIGHT_BRACKET,
	EIK_GraveAccent = GLFW_KEY_GRAVE_ACCENT,
	EIK_World1 = GLFW_KEY_WORLD_1,
	EIK_World2 = GLFW_KEY_WORLD_2,
	EIK_Escape = GLFW_KEY_ESCAPE,
	EIK_Enter = GLFW_KEY_ENTER,
	EIK_Tab = GLFW_KEY_TAB,
	EIK_Backspace = GLFW_KEY_BACKSPACE,
	EIK_Insert = GLFW_KEY_INSERT,
	EIK_Delete = GLFW_KEY_DELETE,
	EIK_Right = GLFW_KEY_RIGHT,
	EIK_Left = GLFW_KEY_LEFT,
	EIK_Down = GLFW_KEY_DOWN,
	EIK_Up = GLFW_KEY_UP,
	EIK_PageUp = GLFW_KEY_PAGE_UP,
	EIK_PageDown = GLFW_KEY_PAGE_DOWN,
	EIK_Home = GLFW_KEY_HOME,
	EIK_End = GLFW_KEY_END,
	EIK_CapsLock = GLFW_KEY_CAPS_LOCK,
	EIK_ScrollLock = GLFW_KEY_SCROLL_LOCK,
	EIK_NumLock = GLFW_KEY_NUM_LOCK,
	EIK_PrintScreen = GLFW_KEY_PRINT_SCREEN,
	EIK_Pause = GLFW_KEY_PAUSE,
	EIK_F1 = GLFW_KEY_F1,
	EIK_F2 = GLFW_KEY_F2,
	EIK_F3 = GLFW_KEY_F3,
	EIK_F4 = GLFW_KEY_F4,
	EIK_F5 = GLFW_KEY_F5,
	EIK_F6 = GLFW_KEY_F6,
	EIK_F7 = GLFW_KEY_F7,
	EIK_F8 = GLFW_KEY_F8,
	EIK_F9 = GLFW_KEY_F9,
	EIK_F10 = GLFW_KEY_F10,
	EIK_F11 = GLFW_KEY_F11,
	EIK_F12 = GLFW_KEY_F12,
	EIK_F13 = GLFW_KEY_F13,
	EIK_F14 = GLFW_KEY_F14,
	EIK_F15 = GLFW_KEY_F15,
	EIK_F16 = GLFW_KEY_F16,
	EIK_F17 = GLFW_KEY_F17,
	EIK_F18 = GLFW_KEY_F18,
	EIK_F19 = GLFW_KEY_F19,
	EIK_F20 = GLFW_KEY_F20,
	EIK_F21 = GLFW_KEY_F21,
	EIK_F22 = GLFW_KEY_F22,
	EIK_F23 = GLFW_KEY_F23,
	EIK_F24 = GLFW_KEY_F24,
	EIK_F25 = GLFW_KEY_F25,
	EIK_KP0 = GLFW_KEY_KP_0,
	EIK_KP1 = GLFW_KEY_KP_1,
	EIK_KP2 = GLFW_KEY_KP_2,
	EIK_KP3 = GLFW_KEY_KP_3,
	EIK_KP4 = GLFW_KEY_KP_4,
	EIK_KP5 = GLFW_KEY_KP_5,
	EIK_KP6 = GLFW_KEY_KP_6,
	EIK_KP7 = GLFW_KEY_KP_7,
	EIK_KP8 = GLFW_KEY_KP_8,
	EIK_KP9 = GLFW_KEY_KP_9,
	EIK_KPDecimal = GLFW_KEY_KP_DECIMAL,
	EIK_KPDivide = GLFW_KEY_KP_DIVIDE,
	EIK_KPMultiply = GLFW_KEY_KP_MULTIPLY,
	EIK_KPSubtract = GLFW_KEY_KP_SUBTRACT,
	EIK_KPAdd = GLFW_KEY_KP_ADD,
	EIK_KPEnter = GLFW_KEY_KP_ENTER,
	EIK_KPEqual = GLFW_KEY_KP_EQUAL,
	EIK_LeftShift = GLFW_KEY_LEFT_SHIFT,
	EIK_LeftControl = GLFW_KEY_LEFT_CONTROL,
	EIK_LeftAlt = GLFW_KEY_LEFT_ALT,
	EIK_LeftSuper = GLFW_KEY_LEFT_SUPER,
	EIK_RightShift = GLFW_KEY_RIGHT_SHIFT,
	EIK_RightControl = GLFW_KEY_RIGHT_CONTROL,
	EIK_RightAlt = GLFW_KEY_RIGHT_ALT,
	EIK_RightSuper = GLFW_KEY_RIGHT_SUPER,
	EIK_Menu = GLFW_KEY_MENU,
	EIK_Last = GLFW_KEY_LAST
};

/** @enum EGLFWMouseKey
* 	@brief enum for glfw input Mouse map*/
enum class EMouseKey : int32
{
	EMK_Button1 = GLFW_MOUSE_BUTTON_1,
	EMK_Button2 = GLFW_MOUSE_BUTTON_2,
	EMK_Button3 = GLFW_MOUSE_BUTTON_3,
	EMK_Button4 = GLFW_MOUSE_BUTTON_4,
	EMK_Button5 = GLFW_MOUSE_BUTTON_5,
	EMK_Button6 = GLFW_MOUSE_BUTTON_6,
	EMK_Button7 = GLFW_MOUSE_BUTTON_7,
	EMK_Button8 = GLFW_MOUSE_BUTTON_8,
	EMK_Left = GLFW_MOUSE_BUTTON_LEFT,
	EMK_Middle = GLFW_MOUSE_BUTTON_MIDDLE,
	EMK_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
	EMK_Last = GLFW_MOUSE_BUTTON_LAST
};

/** @enum EGLFWGamepadKey
* 	@brief enum for glfw input Gamepad map*/
enum class EGamepadKey : int32
{
	EGK_A = GLFW_GAMEPAD_BUTTON_A,
	EGK_B = GLFW_GAMEPAD_BUTTON_B,
	EGK_Back = GLFW_GAMEPAD_BUTTON_BACK,
	EGK_Circle = GLFW_GAMEPAD_BUTTON_CIRCLE,
	EGK_Cross = GLFW_GAMEPAD_BUTTON_CROSS,
	EGK_Square = GLFW_GAMEPAD_BUTTON_SQUARE,
	EGK_Triangle = GLFW_GAMEPAD_BUTTON_TRIANGLE,
	EGK_DPadDown = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
	EGK_DPadLeft = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
	EGK_DPadRight = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
	EGK_DPadUp = GLFW_GAMEPAD_BUTTON_DPAD_UP,
	EGK_Guide = GLFW_GAMEPAD_BUTTON_GUIDE,
	EGK_LeftBumper = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
	EGK_RightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
	EGK_LeftThump = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
	EGK_RightThump = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
	EGK_Start = GLFW_GAMEPAD_BUTTON_START,
	EGK_Last = GLFW_GAMEPAD_BUTTON_LAST
};

/** @enum EGLFWJoysticKey
* 	@brief enum for glfw input Joystic map*/
enum class EJoysticKey : int32
{
	EJK_1 = GLFW_JOYSTICK_1,
	EJK_2 = GLFW_JOYSTICK_2,
	EJK_3 = GLFW_JOYSTICK_3,
	EJK_4 = GLFW_JOYSTICK_4,
	EJK_5 = GLFW_JOYSTICK_5,
	EJK_6 = GLFW_JOYSTICK_6,
	EJK_7 = GLFW_JOYSTICK_7,
	EJK_8 = GLFW_JOYSTICK_8,
	EJK_9 = GLFW_JOYSTICK_9,
	EJK_10 = GLFW_JOYSTICK_10,
	EJK_11 = GLFW_JOYSTICK_11,
	EJK_12 = GLFW_JOYSTICK_12,
	EJK_13 = GLFW_JOYSTICK_13,
	EJK_14 = GLFW_JOYSTICK_14,
	EJK_15 = GLFW_JOYSTICK_15,
	EJK_16 = GLFW_JOYSTICK_16,
	EJK_Last = GLFW_JOYSTICK_LAST,
};

/** @enum EModKey
* 	@brief enum for glfw input Mod map*/
enum class EMod : int32
{
	EMK_Shift = GLFW_MOD_SHIFT,
	EMK_Control = GLFW_MOD_CONTROL,
	EMK_Alt = GLFW_MOD_ALT,
	EMK_Super = GLFW_MOD_SUPER,
	EMK_CapsLock = GLFW_MOD_CAPS_LOCK,
	EMK_NumLock = GLFW_MOD_NUM_LOCK
};

/** @enum EInputState
* 	@brief enum for glfw key state*/
enum class EInputState : int32
{
	EIS_Release = GLFW_RELEASE,
	EIS_Press = GLFW_PRESS,
	EIS_Repeat = GLFW_REPEAT,
	EIS_Hold = 3
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
	EMouseKey eMouseKey;
	EInputState eInputState;
	EMod iMods;
};

/** @struct SInputInfo
* 	@brief structure for input info bridge.
*	This structure serves as a bridge between
*	Input Frames and callback functions
*/
struct SInputInfo
{
	bool bIsInputConsumed = true;
	string sName;
	int32 iInputKey;
	int32 iInputState;
	int32 iInputMod;
	int32 iCurrentInputState = static_cast<int32>(EInputState::EIS_Release);
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
*   @brief Singleton class that manages keyboard input
*	@todo Improve Input Manager to correclty support input states
*	@todo Seperate Devices from Input Manager*/
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
	static inline SMouseKeyInputFrame GetMouseKeyInputFrame();
	static inline SMouseMotionInputFrame GetMouseMotionInputFrame();
	static inline SMouseScrollInputFrame GetMouseScrollInputFrame();

	static void BindInput(string const& InsName, EInputKey IneInputKey, EInputState IneInputState, void (*InrCallback)());
	static void BindInput(string const& InsName, EMouseKey IneInputMouseKey, EInputState IneInputState, void (*InrCallback)());
	static void BindInput(string const& InsName, EDeviceType IneDeviceType, void (*InrCallback)());

	static void ProcessInput();

protected:
	static SMouseKeyInputFrame rMouseInputFrame;
	static SMouseMotionInputFrame rMouseMotionInputFrame;
	static SMouseScrollInputFrame rMouseScrollInputFrame;

	static void CallKeyInputList(vector<SInputInfo> & InsInputInfo);
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

inline SMouseKeyInputFrame InputManager::GetMouseKeyInputFrame() { return rMouseInputFrame; }
inline SMouseMotionInputFrame InputManager::GetMouseMotionInputFrame() { return rMouseMotionInputFrame; }
inline SMouseScrollInputFrame InputManager::GetMouseScrollInputFrame() { return rMouseScrollInputFrame; }