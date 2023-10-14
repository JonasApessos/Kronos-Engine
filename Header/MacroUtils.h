#define K_MAJOR_VERSION 0
#define K_MINOR_VERSION 17
#define K_PATCH 1

#define K_DEBUG

#ifndef K_DEBUG
#ifndef K_REL
#define K_REL 1
#endif
#endif

#ifdef K_REL
#ifndef NDEBUG
#define NDEBUG
#endif
#endif

#ifndef K_GRAPHICS_OPENGL
#define K_GRAPHICS_OPENGL 1
#endif

#ifndef K_GRAPHICS_OPENGLES
#define K_GRAPHICS_OPENGLES 0
#endif

#ifndef K_GRAPHICS_VULKAN
#define K_GRAPHICS_VULKAN 0
#endif

#ifndef K_GRAPHICS_DIRECTX
#define K_GRAPHICS_DIRECTX 0
#endif

#ifdef _WIN32
	#define ERRORCODE errno_t
#elif defined __linux__
	#define ERRORCODE error_t
#endif