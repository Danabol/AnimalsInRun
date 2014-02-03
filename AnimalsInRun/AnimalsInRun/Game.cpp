#include "Game.h"
#include<SDL_image.h>
#include<SDL_opengl.h>
#include <iostream>

using namespace std;

Game::Game(const std::string& title)
{
	this->InitEverything();
	this->win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	this->ren = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	this->running = true;
	
	
	SDLNet_ResolveHost(&ip,NULL,1444);

	this->server = SDLNet_TCP_Open(&ip);
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

void Game::Render()
{

}

//SDL_Texture* Game::LoadImage(const std::string& filename)
//{
//	SDL_Surface* image = IMG_Load(filename.c_str());
//	SDL_Texture* texture = SDL_CreateTextureFromSurface(this->ren, image);
//	SDL_FreeSurface(image);
//	return texture;
//}

void Game::Run()
{
	char* s = "hello world\n";

	while(this->running)
	{
		client = SDLNet_TCP_Accept(server);
		if(client)
		{
			SDLNet_TCP_Send( client,s,strlen(s)+1);
			SDLNet_TCP_Close(client);
			//SDLNet_TCP_Close(server);
		}
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

void Game::Server()
{
	

}

void LogSdlError(const std::string& msg) {
	std::cerr << msg << " error: " << SDL_GetError() << std::endl;
}