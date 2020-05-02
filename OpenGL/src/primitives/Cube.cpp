#include "Cube.h"

#include <iostream>

Cube::Cube()
{
	va.Bind();
    ib.setupData((unsigned int*)&indicesInfo[0], sizeIndices);
	vb.setupData((float*)&vertexInfo[0], sizeof(float) * sizeVertex);
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	va.Unbind();
}
