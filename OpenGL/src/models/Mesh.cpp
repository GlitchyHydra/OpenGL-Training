#include "Mesh.h"
#include "../Renderer.h"
#include <gl/glew.h>

void Mesh::SetupMesh()
{
	GLCall(glGenVertexArrays(1, &VAO_id));
	glGenBuffers(1, &VBO_id);
	glGenBuffers(1, &EBO_id);

	glBindVertexArray(VAO_id);

}