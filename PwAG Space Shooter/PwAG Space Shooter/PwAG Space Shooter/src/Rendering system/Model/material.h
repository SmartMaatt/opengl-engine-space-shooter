#pragma once

class Material
{
public:
	Material();
	Material(glm::vec3 ambientLight);

	void setMaterialShaderUniforms(ShaderProgram &shaderProgram);

	virtual ~Material();

private:
	 glm::vec3 ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);
	// TODO wartoœci definiuj¹ce materia³, takie jak œwiat³o ambient itp.
};

