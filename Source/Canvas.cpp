#include "Canvas.h"

Canvas::Canvas(
	int32 IniWidth, 
	int32 IniHeight, 
	string const& InsTitle) :
	iWidth(IniWidth),
	iHeight(IniHeight),
	sTitle(InsTitle)
{
	Initialize();
}

Canvas::Canvas(Canvas&& InrCanvas) noexcept :
	iRatioX(InrCanvas.iRatioX),
	iRatioY(InrCanvas.iRatioY),
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
	iRatioX(InrCanvas.iRatioX),
	iRatioY(InrCanvas.iRatioY),
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
		iRatioX = InrCanvas.iRatioX;
		iRatioY = InrCanvas.iRatioY;
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
		iRatioX = InrCanvas.iRatioX;
		iRatioY = InrCanvas.iRatioY;
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
	iRatioY = iRatioX = (InfAspectScalar > 1) ? InfAspectScalar : iRatioX;

	SetHeight(GetWidth());
}

void Canvas::SetAspect(float IniAspectX, float IniAspectY)
{
	iRatioX = (IniAspectX > 1.0f) ? IniAspectX : 1.0f;
	iRatioY = (IniAspectY > 1.0f) ? IniAspectY : 1.0f;

	iHeight = GetAspectRatioHeight() * GetWidth();
}

void Canvas::OnResize(GLFWwindow* InrCanvas, int32 IniWidth, int32 IniHeight)
{
	glViewport(static_cast<GLint>(IniWidth*0.166), static_cast<GLint>(IniHeight*0.333 - 18), static_cast<GLsizei>(IniWidth - IniWidth*0.333), static_cast<GLsizei>(IniHeight*0.667));

	//glfwSetCanvasSize(InrCanvas, IniWidth, IniHeight);
}

void Canvas::Initialize()
{
	CreateWindow();

	if (rWindow == nullptr)
		rLog.WriteAndDisplay("Failed to open GLFW Canvas. If you have an Intel GPU, they are not 3.3 compatible.\n");

	glfwMakeContextCurrent(rWindow);

	//glfwSetCanvasAspectRatio(rWindow, iRatioX, iRatioY);
	//glfwSetInputMode(rWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//glViewport(GetWidth()*0.166, GetHeight()*0.333 - 18, GetWidth() - GetWidth()*0.333, GetHeight()*0.667);

	glfwSetWindowSizeCallback(rWindow, Canvas::OnResize);

	//printf("%s\n", glGetString(GL_VERSION));
}