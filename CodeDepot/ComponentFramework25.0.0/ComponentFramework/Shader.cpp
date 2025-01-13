#include "Shader.h"
#include "Debug.h"
#include <fstream>
#include <string.h>

Shader::Shader(const char* vertFilename_, const char* fragFilename_,
	const char* tessCtrlFilename_, const char* tessEvalFilename_,
	const char* geomFilename_) :

	shaderID(0), vertShaderID(0), fragShaderID(0), tessCtrlShaderID(0),
	tessEvalShaderID(0), geomShaderID(0),
	vertFilename(vertFilename_),
	fragFilename(fragFilename_),
	tessCtrlFilename(tessCtrlFilename_),
	tessEvalFilename(tessEvalFilename_),
	geomFilename(geomFilename_) { }


Shader::~Shader() {}


bool Shader::OnCreate() {
	bool status;
	status = CompileAttach();
	if (status == false) return false;
	status = Link();
	if (status == false) return false;

	SetUniformLocations();
	return true;
}

void Shader::OnDestroy() {
	glDetachShader(shaderID, fragShaderID);
	glDetachShader(shaderID, vertShaderID);
	glDeleteShader(fragShaderID);
	glDeleteShader(vertShaderID);


	if (tessCtrlShaderID) {
		glDetachShader(shaderID, tessCtrlShaderID);
		glDeleteShader(tessCtrlShaderID);
	}
	if (tessEvalShaderID) {
		glDetachShader(shaderID, tessEvalShaderID);
		glDeleteShader(tessEvalShaderID);
	}

	if (geomShaderID) {
		glDetachShader(shaderID, geomShaderID);
		glDeleteShader(geomShaderID);
	}

	glDeleteProgram(shaderID);
}



bool Shader::CompileAttach() {
	GLint status;
	const char* vertText = nullptr;
	const char* fragText = nullptr;
	const char* tessCtrlText = nullptr;
	const char* tessEvalText = nullptr;
	const char* geomText = nullptr;

	try {
		vertText = ReadTextFile(vertFilename);
		fragText = ReadTextFile(fragFilename);
		if (vertText == nullptr || fragText == nullptr) {
			return false;
		}
		/// GL_VERTEX_SHADER and GL_FRAGMENT_SHADER are defined in glew.h
		vertShaderID = glCreateShader(GL_VERTEX_SHADER);
		fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		/// Check for errors
		if (vertShaderID == 0 || fragShaderID == 0) {
			std::string errorMsg("Can't create a new shader");
			throw errorMsg;
		}

		glShaderSource(vertShaderID, 1, &vertText, 0);
		glShaderSource(fragShaderID, 1, &fragText, 0);

		glCompileShader(vertShaderID);
		/// Check for errors
		glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &status);
		if (status == 0) {
			GLsizei errorLogSize = 0;
			GLsizei titleLength;
			std::string errorLog = vertFilename;
			errorLog += "\nVERT:\n";
			titleLength = errorLog.length();
			glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(titleLength + errorLogSize);
			glGetShaderInfoLog(vertShaderID, errorLogSize, &errorLogSize, &errorLog[titleLength]);
			throw errorLog;
		}

		glCompileShader(fragShaderID);
		/// Check for errors
		glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &status);
		if (status == 0) {
			GLsizei errorLogSize = 0;
			GLsizei titleLength;
			std::string errorLog = fragFilename;
			errorLog += "\nFrag:\n";
			titleLength = errorLog.length();
			glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(titleLength + errorLogSize);
			glGetShaderInfoLog(fragShaderID, errorLogSize, &errorLogSize, &errorLog[titleLength]);
			throw errorLog;
		}

		if (tessCtrlFilename != nullptr && tessEvalFilename != nullptr) {
			tessCtrlText = ReadTextFile(tessCtrlFilename);
			tessEvalText = ReadTextFile(tessEvalFilename);

			if (tessCtrlText == nullptr || tessEvalText == nullptr) {
				std::string errorLog = "Can't read either tessCtrlFile or tessEvalFile";
				throw errorLog;
			}
			tessCtrlShaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
			tessEvalShaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);

			glShaderSource(tessCtrlShaderID, 1, &tessCtrlText, 0);
			glShaderSource(tessEvalShaderID, 1, &tessEvalText, 0);

			glCompileShader(tessCtrlShaderID);
			/// Check for errors
			glGetShaderiv(tessCtrlShaderID, GL_COMPILE_STATUS, &status);
			if (status == 0) {
				GLsizei errorLogSize = 0;
				GLsizei titleLength;
				std::string errorLog = tessCtrlFilename;
				errorLog += "\nTESS CTRL:\n";
				titleLength = errorLog.length();
				glGetShaderiv(tessCtrlShaderID, GL_INFO_LOG_LENGTH, &errorLogSize);
				errorLog.resize(titleLength + errorLogSize);
				glGetShaderInfoLog(tessCtrlShaderID, errorLogSize, &errorLogSize, &errorLog[titleLength]);
				throw errorLog;
			}

			glCompileShader(tessEvalShaderID);
			/// Check for errors
			glGetShaderiv(tessEvalShaderID, GL_COMPILE_STATUS, &status);
			if (status == 0) {
				GLsizei errorLogSize = 0;
				GLsizei titleLength;
				std::string errorLog = tessEvalFilename;
				errorLog += "\nTESS EVAL:\n";
				titleLength = errorLog.length();
				glGetShaderiv(tessEvalShaderID, GL_INFO_LOG_LENGTH, &errorLogSize);
				errorLog.resize(titleLength + errorLogSize);
				glGetShaderInfoLog(tessEvalShaderID, errorLogSize, &errorLogSize, &errorLog[titleLength]);
				throw errorLog;
			}



		}
		else if ((tessCtrlFilename != nullptr) != (tessEvalFilename != nullptr)) { /// XOR
			std::string errorLog = "To use tessilation there needs to be both a tessCtrlFilename and tessEvalFilename";
			throw errorLog;
		}

		if (geomFilename != nullptr) {
			geomText = ReadTextFile(geomFilename);
			if (geomText == nullptr) {
				std::string errorMsg("Can't open file:");
				throw errorMsg + geomFilename;
			}
			geomShaderID = glCreateShader(GL_GEOMETRY_SHADER);
			if (geomShaderID == 0) {
				std::string errorMsg("Can't create a new geom shader ID");
				throw errorMsg;
			}
			glShaderSource(geomShaderID, 1, &geomText, 0);
			glCompileShader(geomShaderID);
			/// Check for errors
			glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &status);
			if (status == 0) {
				GLsizei errorLogSize = 0;
				GLsizei titleLength;
				std::string errorLog = geomFilename;
				errorLog += "\nGEOM:\n";
				titleLength = errorLog.length();
				glGetShaderiv(geomShaderID, GL_INFO_LOG_LENGTH, &errorLogSize);
				errorLog.resize(titleLength + errorLogSize);
				glGetShaderInfoLog(geomShaderID, errorLogSize, &errorLogSize, &errorLog[titleLength]);
				throw errorLog;
			}

		}
		shaderID = glCreateProgram();
		glAttachShader(shaderID, fragShaderID);
		glAttachShader(shaderID, vertShaderID);
		if (tessCtrlShaderID) glAttachShader(shaderID, tessCtrlShaderID);
		if (tessEvalShaderID) glAttachShader(shaderID, tessEvalShaderID);
		if (geomShaderID) glAttachShader(shaderID, geomShaderID);

		if (vertText) delete[] vertText;
		if (fragText) delete[] fragText;
		if (tessCtrlText) delete[] tessCtrlText;
		if (tessEvalText) delete[] tessEvalText;
		if (geomText) delete[] geomText;

	}
	catch (std::string error) {
		printf("%s\n", &error[0]);
		Debug::Error(error, __FILE__, __LINE__);
		return false;
	}
	return true;
}


