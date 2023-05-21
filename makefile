CFLAGS = -std=c++17 -O0 -og -Wextra --debug

LINUXLDFLAGS = -lassimp -lglfw -lGLEW -lGLESv2 -lGLU -lGL -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
WINLDFLAGS = -lassimp -lglfw3 -lglew32 -lglu32 -lopengl32

HFLAGS = -I Header

SOURCE = Source/Standard.cpp Source/Window.cpp Source/App.cpp Source/Shader.cpp Source/Camera.cpp Source/Renderer.cpp Source/Texture.cpp Source/Vector.cpp Source/Mesh.cpp Source/Model.cpp Source/Log.cpp Source/InputManager.cpp Source/InputHandler.cpp Source/Framebuffer.cpp

KronosEngine: KronosEngine

.PHONY: win-build linux-build clean

win-build: Source/KronosEngine.cpp
	g++ $(CFLAGS) $(HFLAGS) -o KronosEngine Source/KronosEngine.cpp $(SOURCE) $(WINLDFLAGS)

linux-build:
	g++ $(CFLAGS) $(HFLAGS) -o KronosEngine Source/KronosEngine.cpp $(SOURCE) $(LINUXLDFLAGS)

run: KronosEngine
	clear
	./KronosEngine

clean:
	rm -f KronosEngine
