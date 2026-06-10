#pragma once
#include "MacroUtils.h"

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <exception>
#include <thread>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.inl"

#include "assimp/version.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Standard.h"

#include "Timer.h"
#include "App.h"
#include "Canvas.h"
#include "Camera.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Framebuffer.h"
#include "Gizmo.h"
#include "Model.h"

using glm::vec3, glm::vec2 , glm::mat4;

using std::cout, std::exception;