bool Shader::Link() {
	GLint status;
	try {
		glLinkProgram(shaderID);
		/// Check for errors
		glGetProgramiv(shaderID, GL_LINK_STATUS, &status);
		if (status == 0) {
			GLsizei errorLogSize = 0;
			std::string errorLog;
			glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(errorLogSize);
			glGetProgramInfoLog(shaderID, errorLogSize, &errorLogSize, &errorLog[0]);
			throw errorLog;
		}

	}
	catch (std::string error) {
		Debug::Error(error, __FILE__, __LINE__);
		return false;
	}
	return true;
}

GLuint Shader::GetUniformID(std::string name) {
	auto id = uniformMap.find(name);
#ifdef _DEBUG
	static bool writeBadUniformWarning = true;
	if (id == uniformMap.end()) {
		if (writeBadUniformWarning) {
			Debug::Warning(name + " :No such uniform name", __FILE__, __LINE__);
			writeBadUniformWarning = false;/// I already told you, don't repeat the message 
		}
		return -1;
	}
#endif 
	return id->second;
}

void Shader::SetUniformLocations() {
	int count;
	GLsizei actualLen;
	GLint size;
	GLenum type;
	char* name;
	int maxUniformListLength;
	unsigned int loc;
	char buffer[512];

	std::string activeUniformList = "Uniforms:\n";
	glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &count);
	sprintf_s(buffer, 512, "There are %d active Uniforms\n", count);

	/// get the length of the longest named uniform 
	glGetProgramiv(shaderID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformListLength);

	/// Create a little buffer to hold the uniform's name - old C memory call just for fun 
	name = (char*)malloc(sizeof(char) * maxUniformListLength);


	for (int i = 0; i < count; ++i) {

		/// Get the name of the ith uniform

		glGetActiveUniform(shaderID, i, maxUniformListLength, &actualLen, &size, &type, name);
		/// Get the (unsigned int) loc for this uniform
		loc = glGetUniformLocation(shaderID, name);
		std::string uniformName = name;
		uniformMap[uniformName] = loc;

		sprintf_s(buffer, 512, "\"%s\" loc:%d\n", uniformName.c_str(), uniformMap[uniformName]);
		activeUniformList += buffer;
	}
	Debug::Info(activeUniformList, __FILE__, __LINE__);
	free(name);
}

/// Read from the specified file and return a char array from the heap 
/// The memory must be deleted within this class. It may not be the best way 
/// to do this but it is all private and I did delete it! SSF
char* Shader::ReadTextFile(const char* filename) {
	char* buffer = nullptr;
	std::ifstream file(filename, std::ios::binary);
	if (file.is_open()) {								/// Open the file
		file.seekg(0, std::ios::end);					/// goto the end of the file
		int bufferSize = (int)file.tellg();				/// Get the length of the file
		if (bufferSize == 0) {							/// If zero, bad file
			std::string errorMsg("Can't read shader file: ");
			std::string str2(filename);
			errorMsg += str2;
			throw errorMsg;								/// Bail out
		}
		buffer = new char[(int)(bufferSize + 1)];		/// Need to NULL terminate the array
		file.seekg(0, std::ios::beg);
		file.read(buffer, bufferSize);
		buffer[bufferSize] = NULL;						/// Add the NULL
		file.close();
	}
	else {
		std::string errorMsg("Can't open shader file: ");
		errorMsg += filename;
		Debug::Error(errorMsg, __FILE__, __LINE__);
	}
	return buffer;
}