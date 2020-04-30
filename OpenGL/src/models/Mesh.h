#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

#include "../VertexArray.h"
#include "../IndexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"

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
	Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind, std::vector<Texture> tex,
		VertexArray va_) : vertices(vert), indices(ind), textures(tex), va(va_)
	{
		 VertexBuffer vb(&vertices[0], vert.size());
		 IndexBuffer ib(&indices[0], indices.size());
	};
	~Mesh();

	void Bind() const;
	void SetupMesh();
};