#ifndef _CLIENT_H_
#define _CLIENT_H_
#include <SDL.h>
#include<SDL_image.h>
#include<SDL_net.h>
#include <iostream>
#include <string>

class Client
{
private:
	//methods

	//variables
	IPaddress ip;
	TCPsocket client;
	char message[100];

public:
	Client();
	~Client();

	//methods
	void InitEverything();
	void Run();
	
	//variables
	

};
#endif;