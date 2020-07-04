#include "Mesh.h"

Mesh::Mesh() 
{}

Mesh::Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind)
	: vertices(vert), indices(ind)
{
	SetupMesh();
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
	vb.setupData(&vertices[0], vertices.size() * sizeof(Vertex));
	ib.setupData(&indices[0], indices.size());
	vbl.Push<float>(3);
	vbl.Push<float>(3);
	vbl.Push<float>(2);
	va.AddBuffer(vb, vbl);
	//unbind after setup
	va.Unbind();
}

void Mesh::InitMesh()
{

}
