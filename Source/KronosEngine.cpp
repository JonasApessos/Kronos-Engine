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

int GLFWInit()
{
	MainCamera.SetMinRotation(vec3(-360.0f, -89.0f, -360.0f));
	MainCamera.SetMaxRotation(vec3(360.0f, 89.0f, 360.0f));
	// Initialise GLFW
	glewExperimental = true; // Needed for core profile

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");

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
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Glew context failed to load\n");
		glfwTerminate();
		return -2;
	}

	return true;
}

void OnWindowResize(GLFWwindow* InrWindow, int32 IniWindowWidth, int32 IniWidthHeight) noexcept
{
	glViewport(0, 0, static_cast<GLsizei>(IniWindowWidth), static_cast<GLsizei>(IniWidthHeight));
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

int main()
{
	if (GLFWInit())
	{

		// Open a window and create its OpenGL context
		GLFWwindow* Window = glfwCreateWindow(WindowWidth, WindowHeight, "Tutorial 01", NULL, NULL); // (In the accompanying source code, this variable is global for simplicity)

		if (Window == NULL)
		{
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
			glfwTerminate();
			return 1;
		}

		glfwMakeContextCurrent(Window);

		glfwSetWindowAspectRatio(Window, 16, 9);
		glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


		if (!GLEWInit())
			return -2;

		glViewport(0, 0, WindowWidth, WindowHeight);

		glfwSetFramebufferSizeCallback(Window, OnWindowResize);
		glfwSetCursorPosCallback(Window, MouseCallback);
		glfwSetScrollCallback(Window, ScrollCallback);

		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

		cout << "Maximum nr if vertex attributes supported: " << nrAttributes << "\n";

		Texture FrameBufferTexture(
			WindowWidth,
			WindowHeight,
			ETextureType::ETT_Albedo,
			ETextureDataType::ETDT_Texture2D,
			ETextureSlot::ETS_Slot0,
			ETextureFormat::ETF_RGB);

		Framebuffer rFramebuffer(
			EFramebufferOp::EFO_FrameBuffer,
			EFramebufferAttach::EFA_Color,
			EFramebufferTex::EFT_Texture2D,
			&FrameBufferTexture,
			0);

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

		Texture GrassTexture("Resource/Img/grass.png", ETextureType::ETT_Albedo, ETextureDataType::ETDT_Texture2D, ETextureSlot::ETS_Slot0);

		GrassTexture.SetTextureWrap(ETextureWrap::ETW_Clip);

		vector<Texture> Textures = { GrassTexture };

		Mesh PlanarGrass = Mesh(Vertices, Indices, Textures);


		Vertices.at(0).VertexData.Position = Pos1.VertexData.Position + 1.f;
		Vertices.at(1).VertexData.Position = Pos2.VertexData.Position + 1.f;
		Vertices.at(2).VertexData.Position = Pos3.VertexData.Position + 1.f;
		Vertices.at(3).VertexData.Position = Pos4.VertexData.Position + 1.f;

		Mesh PlanarGrass2 = Mesh(Vertices, Indices, Textures);


		glEnable(GL_DEPTH_TEST);

		glEnable(GL_STENCIL_TEST);

		glEnable(GL_CULL_FACE);

		glCullFace(GL_BACK);

		glDepthMask(GL_TRUE);

		glDepthFunc(GL_LESS);

		glStencilMask(0xFF);

		glStencilFunc(GL_GEQUAL, 1, 0xFF);

		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glfwSwapInterval(1);

		glClearColor(.2f * 0.3f, .4f * 0.3f, .3f * 0.3f, 1.f);

		MainCamera.SetYaw(-89.0f);

		//Model NewModel("cube/cube.obj");

		rShaderLight.Use();
		//Main loop
		while (!glfwWindowShouldClose(Window))
		{
			ProcessInput(Window);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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

			glfwSwapBuffers(Window);
			glfwPollEvents();
		}

		//glDeleteFramebuffers(1, &BufferID);

		glfwTerminate();
	}
	else
		return -1;

	return 0;
}