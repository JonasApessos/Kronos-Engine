#include "InputManager.h"

EGLFWInputKey InputManager::eKeyPressed = EGLFWInputKey::EGLFWIK_0;
uint32 InputManager::iScanCode = 0;
EGLFWInputState InputManager::eAction = EGLFWInputState::EGLFWIS_Press;
uint32 InputManager::iMods = 0;

uint64 InputManager::iInputHandlerID = 0;

GLFWwindow* InputManager::rCurrentWindowInputP = nullptr;

InputManager* InputManager::rSingletonInputManagerP = new InputManager();

InputManager* InputManager::GetInstance()
{
	return rSingletonInputManagerP;
}

void InputManager::Destroy()
{
	//TODO:Fix memory leak in vector class!!!
	/*if (rInputHandleMap != nullptr)
	{
		delete rInputHandleMap;

		rInputHandleMap = nullptr;
	}*/

	if (rSingletonInputManagerP != nullptr)
	{
		delete rSingletonInputManagerP;

		rSingletonInputManagerP = nullptr;
	}

	rCurrentWindowInputP = nullptr;
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
	if(rCurrentWindowInputP != nullptr)
		glfwSetKeyCallback(rCurrentWindowInputP, InputManager::RecordInput);
}