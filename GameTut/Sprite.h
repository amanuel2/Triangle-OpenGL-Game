#pragma once
#include<GL\glew.h>
#include<iostream>

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
	float vertexPoints[12];
	//Gluint -> unsigned int + Must 32BIT .
	GLuint _vboID;
};

