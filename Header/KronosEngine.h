#pragma once
#include "MacroUtils.h"

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <exception>
#include <iomanip>
#include <threads.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>

#include "assimp/version.h"

#include "Standard.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "App.h"
#include "Canvas.h"
#include "Camera.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Framebuffer.h"
#include "Gizmo.h"
#include "Model.h"