#include "InputManager.h"

EGLFWInputKey InputManager::eKeyPressed = EGLFWInputKey::EGLFWIK_0;
uint32 InputManager::iScanCode = 0;
EGLFWInputState InputManager::eAction = EGLFWInputState::EGLFWIS_Press;
uint32 InputManager::iMods = 0;

uint64 InputManager::iInputHandlerID = 0;

GLFWwindow* InputManager::rCurrentWindowInput = nullptr;

InputManager* InputManager::rInputManager = nullptr;

InputManager* InputManager::GetInstance()
{
	if(rInputManager == nullptr)
		rInputManager = new InputManager();

	return rInputManager;
}

void InputManager::RecordInput(GLFWwindow* InrWindow, int IniKeyCode, int IniScanCode, int IniAction, int IniMods)
{
	InputManager::eKeyPressed = static_cast<EGLFWInputKey>(IniKeyCode);
	InputManager::iScanCode = static_cast<uint32>(IniScanCode);
	InputManager::eAction = static_cast<EGLFWInputState>(IniAction);
	InputManager::iMods = static_cast<uint32>(IniMods);
}

InputManager::InputManager()
{
	if(rCurrentWindowInput != nullptr)
		glfwSetKeyCallback(rCurrentWindowInput, InputManager::RecordInput);
}