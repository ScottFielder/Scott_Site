#pragma once

#include "glew.h"
#include <unordered_map>
#include <string>

class Shader {
	Shader(const Shader&) = delete;
	Shader(Shader&&) = delete;
	Shader& operator = (const Shader&) = delete;
	Shader& operator = (Shader&&) = delete;
private:
	const char* vertFilename;
	const char* fragFilename;
	const char* tessCtrlFilename;
	const char* tessEvalFilename;
	const char* geomFilename;

	GLuint  shaderID;
	GLuint vertShaderID;
	GLuint fragShaderID;
	GLuint tessCtrlShaderID;
	GLuint tessEvalShaderID;
	GLuint geomShaderID;
	std::unordered_map<std::string, GLuint > uniformMap;

	/// Private helper methods
	char* ReadTextFile(const char* fileName);
	bool CompileAttach();
	bool Link();
	void SetUniformLocations();


public:
	Shader(const char* vertFilename_, const char* fragFilename_,
		const char* tessCtrlFilename_ = nullptr, const char* tessEvalFilename = nullptr,
		const char* geomFilename_ = nullptr);
	~Shader();
	bool OnCreate();
	void OnDestroy();
	inline GLuint GetProgram() const { return shaderID; }
	GLuint GetUniformID(std::string name);
};
