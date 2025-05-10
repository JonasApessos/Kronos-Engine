#include "Canvas.h"

Canvas::Canvas(
	int32 IniWidth, 
	int32 IniHeight, 
	string const& InsTitle) :
	iWidth(IniWidth),
	iHeight(IniHeight),
	sTitle(InsTitle)
{
	Init();
}

Canvas::Canvas(Canvas&& InrCanvas) noexcept :
	fRatioX(InrCanvas.fRatioX),
	fRatioY(InrCanvas.fRatioY),
	iWidth(InrCanvas.iWidth),
	iHeight(InrCanvas.iHeight),
	sTitle(InrCanvas.sTitle),
	rWindow(InrCanvas.rWindow),
	rMonitor(InrCanvas.rMonitor),
	rVidMode(InrCanvas.rVidMode)	
{
	InrCanvas.rWindow = nullptr;
	InrCanvas.rMonitor = nullptr;
}

Canvas::Canvas(Canvas const& InrCanvas) noexcept :
	fRatioX(InrCanvas.fRatioX),
	fRatioY(InrCanvas.fRatioY),
	iWidth(InrCanvas.iWidth),
	iHeight(InrCanvas.iHeight),
	sTitle(InrCanvas.sTitle),
	rWindow(InrCanvas.rWindow),
	rMonitor(InrCanvas.rMonitor),
	rVidMode(InrCanvas.rVidMode) {}

Canvas::~Canvas()
{
	Destroy();
}

Canvas& Canvas::operator=(Canvas const& InrCanvas) noexcept
{
	if (this != &InrCanvas)
	{
		iWidth = InrCanvas.iWidth;
		iHeight = InrCanvas.iHeight;
		fRatioX = InrCanvas.fRatioX;
		fRatioY = InrCanvas.fRatioY;
		sTitle = InrCanvas.sTitle;
		rWindow = InrCanvas.rWindow;
		rMonitor = InrCanvas.rMonitor;
		rVidMode = InrCanvas.rVidMode;
	}

	return *this;
}

Canvas& Canvas::operator=(Canvas&& InrCanvas) noexcept
{
	if (this != &InrCanvas)
	{
		iWidth = InrCanvas.iWidth;
		iHeight = InrCanvas.iHeight;
		fRatioX = InrCanvas.fRatioX;
		fRatioY = InrCanvas.fRatioY;
		sTitle = InrCanvas.sTitle;
		rWindow = InrCanvas.rWindow;
		rMonitor = InrCanvas.rMonitor;
		rVidMode = InrCanvas.rVidMode;

		InrCanvas.rWindow = nullptr;
		InrCanvas.rMonitor = nullptr;
	}

	return *this;
}

void Canvas::Destroy()
{
	if (rWindow != nullptr)
	{
		glfwDestroyWindow(rWindow);

		rWindow = nullptr;
	}

	if (rMonitor != nullptr)
	{
		delete rMonitor;

		rMonitor = nullptr;
	}
}

void Canvas::SetAspect(float InfAspectScalar)
{
	fRatioY = fRatioX = (InfAspectScalar > 1.0f) ? InfAspectScalar : fRatioX;

	SetHeight(GetWidth());
}

void Canvas::SetAspect(float InfAspectX, float InfAspectY)
{
	fRatioX = (InfAspectX * InfAspectX > 1.0f) + (1.0f * InfAspectX <= 1.0f);
	fRatioY = (InfAspectY * InfAspectY > 1.0f) + (1.0f * InfAspectY <= 1.0f);

	iHeight = GetAspectRatioHeight() * GetWidth();
}

void Canvas::OnResize(GLFWwindow* InrCanvas, int32 IniWidth, int32 IniHeight)
{
	glViewport(
		static_cast<GLint>(IniWidth * 0.166f * 2.0f),
		static_cast<GLint>(IniHeight * 0.333f * 2.0f),
		static_cast<GLsizei>((IniWidth - IniWidth * 0.333f) * 2.0f),
		static_cast<GLsizei>((IniHeight * 0.667f) * 2.0f));
}

void Canvas::Init()
{
	glfwWindowHint(GLFW_SAMPLES, 4); // 2x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 


	rWindow = CreateWindow();

	if (rWindow == nullptr)
		rLog.WriteAndDisplay("Failed to open GLFW Canvas. If you have an Intel GPU, they are not 3.3 compatible.\n");

	glfwMakeContextCurrent(rWindow);

	glfwSetWindowSizeCallback(rWindow, Canvas::OnResize);
}