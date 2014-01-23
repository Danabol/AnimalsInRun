#include "Game.h"
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_net.h>
#include <iostream>

using namespace std;

Game::Game()
{
	
	win = SDL_CreateWindow("Animals In Run", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	running = true;

}

void Game::GetEvents()
{
	SDL_Event occur;
	while(SDL_PollEvent(&occur))
	{
		if(occur.type==SDL_QUIT)
		{
			running = false;
		}
		if(occur.type== SDL_KEYDOWN)
		{
			switch (occur.key.keysym.sym)
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

SDL_Texture* Game::LoadImage(char* filename)
{
	SDL_Surface *image = IMG_Load(filename);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, image);
    SDL_FreeSurface(image);
	return texture;

}

void Game::Run()
{
	
	while(running)
	{
		GetEvents();

	}
}



Game::~Game()
{
    SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	SDLNet_Quit();
	IMG_Quit();
	SDL_Quit();
	
}