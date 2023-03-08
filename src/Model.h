#pragma once

#include <json/json.hpp>

#include "Mesh.h"

using json = nlohmann::json;

class Model
{
public:
	// Properties
	std::vector<Mesh> Meshes;

	// Method
	Model(const char* file);

	void Draw(Shader& shader, Camera& camera);
	void Draw(Shader& shader, Camera& camera, float scale);


private:
	// Properties
	const char* m_file;
	std::vector<unsigned char> m_data;
	json m_json;
	std::vector<std::string> m_loadedTexName;
	std::vector<Texture> m_loadedTex;
	std::vector<glm::mat4> m_matricesMeshes;
	std::vector<glm::vec3> m_translationsMeshes;
	std::vector<glm::quat> m_rotationsMeshes;
	std::vector<glm::vec3> m_scalesMeshes;


	//Method
	void loadMesh(unsigned int indMesh);

	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	std::vector<unsigned char> getData();

	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();

	std::vector<Vertex> assembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> texUVs);


	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);


	template<typename GROUP_TYPE, typename VALUE_TYPE>
	void readData(unsigned int beginnOfData, unsigned int endOfData, std::vector<GROUP_TYPE>& dataVec)
	{
		for (unsigned int i = beginnOfData; i < endOfData; i)
		{
			unsigned char bytes[] = { m_data[i++], m_data[i++], m_data[i++], m_data[i++] };
			VALUE_TYPE value;
			std::memcpy(&value, bytes, sizeof(VALUE_TYPE));
			dataVec.push_back(static_cast<GROUP_TYPE>(value));
		}
	}
};

