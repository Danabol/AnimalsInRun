#include <SDL.h>
#include <SDL_net.h>
#include <string>



class Game
{
private:
	const static int DEFAULT_WINDOW_WIDTH = 360;
	const static int DEFAULT_WINDOW_HEIGHT = 480;

	//variables
	bool running;
	SDL_Window *win;
	SDL_Renderer *ren;
	IPaddress ip;
	TCPsocket server ;
	TCPsocket client;

	//methods
	void InitEverything();
	void GetEvents();
	void Render();
	void Server();
	SDL_Texture* LoadImage(const std::string& filename);

public:
	Game(const std::string& title);
	~Game();

	//variables

	//methods
	void Run();
};

void LogSdlError(const std::string& msg);