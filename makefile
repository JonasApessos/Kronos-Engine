#CFLAGS = -std=c++17 -O0 -og -time -Wextra --debug
CFLAGS = -std=c++17 -O0 -og -Wextra --debug
#CFLAGS = -std=c++17 -O2 -Wextra

LDFLAGS = -lassimp -lglfw -lGLEW -lGLESv2 -lGLU -lGL -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
#LDFLAGS = -lassimp -lglfw3 -lglew32 -lglu32 -lopengl32

HFLAGS = -I Header -I Dep/stb
#HFLAGS = -I Header -I Dep/glew-2.2.0/include -I Dep/Assimp-5.2.5/include -I Dep/stb

SOURCE = Source/Standard.cpp Source/Window.cpp Source/App.cpp Source/Shader.cpp Source/Camera.cpp Source/Renderer.cpp Source/Texture.cpp Source/Vector.cpp Source/Mesh.cpp Source/Model.cpp Source/Log.cpp Source/InputManager.cpp Source/InputHandler.cpp Source/Framebuffer.cpp

KronosEngine: KronosEngine
	build

.PHONY: build run clean

build: Source/KronosEngine.cpp
	g++ $(CFLAGS) $(HFLAGS) -o KronosEngine Source/KronosEngine.cpp $(SOURCE) $(LDFLAGS)

run: KronosEngine
	clear
	./KronosEngine

clean:
	rm -f KronosEngine
