#include "KronosEngine.h"

using glm::vec3, glm::vec2 , glm::mat4;

using std::cout, std::exception;

constexpr int32 WindowWidth = 1024;
constexpr int32 WindowHeight = static_cast<int32>(static_cast<float>(WindowWidth) * static_cast<float>(9.0f / 16.0f));

float MouseLastX = WindowWidth / 2, MouseLastY = WindowHeight / 2;

Camera MainCamera(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), 45.0f, (16.0f / 9.0f), 10.0f, 0.1f, 100.0f);

float DeltaTime = 0.0f, LastFrame = 0.0f;

Log rGlobalLog("Log");

void ProcessInput(GLFWwindow* InrWindow)
{
	if (glfwGetKey(InrWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(InrWindow, true);
	else if (glfwGetKey(InrWindow, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (glfwGetKey(InrWindow, GLFW_KEY_1) == GLFW_RELEASE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

int main(int argc, char **argv)
{
	try 
	{
		App* KronosApp = new App(argc, argv);

		if (KronosApp->IsInitSuccess())
		{
			MainCamera.SetMinRotation(vec3(-360.0f, -89.0f, -360.0f));
			MainCamera.SetMaxRotation(vec3(360.0f, 89.0f, 360.0f));

			Window* MainWindow = new Window(1024, static_cast<int32>(1024.f * (9.0f / 16.0f)), "Kronos Engine");
			

			if (glewInit() == GLEW_OK)
				glewExperimental = true; // Needed for core profile
			else
			{
				rGlobalLog.WriteAndDisplay("Glew context failed to load", ELogSeverity::ELS_Critical);
				KronosApp->Destroy();
				return -2;
			}
			
			glfwSetCursorPosCallback(MainWindow->GetWindow(), MouseCallback);
			glfwSetScrollCallback(MainWindow->GetWindow(), ScrollCallback);
			
			GLint nrAttributes;
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
			
			rGlobalLog.WriteAndDisplay("Maximum nr if vertex attributes supported: " + to_string(nrAttributes));

			Texture* FrameBufferTexture = new Texture(
				MainWindow->GetWidth(),
				MainWindow->GetHeight(),
				ETextureType::ETT_Albedo,
				EGLTextureDataType::EGLTDT_Texture2D,
				EGLTextureSlot::EGLTS_Slot0,
				EGLTextureFormat::EGLTF_RGB);

			Framebuffer* rFramebuffer = new Framebuffer(
				EGLFramebufferOp::EGLFO_FrameBuffer,
				EGLFramebufferAttach::EGLFA_Color,
				EGLFramebufferTex::EGLFT_Texture2D,
				FrameBufferTexture,
				0);

			Renderer* rRenderer = new Renderer();

			Shader rShaderLight("Resource/Shader/Light.vs", "Resource/Shader/Light.fs");
			Shader rShaderCubeLight("Resource/Shader/LightColorCube.vs", "Resource/Shader/LightColorCube.fs");
			Shader rShaderStencil("Resource/Shader/Stencil.vs", "Resource/Shader/Stencil.fs");

			rRenderer->EnableMode(EGLEnable::EGLE_DepthTest, true);
			rRenderer->EnableMode(EGLEnable::EGLE_StencilTest, true);
			rRenderer->EnableMode(EGLEnable::EGLE_CullFace, true);
			rRenderer->EnableMode(EGLEnable::EGLE_ProgramPointSize, true);

			glPointSize(10);

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

			Model NewModel2(SShapePrimCube(0.2f,0.2f).GetModel());

			NewModel2.Translate(vec3(1.f, 0.f, 0.f));
			
			mat4 View = MainCamera.GetView();
			mat4 Projection = MainCamera.GetProjection();
			vec3 CameraPosition = -MainCamera.GetLocation();

			glReleaseShaderCompiler();

			GizmoTransform test = GizmoTransform();

			//Main loop
			while (!glfwWindowShouldClose(MainWindow->GetWindow()))
			{
				ProcessInput(MainWindow->GetWindow());

				rRenderer->Clear();

				WindowRenderLoop();

				View = MainCamera.GetView();
				Projection = MainCamera.GetProjection();

				CameraPosition = -MainCamera.GetLocation();
				
				rShaderCubeLight.Use();
				rShaderCubeLight.SetVec3("ObjectColor", 1.0f, 0.5f, 0.31f);
				rShaderCubeLight.SetVec3("LightColor", 1.0f, 1.0f, 1.0f);
				rShaderCubeLight.SetVec3("LightPos", 1.f, -2.0f, 1.f);
				rShaderCubeLight.SetVec3("ViewPos", CameraPosition);
				rShaderCubeLight.SetVec3("ObjectPos", 0.f, 0.f, 0.f);

				rShaderCubeLight.SetMat4("View", View);
				rShaderCubeLight.SetMat4("Projection", Projection);
				rShaderCubeLight.SetMat4("Model", NewModel2.GetTransformMatrix());
				
				
				//NewModel->Draw(rShaderCubeLight);
				//NewModel2.Draw(rShaderCubeLight);

				rShaderCubeLight.SetMat4("Model", test.GetTransformMatrix());

				test.Draw(rShaderCubeLight);
				
				glfwSwapBuffers(MainWindow->GetWindow());
				glfwPollEvents();
			}

			delete rFramebuffer;
			delete rRenderer;
			delete MainWindow;
			delete KronosApp;
		}
		else
			return -1;
	} catch (exception &e)
	{
		cerr << e.what() << "\n";
	}

	return 0;
}