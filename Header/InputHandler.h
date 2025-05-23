#pragma once

#include <string>

#include "Standard.h"

#include "Primitives.h"

using std::string;
using KronosPrim::uint32, KronosPrim::int32;

/** @enum EGLFWInputKey
* 	@brief enum for glfw input key map
*	@todo seperate input bindings from InputManager, This class should manage for every binding the execution*/
/*enum class EGLFWInputKey : int32
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
	EGLFWIK_Last = GLFW_KEY_LAST,
};*/

/** @enum EGLFWInputState
* 	@brief enum for glfw key state*/
/*enum class EGLFWInputState : int32
{
	EGLFWIS_Release = GLFW_RELEASE,
	EGLFWIS_Repeat = GLFW_REPEAT,
	EGLFWIS_Press = GLFW_PRESS
};*/

/** @class Import
*   @brief Singleton importer class.
*    
*   The singleton class imports object from files.
*/
/*template<typename T, typename ObjectReference>
class InputKeyHandler
{
public:
	uint32 iHandlerID;

	InputKeyHandler(string const& InsName, EGLFWInputKey IneKeyCode, uint32 IniHandlerID);

	~InputKeyHandler();

	void BindCallback(EGLFWInputState IneInputState, ObjectReference* InrCallee, T (ObjectReference::*InrCallbackFunc)());

	void ExecInputEvent(EGLFWInputState IneInputState);

	inline string GetName() const;

protected:
	string sName;

	EGLFWInputKey eKeyCode;

	ObjectReference* rCalleeClass;

	virtual inline void OnPressed();
	virtual inline void OnContinued();
	virtual inline void OnRelease();

private:

	T (ObjectReference::*OnPressedFuncCallback)() = nullptr;
	T (ObjectReference::*OnContinuedFuncCallback)() = nullptr;
	T (ObjectReference::*OnReleaseFuncCallback)() = nullptr;
};

template<typename T, typename ObjectReference>
inline string InputKeyHandler<T, ObjectReference>::GetName() const { return sName; }

//TODO:Add Error logs on false.
template<typename T, typename ObjectReference>
inline void InputKeyHandler<T, ObjectReference>::OnPressed()
{ 
	if (OnPressedFuncCallback != nullptr)
		(rCalleeClass->*OnPressedFuncCallback)();
}

//TODO:Add Error logs on false.
template<typename T, typename ObjectReference>
inline void InputKeyHandler<T, ObjectReference>::OnContinued()
{ 
	if (OnContinuedFuncCallback != nullptr)
		(rCalleeClass->*OnContinuedFuncCallback)();
}

//TODO:Add Error logs on false.
template<typename T, typename ObjectReference>
inline void InputKeyHandler<T, ObjectReference>::OnRelease()
{ 
	if (OnReleaseFuncCallback != nullptr)
		(rCalleeClass->*OnReleaseFuncCallback)();
}*/