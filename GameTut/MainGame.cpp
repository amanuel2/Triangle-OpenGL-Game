#include "MainGame.h"

//FLAGS
//-------
//SDL_WINDOW_FULLSCREEN = 0x00000001,         /**< fullscreen window */
//SDL_WINDOW_OPENGL = 0x00000002,             /**< window usable with OpenGL context */
//SDL_WINDOW_SHOWN = 0x00000004,              /**< window is visible */
//SDL_WINDOW_HIDDEN = 0x00000008,             /**< window is not visible */
//SDL_WINDOW_BORDERLESS = 0x00000010,         /**< no window decoration */
//SDL_WINDOW_RESIZABLE = 0x00000020,          /**< window can be resized */
//SDL_WINDOW_MINIMIZED = 0x00000040,          /**< window is minimized */
//SDL_WINDOW_MAXIMIZED = 0x00000080,          /**< window is maximized */
//SDL_WINDOW_INPUT_GRABBED = 0x00000100,      /**< window has grabbed input focus */
//SDL_WINDOW_INPUT_FOCUS = 0x00000200,        /**< window has input focus */
//SDL_WINDOW_MOUSE_FOCUS = 0x00000400,        /**< window has mouse focus */
//SDL_WINDOW_FULLSCREEN_DESKTOP = (SDL_WINDOW_FULLSCREEN | 0x00001000),
//SDL_WINDOW_FOREIGN = 0x00000800,            /**< window not created by //SDL */
//SDL_WINDOW_ALLOW_HIGHDPI = 0x00002000,      /**< window should be created in high-DPI mode if supported */
//SDL_WINDOW_MOUSE_CAPTURE = 0x00004000       /**< window has mouse captured (unrelated to INPUT_GRABBED) */
//#define SDL_WINDOWPOS_CENTERED_MASK    0x2FFF0000
//#define SDL_WINDOWPOS_CENTERED_DISPLAY(X)  (SDL_WINDOWPOS_CENTERED_MASK|(X))
//#define SDL_WINDOWPOS_CENTERED         SDL_WINDOWPOS_CENTERED_DISPLAY(0)
//#define SDL_WINDOWPOS_ISCENTERED(X)    \
            (((X)&0xFFFF0000) == SDL_WINDOWPOS_CENTERED_MASK)



MainGame::MainGame(int width, int height):_screenWidth(width), _screenHieght(height)
{
	__window = NULL;
	__gameState = GameState::PLAY;
	for (int i = 0; i < 4; i++)
		s[i] = 0.0f;
	av[0] = 0.0f;
	av[1] = 0.0f;
	av[2] = 0.0f;

	vertexData[0] = 0.0f;
	vertexData[1] = 1.0f;
	vertexData[2] = 0.0f;
	vertexData[3] = -1.0f;
	vertexData[4] == 0.0f;
	vertexData[5] == 1.0f;

	infoFile.open("INFO_FILE.txt");
}

void MainGame::HandleVtx()
{
	for (int i = 0; i <= 5; i++) 
	{
		if (vertexData[i] > 1)
		{
			vertexData[i] = -1.0f;
		}
		else if (vertexData[i] < -1)
		{
			vertexData[i] = 1.0f;
		}
	}

}

