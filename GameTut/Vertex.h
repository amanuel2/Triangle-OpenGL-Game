#pragma once
#include<GL\glew.h>
struct Vertex
{
	//X,Y Coordinates
	struct Position 
	{
		float x,y;
	}position;
	//RGBA
	struct Color
	{
		GLubyte R,G,B,A;
	}color;
};