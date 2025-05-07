#pragma once

#include <string>
#include <glm/glm.hpp>
#include <assimp/version.h>

#include "Log.h"
#include "Canvas.h"

using std::string;

/** @class App
* 	@brief class to manage the application
* 
*/
class App
{
public:
	App(int iniCommandIndex, char** IncCommandArguments); /*!< @brief default constructor*/

	~App(); /*!< @brief default destructor*/

	/*! @fn Destroy
		@brief Overridable function for destruction
		@deprecated will be moved
	*/
	void Destroy();

	bool Init(Canvas const* InrCanvas);

	inline bool IsInitSuccess() const; /*!< @return bool @brief true on succesful init*/

	inline string GetAppName() const;

	inline string GetGLFWVersion() const;
	inline string GetGladVersion() const;
	inline string GetOpenglVersion() const;
	inline string GetAssimpVersion() const;
	inline string GetGLMVersion() const;
	inline string GetImguiVersion() const;
protected:
	string sAppTitle = ""; /*!< App Title*/

	Log rLog; /*!< Logging manager*/

private:
	bool bIsGLFWInit = false;
	bool bIsGladInit = false;
	bool bIsImguiInit = false;
	bool bIsInitSuccess = false;

	uint32 iGladVersion = 0;

	bool InitGLFW();
	bool InitGlad();
	bool InitImgui(Canvas const *InrCanvas);

	void DestroyImguiContext();
};

inline bool App::IsInitSuccess() const { return bIsInitSuccess; }

inline string App::GetAppName() const { return sAppTitle; }
inline string App::GetGLFWVersion() const { return string(to_string(GLFW_VERSION_MAJOR) + "." + to_string(GLFW_VERSION_MINOR) + "." + to_string(GLFW_VERSION_REVISION)); }
inline string App::GetGladVersion() const { return string(to_string(GLAD_VERSION_MAJOR(iGladVersion)) + "." + to_string(GLAD_VERSION_MINOR(iGladVersion))); }
inline string App::GetOpenglVersion() const { return string(reinterpret_cast<const char*>(glGetString(GL_VERSION))); }
inline string App::GetAssimpVersion() const { return string(to_string(aiGetVersionMajor()) + "." + to_string(aiGetVersionMinor()) + "." + to_string(aiGetVersionPatch()) + "." + to_string(aiGetVersionRevision())); }
inline string App::GetGLMVersion() const { return to_string(GLM_VERSION); }
inline string App::GetImguiVersion() const { return string(IMGUI_VERSION); }