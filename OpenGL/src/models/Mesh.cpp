#include "Mesh.h"
#include "../Renderer.h"
#include <gl/glew.h>

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
	vb.Bind();
	vbl.Push<float>(3);
	vbl.Push<float>(3);
	vbl.Push<float>(2);
	va.AddBuffer(vb, vbl);
	//unbind after setup
	va.Unbind();
}