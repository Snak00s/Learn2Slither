#include"Game.hpp"

Snake_dir	key_down(SDL_Event &event);

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
	SDL_Renderer	*renderer;
	SDL_Window		*win;

	if (!init_sdl(&win, &renderer))
		return(1);

	Game	game(10, 10);

	Snake	&snake = game.getSnake();
	SDL_Event event;
	bool running = 1;
	while(running)
	{
		Snake_dir move = Snake_dir::MOVE_NONE;
		clear();
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) {
				running = false;
			}
			if (event.type == SDL_KEYDOWN)
				move = key_down(event);
		}
		if (move != Snake_dir::MOVE_NONE)
			game.playTurn(move);
		SDL_RenderPresent(renderer);
		print_board_vec(snake.getSnakeVision());
		std::cout << "North : ";
		print_board_row(snake.getNorthVision());
		std::cout << "South : ";
		print_board_row(snake.getSouthVision());
		std::cout << "East : ";
		print_board_row(snake.getEastVision());
		std::cout << "West : ";
		print_board_row(snake.getWestVision());
		SDL_Delay(10);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return(0);
}