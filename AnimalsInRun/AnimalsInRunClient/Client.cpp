#include "Client.h"

using namespace std;

Client::Client()
{
	this->InitEverything();
	SDLNet_ResolveHost(&ip,"127.0.0.1",1444);
	client= SDLNet_TCP_Open(&ip);
}

void Client::InitEverything()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG);
	SDLNet_Init();
}

Client::~Client()
{
	SDLNet_TCP_Close(client);

	SDLNet_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Client::Run()
{
	SDLNet_TCP_Recv(client,message,100);
	cout<<message<<endl;
	SDL_Delay(10000);
}

