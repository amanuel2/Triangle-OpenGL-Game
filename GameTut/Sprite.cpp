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

	//This array will hold our vertex data.
	//We need 6 vertices, and each vertex has 2
	//floats for X and Y

	//First Triangle
	vertexPoints[0].position.x = x + width;
	vertexPoints[0].position.y = y + height;

	vertexPoints[1].position.x = x;
	vertexPoints[1].position.y = y + height;

	vertexPoints[2].position.x = x;
	vertexPoints[2].position.y = y;

	//Second Triangle
	vertexPoints[3].position.x = x;
	vertexPoints[3].position.y = y;

	vertexPoints[4].position.x = x + width;
	vertexPoints[4].position.y = y;

	vertexPoints[5].position.x = x + width;
	vertexPoints[5].position.y = y + height;

	//Set all vertex colors to rgba(156, 39, 176,1.0) Purple Material Colors
	for (int i = 0; i < 6; i++) {
		vertexPoints[i].color.R = 156;
		vertexPoints[i].color.G = 39;
		vertexPoints[i].color.B = 176;
		vertexPoints[i].color.A = 1.0;
	}

	//rgba(244, 67, 54,1.0)
	vertexPoints[1].color.R = 244;
	vertexPoints[1].color.G = 67;
	vertexPoints[1].color.B = 54;
	vertexPoints[1].color.A = 1.0;

	//rgba(63, 81, 181,1.0)
	vertexPoints[4].color.R = 63;
	vertexPoints[4].color.G = 81;
	vertexPoints[4].color.B = 181;
	vertexPoints[4].color.A = 1.0;


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
	//Position Attribute Pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void *) offsetof(Vertex, position));



	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));


	//Now Drawing
	//0 , since position 0 is our first data.
	//and 6 vertices
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Disable attrib array
	glDisableVertexAttribArray(0);

	//To Be Safe Unbind Buffer
	//Much more like deleting
	//variables allocated to
	//heap memory

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}