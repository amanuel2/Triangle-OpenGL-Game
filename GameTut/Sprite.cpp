#include "Sprite.h"

Sprite::Sprite()
{
	//Initalize to 0 To check if 
	//it has been created
	_vboID = 0;
}

Sprite::~Sprite()
{
	//Free RAM For better Performance
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height)
{
	if (_vboID == 0)
	{
		//Give _vboID
		//The Vertex Buffer
		//Object ID
		glGenBuffers(1, &_vboID);
		cout << _vboID << endl;
	}
	//  ___________
	//  |		  |
	//  |		  |
	//  |		  |
	//  |_________|

	//First Triangle
	vertexPoints[0] = x;
	vertexPoints[1] = y + (height*2);

	vertexPoints[2] = x + (width/2);
	vertexPoints[3] = y + (height/2);

	vertexPoints[4] = x;
	vertexPoints[5] = y;

	//Second Triangles
//	vertexPoints[6] = x + width;
//	vertexPoints[7] = y + height;

//	vertexPoints[8] = x;
//	vertexPoints[9] = y;

//	vertexPoints[10] = x;
//	vertexPoints[11] = y + height;


	//Make Buffer Active
	//GL_ARRAY_BUFFER = Basic Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER,_vboID);


	//Stage : Uploading The Data
//	 CPU			  GPU
//  -----			 _____
//  _________		________
//	|		|		|	   |
//	|		|		|	   |
//	|	  __|		|___   |
//	|_____|_| ----->|__|___|

	//Uploading The Vertex Buffer Object to GPU.
	//Dont Understand what GL_STATIC_DRAW IS.
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexPoints),&vertexPoints,GL_STATIC_DRAW);

	//To Be Safe Unbind Buffer
	//Much more like deleting
	//variables allocated to
	//heap memory

	glBindBuffer(GL_ARRAY_BUFFER,0);

}

void Sprite::draw()
{
	//Make Buffer Active
	//GL_ARRAY_BUFFER = Basic Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);


	//Just give Position Attribute
	//No Color, Ligtining, and such.
	//1 vertex attrib aray
	glEnableVertexAttribArray(0);


	//Attributes Given to function
	// 0 (because we enabled only position above ^^)
	// 2 (Size of each cordinate. (since we are doing x,y(2D) then we pass in 2) )
	// GL_FLOAT (because we are using float arrays for our vertex Data..)
	// GL_FALSE (not normalized. Later Lesson Explaining why not)
	// 0 (stride.. Later Lesson Explaining why)
	// 0 (Later Lesson Explaining why)
	/*
	*This tells where Data is/How you should draw the image you recieved from CPU.
	*(as we did in init function)
	* We put in 2 because its x,and y coordinates
	*/
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


	//Now Drawing
	//0 , since position 0 is our first data.
	//and 6 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Disable attrib array
	glDisableVertexAttribArray(0);

	//To Be Safe Unbind Buffer
	//Much more like deleting
	//variables allocated to
	//heap memory

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}