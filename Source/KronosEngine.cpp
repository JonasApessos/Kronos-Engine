#include "KronosEngine.h"

using glm::vec3, glm::vec2 , glm::mat4;

using std::cout, std::exception;

constexpr int32 CanvasWidth = 1024;
constexpr int32 CanvasHeight = static_cast<int32>(static_cast<float>(CanvasWidth) * 9.f / 16.f);

float MouseLastX = CanvasWidth * 0.5f, MouseLastY = CanvasHeight * 0.5f;

Camera rMainCamera(vec3(0.f, 0.f, 10.f), vec3(0.f, 0.f, 1.f), vec3(0.f, 1.f, 0.f), 45.f, (16.f / 9.f), 10.f, 0.1f, 100.f);

float DeltaTime = 0.f, LastFrame = 0.f;

Log rGlobalLog("Log");

static int Index = 0;

const char* ctest[] = {"test1", "test2", "Test3", "Test4", "Test5", "Test6", "Test7", "Test8", "Test9"};

bool FirstMouse = true;


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

GLvoid CanvasRenderLoop()
{
	const float CurrentFrame = static_cast<float>(glfwGetTime());

	DeltaTime = CurrentFrame - LastFrame;
	LastFrame = CurrentFrame;

	rMainCamera.Update();
}

