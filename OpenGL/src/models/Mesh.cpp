#include "Mesh.h"
#include "Renderer.h"

Mesh::Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind, std::vector<Texture> tex)
	: vertices(vert), indices(ind), textures(tex)
{
	//VertexBuffer Data gen
	this->vb = VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));
	//IndexBuffer Data gen
	this->ib = IndexBuffer(&indices[0], indices.size() * sizeof(unsigned int));
}

Mesh::~Mesh()
{

}

void Mesh::Bind() const
{
	va.Bind();
}

void Mesh::SetupMesh()
{
    va.Bind();
	vbl.Push<float>(3);
	vbl.Push<float>(3);
	vbl.Push<float>(2);
	va.AddBuffer(vb, vbl);
	//unbind after setup
	va.Unbind();
}