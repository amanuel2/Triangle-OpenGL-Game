#pragma once
#include<GL\glew.h>
#include<iostream>
#include<cstddef>
#include"Vertex.h"

using std::cout;
using std::endl;

class Sprite
{
public:
	Sprite(  );
	~Sprite(  );
	void init(float x, float y, float width, float height );
	void draw( );

private:
	float _width, _height, _x, _y;
	Vertex vertexPoints[6];
	//Gluint -> unsigned int + Must 32BIT .
	GLuint _vboID;
};

