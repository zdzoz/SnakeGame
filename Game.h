#pragma once

#include "SDL.h"
#include <iostream>
#include <vector>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void snake(int len);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool isRunning() { return running; }

private:
	int x = 100;
	int y = 100;
	int dir = 1; // up = 0, right = 1, down = 2, left = 3
	int len = 2;
	int snakeSize = 20;
	bool running;
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::vector<SDL_Rect> snakeTrail{ (SDL_Rect{ x, y, snakeSize, snakeSize }) };
};

