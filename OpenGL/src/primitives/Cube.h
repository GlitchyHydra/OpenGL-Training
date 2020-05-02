#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class Cube
{
public:
	const float vertexInfo[40] =  {
		-50.0f, -50.0f, -50.0f,  0.0f, 0.0f, //0
		 50.0f, -50.0f, -50.0f,  1.0f, 0.0f, //1
		 50.0f,  50.0f, -50.0f,  1.0f, 1.0f, //2
		-50.0f,  50.0f, -50.0f,  0.0f, 1.0f, //3
		-20.0f,  70.0f,  50.0f,  0.0f, 0.0f, //4
		 70.0f,  70.0f,  50.0f,  1.0f, 0.0f, //5
		-30.0f, -30.0f,  50.0f,  0.0f, 1.0f, //6
		 70.0f, -30.0f,  50.0f,  1.0f, 1.0f  //7
	};
	const unsigned int indicesInfo[36] = {
		//front
		0, 1, 2,
		2, 3, 0,
		//rear
		6, 5, 7,
		6, 4, 5,
		//top
		3, 5, 2,
		3, 4, 5,
		//bottom
		0, 7, 1,
		0, 6, 1,
		//left
		0, 3, 4,
		0, 4, 6,
		//right
		1, 5, 7,
		1, 2, 5
	};
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;
private:
	unsigned int sizeVertex = (3 + 2) * 8;
	unsigned int sizeIndices = 36;
	VertexBufferLayout layout;
public:
	Cube();
	~Cube() {};


};



