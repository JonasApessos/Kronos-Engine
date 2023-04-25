#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "GLFW/glfw3.h"
#include "Primitives.h"
#include "InputHandler.h"

using KronosPrim::uint64;

using std::map, std::vector;

class InputManager
{
public:

	InputManager(const InputManager&) = delete;

	static InputManager* GetInstance();

	static void Destroy();

	template<typename T, typename C>
	static void BindKey(const string& InsHandleName, EGLFWInputKey IneInputKey, C* InrCallee, T (C::*InrCallbackFunc)());

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

	static GLFWwindow* rCurrentWindowInputP;

	static InputManager* rSingletonInputManagerP;

	InputManager();
};


template<typename T, typename C>
map<EGLFWInputKey, vector<InputKeyHandler<T, C>*>>* InputManager::rInputHandleMap = new map<EGLFWInputKey, vector<InputKeyHandler<T, C>*>>();


inline void InputManager::SetCurrentWindow(GLFWwindow* InrWindowP) 
{ 
	rCurrentWindowInputP = InrWindowP;  

	if(rCurrentWindowInputP != nullptr )
		glfwSetKeyCallback(rCurrentWindowInputP, InputManager::RecordInput); 
}
inline GLFWwindow* InputManager::GetCurrentWindow() { return rCurrentWindowInputP; }

/*TODO:Temp code, make it more robust.
future update, should re-use previously nullified InputKeyHandler so not have to
re-costruct which takes times and resources*/
template<typename T, typename C>
void InputManager::BindKey(const string& InsHandleName, EGLFWInputKey IneInputKey, C* InrCallee, T(C::* InrCallbackFunc)())
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
	if (rInputHandleMap->contains(eKeyPressed))
	{
		for (InputKeyHandler<T, C>* rKeyHandlerP : rInputHandleMap->at(eKeyPressed))
		{
			if (rKeyHandlerP != nullptr)
				rKeyHandlerP->ExecInputEvent(eAction);
		}
	}
}