#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <iomanip>

#include "KronosEngine.h"

using glm::vec3, glm::vec2 , glm::mat4;

using std::cout;


int WindowWidth = 1024;
int WindowHeight = static_cast<int>(WindowWidth * static_cast<float>(9.0f / 16.0f));

float MouseLastX = WindowWidth / 2, MouseLastY = WindowHeight / 2;

Camera MainCamera(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), 45.0f, (16.0f / 9.0f), 10.0f, 0.1f, 100.0f);

float DeltaTime = 0.0f, LastFrame = 0.0f;

Texture* Test;

Log rGlobalLog("Log", "Log/", "Log.txt");

int GLFWInit()
{
	Log rGLFWLog("GLFWLog", "Log/", "Log.txt");

	MainCamera.SetMinRotation(vec3(-360.0f, -89.0f, -360.0f));
	MainCamera.SetMaxRotation(vec3(360.0f, 89.0f, 360.0f));
	// Initialise GLFW
	glewExperimental = true; // Needed for core profile

	if (!glfwInit())
	{
		rGLFWLog.WriteAndDisplay("Failed to initialize GLFW", ELogSeverity::ELS_Critical);

		glfwTerminate();

		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 2); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	return true;
}

int GLEWInit()
{
	Log rGLEWLog("GLEWLog", "Log/", "Log.txt");

	if (glewInit() != GLEW_OK)
	{
		rGLEWLog.WriteAndDisplay("Glew context failed to load", ELogSeverity::ELS_Critical);

		return -2;
	}

	return true;
}

void OnWindowResize(GLFWwindow* InrWindow, int32 IniWindowWidth, int32 IniWindowHeight) noexcept
{
	glViewport(0, 0, static_cast<GLsizei>(IniWindowWidth), static_cast<GLsizei>(IniWindowHeight));
	glfwSetWindowSize(InrWindow, IniWindowWidth, IniWindowHeight);
}

