# Kronos-Engine

# Installation
In Linux distributions you can open your terminal and execute the commands below.(every distrubution may need some change for the package manager and permission)

you will need the gcc compilation suite, using Linux distro you can use:
Debian:<br>
  <code>sudo apt install build-essential</code>
  
this will download the basic suit in order to build the project

Also install:<br>
  <code>sudo apt install make</code>

if you are using Linux distrubution you can install the following packages with the command below:
Debian:<br>
  <code>sudo apt install libglfw3-dev libglfw3 libassimp-dev libstb-dev libstb0 libglm-dev libglew-dev libglew2.2</code>
  
your also going to need the mold linker:<br>
  <code>sudo apt install mold</code>

The same librarys can be found in windows using MSYS. Using visual studio is not supported by default, althought the setup is not difficult.

# Compilation
In order to compile, you will need Make in order to build from the makefile

For compilation you will need certain librarys in order to work:
1) <a href=https://www.glfw.org/>GLFW</a>
2) <a href=https://github.com/assimp/assimp>Assimp</a>
3) <a href=https://github.com/nothings/stb>stb</a>
4) <a href=https://github.com/g-truc/glm>GLM</a>
5) <a href=https://glew.sourceforge.net/>GLEW</a>

Working on some futures in order to reduce needed librarys to link.

First run the setup using<br>
<code>make Setup</code>

You will also need to run the setup for DEBUG=0 with the following command<br>
<code>make Setup DEBUG=0</code>

In order to build the project after installing all the necessary librarys, you run the following command:<br>
  <code>make</code>

If you only need to build the project you can run:<br>
<code>make Build</code> or <code>make Build -j</code> for multicompilation.<br>

<code>make Build DEBUG=0</code> or <code>make Build -j DEBUG=0</code> for release build

if you only need to run the executable then type:<br>
<code>make Run</code> or <code>make Run DEBUG=0</code> to run either debug or release build

you can use clang compiler if you have it installed in your system<br>
<code>make Build USE_CLANG=1</code>

# Optional
You can generate documentation for the project using doxygen:<br>
Debian:<br>
  <code>sudo apt install doxygen</code><br>
  to execute:<br>
  <code>doxygen doxygen-config</code><br>

you can find the generated html in: DOCS/html/index.html of the project directory.
