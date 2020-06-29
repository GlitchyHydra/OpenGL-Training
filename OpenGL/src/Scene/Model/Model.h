#include "Scene/Mesh/Mesh.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer;

class Model
{
private:
	std::vector<Mesh> meshes;
	std::vector<Texture*> textures;
	const std::string& mFilePath;
	mutable glm::mat4 totalTrans;
public:
	glm::vec3 translation = glm::vec3(960.f, 540.f, 10.f);
	glm::mat4 rotation;
	glm::vec3 scale = glm::vec3(100.0f, 100.0f, 100.0f);

public :
	Model(const std::string& path);
	~Model() {};

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType typeName);
	void Draw(Shader& shader, const Renderer& renderer) const;

	void SetModelTrans(Shader& shader) const;
private:
	void loadModel();
	void processNode(aiNode* node, const aiScene* scene);
	void processMesh(aiMesh* ai_Mesh, const aiScene* scene, Mesh& mesh);
	void InitTextures(const aiScene* scene, const std::string& Filename);
};