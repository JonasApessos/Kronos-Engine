#pragma once

#include "MacroUtils.h"

#define STB_IMAGE_IMPLEMENTATION

#include <assert.h>
#include <stdint.h>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <exception>
#include <iomanip>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Primitives.h"

#include "Log.h"

#include "Standard.h"

#include "App.h"

#include "InputManager.h"

#include "Window.h"

#include "Texture.h"

#include "Framebuffer.h"

#include "Shader.h"

#include "Camera.h"

#include "Renderer.h"

#include "Mesh.h"

#include "Model.h"

#include "Gizmo.h"

#include "ShapePrimitives.h"

#include "Import.h"

#include "Export.h"