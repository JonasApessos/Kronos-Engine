#include "InputHandler.h"


InputKeyHandler::InputKeyHandler(const string& InsName, EGLFWInputKey IneKeyCode, uint32 IniHandlerID) :
	sName(InsName),
	eKeyCode(IneKeyCode),
	iHandlerID(IniHandlerID),
	OnPressedFuncCallback(nullptr),
	OnReleaseFuncCallback(nullptr),
	OnContinuedFuncCallback(nullptr)
{
}

InputKeyHandler::~InputKeyHandler()
{
	OnPressedFuncCallback = nullptr;
	OnContinuedFuncCallback = nullptr;
	OnReleaseFuncCallback = nullptr;
}

void InputKeyHandler::BindCallback(EGLFWInputState IneInputState, void (*InrCallbackFunc)())
{
	switch (IneInputState)
	{
	case EGLFWInputState::EGLFWIS_Press:
		OnPressedFuncCallback = InrCallbackFunc;
		break;

	case EGLFWInputState::EGLFWIS_Release:
		OnContinuedFuncCallback = InrCallbackFunc;
		break;

	case EGLFWInputState::EGLFWIS_Repeat:
		OnReleaseFuncCallback = InrCallbackFunc;
		break;
	}
}

void InputKeyHandler::ExecInputEvent(int32 IniAction)
{
	switch (IniAction)
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