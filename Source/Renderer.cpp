#include "Renderer.h"


Renderer::Renderer()
{
	Initialize();
}

Renderer::~Renderer()
{

}

void Renderer::Initialize()
{
	rLog = Log("LogRenderer");
}

bool Renderer::EnableMode(EGLEnable IneEnable, bool InbEnable)
{
	if (InbEnable)
	{
		if (!IsModeEnabled(IneEnable))
			glEnable(static_cast<GLenum>(IneEnable));
		else
		{
			rLog.Write("Mode is already enabled");
			return false;
		}
	}
	else
	{
		if (IsModeEnabled(IneEnable))
			glDisable(static_cast<GLenum>(IneEnable));
		else
		{
			rLog.Write("Mode is already disabled");
			return false;
		}
	}

	DisplayAllGLError();

	return true;
}