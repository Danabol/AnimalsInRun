#include "Game.h"

#include<SDL_image.h>
#include <iostream>

Game::Game(const std::string& title)
{
	this->win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	this->ren = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	this->running = true;
}

void Game::GetEvents()
{
	SDL_Event occur;
	while(SDL_PollEvent(&occur))
	{
		if(occur.type == SDL_QUIT)
		{
			this->running = false;
		}
		if(occur.type == SDL_KEYDOWN)
		{
			switch(occur.key.keysym.sym)
			{
			default:
				break;
			}
		}
	}
}

void Game::InitEverything()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG);
	SDLNet_Init();
}

SDL_Texture* Game::LoadImage(const std::string& filename)
{
	SDL_Surface* image = IMG_Load(filename.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(this->ren, image);
	SDL_FreeSurface(image);
	return texture;
}

void Game::Run()
{
	while(this->running)
	{
		this->GetEvents();
	}
}

Game::~Game()
{
	SDL_DestroyRenderer(this->ren);
	SDL_DestroyWindow(this->win);

	SDLNet_Quit();
	IMG_Quit();
	SDL_Quit();
}

void LogSdlError(const std::string& msg) {
	std::cerr << msg << " error: " << SDL_GetError() << std::endl;
}