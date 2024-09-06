project('KronosEngine', ['cpp', 'c'],
  version : '0.1',
  meson_version: '>= 0.62.0',
  default_options : ['warning_level=Wall','c_std=c18','cpp_std=c++20'])

glewdep = dependency('GLEW', method : 'pkg-config')

opengldep = dependency('GL', method : 'auto')

dldep = dependency('dl', method : 'auto')

x11dep = dependency('X11', method : 'auto')

waylanddep = dependency('wayland-client', method : 'auto')

threaddep = dependency('threads', method : 'system')

glfwdep = dependency('glfw3', method : 'pkg-config')

assimpdep = dependency('assimp', method : 'auto')

imguidep = dependency('imgui', method : 'pkg-config')

headers = include_directories('Header')

sources = files('Source/App.cpp',
'Source/Camera.cpp',
'Source/FileHandler.cpp',
'Source/GeomGenerator.cpp',
'Source/Framebuffer.cpp',
'Source/Export.cpp',
'Source/Gizmo.cpp',
'Source/Import.cpp',
'Source/InputHandler.cpp',
'Source/InputManager.cpp',
'Source/Log.cpp',
'Source/Mesh.cpp',
'Source/Model.cpp',
'Source/Object.cpp',
'Source/Renderer.cpp',
'Source/Shader.cpp',
'Source/Standard.cpp',
'Source/Texture.cpp',
'Source/Vector.cpp',
'Source/Window.cpp',
'Source/KronosEngine.cpp')


dep = [
opengldep,
dldep,
glewdep,
x11dep,
waylanddep,
threaddep,
glfwdep,
assimpdep,
imguidep
]

exe = executable('KronosEngine',
[sources],
dependencies : dep,
cpp_args : ['-O0','-g3','-ggdb','-Wextra','--debug'],
link_args : ['-pthread'],
include_directories : [headers],
install : true)

test('basic', exe)