void MainGame::displayCoordinates()
{
	cout << "COORDINATES " << endl;
	cout << "-----------" << endl;
	cout << "[" << vertexData[0] << "," << vertexData[1] << "]" << endl;
	cout << "[" << vertexData[2] << "," << vertexData[3] << "]" << endl;
	cout << "[" << vertexData[4] << "," << vertexData[5] << "]" << endl;
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string MainGame::currentDateTime() {
	time_t     now = time(0);
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return buf;
}

void MainGame::WriteStatements(){

	infoFile << "DATE/TIME<YYYY-MM-DD.HH:mm:ss> : " << currentDateTime() << endl;
	infoFile << "--------------------------------------------------------" << endl;
	infoFile << "COORDINATES " << endl;
	infoFile << "-----------" << endl;
	infoFile << "[" << vertexData[0] << "," << vertexData[1] << "]" << endl;
	infoFile << "[" << vertexData[2] << "," << vertexData[3] << "]" << endl;
	infoFile << "[" << vertexData[4] << "," << vertexData[5] << "]" << endl;

	infoFile << "--------------" << endl;
	infoFile << "TRIANGLE COLOR" << endl;
	infoFile << "----------------" << endl;
	infoFile << "R : " << av[0] << endl << "G : " << av[1] << endl << "B : " << av[2] << endl;

	infoFile << "--------------" << endl;
	infoFile << "BACKGROUND COLOR" << endl;
	infoFile << "----------------" << endl;
	infoFile << "R : " << s[0] << endl << "G : " << s[1] << endl << "B : " << s[2] << "A : " << s[3] << endl;

}

void MainGame::run() {
	//Initalizes Systems First
	initSystem();


	//Then Loops until user Exits
	gameLoop();
}

void MainGame::MaintainColorAv()
{
	if (av[0] >= 1.0f || av[1] >= 1.0f || av[2] >= 1.0f)
		av[0] = 0.0f, av[1] = 0.0f, av[2] = 0.0f;

	//Print Out RGBA For Info
	/*
	R - Red = Redness
	G - Green = Greeness
	B - Blue = Blueness
	*/
	cout << "TRIANGLE : " << "R : " << av[0] << " G : " << av[1] << "B : " << av[2] << endl;
}

void MainGame::drawTriangle()
{
	//Draw a triangle using the crappy immediate mode
	glBegin(GL_TRIANGLES);
	glColor3f(av[0], av[1], av[2]);
	glVertex2f(vertexData[0], vertexData[1]);
	glVertex2f(vertexData[2], vertexData[3]);
	glVertex2f(vertexData[4], vertexData[5]);
	glEnd();
}
void MainGame::MaintainColor()
{
	if (s[0] >= 1.0f || s[1] >= 1.0f || s[2] >= 1.0f || s[3] >= 1.0f)
		s[0] = 0.0f, s[1] = 0.0f, s[2] = 0.0f, s[3] = 0.0f;
	else
		s[0] += 0.05f, s[1] += 0.05f, s[2] += 0.05f, s[3] += 0.05f;

	//Print Out RGBA For Info
	/*
	R - Red = Redness
	G - Green = Greeness
	B - Blue = Blueness
	A - Alpha = Depth 
	*/
	cout << "BACKGROUND : " << "R : " << s[0]  << " G : " << s[1] << "B : " << s[2]  << " A : " << s[3] << endl;
}

void fatalErr(string msg)
{
	cout << msg << endl;
	//exit(1);
}
bool MainGame::loadMedia(char* filePath)
{
	//Loading success flag
	bool success = true;

	//Load splash image
	 gHelloWorld = SDL_LoadBMP(filePath);
	if (gHelloWorld == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", filePath, SDL_GetError());
		success = false;
	}

	return success;
}
void MainGame::quitCheck()
{
	std::string quitOption;
	std::cout << "Are you sure you want to quit?(Y or N)" << std::endl;
	std::cin >> quitOption;

	std::transform(quitOption.begin(), quitOption.end(), quitOption.begin(), tolower);

	if (quitOption.compare("y") == 0){
		__gameState = GameState::EXIT;
		gameLoop();
	}
	else {
		__gameState = GameState::PLAY;
		gameLoop();
	}

}
void MainGame::initSystem() 
{
	//Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Creation Window
	__window = SDL_CreateWindow(
		"Triangle Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_screenWidth,
		_screenHieght,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);
	//Checks for any errors..
	if (__window == NULL)
		fatalErr("Could Not Create SDL...");


	SDL_GLContext glConx = SDL_GL_CreateContext(__window);
	if (glConx == NULL)
		fatalErr("Could not create GL Context");

	//Sets up Extension. For
	//Unsported Hardware
	GLenum errorGl = glewInit();

	if (errorGl != GLEW_OK /*Or 0*/)
		fatalErr("Couldnt Initalize Glew!");

	//Tell SDL that we want a double buffered window so we dont get
	//any flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

	//Set the background color to blue
	glClearColor(s[1], s[2], s[3], s[4]);

	this->loadMedia("2XcTz.bmp");

}

void MainGame::drawGame() 
{
	//glClearDepth(0.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//Draw a triangle using the crappy immediate mode
	glBegin(GL_TRIANGLES);
	glColor3f(av[0], av[1], av[2]);
	glVertex2f(vertexData[0], vertexData[1]);
	glVertex2f(vertexData[2], vertexData[3]);
	glVertex2f(vertexData[4], vertexData[5]);
	glEnd();

	

	//Swap our buffer and draw everything to the screen!
	SDL_GL_SwapWindow(__window);
}

void MainGame::processInput()
{
	SDL_Event evt;
	//If there is an Event
	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {
		case SDL_QUIT:
			//this -> quitCheck();
			exit(1);
			delete[]s,
			delete[]av,
			delete[]vertexData;
			infoFile.close();
			break;
		case SDL_MOUSEMOTION:
			std::cout << " Current X " << evt.motion.x << std::endl;
			std::cout << " Current Y " << evt.motion.y << std::endl;
			break;
		case SDL_KEYUP:
			if (evt.key.keysym.sym == SDLK_ESCAPE)
			{
				delete[]s,
				delete[]av,
				delete[]vertexData;
				infoFile.close();
				exit(1);
			}
			if (evt.key.keysym.sym == SDLK_i)
			{
				//Set the background color to
				//Alpha
				s[3] += 0.1f;
				glClearColor(s[1], s[2], s[3], s[4]);
			}
			else if (evt.key.keysym.sym == SDLK_j)
			{
				//G-Green
				s[1] += 0.01f;
				glClearColor(s[1], s[2], s[3], s[4]);
			}
			else if (evt.key.keysym.sym == SDLK_k)
			{
				//R - Red
				s[0] += 0.01f;
				glClearColor(s[1], s[2], s[3], s[4]);
			}
			else if (evt.key.keysym.sym == SDLK_l)
			{
				//B - Blue
				s[2] += 0.01f;
				glClearColor(s[1], s[2], s[3], s[4]);
			}
			else if (evt.key.keysym.sym == SDLK_a)
			{
				//R - Red
				av[0] += 0.01f;
			}
			else if (evt.key.keysym.sym == SDLK_w)
			{
				//G - Green
				av[1] += 0.01f;
			}
			else if (evt.key.keysym.sym == SDLK_d)
			{
				//B - Blue
				av[2] += 0.01f;
			}

			else if (evt.key.keysym.sym == SDLK_UP)
			{
				vertexData[0] += 0.1f;
			}
			else if (evt.key.keysym.sym == SDLK_DOWN)
			{
				vertexData[1] += 0.1f;
			}
			else if (evt.key.keysym.sym == SDLK_RIGHT)
			{
				vertexData[2] += 0.1f;
			}
			else if (evt.key.keysym.sym == SDLK_LEFT)
			{
				vertexData[3] += 0.1f;
			}
			else if (evt.key.keysym.sym == SDLK_RSHIFT)
			{
				vertexData[4] += 0.1f;
			}
			else if (evt.key.keysym.sym == SDLK_RCTRL)
			{
				vertexData[5] += 0.1f;
			}

			else
				fatalErr("UNDEFINED RGBA COLOR");

			this->MaintainColor();
			this->HandleVtx();
			this->drawTriangle();
			this->MaintainColorAv();
			this->displayCoordinates();
			this->WriteStatements();

		}
	}

}
void MainGame::gameLoop() {

	while (__gameState != GameState::EXIT) {
		/**
		**Proccess input, so AI Can interact
		**With User
		*/
		processInput();
		drawGame();
	}

}
MainGame::~MainGame()
{
}
