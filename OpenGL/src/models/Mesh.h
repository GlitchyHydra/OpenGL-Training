#pragma once

#include "Texture.h"
#include "glm//vec3.hpp"
#include "glm//vec2.hpp"
#include "VertexBufferLayout.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	IndexBuffer ib;
	VertexArray va;
private:
	VertexBuffer vb;
	VertexBufferLayout vbl;
public:
	Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind, std::vector<Texture> tex);
	~Mesh();

	void Bind() const;
	void SetupMesh();
};