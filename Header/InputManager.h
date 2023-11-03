#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "GLFW/glfw3.h"

#include "Primitives.h"
#include "InputHandler.h"

using std::map, std::vector;

using KronosPrim::uint64;

/** @class InputManager
*   @brief Singleton class that manages template class InputKeyHandler*/
class InputManager
{
public:

	InputManager(InputManager const&) = delete;
	InputManager(InputManager&&) = delete;

	InputManager& operator=(InputManager const&) = delete;
	InputManager& operator=(InputManager&&) = delete;

	static InputManager* GetInstance();

	template<typename T, typename C>
	static void BindKey(string const& InsHandleName, EGLFWInputKey IneInputKey, C* InrCallee, T (C::*InrCallbackFunc)());

	static inline void SetCurrentWindow(GLFWwindow* InrWindowP);

	static inline GLFWwindow* GetCurrentWindow();

	template<typename T, typename C>
	void ProcessInput();

protected:
	static EGLFWInputKey eKeyPressed;
	static uint32 iScanCode;
	static EGLFWInputState eAction;
	static uint32 iMods;
	
	static void RecordInput(GLFWwindow* InrWindow, int IniKeyCode, int IniScanCode, int IniAction, int IniMods);
private:
	//incremental id, there is no recycling.
	static uint64 iInputHandlerID;

	template<typename T, typename C>
	static map<EGLFWInputKey, vector<InputKeyHandler<T, C>*>>* rInputHandleMap;

	static GLFWwindow* rCurrentWindowInput;

	static InputManager* rInputManager;

	InputManager();
};


template<typename T, typename C>
map<EGLFWInputKey, vector<InputKeyHandler<T, C>*>>* InputManager::rInputHandleMap = new map<EGLFWInputKey, vector<InputKeyHandler<T, C>*>>();


inline void InputManager::SetCurrentWindow(GLFWwindow* InrWindowP) 
{ 
	rCurrentWindowInput = InrWindowP;  

	if(rCurrentWindowInput != nullptr )
		glfwSetKeyCallback(rCurrentWindowInput, InputManager::RecordInput); 
}

inline GLFWwindow* InputManager::GetCurrentWindow() { return rCurrentWindowInput; }

/*TODO:Temp code, make it more robust.
future update, should re-use previously nullified InputKeyHandler so not have to
re-costruct which takes times and resources*/
template<typename T, typename C>
void InputManager::BindKey(string const& InsHandleName, EGLFWInputKey IneInputKey, C* InrCallee, T(C::* InrCallbackFunc)())
{
	/*bool IsBinded = false;
	if (!rInputHandleMap->contains(IneInputKey))
		rInputHandleMap->insert(std::pair<EGLFWInputKey, vector<InputKeyHandler<T, C>*>>(IneInputKey, vector<InputKeyHandler<T, C>*>()));

	vector<InputKeyHandler<T, C>*>* rKeyHandlerListP = &rInputHandleMap->at(IneInputKey);

	for (InputKeyHandler<T, C>* rKeyHandlerP : *rKeyHandlerListP)
	{
		if (rKeyHandlerP != nullptr && rKeyHandlerP->GetName() == InsHandleName)
		{
			IsBinded = true;
			break;
		}
	}

	if (!IsBinded)
	{
		iInputHandlerID++;

		InputKeyHandler<T, C>* TempInputHandler = new InputKeyHandler<T, C>(InsHandleName, IneInputKey, iInputHandlerID);

		TempInputHandler->BindCallback(EGLFWInputState::EGLFWIS_Press, InrCallee, InrCallbackFunc);

		rInputHandleMap->at(static_cast<EGLFWInputKey>(IneInputKey)).push_back(TempInputHandler);

		TempInputHandler = nullptr;
	}*/

}

template<typename T, typename C>
void InputManager::ProcessInput()
{
	if (rInputHandleMap<T, C>->contains(eKeyPressed))
	{
		for (InputKeyHandler<T, C>* rKeyHandlerP : rInputHandleMap<T, C>->at(eKeyPressed))
		{
			if (rKeyHandlerP != nullptr)
				rKeyHandlerP->ExecInputEvent(eAction);
		}
	}
}