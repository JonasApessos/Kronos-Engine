#include "InputManager.h"

Log InputManager::rLog("LogInputManager");

map<EDeviceType, vector<SInputInfo>> InputManager::rKeyboardKeyList;

SKeyInputFrame InputManager::rKeyInputFrame = SKeyInputFrame();
SMouseKeyInputFrame InputManager::rMouseInputFrame = SMouseKeyInputFrame();
SMouseMotionInputFrame InputManager::rMouseMotionInputFrame = SMouseMotionInputFrame();
SMouseScrollInputFrame InputManager::rMouseScrollInputFrame = SMouseScrollInputFrame();

uint64 InputManager::iInputHandlerID = 0;

GLFWwindow* InputManager::rCurrentWindowInput = nullptr;

InputManager* InputManager::rInputManager = nullptr;

InputManager* InputManager::GetInstance()
{
	if(rInputManager == nullptr)
		rInputManager = new InputManager();

	return rInputManager;
}

void InputManager::BindInput(string const& InsName,
EGLFWInputKey IneInputKey,
EGLFWInputState IneInputState,
void (*InrCallback)())
{
	rKeyboardKeyList[EDeviceType::EDT_Keyboard].push_back(SInputInfo(InsName,
		static_cast<int32>(IneInputKey),
		static_cast<int32>(IneInputState),
		0,
		*InrCallback));
}

void InputManager::BindInput(string const& InsName,
EGLFWMouseKey IneInputMouseKey,
EGLFWInputState IneInputState,
void (*InrCallback)())
{
	rKeyboardKeyList[EDeviceType::EDT_Mouse].push_back(SInputInfo(InsName,
	static_cast<int32>(IneInputMouseKey),
	static_cast<int32>(IneInputState),
	0,
	*InrCallback));
}

void InputManager::BindInput(string const& InsName, EDeviceType IneDeviceType, void (*InrCallback)())
{
	rKeyboardKeyList[IneDeviceType].push_back(SInputInfo(InsName, 0, 0, 0, *InrCallback));
}

void InputManager::OnKey(GLFWwindow* InrWindow, int IniKeyCode, int IniScanCode, int IniAction, int IniMods)
{
	rKeyInputFrame.eKeyPressed = static_cast<EGLFWInputKey>(IniKeyCode);
	rKeyInputFrame.iScanCode = static_cast<uint32>(IniScanCode);
	rKeyInputFrame.eAction = static_cast<EGLFWInputState>(IniAction);
	rKeyInputFrame.iMods = static_cast<EGLFWModKey>(IniMods);

	rKeyInputFrame.IsInputConsumed = false;
}

void InputManager::OnMousePos(GLFWwindow* InrWindow, double IndPosX, double IndPosY)
{
	rMouseMotionInputFrame.dXPos = IndPosX;
	rMouseMotionInputFrame.dYPos = IndPosY;

	rMouseMotionInputFrame.IsInputConsumed = false;
}

void InputManager::OnMouseButton(GLFWwindow* InrWindow, int IniButton, int IniAction, int IniMods)
{
	rMouseInputFrame.eMouseKey = static_cast<EGLFWMouseKey>(IniButton);
	rMouseInputFrame.eInputState = static_cast<EGLFWInputState>(IniAction);
	rMouseInputFrame.iMods = static_cast<EGLFWModKey>(IniMods);

	rMouseInputFrame.IsInputConsumed = false;
}

void InputManager::OnScroll(GLFWwindow* InrWindow, double IndOffsetX, double IndOffsetY)
{
	rMouseScrollInputFrame.dScrollX = IndOffsetX;
	rMouseScrollInputFrame.dScrollY = IndOffsetY;

	rMouseScrollInputFrame.IsInputConsumed = false;
}

void InputManager::ProcessInput()
{

	for(map<EDeviceType, vector<SInputInfo>>::iterator::value_type rIt : rKeyboardKeyList)
	{
		switch(rIt.first)
		{
			case EDeviceType::EDT_Keyboard:
				CallKeyInputList(rIt.second);
				break;

			case EDeviceType::EDT_Mouse:
				CallMousePosList(rIt.second);
				CallMouseButtonInputList(rIt.second);
				CallScrollInputList(rIt.second);
				break;

			case EDeviceType::EDT_Gamepad:
				break;

			case EDeviceType::EDT_Joystic:
				break;
		}
	}
}

