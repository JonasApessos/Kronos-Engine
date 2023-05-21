#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Log.h"
#include "Window.h"

using std::string;

class App
{
public:
	App(int iniCommandIndex, char** IncCommandArguments);

	~App();

	void Destroy();

	inline bool IsInitSuccess() const;
protected:
	string sAppTitle = "";

	Log rLog;

private:
	bool bIsGLFWInit = false;
	bool bIsInitSuccess = false;

	void InitGLFW();
};

inline bool App::IsInitSuccess() const { return bIsInitSuccess; }