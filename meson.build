project('KronosEngine', ['cpp', 'c'],
  version : '0.2',
  meson_version: '>= 0.62.0',
  license: 'MIT')

glewdep = dependency('GLEW', method : 'auto')

opengldep = dependency('GL', method : 'auto')

dldep = dependency('dl', method : 'auto')

x11dep = dependency('X11', method : 'auto')

waylanddep = dependency('wayland-client', method : 'auto', required : false)

threaddep = dependency('threads', method : 'auto')

glmdep = dependency('glm', method : 'auto')

glfwdep = dependency('glfw3', method : 'auto')

assimpdep = dependency('assimp', method : 'auto')

imguidep = dependency('imgui', method : 'auto')

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
glmdep,
glfwdep,
assimpdep,
imguidep
]

exe = executable('KronosEngine',
[sources],
dependencies : dep,
include_directories : [headers],
install : true)

test('basic', exe)
