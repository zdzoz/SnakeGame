#include "Game.h"



Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized..." << std::endl;
		
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window successfully created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer successfully created!" << std::endl;
		}

		running = true;
	}
	else {
		running = false;
	}
}

void Game::snake(int len) {
	int ud, lf;
	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);

	switch (dir){
	case 0: // up
		if (dir != 2) {
			ud = -1;
			lf = 0;
		}
		break;
	case 1: // right
		if (dir != 3) {
			ud = 0;
			lf = 1;
		}
		break;
	case 2: // down
		if (dir != 0) {
			ud = 1;
			lf = 0;
		}
		break;
	case 3: // left
		if (dir != 1) {
			ud = 0;
			lf = -1;
		}
		break;
	}

	if (snakeTrail.size() == len - 1) {
		for (int i = 0; i < 2; i++){
			x += (20 * lf);
			y += (20 * ud);
			snakeTrail.insert(snakeTrail.begin(), 1, (SDL_Rect{ x, y, snakeSize, snakeSize }));
		}
		//x += (20 * lf);
		//y += (20 * ud);
		//snakeTrail.insert(snakeTrail.begin(), 1, (SDL_Rect{ x, y, snakeSize, snakeSize }));
	}
	else {
		x += (20 * lf);
		y += (20 * ud);
		if (x > ww)
			x = 0;
		if (x < 0)
			x = ww;
		if (y > wh)
			y = 0;
		if (y < 0)
			y = wh;
		snakeTrail.insert(snakeTrail.begin(), 1, (SDL_Rect{ x, y, snakeSize, snakeSize }));
	}

	std::cout << "\nSnake vector-size: " << snakeTrail.size() << std::endl;

	// Set render colour to green
	SDL_SetRenderDrawColor(renderer, 0, 255, 100, 255);
	for (int i = 0; i < snakeTrail.size(); i++) {
		std::cout << "Current i value: " << i << std::endl;
		SDL_RenderDrawRect(renderer, &snakeTrail[i]);
		SDL_RenderFillRect(renderer, &snakeTrail[i]);
	}
	// Set render colour back to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	snakeTrail.pop_back();
}

void Game::handleEvents() {
	
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch (event.type){
	case SDL_QUIT:
		running = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			if (dir != 2)
				dir = 0;
			break;
		case SDLK_RIGHT:
			if (dir != 3)
				dir = 1;
			break;
		case SDLK_DOWN:
			if (dir != 0)
				dir = 2;
			break;
		case SDLK_LEFT:
			if (dir != 1)
				dir = 3;
			break;
		case SDLK_SPACE:
			len++;
			break;
		}
		break;
	default:
		break;
	}
}

void Game::update() {
	
	//x += xdir*(snakeSize);
	//y += ydir*(snakeSize);
} 

void Game::render() {
	SDL_RenderClear(renderer);
	snake(len);
	SDL_RenderPresent(renderer);
}
 
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned." << std::endl;
}
