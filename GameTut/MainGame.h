#pragma once
#pragma warning(disable : 4996)
#include<SDL.h>
#include<GL/glew.h>
#include<string>
#include<iostream>
#include<algorithm>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include<SDL_image.h>


typedef std::string str;

using std::cout;
using std::endl;
using std::string;


enum class GameState {
	PLAY,
	EXIT
};

class MainGame
{
public:

	struct tm  tstruct;

	MainGame(int width, int height);
	~MainGame();

	void run();

private:
	void initSystem(), processInput(), gameLoop(),
		quitCheck(), drawGame(), MaintainColor(),
		drawTriangle(), MaintainColorAv(), HandleVtx(),
		displayCoordinates(), WriteStatements();
	const str currentDateTime();
	std::ofstream infoFile;
	long float *s = new long float[4];
	float *vertexData = new float[6];
	float *av = new float[3];
	char dir = 'r', str[26];
	bool loadMedia(char* filePath);
	int _screenWidth;
	int _screenHieght;
	SDL_Surface *gHelloWorld;
	GameState __gameState;
	SDL_Window *__window;

};
