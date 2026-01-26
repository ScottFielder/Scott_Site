#pragma once
#include "glew.h"
#include "Component.h"
#include <unordered_map>
#include <string>

class ShaderComponent: public Component {
	ShaderComponent(const ShaderComponent&) = delete;
	ShaderComponent(ShaderComponent&&) = delete;
	ShaderComponent& operator = (const ShaderComponent&) = delete;
	ShaderComponent& operator = (ShaderComponent&&) = delete;

private:
	const char* vertFilename;
	const char* fragFilename;
	const char* tessCtrlFilename;
	const char* tessEvalFilename;
	const char* geomFilename;

	
	GLuint shaderID;
	GLuint vertShaderID;
	GLuint fragShaderID;
	GLuint tessCtrlShaderID;
	GLuint tessEvalShaderID;
	GLuint geomShaderID;

	std::unordered_map<std::string, GLuint > uniformMap;

	/// Private helper methods
	char* ReadTextFile(const char *fileName);	
	bool CompileAttach();
	bool Link();
	void SetUniformLocations();
	

public:
	ShaderComponent(Component* parent_,const char* vertFilename_, const char* fragFilename_, 
		const char* tessCtrlFilename_ = nullptr, const char* tessEvalFilename = nullptr,
		const char* geomFilename_ = nullptr);

	~ShaderComponent();

	GLuint GetUniformID(std::string name);
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime ) override;
	void Render() const override;

	inline GLuint GetProgram() const { return shaderID;}
};