void InputManager::CallKeyInputList(vector<SInputInfo> const& InsInputInfo)
{
	if(!rKeyInputFrame.IsInputConsumed)
	{
		uint32 iLoop = 0;

		while(iLoop < InsInputInfo.size())
		{
			if(static_cast<EGLFWInputKey>(InsInputInfo[iLoop].iInputKey) == rKeyInputFrame.eKeyPressed &&
			static_cast<EGLFWInputState>(InsInputInfo[iLoop].iInputState) == rKeyInputFrame.eAction &&
			InsInputInfo[iLoop].iInputMod == static_cast<uint32>(rKeyInputFrame.iMods))
			{
				if(InsInputInfo[iLoop].rCallback != nullptr)
					InsInputInfo[iLoop].rCallback();
			}

			++iLoop;
		}

		rKeyInputFrame.IsInputConsumed = true;
	}
}

void InputManager::CallMousePosList(vector<SInputInfo> const& InsInputInfo)
{
	if(!rMouseMotionInputFrame.IsInputConsumed)
	{
		uint32 iLoop = 0;

		while(iLoop < InsInputInfo.size())
		{
			if(InsInputInfo[iLoop].rCallback != nullptr)
				InsInputInfo[iLoop].rCallback();

			++iLoop;
		}

		rMouseMotionInputFrame.IsInputConsumed = true;
	}
}

void InputManager::CallMouseButtonInputList(vector<SInputInfo> const& InsInputInfo)
{
	if(!rMouseInputFrame.IsInputConsumed)
	{
		uint32 iLoop = 0;

		while(iLoop < InsInputInfo.size())
		{
			if(static_cast<EGLFWMouseKey>(InsInputInfo[iLoop].iInputKey) == rMouseInputFrame.eMouseKey &&
			static_cast<EGLFWInputState>(InsInputInfo[iLoop].iInputState) == rMouseInputFrame.eInputState &&
			InsInputInfo[iLoop].iInputMod == static_cast<uint32>(rMouseInputFrame.iMods))
			{
				if(InsInputInfo[iLoop].rCallback != nullptr)
					InsInputInfo[iLoop].rCallback();
			}

			++iLoop;
		}

		rMouseInputFrame.IsInputConsumed = true;
	}
}

void InputManager::CallScrollInputList(vector<SInputInfo> const& InsInputInfo)
{
	if(!rMouseScrollInputFrame.IsInputConsumed)
	{
		uint32 iLoop = 0;

		while(iLoop < InsInputInfo.size())
		{
			if(InsInputInfo[iLoop].rCallback != nullptr)
				InsInputInfo[iLoop].rCallback();

			++iLoop;
		}

		rMouseScrollInputFrame.IsInputConsumed = true;
	}
}

InputManager::InputManager()
{
	rKeyboardKeyList.emplace(EDeviceType::EDT_Keyboard, vector<SInputInfo>());
	rKeyboardKeyList.emplace(EDeviceType::EDT_Joystic, vector<SInputInfo>());
	rKeyboardKeyList.emplace(EDeviceType::EDT_Mouse, vector<SInputInfo>());
	rKeyboardKeyList.emplace(EDeviceType::EDT_Gamepad, vector<SInputInfo>());

	if(rCurrentWindowInput != nullptr)
	{
		glfwSetKeyCallback(rCurrentWindowInput, InputManager::OnKey);
		glfwSetCursorPosCallback(rCurrentWindowInput, InputManager::OnMousePos);
		//glfwSetCursorEnterCallback(rCurrentWindowInput, InputManager::OnCursorEnter);
		glfwSetMouseButtonCallback(rCurrentWindowInput, InputManager::OnMouseButton);
		glfwSetScrollCallback(rCurrentWindowInput, InputManager::OnScroll);
	}
}