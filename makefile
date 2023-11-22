DEBUG = 1

USE_CLANG = 0

LINUX_LIB = -lassimp -lglfw -lGLEW -lGLESv2 -lGLU -lGL -ldl -lpthread -lX11
WIN_LIB = -lassimp -lglfw3 -lglew32 -lglu32 -lopengl32

HFLAGS = -IHeader -IDep

SOURCE = Source

DEP = Dep

IMGUI_PATH = ""

PROGRAM = KronosEngine

ifeq ($(USE_CLANG), 1)
	CXX = clang++
endif

ifeq ($(DEBUG), 1)
	BUILD_PATH = build-debug
	CXXFLAGS = -std=c++17 -O0 -og -g3 -ggdb -Wextra --debug
	LDFLAGS = -fuse-ld=mold -pthread
else
	BUILD_PATH = build-rel
	CXXFLAGS = -std=c++17 -O2 -Wextra -Wall -pedantic -Wshadow -Wconversion -Wunreachable-code
	LDFLAGS = -fuse-ld=mold -pthread -s
endif

IMGUI_OBJ=$(BUILD_PATH)/imgui.o $\
$(BUILD_PATH)/imgui_draw.o $\
$(BUILD_PATH)/imgui_tables.o $\
$(BUILD_PATH)/imgui_widgets.o $\
$(BUILD_PATH)/imgui_impl_glfw.o $\
$(BUILD_PATH)/imgui_impl_opengl3.o

OBJ=$(BUILD_PATH)/Standard.o $\
$(BUILD_PATH)/Object.o $\
$(BUILD_PATH)/Vector.o $\
$(BUILD_PATH)/Texture.o $\
$(BUILD_PATH)/FileHandler.o $\
$(BUILD_PATH)/Shader.o $\
$(BUILD_PATH)/InputHandler.o $\
$(BUILD_PATH)/Framebuffer.o $\
$(BUILD_PATH)/App.o $\
$(BUILD_PATH)/Window.o $\
$(BUILD_PATH)/Mesh.o $\
$(BUILD_PATH)/Model.o $\
$(BUILD_PATH)/Gizmo.o $\
$(BUILD_PATH)/Log.o $\
$(BUILD_PATH)/Renderer.o $\
$(BUILD_PATH)/Camera.o $\
$(BUILD_PATH)/InputManager.o $\
$(BUILD_PATH)/Export.o $\
$(BUILD_PATH)/Import.o $\
$(BUILD_PATH)/GeomGenerator.o

All:
	-make Build -j
	-make Link
	-make Run

Rebuild:
	-make Build -j
	-make Link

Clean:
	-rm -r $(BUILD_PATH)

Setup:
	-git submodule update --init --recursive
	-mkdir $(BUILD_PATH)
	-rm $(BUILD_PATH)/Timings
	-touch $(BUILD_PATH)/Timings

Rebuild-All:Clean Setup Rebuild

Run:
	./$(BUILD_PATH)/KronosEngine

Build:ImGui-Build $(OBJ)

ImGui-Build: imgui.o imgui_draw.o imgui_tables.o imgui_widgets.o imgui_impl_glfw.o imgui_impl_opengl3.o

Link:
	$(CXX) $(SOURCE)/$(PROGRAM).cpp $(OBJ) $(IMGUI_OBJ) $(CXXFLAGS) $(HFLAGS) $(LDFLAGS) $(LINUX_LIB) -o $(BUILD_PATH)/$(PROGRAM)

$(OBJ): %.o: %.cpp

%.o: %.cpp

%.cpp:
	$(CXX) -c $(CXXFLAGS) $(HFLAGS) $(patsubst $(BUILD_PATH)/%,$(SOURCE)/%, $@) -o $(patsubst %.cpp,%.o, $@)

imgui.o:
	$(CXX) -c $(CXXFLAGS) $(HFLAGS) $(DEP)/imgui.cpp -o $(BUILD_PATH)/imgui.o

imgui_draw.o:
	$(CXX) -c $(CXXFLAGS) $(HFLAGS) $(DEP)/imgui_draw.cpp -o $(BUILD_PATH)/imgui_draw.o

imgui_tables.o:
	$(CXX) -c $(CXXFLAGS) $(HFLAGS) $(DEP)/imgui_tables.cpp -o $(BUILD_PATH)/imgui_tables.o

imgui_widgets.o:
	$(CXX) -c $(CXXFLAGS) $(HFLAGS) $(DEP)/imgui_widgets.cpp -o $(BUILD_PATH)/imgui_widgets.o

imgui_impl_glfw.o:
	$(CXX) -c $(CXXFLAGS) $(HFLAGS) $(DEP)/backends/imgui_impl_glfw.cpp -o $(BUILD_PATH)/imgui_impl_glfw.o

imgui_impl_opengl3.o:
	$(CXX) -c $(CXXFLAGS) $(HFLAGS) $(DEP)/backends/imgui_impl_opengl3.cpp -o $(BUILD_PATH)/imgui_impl_opengl3.o

.PHONY: Rebuild-All Clean Setup All Run Link Build Rebuild ImGui-Build
