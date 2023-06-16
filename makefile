CFLAGSDEBUG = -std=c++17 -O0 -og -g3 -Wextra --debug
CFLAGSREL = -std=c++17 -O2 -Wextra -Wall -s -pedantic -Wshadow -Wconversion -Wunreachable-code

LINUXLDFLAGS = -lassimp -lglfw -lGLEW -lGLESv2 -lGLU -lGL -ldl -lpthread -lX11 -lXrandr
WINLDFLAGS = -lassimp -lglfw3 -lglew32 -lglu32 -lopengl32

HFLAGS = -I Header

SOURCE = Source/KronosEngine.cpp Source/Standard.cpp Source/Window.cpp Source/App.cpp Source/Shader.cpp Source/Camera.cpp Source/Renderer.cpp Source/Texture.cpp Source/Vector.cpp Source/Mesh.cpp Source/Model.cpp Source/Log.cpp Source/Import.cpp Source/Export.cpp Source/InputManager.cpp Source/InputHandler.cpp Source/Framebuffer.cpp

setup:
	mkdir build-rel
	mkdir build-debug

all-win-debug: win-debug run-debug

all-win-rel: win-rel run-rel

all-linux-debug: linux-debug run-debug

all-linux-rel: linux-rel run-rel

.PHONY: win-debug win-rel linux-debug linux-rel run-debug run-rel clean-debug clean-rel

win-rel:
	g++ $(CFLAGSREL) $(HFLAGS) -o build-rel/KronosEngine.exe $(SOURCE) $(WINLDFLAGS)

linux-rel:
	g++ $(CFLAGSREL) $(HFLAGS) -o build-rel/KronosEngine $(SOURCE) $(LINUXLDFLAGS)

win-debug:
	g++ $(CFLAGSDEBUG) $(HFLAGS) -o build-debug/KronosEngine.exe $(SOURCE) $(WINLDFLAGS)

linux-debug:
	g++ $(CFLAGSDEBUG) $(HFLAGS) -o build-debug/KronosEngine $(SOURCE) $(LINUXLDFLAGS)

run-debug:
	clear
	time ./build-debug/KronosEngine

run-rel:
	clear
	time ./build-rel/KronosEngine

clean-debug:
	rm -r build-debug

clean-rel:
	rm -r build-rel
