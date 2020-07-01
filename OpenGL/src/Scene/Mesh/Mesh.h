#pragma once

#include "abstractions/Texture.h"
#include "abstractions/VertexBufferLayout.h"

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

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
	unsigned int matInd;
	VertexArray va;
	IndexBuffer ib;

private:
	VertexBuffer vb;
	VertexBufferLayout vbl;

public:
	Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind);
	Mesh();
	~Mesh();

	void Bind() const;
	void SetupMesh();
private:
	void InitMesh();
};