#include "InputHandler.h"

template<typename T, typename ObjectReference>
InputKeyHandler<T, ObjectReference>::InputKeyHandler(const string& InsName, EGLFWInputKey IneKeyCode, uint32 IniHandlerID) :
	sName(InsName),
	eKeyCode(IneKeyCode),
	iHandlerID(IniHandlerID),
	OnPressedFuncCallback(nullptr),
	OnReleaseFuncCallback(nullptr),
	OnContinuedFuncCallback(nullptr)
{
}

template<typename T, typename ObjectReference>
InputKeyHandler<T, ObjectReference>::~InputKeyHandler()
{
	OnPressedFuncCallback = nullptr;
	OnContinuedFuncCallback = nullptr;
	OnReleaseFuncCallback = nullptr;
}

template<typename T, typename ObjectReference>
void InputKeyHandler<T, ObjectReference>::ExecInputEvent(EGLFWInputState IneInputState)
{
	switch (IneInputState)
	{
	case EGLFWInputState::EGLFWIS_Press:
		OnPressed();
		break;

	case EGLFWInputState::EGLFWIS_Release:
		OnRelease();
		break;

	case EGLFWInputState::EGLFWIS_Repeat:
		OnContinued();
		break;
	}
}