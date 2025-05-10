#include "InputManager.h"

Log InputManager::rLog("LogInputManager");

map<EDeviceType, vector<SInputInfo>> InputManager::rKeyboardKeyList;

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
EInputKey IneInputKey,
EInputState IneInputState,
void (*InrCallback)())
{
	rKeyboardKeyList[EDeviceType::EDT_Keyboard].push_back(
		SInputInfo(
			InsName,
			static_cast<int32>(IneInputKey),
			static_cast<int32>(IneInputState),
			0,
			*InrCallback));
}

void InputManager::BindInput(string const& InsName,
EMouseKey IneInputMouseKey,
EInputState IneInputState,
void (*InrCallback)())
{
	rKeyboardKeyList[EDeviceType::EDT_Mouse].push_back(
		SInputInfo(
			InsName,
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
	for (map<EDeviceType, vector<SInputInfo>>::iterator::value_type &rIt : rKeyboardKeyList)
	{
		for(int32 i = 0; i < rIt.second.size(); i++)
		{
			rIt.second[i].iCurrentInputState = glfwGetKey(InrWindow, rIt.second[i].iInputKey);
			rIt.second[i].bIsInputConsumed = !(static_cast<EInputState>(rIt.second[i].iCurrentInputState) == EInputState::EIS_Press);
		}
	}
}

void InputManager::OnMousePos(GLFWwindow* InrWindow, double IndPosX, double IndPosY)
{
	rMouseMotionInputFrame.dXPos = IndPosX;
	rMouseMotionInputFrame.dYPos = IndPosY;

	rMouseMotionInputFrame.IsInputConsumed = false;
}

void InputManager::OnMouseButton(GLFWwindow* InrWindow, int IniButton, int IniAction, int IniMods)
{
	rMouseInputFrame.eMouseKey = static_cast<EMouseKey>(IniButton);
	rMouseInputFrame.eInputState = static_cast<EInputState>(IniAction);
	rMouseInputFrame.iMods = static_cast<EMod>(IniMods);

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
	for(map<EDeviceType, vector<SInputInfo>>::iterator::value_type &rIt : rKeyboardKeyList)
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

			//TODO: Handle gamepad input
			case EDeviceType::EDT_Gamepad:
				break;

			//TODO: Handle Joystic input
			case EDeviceType::EDT_Joystic:
				break;

			//TODO: Error binding input device, Unknown device
			case EDeviceType::EDT_Unknown:
				rLog.WriteAndDisplay("failed to bind device input, unknown device detected. can't handle input, aborting.");
				break;
		}
	}
}

void InputManager::CallKeyInputList(vector<SInputInfo> & InsInputInfo)
{
	uint32 iLoop = 0;

	while(iLoop < InsInputInfo.size())
	{
		if(!InsInputInfo[iLoop].bIsInputConsumed)
		{
			switch(static_cast<EInputState>(InsInputInfo[iLoop].iInputState))
			{
				case EInputState::EIS_Press:
				case EInputState::EIS_Release:
				{
					if(static_cast<EInputState>(InsInputInfo[iLoop].iCurrentInputState) == static_cast<EInputState>(InsInputInfo[iLoop].iInputState))
					{
						InsInputInfo[iLoop].rCallback();
						InsInputInfo[iLoop].bIsInputConsumed = true;
					}
					break;
				}

				case EInputState::EIS_Hold:
				{
					if(static_cast<EInputState>(InsInputInfo[iLoop].iCurrentInputState) == EInputState::EIS_Press)
						InsInputInfo[iLoop].rCallback();
					else if(static_cast<EInputState>(InsInputInfo[iLoop].iCurrentInputState) == EInputState::EIS_Release)
						InsInputInfo[iLoop].bIsInputConsumed = true;

					break;
				}

				default:
				{

					break;
				}
			}

		}

		++iLoop;
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
			if(static_cast<EMouseKey>(InsInputInfo[iLoop].iInputKey) == rMouseInputFrame.eMouseKey &&
			static_cast<EInputState>(InsInputInfo[iLoop].iInputState) == rMouseInputFrame.eInputState &&
			InsInputInfo[iLoop].iInputMod == static_cast<int32>(rMouseInputFrame.iMods) &&
			InsInputInfo[iLoop].rCallback != nullptr)
			{
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