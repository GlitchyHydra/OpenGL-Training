#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

enum TextureType {
	TEX_DIFFUSE = 0, TEX_BLICK = 1
};

struct Texture {
	unsigned int id;
	TextureType type;
};

class Mesh
{
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	unsigned int VAO_id, VBO_id, EBO_id;
public:
	Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind, std::vector<Texture> tex)
		: vertices(vert), indices(ind), textures(tex) {};
	~Mesh();

	void Bind() const;
	void SetupMesh();
};