void GUIMainMenu(Canvas* InrCanvas)
{
	bool IsMainCanvasVisible = true;

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
			ImGui::MenuItem("Preferences");
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

void GUICreatorTab(Canvas* InrCanvas)
{
	bool IsMainCanvasVisible = true;

	//Creator Tab
	if(ImGui::Begin("Creator Tab",
	&IsMainCanvasVisible,
	ImGuiWindowFlags_NoCollapse |
	ImGuiWindowFlags_NoResize |
	ImGuiWindowFlags_NoDecoration |
	ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoBringToFrontOnFocus))
	{
		
		ImGui::SetWindowPos(
			ImVec2(
				0.f,
				0.f));

		ImGui::SetWindowSize(
			ImVec2(
				static_cast<float>(InrCanvas->GetWidth()) * 0.166f,
				static_cast<float>(InrCanvas->GetHeight()) * 0.667f));

		ImGui::Text("Creator TAB");

		ImGui::End();
	}
}

void GUIOutlineTab(Canvas* InrCanvas)
{

	bool IsMainCanvasVisible = true;

	//Outliner Tab
	if(ImGui::Begin("Outliner",
	&IsMainCanvasVisible,
	ImGuiWindowFlags_NoCollapse |
	ImGuiWindowFlags_NoResize |
	ImGuiWindowFlags_NoDecoration |
	ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoBringToFrontOnFocus))
	{
		ImGui::SetWindowPos(
			ImVec2(
				static_cast<float>(InrCanvas->GetWidth()) - static_cast<float>(InrCanvas->GetWidth()) * 0.166f,
				0.f));

		ImGui::SetWindowSize(
			ImVec2(
			static_cast<float>(InrCanvas->GetWidth()) * 0.166f,
			static_cast<float>(InrCanvas->GetHeight()) * 0.667f));

		if(ImGui::BeginTabBar("OutlineTab"))
		{
			if(ImGui::TabItemButton("Outline")){}
			if(ImGui::TabItemButton("Propertys")){}

			ImGui::EndTabBar();
		}


		if(ImGui::BeginListBox(
			"OutlineList",
			ImVec2(
				static_cast<float>(InrCanvas->GetWidth()) * 0.166f,
				static_cast<float>(InrCanvas->GetHeight()) * 0.667f)))
		{

			bool is_selected = false;

			for (int n = 0; n < IM_ARRAYSIZE(ctest); n++)
			{
				is_selected = (Index == n);
				
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

void GUIAssetTab(Canvas* InrCanvas)
{

	bool IsMainCanvasVisible = true;

	//Asset Browser Tab
	if(ImGui::Begin("Asset Browser Tab", 
	&IsMainCanvasVisible,
	ImGuiWindowFlags_NoCollapse | 
	ImGuiWindowFlags_NoResize |
	ImGuiWindowFlags_NoDecoration |
	ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoBringToFrontOnFocus))
	{
		ImGui::SetWindowPos(
			ImVec2(
				0.f,
				static_cast<float>(InrCanvas->GetHeight()) * 0.667f));

		ImGui::SetWindowSize(
			ImVec2(
			static_cast<float>(InrCanvas->GetWidth()),
			static_cast<float>(InrCanvas->GetHeight()) * 0.333f));

		ImGui::Text("Asset TAB");

		ImGui::End();
	}
}

bool GUISetupStyle(Canvas* InrCanvas)
{
	ImGuiStyle& rStyle = ImGui::GetStyle();

	rStyle.WindowPadding = ImVec2(0.f,0.f);
	rStyle.DisplayWindowPadding = ImVec2(0.f,0.f);
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

	rMainCamera.SetFOV(rMainCamera.GetFOV() - static_cast<float>(rMouseScrollInput.dScrollY) * DeltaTime);

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

		Canvas* rMainCanvas = new Canvas(CanvasWidth, CanvasHeight, "Kronos Engine");

		if (rKronosApp->Init(rMainCanvas))
		{
			rGlobalLog.WriteAndDisplay("OpenGL Driver version: " + rKronosApp->GetOpenglVersion());
			rGlobalLog.WriteAndDisplay("OpenGL Loaded version: " + rKronosApp->GetGladVersion());
			rGlobalLog.WriteAndDisplay("GLFW version: " + rKronosApp->GetGLFWVersion());
			rGlobalLog.WriteAndDisplay("Imgui version: " + rKronosApp->GetImguiVersion());
			rGlobalLog.WriteAndDisplay("Assimp version: " + rKronosApp->GetAssimpVersion());
			rGlobalLog.WriteAndDisplay("GLM Version: " + rKronosApp->GetGLMVersion());

			rMainCamera.SetMinRotation(vec3(-360.0f, -89.0f, -360.0f));
			rMainCamera.SetMaxRotation(vec3(360.0f, 89.0f, 360.0f));

			GUISetupStyle(rMainCanvas);

			int x, y, z, w;

			float scalex, scaley;

			glfwGetWindowSize(rMainCanvas->GetWindow(), &x, &y);
			glfwGetFramebufferSize(rMainCanvas->GetWindow(), &z, &w);
			glfwGetWindowContentScale(rMainCanvas->GetWindow(), &scalex, &scaley);

			glViewport(
				static_cast<GLint>(rMainCanvas->GetWidth() * 0.166f * scalex),
				static_cast<GLint>(rMainCanvas->GetHeight() * 0.333f * scaley),
				static_cast<GLsizei>(rMainCanvas->GetWidth() * scalex - rMainCanvas->GetWidth() * scalex * 0.333f),
				static_cast<GLsizei>(rMainCanvas->GetHeight() * scaley * 0.667f));
			
			//glfwSetCursorPosCallback(rMainCanvas->GetCanvas(), MouseCallback);
			//glfwSetScrollCallback(rMainCanvas->GetCanvas(), ScrollCallback);
			
			GLint nrAttributes;
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
			
			rGlobalLog.WriteAndDisplay("Maximum nr if vertex attributes supported: " + to_string(nrAttributes));

			Texture* FrameBufferTexture = new Texture(
				rMainCanvas->GetWidth(),
				rMainCanvas->GetHeight(),
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

			Renderer* rViewportRenderer = new Renderer();

			Shader rShaderLight("Resource/Shader/Light.vs", "Resource/Shader/Light.fs");
			Shader rShaderCubeLight("Resource/Shader/LightColorCube.vs", "Resource/Shader/LightColorCube.fs");
			Shader rShaderStencil("Resource/Shader/Stencil.vs", "Resource/Shader/Stencil.fs");


			SetupRenderer(rViewportRenderer);

			glfwSwapInterval(1);

			rMainCamera.SetYaw(-89.0f);
			
			mat4 View = rMainCamera.GetView();
			mat4 Projection = rMainCamera.GetProjection();
			vec3 CameraPosition = -rMainCamera.GetLocation();

			glReleaseShaderCompiler();

			GizmoTransform Gizmo = GizmoTransform();

			Gizmo.ConstructGizmo();

			InputManager::GetInstance()->SetCurrentWindow(rMainCanvas->GetWindow());

			InputManager::GetInstance()->BindInput("MoveForwards", EInputKey::EIK_W, EInputState::EIS_Hold, &MoveCameraForwards);
			InputManager::GetInstance()->BindInput("MoveBackwords", EInputKey::EIK_S, EInputState::EIS_Hold, &MoveCameraBackwards);
			InputManager::GetInstance()->BindInput("MoveLeftwards", EInputKey::EIK_A, EInputState::EIS_Hold, &MoveCameraLeftwards);
			InputManager::GetInstance()->BindInput("MoveRightwords", EInputKey::EIK_D, EInputState::EIS_Hold, &MoveCameraRightwards);
			InputManager::GetInstance()->BindInput("MouseMovement", EDeviceType::EDT_Mouse, &OnMouseMove);
			InputManager::GetInstance()->BindInput("MouseScroll",EDeviceType::EDT_Mouse, &OnMouseScroll);

			//Main loop
			while (!glfwWindowShouldClose(rMainCanvas->GetWindow()))
			{
				CanvasRenderLoop();

				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				GUIMainMenu(rMainCanvas);
				GUICreatorTab(rMainCanvas);
				GUIOutlineTab(rMainCanvas);
				GUIAssetTab(rMainCanvas);

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
				rShaderCubeLight.SetMat4("Model", Gizmo.GetTransformMatrix());

				Gizmo.Draw(rShaderCubeLight);

				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
				
				glfwSwapBuffers(rMainCanvas->GetWindow());
				rViewportRenderer->Clear();
				InputManager::GetInstance()->ProcessInput();
				glfwPollEvents();
			}

			delete rFramebuffer;
			delete rViewportRenderer;
		}
		else
			return -1;
		
		delete rMainCanvas;
		delete rKronosApp;

	} catch (exception &e)
	{
		cerr << e.what() << "\n";
	}

	return 0;
}
