#include "InputManager.h"


InputManager* InputManager::GetInputManagerInstance()
{
	return rSingletonInputManagerP;
}

void InputManager::Destroy()
{
	//TODO:Fix memory leak in vector class!!!
	if (rInputHandleMap != nullptr)
	{
		delete rInputHandleMap;

		rInputHandleMap = nullptr;
	}

	if (rSingletonInputManagerP != nullptr)
	{
		delete rSingletonInputManagerP;

		rSingletonInputManagerP = nullptr;
	}
}

//TODO:Temp code, make it more robust.
void InputManager::BindKey(const string& InsHandleName, EGLFWInputKey IneInputKey, void (*InrCallbackFunc)())
{
	vector<InputKeyHandler*> rKeyHandlerList = rInputHandleMap->at(static_cast<EGLFWInputKey>(IneInputKey));

	for (InputKeyHandler* rKeyHandler : rKeyHandlerList)
	{
		if (rKeyHandler->GetName() == InsHandleName)
		{
			rKeyHandlerList.push_back(new InputKeyHandler(InsHandleName, IneInputKey, 0));
		}

	}
}

void InputManager::ProcessInput(GLFWwindow* InrWindowP, int Inikey, int IniScanCode, int IniAction, int IniMods)
{
	vector<InputKeyHandler*> rKeyHandlerList = rInputHandleMap->at(static_cast<EGLFWInputKey>(Inikey));

	for (InputKeyHandler* rKeyHandler : rKeyHandlerList)
	{
		if (rKeyHandler != nullptr)
			rKeyHandler->ExecInputEvent(IniAction);
	}
}

InputManager::InputManager()
{
	if (rCurrentWindowInputP != nullptr)
		glfwSetKeyCallback(rCurrentWindowInputP, InputManager::ProcessInput);
}