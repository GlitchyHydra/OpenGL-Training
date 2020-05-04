#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Renderer;

class Model
{
private:
	std::vector<Mesh> meshes;
	std::string& mFilePath;
	glm::mat4 rotation;
	//matrix with 1, translations coords
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	//scale num, zero in right column
	glm::mat4 scale = glm::translate(glm::mat4(2.0f), glm::vec3(0.0f, 0.0f, 0.0f));;
public :
	Model(std::string& path);
	~Model() {};

	void loadModel();
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType typeName);
	void Draw(Shader shader, Renderer renderer);

};