void ProcessInput(GLFWwindow* InrWindow)
{
	const float CameraSpeed = 10.f * DeltaTime;

	if (glfwGetKey(InrWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(InrWindow, true);
	else if (glfwGetKey(InrWindow, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (glfwGetKey(InrWindow, GLFW_KEY_1) == GLFW_RELEASE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (Test && glfwGetKey(InrWindow, GLFW_KEY_2) == GLFW_PRESS)
		Test->SetTextureMinFilter(ETextureMinFilter::ETMF_Linear);
	else if (Test && glfwGetKey(InrWindow, GLFW_KEY_3) == GLFW_PRESS)
		Test->SetTextureMinFilter(ETextureMinFilter::ETMF_Nearest);
	else if (Test && glfwGetKey(InrWindow, GLFW_KEY_4) == GLFW_PRESS)
		Test->SetTextureMinFilter(ETextureMinFilter::ETMF_NearestMipMapLinear);

	if (glfwGetKey(InrWindow, GLFW_KEY_W) == GLFW_PRESS)
		MainCamera.TravelForwards(1.0f * DeltaTime);
	else if (glfwGetKey(InrWindow, GLFW_KEY_S) == GLFW_PRESS)
		MainCamera.TravelForwards(-1.0f * DeltaTime);

	if (glfwGetKey(InrWindow, GLFW_KEY_A) == GLFW_PRESS)
		MainCamera.TravelSideways(-1.0f * DeltaTime);
	else if (glfwGetKey(InrWindow, GLFW_KEY_D) == GLFW_PRESS)
		MainCamera.TravelSideways(1.0f * DeltaTime);

	if (glfwGetKey(InrWindow, GLFW_KEY_E) == GLFW_PRESS)
		MainCamera.TravelUpwards(1.0f * DeltaTime);
	else if (glfwGetKey(InrWindow, GLFW_KEY_Q) == GLFW_PRESS)
		MainCamera.TravelUpwards(-1.0f * DeltaTime);
}

bool FirstMouse = true;

void MouseCallback(GLFWwindow* InrWindow, double XPosIn, double YPosIn)
{
	const float XPos = static_cast<float>(XPosIn);
	const float YPos = static_cast<float>(YPosIn);

	if (FirstMouse)
	{
		MouseLastX = XPos;
		MouseLastY = YPos;
		FirstMouse = false;
	}

	const float XOffset = (XPos - MouseLastX) * 4.0f * DeltaTime;
	const float YOffset = (MouseLastY - YPos) * 4.0f * DeltaTime;

	MouseLastX = XPos;
	MouseLastY = YPos;

	MainCamera.AddYaw(XOffset);
	MainCamera.AddPitch(YOffset);
}

void ScrollCallback(GLFWwindow* InrWindow, double XOffset, double YOffset)
{
	MainCamera.SetFOV(MainCamera.GetFOV() - static_cast<float>(YOffset));

	if (MainCamera.GetFOV() < 1.0f)
		MainCamera.SetFOV(1.0f);
	else if (MainCamera.GetFOV() > 45.0f)
		MainCamera.SetFOV(45.0f);
}


GLvoid DepthView() noexcept
{
	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

GLvoid SolidView()
{
	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Shader rSolidColor("Resource/Shader/Solid.vs", "Resource/Shader/Solid.fs");
}

GLvoid MaterialView() noexcept
{
	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

GLvoid WindowRenderLoop()
{
	const float CurrentFrame = static_cast<float>(glfwGetTime());

	DeltaTime = CurrentFrame - LastFrame;
	LastFrame = CurrentFrame;

	MainCamera.Update();
}

/*void TestFunc()
{
	cout << "test\n";
}*/

int main(int argc, char **argv)
{	
	//void (*PointerFunc0)() = &TestFunc;

	//void (*PointerFunc)() = PointerFunc0;

	if (GLFWInit())
	{
		//PointerFunc();

		Window* MainWindow = new Window(1024, (1024 * (9.0f / 16.0f)), "Tutorial 01");

		// Open a window and create its OpenGL context
		//GLFWwindow* Window = glfwCreateWindow(WindowWidth, WindowHeight, "Tutorial 01", NULL, NULL); // (In the accompanying source code, this variable is global for simplicity)

		/*if (Window == NULL)
		{
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
			glfwTerminate();
			return 1;
		}*/

		//glfwMakeContextCurrent(Window);

		//glfwSetWindowAspectRatio(Window, 16, 9);
		//glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (!GLEWInit())
			return -2;

		glViewport(0, 0, MainWindow->GetWidth(), MainWindow->GetHeight());

		glfwSetFramebufferSizeCallback(MainWindow->GetWindow(), OnWindowResize);
		glfwSetCursorPosCallback(MainWindow->GetWindow(), MouseCallback);
		glfwSetScrollCallback(MainWindow->GetWindow(), ScrollCallback);

		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

		rGlobalLog.WriteAndDisplay("Maximum nr if vertex attributes supported: " + to_string(nrAttributes));

		Texture* FrameBufferTexture = new Texture(
			WindowWidth,
			WindowHeight,
			ETextureType::ETT_Albedo,
			ETextureDataType::ETDT_Texture2D,
			ETextureSlot::ETS_Slot0,
			ETextureFormat::ETF_RGB);

		Framebuffer* rFramebuffer = new Framebuffer(
			EFramebufferOp::EFO_FrameBuffer,
			EFramebufferAttach::EFA_Color,
			EFramebufferTex::EFT_Texture2D,
			FrameBufferTexture,
			0);

		Renderer* rRenderer = new Renderer();

		FrameBufferTexture = nullptr;

		Shader rShaderLight("Resource/Shader/Light.vs", "Resource/Shader/Light.fs");
		Shader rShaderCubeLight("Resource/Shader/LightColorCube.vs", "Resource/Shader/LightColorCube.fs");
		Shader rShaderStencil("Resource/Shader/Stencil.vs", "Resource/Shader/Stencil.fs");

		Vertex Pos1, Pos2, Pos3, Pos4;

		Pos1.VertexData.Position = vec3(0.0f, 0.0f, 0.0f);
		Pos1.VertexData.Normal = vec3(0.0f, 0.0f, 1.0f);
		Pos1.VertexData.TexCoords = vec2(0.0f, 0.0f);

		Pos2.VertexData.Position = vec3(1.0f, 0.0f, 0.0f);
		Pos2.VertexData.Normal = vec3(0.0f, 0.0f, 1.0f);
		Pos2.VertexData.TexCoords = vec2(1.0f, 0.0f);

		Pos3.VertexData.Position = vec3(1.0f, 1.0f, 0.0f);
		Pos3.VertexData.Normal = vec3(0.0f, 0.0f, 1.0f);
		Pos3.VertexData.TexCoords = vec2(1.0f, 1.0f);

		Pos4.VertexData.Position = vec3(0.0f, 1.0f, 0.0f);
		Pos4.VertexData.Normal = vec3(0.0f, 0.0f, 1.0f);
		Pos4.VertexData.TexCoords = vec2(0.0f, 1.0f);

		vector<Vertex> Vertices = {
			Pos1,
			Pos2,
			Pos3,
			Pos4
		};

		vector<uint32_t> Indices = {
			0, 1, 2,
			2, 3, 0
		};

		Texture* rGrassTexture = new Texture(
			"Resource/Img/grass.png",
			ETextureType::ETT_Albedo,
			ETextureDataType::ETDT_Texture2D,
			ETextureSlot::ETS_Slot0,
			ETextureFormat::ETF_RGBA);

		rGrassTexture->SetTextureWrap(ETextureWrap::ETW_Clip);

		vector<Texture*> rTextures;

		rTextures.push_back(rGrassTexture);

		Mesh PlanarGrass = Mesh(Vertices, Indices, &rTextures);

		Vertices.at(0).VertexData.Position = Pos1.VertexData.Position + 1.f;
		Vertices.at(1).VertexData.Position = Pos2.VertexData.Position + 1.f;
		Vertices.at(2).VertexData.Position = Pos3.VertexData.Position + 1.f;
		Vertices.at(3).VertexData.Position = Pos4.VertexData.Position + 1.f;

		Mesh PlanarGrass2 = Mesh(Vertices, Indices, &rTextures);


		rRenderer->EnableMode(EGLEnable::EGLE_DepthTest, true);
		rRenderer->EnableMode(EGLEnable::EGLE_StencilTest, true);
		rRenderer->EnableMode(EGLEnable::EGLE_CullFace, true);

		rRenderer->SetCullFace(EGLCullFace::EGLCF_Back);

		rRenderer->EnableDepthMask(true);
		rRenderer->SetDepthFunc(EGLFunc::EGLDF_Less);

		rRenderer->SetStencilMask(0xFF);
		rRenderer->SetStencilFunc(EGLFunc::EGLDF_GEqual, 1, 0xFF);

		rRenderer->SetStencilOp(EGLStencilOp::EGLSO_Keep);

		rRenderer->SetPolygonMode(EGLCullFace::EGLCF_FrontAndBack, EGLPolygonMode::EGLP_Fill);

		rRenderer->SetClearColor(.2f * 0.3f, .4f * 0.3f, .3f * 0.3f, 1.f);

		rRenderer->SetClearBuffer(EGLClearBuffer::EGLC_ColorBufferBit | EGLClearBuffer::EGLC_DepthBufferBit | EGLClearBuffer::EGLC_StencilBufferBit);

		glfwSwapInterval(1);

		MainCamera.SetYaw(-89.0f);

		//Model NewModel("cube/cube.obj");

		rShaderLight.Use();
		//Main loop
		while (!glfwWindowShouldClose(MainWindow->GetWindow()))
		{
			ProcessInput(MainWindow->GetWindow());

			rRenderer->Clear();

			WindowRenderLoop();

			mat4 View = MainCamera.GetView();
			mat4 Projection = MainCamera.GetProjection();
			mat4 Model = mat4(1.0f);

			vec3 CameraPosition = -MainCamera.GetLocation();
			vec3 CameraFront = MainCamera.GetFront();

			rShaderLight.Use();
			rShaderLight.SetVec3("ViewPos", CameraPosition);

			rShaderLight.SetVec3("DirLight.Direction", CameraPosition);
			rShaderLight.SetVec3("DirLight.Diffuse", 1.0f);
			rShaderLight.SetVec3("DirLight.Specular", 1.0f);
			rShaderLight.SetVec3("DirLight.Ambient", 0.3f);

			rShaderLight.SetMat4("View", View);
			rShaderLight.SetMat4("Projection", Projection);
			rShaderLight.SetMat4("Model", Model);

			PlanarGrass.Draw(rShaderLight);
			PlanarGrass2.Draw(rShaderLight);


			//NewModel.Draw(rShaderLight);

			glfwSwapBuffers(MainWindow->GetWindow());
			glfwPollEvents();
		}

		//glDeleteFramebuffers(1, &BufferID);

		glfwDestroyWindow(MainWindow->GetWindow());
		glfwTerminate();
		
		delete rFramebuffer;
		delete rGrassTexture;
		delete rRenderer;
	}
	else
		return -1;

	return 0;
}