#include "KronosEngine.h"

using glm::vec3, glm::vec2 , glm::mat4;

using std::cout, std::exception;

constexpr int32 WindowWidth = 1280;
constexpr int32 WindowHeight = static_cast<int32>(static_cast<float>(WindowWidth) * static_cast<float>(9.0f / 16.0f));

float MouseLastX = WindowWidth / 2, MouseLastY = WindowHeight / 2;

Camera rMainCamera(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), 45.0f, (16.0f / 9.0f), 10.0f, 0.1f, 100.0f);

float DeltaTime = 0.0f, LastFrame = 0.0f;

Log rGlobalLog("Log");

static int Index = 0;

const char* ctest[] = {"test1", "test2", "Test3", "Test4", "Test5", "Test6", "Test7", "Test8", "Test9"};

/**
 * @deprecated Deprecated function
*/
void ProcessInput(GLFWwindow* InrWindow)
{
	if (glfwGetKey(InrWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(InrWindow, true);
	else if (glfwGetKey(InrWindow, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (glfwGetKey(InrWindow, GLFW_KEY_1) == GLFW_RELEASE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	if (glfwGetKey(InrWindow, GLFW_KEY_W) == GLFW_PRESS)
		rMainCamera.TravelForwards(1.0f * DeltaTime);
	else if (glfwGetKey(InrWindow, GLFW_KEY_S) == GLFW_PRESS)
		rMainCamera.TravelForwards(-1.0f * DeltaTime);

	if (glfwGetKey(InrWindow, GLFW_KEY_A) == GLFW_PRESS)
		rMainCamera.TravelSideways(-1.0f * DeltaTime);
	else if (glfwGetKey(InrWindow, GLFW_KEY_D) == GLFW_PRESS)
		rMainCamera.TravelSideways(1.0f * DeltaTime);

	if (glfwGetKey(InrWindow, GLFW_KEY_E) == GLFW_PRESS)
		rMainCamera.TravelUpwards(1.0f * DeltaTime);
	else if (glfwGetKey(InrWindow, GLFW_KEY_Q) == GLFW_PRESS)
		rMainCamera.TravelUpwards(-1.0f * DeltaTime);
}

bool FirstMouse = true;

/**
 * @deprecated Deprecated function callback
*/
void MouseCallback(GLFWwindow* InrWindow, double XPosIn, double YPosIn)
{
	ImGui_ImplGlfw_CursorPosCallback(InrWindow, XPosIn, YPosIn);

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

	rMainCamera.AddYaw(XOffset);
	rMainCamera.AddPitch(YOffset);
}


/**
 * @deprecated Deprecated function callback
*/
void ScrollCallback(GLFWwindow* InrWindow, double XOffset, double YOffset)
{
	ImGui_ImplGlfw_ScrollCallback(InrWindow, XOffset, YOffset);

	rMainCamera.SetFOV(rMainCamera.GetFOV() - static_cast<float>(YOffset));

	if (rMainCamera.GetFOV() < 1.0f)
		rMainCamera.SetFOV(1.0f);
	else if (rMainCamera.GetFOV() > 45.0f)
		rMainCamera.SetFOV(45.0f);
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

	rMainCamera.Update();
}

void GUIMainMenu(Window* InrWindow)
{
	bool IsMainWindowVisible = true;

	if(ImGui::BeginMainMenuBar())
	{
		if(ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Save");
			ImGui::Separator();
			ImGui::MenuItem("Save As");

			ImGui::EndMenu();
		}

		if(ImGui::BeginMenu("Edit"))
		{
			ImGui::MenuItem("Prefrences");
			ImGui::Separator();
			ImGui::MenuItem("Settings");

			ImGui::EndMenu();
		}

		if(ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("About");
			ImGui::Separator();
			ImGui::MenuItem("Docs");

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void GUICreatorTab(Window*  InrWindow)
{
	bool IsMainWindowVisible = true;

	//Creator Tab
	if(ImGui::Begin("Creator Tab",
	&IsMainWindowVisible,
	ImGuiWindowFlags_NoCollapse |
	ImGuiWindowFlags_NoResize |
	ImGuiWindowFlags_NoDecoration |
	ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoBringToFrontOnFocus))
	{
		
		ImGui::SetWindowPos(ImVec2(0,18));
		ImGui::SetWindowSize(ImVec2(InrWindow->GetWidth()*0.166, InrWindow->GetHeight()*0.667));

		ImGui::Text("Creator TAB");

		ImGui::End();
	}
}

void GUIOutlineTab(Window* InrWindow)
{

	bool IsMainWindowVisible = true;

	//Outliner Tab
	if(ImGui::Begin("Outliner",
	&IsMainWindowVisible,
	ImGuiWindowFlags_NoCollapse |
	ImGuiWindowFlags_NoResize |
	ImGuiWindowFlags_NoDecoration |
	ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoBringToFrontOnFocus))
	{
		ImGui::SetWindowPos(ImVec2(InrWindow->GetWidth() - InrWindow->GetWidth()*0.166, 18));
		ImGui::SetWindowSize(ImVec2(InrWindow->GetWidth()*0.166, InrWindow->GetHeight()*0.667));

		if(ImGui::BeginTabBar("OutlineTab"))
		{
			if(ImGui::TabItemButton("Outline")){}
			if(ImGui::TabItemButton("Propertys")){}

			ImGui::EndTabBar();
		}


		if(ImGui::BeginListBox("OutlineList", ImVec2(InrWindow->GetWidth()*0.166, InrWindow->GetHeight()*0.667)))
		{

			for (int n = 0; n < IM_ARRAYSIZE(ctest); n++)
			{
				const bool is_selected = (Index == n);
				if (ImGui::Selectable(ctest[n], is_selected))
					Index = n;

				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndListBox();
		}

		ImGui::End();
	}
}

void GUIAssetTab(Window*  InrWindow)
{

	bool IsMainWindowVisible = true;

	//Asset Browser Tab
	if(ImGui::Begin("Asset Browser Tab", 
	&IsMainWindowVisible,
	ImGuiWindowFlags_NoCollapse | 
	ImGuiWindowFlags_NoResize |
	ImGuiWindowFlags_NoDecoration |
	ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoBringToFrontOnFocus))
	{
		ImGui::SetWindowPos(ImVec2(0, InrWindow->GetHeight()*0.667 + 18));
		ImGui::SetWindowSize(ImVec2(InrWindow->GetWidth(), InrWindow->GetHeight()*0.333 - 18));

		ImGui::Text("Asset TAB");

		ImGui::End();
	}
}

bool InitGlad()
{
	uint32 version = gladLoadGL((GLADloadfunc)glfwGetProcAddress);

	if ( version == 0)
		return false;

	rGlobalLog.WriteAndDisplay("Loaded OpengGL Context Version: "  + to_string(GLAD_VERSION_MAJOR(version)) + "."+ to_string(GLAD_VERSION_MINOR(version)));
	rGlobalLog.WriteAndDisplay("Driver OpenGL version: " + string((const char*)glGetString(GL_VERSION)));

	return true;
}

bool InitGUI(Window* InrWindow)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	if(!ImGui_ImplGlfw_InitForOpenGL(InrWindow->GetWindow(), true))
	{
		rGlobalLog.WriteAndDisplay("ImGui failed to bind to Opengl", ELogSeverity::ELS_Critical);
		return false;
	}

	if(!ImGui_ImplOpenGL3_Init("#version 450"))
	{
		rGlobalLog.WriteAndDisplay("ImGui failed to detect requested opengl version", ELogSeverity::ELS_Critical);
		//return false;
	}

	rGlobalLog.WriteAndDisplay("ImGui Version: " + string(IMGUI_VERSION));

	ImGuiStyle& rStyle = ImGui::GetStyle();

	rStyle.WindowPadding = ImVec2(0,0);
	rStyle.DisplayWindowPadding = ImVec2(0,0);
	rStyle.WindowBorderSize = 1.f;

	rStyle.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f,0.1f,0.1f,1.f);
	rStyle.Colors[ImGuiCol_ChildBg] = ImVec4(0.1f,0.1f,0.1f,1.f);
	rStyle.Colors[ImGuiCol_Button] = ImVec4(0.3f,0.15f,0.f,1.f);
	rStyle.Colors[ImGuiCol_FrameBg] = ImVec4(0.15f,0.15f,0.15f,1.f);
	rStyle.Colors[ImGuiCol_Tab] = ImVec4(0.6f,0.3f,0.f,1.f);
	rStyle.Colors[ImGuiCol_TabHovered] = ImVec4(0.8f,0.4f,0.f,1.f);
	rStyle.Colors[ImGuiCol_TabActive] = ImVec4(0.8f,0.4f,0.f,1.f);

	return true;
}

void DestroyGUIContext()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void SetupRenderer(Renderer* InrRenderer)
{
	InrRenderer->EnableMode(EGLEnable::EGLE_DepthTest, true);
	InrRenderer->EnableMode(EGLEnable::EGLE_StencilTest, true);
	InrRenderer->EnableMode(EGLEnable::EGLE_CullFace, true);
	InrRenderer->EnableMode(EGLEnable::EGLE_ProgramPointSize, true);

	glPointSize(10);

	InrRenderer->SetCullFace(EGLCullFace::EGLCF_Back);

	InrRenderer->EnableDepthMask(true);
	InrRenderer->SetDepthFunc(EGLFunc::EGLDF_Less);

	InrRenderer->SetStencilMask(0xFF);
	InrRenderer->SetStencilFunc(EGLFunc::EGLDF_GEqual, 1, 0xFF);

	InrRenderer->SetStencilOp(EGLStencilOp::EGLSO_Keep);

	InrRenderer->SetPolygonMode(EGLCullFace::EGLCF_FrontAndBack, EGLPolygonMode::EGLP_Fill);

	InrRenderer->SetClearColor(.2f * 0.3f, .4f * 0.3f, .3f * 0.3f, 1.f);

	InrRenderer->SetClearBuffer(EGLClearBuffer::EGLC_ColorBufferBit | EGLClearBuffer::EGLC_DepthBufferBit | EGLClearBuffer::EGLC_StencilBufferBit);

}

void OnMouseScroll()
{
	SMouseScrollInputFrame rMouseScrollInput = InputManager::GetInstance()->GetMouseScrollInputFrame();

	ImGui_ImplGlfw_ScrollCallback(InputManager::GetCurrentWindow(), rMouseScrollInput.dScrollX, rMouseScrollInput.dScrollY);

	rMainCamera.SetFOV(rMainCamera.GetFOV() - static_cast<float>(rMouseScrollInput.dScrollY));

	if (rMainCamera.GetFOV() < 1.0f)
		rMainCamera.SetFOV(1.0f);
	else if (rMainCamera.GetFOV() > 45.0f)
		rMainCamera.SetFOV(45.0f);
}

void OnMouseMove()
{
	SMouseMotionInputFrame rMouseMotion = InputManager::GetInstance()->GetMouseMotionInputFrame();

	ImGui_ImplGlfw_CursorPosCallback(InputManager::GetCurrentWindow(), rMouseMotion.dXPos, rMouseMotion.dYPos);

	const float XPos = static_cast<float>(rMouseMotion.dXPos);
	const float YPos = static_cast<float>(rMouseMotion.dYPos);

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

	rMainCamera.AddYaw(XOffset);
	rMainCamera.AddPitch(YOffset);
}

void MoveCameraForwards()
{
	rMainCamera.TravelForwards(1.0f * DeltaTime);
}

void MoveCameraBackwards()
{
	rMainCamera.TravelForwards(-1.0f * DeltaTime);
}

void MoveCameraLeftwards()
{
	rMainCamera.TravelSideways(-1.0f * DeltaTime);
}

void MoveCameraRightwards()
{
	rMainCamera.TravelSideways(1.0f * DeltaTime);
}

void ExecuteInputManager(int Stop)
{
	while(Stop)
	{
		InputManager::GetInstance()->ProcessInput();
	}
}

int main(int argc, char **argv)
{
	try 
	{
		App* rKronosApp = new App(argc, argv);

		if (rKronosApp->IsInitSuccess())
		{
			rMainCamera.SetMinRotation(vec3(-360.0f, -89.0f, -360.0f));
			rMainCamera.SetMaxRotation(vec3(360.0f, 89.0f, 360.0f));

			Window* rMainWindow = new Window(1024, static_cast<int32>(1024.f * (9.0f / 16.0f)), "Kronos Engine");

			if(!InitGlad())
			{
				rGlobalLog.WriteAndDisplay("Failed to init glad...clossing application");
				rKronosApp->Destroy();
				return -2;
			}

			glViewport(rMainWindow->GetWidth()*0.166, rMainWindow->GetHeight()*0.333 - 18, rMainWindow->GetWidth() - rMainWindow->GetWidth()*0.333, rMainWindow->GetHeight()*0.667);
			

			if(!InitGUI(rMainWindow))
			{
				rGlobalLog.WriteAndDisplay("Failed to init ImGui. Closing");
				rKronosApp->Destroy();
				return -3;
			}

			rGlobalLog.WriteAndDisplay("GLFW version: " + to_string(GLFW_VERSION_MAJOR) + "." + to_string(GLFW_VERSION_MINOR) + "." + to_string(GLFW_VERSION_REVISION));
			rGlobalLog.WriteAndDisplay("Assimp version: " + to_string(aiGetVersionMajor()) + "." + to_string(aiGetVersionMinor()) + "." + to_string(aiGetVersionRevision()));
			rGlobalLog.WriteAndDisplay("GLM Version: " + to_string(GLM_VERSION));
			
			//glfwSetCursorPosCallback(rMainWindow->GetWindow(), MouseCallback);
			//glfwSetScrollCallback(rMainWindow->GetWindow(), ScrollCallback);
			
			GLint nrAttributes;
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
			
			rGlobalLog.WriteAndDisplay("Maximum nr if vertex attributes supported: " + to_string(nrAttributes));

			Texture* FrameBufferTexture = new Texture(
				rMainWindow->GetWidth(),
				rMainWindow->GetHeight(),
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


			SetupRenderer(rRenderer);

			glfwSwapInterval(1);

			rMainCamera.SetYaw(-89.0f);

			Model NewModel2(SShapePrimCube(0.2f,0.2f).GetModel());

			NewModel2.Translate(vec3(1.f, 0.f, 0.f));
			
			mat4 View = rMainCamera.GetView();
			mat4 Projection = rMainCamera.GetProjection();
			vec3 CameraPosition = -rMainCamera.GetLocation();

			glReleaseShaderCompiler();

			GizmoTransform Gizmo = GizmoTransform();

			Gizmo.ConstructGizmo();

			InputManager::GetInstance()->SetCurrentWindow(rMainWindow->GetWindow());

			InputManager::GetInstance()->BindInput("MoveForwards", EInputKey::EIK_W, EInputState::EIS_Hold, &MoveCameraForwards);
			InputManager::GetInstance()->BindInput("MoveBackwords", EInputKey::EIK_S, EInputState::EIS_Hold, &MoveCameraBackwards);
			InputManager::GetInstance()->BindInput("MoveLeftwards", EInputKey::EIK_A, EInputState::EIS_Hold, &MoveCameraLeftwards);
			InputManager::GetInstance()->BindInput("MoveRightwords", EInputKey::EIK_D, EInputState::EIS_Hold, &MoveCameraRightwards);
			InputManager::GetInstance()->BindInput("MouseMovement", EDeviceType::EDT_Mouse, &OnMouseMove);
			InputManager::GetInstance()->BindInput("MouseScroll",EDeviceType::EDT_Mouse, &OnMouseScroll);

			//Main loop
			while (!glfwWindowShouldClose(rMainWindow->GetWindow()))
			{
				WindowRenderLoop();

				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				GUIMainMenu(rMainWindow);
				GUICreatorTab(rMainWindow);
				GUIOutlineTab(rMainWindow);
				GUIAssetTab(rMainWindow);

				View = rMainCamera.GetView();
				Projection = rMainCamera.GetProjection();

				CameraPosition = -rMainCamera.GetLocation();
				
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

				rShaderCubeLight.SetMat4("Model", Gizmo.GetTransformMatrix());

				Gizmo.Draw(rShaderCubeLight);

				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
				
				glfwSwapBuffers(rMainWindow->GetWindow());
				rRenderer->Clear();
				InputManager::GetInstance()->ProcessInput();
				glfwPollEvents();
			}

			DestroyGUIContext();

			delete rFramebuffer;
			delete rRenderer;
			delete rMainWindow;
			delete rKronosApp;
		}
		else
			return -1;
	} catch (exception &e)
	{
		cerr << e.what() << "\n";
	}

	return 0;
}
