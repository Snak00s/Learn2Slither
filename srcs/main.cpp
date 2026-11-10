#include"Board.hpp"

// W = wall
// H = snake head
// S = snake body segment
// G = green apple
// R = red apple
// 0 = empty space

bool	key_down(SDL_Event &event, Snake &snake);

void	clear()
{
	std::cout << "[H[2J[3J" << std::endl;
	return ;
}

int init_sdl(SDL_Window **win, SDL_Renderer **renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init : " << SDL_GetError() << std::endl;
		return (1);
	}

	int n = SDL_GetNumRenderDrivers();
	for (int i = 0; i < n; i++)
	{
		SDL_RendererInfo	openInfo;
		SDL_GetRenderDriverInfo(i, &openInfo);
		std::string name(openInfo.name);
		if (name == "opengles2")
		{
			n = i;
			break;
		}
	}

	*win = SDL_CreateWindow(
        "Feur", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        400, 300, 
        SDL_WINDOW_SHOWN
    );
	if (!win)
	{
		std::cout << "Window : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return (0);
	}
	*renderer = SDL_CreateRenderer(*win, n, SDL_RENDERER_ACCELERATED);
	if (!*renderer) {
		std::cout << "Render could not be created because of WebGl, please restart your web browser." << std::endl;
		SDL_DestroyWindow(*win);
		SDL_Quit();
		return (0);
	}
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	SDL_EventState(SDL_KEYUP, SDL_ENABLE);
	return (1);
}

int main(int argc, char **argv)
{
	std::srand(time(0));
	(void)argc, (void)argv;
	Board board(10, 10);

	SDL_Renderer	*renderer;
	SDL_Window		*win;

	if (!init_sdl(&win, &renderer))
		return(1);

	SDL_Event event;
	bool running = 1;
	while(running)
	{
		clear();
		bool moved = 0;
		(void)moved;
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) {
				running = false;
			}
			if (event.type == SDL_KEYDOWN)
				moved = key_down(event, board.getNoConstSnake());
		}
		SDL_RenderPresent(renderer);
		std::cout << board << std::endl;
		SDL_Delay(10);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return(0);
}