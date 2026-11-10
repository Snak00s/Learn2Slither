#include"Board.hpp"

bool	key_down(SDL_Event &event, Snake &snake)
{
	bool moved = 1;
	switch(event.key.keysym.sym)
	{
		case SDLK_w:
			snake.move(Snake_dir::MOVE_UP);
			break;
		case SDLK_a:
			snake.move(Snake_dir::MOVE_LEFT);
			break;
		case SDLK_s:
			snake.move(Snake_dir::MOVE_DOWN);
			break;
		case SDLK_d:
			snake.move(Snake_dir::MOVE_RIGHT);
			break;
		default:
			moved = 0;
			break;
	}
	return(moved)
}