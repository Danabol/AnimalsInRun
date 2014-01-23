#include <SDL.h>
#include<SDL_net.h>


class Game
{
private:
	//variables
	bool running;
	SDL_Window *win;
	SDL_Renderer *ren;

	//methods
	void InitEverything();
	void GetEvents();
	void Render();
	SDL_Texture* LoadImage(char* filename);



public:
	Game();
	~Game();

	//variables

	//methods
	void Run();


};