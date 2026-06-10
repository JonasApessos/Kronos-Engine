#include "ManagerInput.h"

Log ManagerInput::rLog("LogInputManager");

map<EDeviceType, vector<SInputInfo>> ManagerInput::rKeyboardKeyList;

SMouseKeyInputFrame ManagerInput::rMouseInputFrame = SMouseKeyInputFrame();
SMouseMotionInputFrame ManagerInput::rMouseMotionInputFrame = SMouseMotionInputFrame();
SMouseScrollInputFrame ManagerInput::rMouseScrollInputFrame = SMouseScrollInputFrame();

uint64 ManagerInput::iInputHandlerID = 0;

GLFWwindow* ManagerInput::rCurrentWindowInput = nullptr;

ManagerInput* ManagerInput::rInputManager = nullptr;

ManagerInput* ManagerInput::GetInstance()
{
	if(rInputManager == nullptr)
		rInputManager = new ManagerInput();

	return rInputManager;
}

void ManagerInput::BindInput(string const& InsName,
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

void ManagerInput::BindInput(string const& InsName,
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

void ManagerInput::BindInput(string const& InsName, EDeviceType IneDeviceType, void (*InrCallback)())
{
	rKeyboardKeyList[IneDeviceType].push_back(SInputInfo(InsName, 0, 0, 0, *InrCallback));
}

void ManagerInput::OnKey(GLFWwindow* InrWindow, int IniKeyCode, int IniScanCode, int IniAction, int IniMods)
{
	for (map<EDeviceType, vector<SInputInfo>>::iterator::value_type &rIt : rKeyboardKeyList)
	{
		for(size_t i = 0; i < rIt.second.size(); i++)
		{
			rIt.second[i].iCurrentInputState = glfwGetKey(InrWindow, rIt.second[i].iInputKey);
			rIt.second[i].bIsInputConsumed = !(static_cast<EInputState>(rIt.second[i].iCurrentInputState) == EInputState::EIS_Press);
		}
	}
}

void ManagerInput::OnMousePos(GLFWwindow* InrWindow, double IndPosX, double IndPosY)
{
	rMouseMotionInputFrame.dXPos = IndPosX;
	rMouseMotionInputFrame.dYPos = IndPosY;

	rMouseMotionInputFrame.IsInputConsumed = false;
}

void ManagerInput::OnMouseButton(GLFWwindow* InrWindow, int IniButton, int IniAction, int IniMods)
{
	rMouseInputFrame.eMouseKey = static_cast<EMouseKey>(IniButton);
	rMouseInputFrame.eInputState = static_cast<EInputState>(IniAction);
	rMouseInputFrame.iMods = static_cast<EMod>(IniMods);

	rMouseInputFrame.IsInputConsumed = false;
}

void ManagerInput::OnScroll(GLFWwindow* InrWindow, double IndOffsetX, double IndOffsetY)
{
	rMouseScrollInputFrame.dScrollX = IndOffsetX;
	rMouseScrollInputFrame.dScrollY = IndOffsetY;

	rMouseScrollInputFrame.IsInputConsumed = false;
}

void ManagerInput::ProcessInput()
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
				rLog.WriteAndDisplay("failed to bind device input, unknown device detected. Aborting.");
				break;
		}
	}
}

void ManagerInput::CallKeyInputList(vector<SInputInfo> & InsInputInfo)
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

void ManagerInput::CallMousePosList(vector<SInputInfo> const& InsInputInfo)
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

void ManagerInput::CallMouseButtonInputList(vector<SInputInfo> const& InsInputInfo)
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

void ManagerInput::CallScrollInputList(vector<SInputInfo> const& InsInputInfo)
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

ManagerInput::ManagerInput()
{
	rKeyboardKeyList.emplace(EDeviceType::EDT_Keyboard, vector<SInputInfo>());
	rKeyboardKeyList.emplace(EDeviceType::EDT_Joystic, vector<SInputInfo>());
	rKeyboardKeyList.emplace(EDeviceType::EDT_Mouse, vector<SInputInfo>());
	rKeyboardKeyList.emplace(EDeviceType::EDT_Gamepad, vector<SInputInfo>());

	if(rCurrentWindowInput != nullptr)
	{
		glfwSetKeyCallback(rCurrentWindowInput, ManagerInput::OnKey);
		glfwSetCursorPosCallback(rCurrentWindowInput, ManagerInput::OnMousePos);
		//glfwSetCursorEnterCallback(rCurrentWindowInput, ManagerInput::OnCursorEnter);
		glfwSetMouseButtonCallback(rCurrentWindowInput, ManagerInput::OnMouseButton);
		glfwSetScrollCallback(rCurrentWindowInput, ManagerInput::OnScroll);
	}
}
