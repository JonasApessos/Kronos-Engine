#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "GLFW/glfw3.h"
#include "InputHandler.h"

using std::map, std::vector;

class InputManager
{
public:

	InputManager(const InputManager&) = delete;

	static InputManager* GetInputManagerInstance();

	static void Destroy();

	static void BindKey(const string& InsHandleName, EGLFWInputKey IneInputKey, void (*InrCallbackFunc)());

	static inline void SetCurrentWindow(GLFWwindow* InrWindowP);

	static inline GLFWwindow* GetCurrentWindow();

protected:
	static void ProcessInput(GLFWwindow* InrWindowP, int IniKey, int IniScanCode, int IniAction, int IniMods);

private:
	static map<EGLFWInputKey, vector<InputKeyHandler*>>* rInputHandleMap;

	static GLFWwindow* rCurrentWindowInputP;

	static InputManager* rSingletonInputManagerP;

	InputManager();
};

map<EGLFWInputKey, vector<InputKeyHandler*>>* InputManager::rInputHandleMap = new map<EGLFWInputKey, vector<InputKeyHandler*>>();

GLFWwindow* InputManager::rCurrentWindowInputP = nullptr;

InputManager* InputManager::rSingletonInputManagerP = new InputManager();

inline void InputManager::SetCurrentWindow(GLFWwindow* InrWindowP) { glfwSetKeyCallback(InrWindowP, InputManager::ProcessInput); }
inline GLFWwindow* InputManager::GetCurrentWindow() { return rCurrentWindowInputP; }