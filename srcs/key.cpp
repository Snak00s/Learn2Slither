#include"Board.hpp"

Snake_dir	key_down(SDL_Event &event)
{
	switch(event.key.keysym.sym)
	{
		case SDLK_w:
			return(Snake_dir::MOVE_UP);
		case SDLK_a:
			return(Snake_dir::MOVE_LEFT);
		case SDLK_s:
			return(Snake_dir::MOVE_DOWN);
		case SDLK_d:
			return(Snake_dir::MOVE_RIGHT);
		default:
			return(Snake_dir::MOVE_NONE);
	}
	return(Snake_dir::MOVE_NONE);
}