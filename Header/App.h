#pragma once

#include <string>

#include "Log.h"
#include "Window.h"

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

	inline bool IsInitSuccess() const; /*!< @return bool @brief true on succesful init*/
protected:
	string sAppTitle = ""; /*!< App Title*/

	Log rLog; /*!< Logging manager*/

private:
	bool bIsGLFWInit = false;
	bool bIsInitSuccess = false;

	void InitGLFW();
};

inline bool App::IsInitSuccess() const { return bIsInitSuccess; }