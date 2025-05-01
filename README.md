# Kronos-Engine

# Installation
In Linux distributions you can open your terminal and execute the commands below.(every distrubution may need some change for the package manager and permission)

you will need the gcc compilation suite, using Linux distro you can use:
Debian:<br>
  <code>sudo apt install build-essential</code>
  
this will download the basic suit in order to build the project

Also install:<br>
  <code>sudo apt install scons</code>

if you are using Linux distrubution you can install the following packages with the command below:
Debian:<br>
  <code>sudo apt install libglfw3-dev libglfw3 libassimp-dev libstb-dev libstb0 libglm-dev</code>
  
your also going to need the mold linker:<br>
  <code>sudo apt install mold</code>

<h2>imgui</h2>
you will need to download imgui from the github source yourself and add it in the dependency folder, rename the folder to imgui or the build system won't be able to find the dependency

will use git submodule in the future to automatically download the dependencies

The same libraries can be found in windows using MSYS. Using visual studio is not supported by default, although the setup is not difficult.

# Compilation
In order to compile, you will need SCons in order to build from the SConstruct

For compilation you will need certain libraries in order to work:
1) <a href=https://www.glfw.org/>GLFW</a>
2) <a href=https://github.com/assimp/assimp>Assimp</a>
3) <a href=https://github.com/nothings/stb>stb</a>
4) <a href=https://github.com/g-truc/glm>GLM</a>
5) <a href=https://github.com/ocornut/imgui>imgui</a>

Working on some futures in order to reduce needed libraries to link.

In order to build the project after installing all the necessary libraries, you must run the following command:<br>
  <code>scons</code>

If you need to build in debug:<br>
<code>scons --build=debug</code>

if you need to use multithread build then add the following argument:
<code>scons -j4</code>

change the number to the number the jobs you need to build faster

<code>make Build DEBUG=0</code> or <code>make Build -j DEBUG=0</code> for release build

After build you will find the executable in the buildgcc directory:<br>

# Optional
You can generate documentation for the project using doxygen:<br>
Debian:<br>
  <code>sudo apt install doxygen</code><br>
  to execute:<br>
  <code>doxygen doxygen-config</code><br>

you can find the generated html in: DOCS/html/index.html of the project directory.