#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <string>
#include <vector>

#include "Mesh.h"
#include "../Shader.h"

class Renderer;

class Model
{
private:
	std::vector<Mesh> meshes;
	std::string& mFilePath;
public :
	Model(std::string& path);
	~Model() {};

	void loadModel();
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType typeName);
	void Draw(Shader shader, Renderer renderer);

};