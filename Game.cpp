#include "Game.h"
#include <string>
#include "texturemanager.h" 
#include "gameObject.h"
#include "SDL.h"
#include "ecs.h"
#include "components.h"


gameObject* ball;
gameObject* racket1;
gameObject* racket2;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& newBall(manager.addEntity());
auto& newPlayer(manager.addEntity());

Game::Game()
{
	isRunning = true;

}
Game::~Game()
{

}


void Game::init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialised" << std::endl;
		window = SDL_CreateWindow("random pong", xpos, ypos, width, height, flags);
		SDL_INIT_EVERYTHING;

		if (window)
		{
			std::cout << "Window created" << std::endl;
		}
		

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}
		

		isRunning = true;
	} else {
		isRunning = false;
	}

	ball = new gameObject("ball.png", 340, 250, 75, 80);
	racket1 = new gameObject("racket.png", -50, 130, 120, 200);
	racket2 = new gameObject("racket.png", 745, 140, 75, 200);
	SDL_Rect wall;
	wall.x = racket1->xpos;
	wall.y = racket1->ypos;
	wall.w = racket1->width;
	wall.h = racket1->height;
	SDL_Rect wall2;
	wall2.x = racket2->xpos;
	wall2.y = racket2->ypos;
	wall2.w = racket2->width;
	wall2.h = racket2->height;

	newBall.getComponent<BallComponent>();
	newPlayer.getComponent<RacketComponent1>();
}

void Game::update()
{
	ball->Update();
	racket1->Update();
	racket2->Update();
	manager.update();
}

void Game::render()
{
	//ball texture
	SDL_RenderClear(renderer);
	ball->Render();
	//racket1 texture
	racket1->Render();
	//racket2 texture
	racket2->Render();
	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	}
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	
	SDL_Quit();
	std::cout << "game cleaned" << std::endl;
}
