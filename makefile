DEBUG = 1

USE_CLANG = 0

LINUXLDFLAGS = -lassimp -lglfw -lGLEW -lGLESv2 -lGLU -lGL -ldl -lpthread -lX11
WINLDFLAGS = -lassimp -lglfw3 -lglew32 -lglu32 -lopengl32

HFLAGS = -I Header

SOURCE = Source

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

.PHONY: Rebuild-All Clean Setup All Run Link Build


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

All: Setup Build Run

Clean:
	-rm -r $(BUILD_PATH)

Setup:
	-mkdir $(BUILD_PATH)
	-rm $(BUILD_PATH)/Timings
	-touch $(BUILD_PATH)/Timings

Build:$(OBJ) Link

Rebuild-All:Clean Setup Build

Run:
	./$(BUILD_PATH)/KronosEngine

Link:
	$(CXX) $(SOURCE)/$(PROGRAM).cpp $(OBJ) $(CXXFLAGS) $(HFLAGS) $(LDFLAGS) $(LINUXLDFLAGS) -o $(BUILD_PATH)/$(PROGRAM)

$(OBJ): %.o: %.cpp

%.o: %.cpp

%.cpp:
	$(CXX) -c $(CXXFLAGS) $(HFLAGS) $(patsubst $(BUILD_PATH)/%,$(SOURCE)/%, $@) -o $(patsubst %.cpp,%.o, $@)