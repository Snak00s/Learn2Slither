#ifndef BUTTON_HPP
# define BUTTON_HPP

#include"main.hpp"

class Button
{
	private:
		SDL_FRect				_button_rect;
		std::string				_name;
		SDL_Color				_background_color;
		std::function<void()>	_func;

	public:
		// Button(std::string const name, const float pos_x, const float pos_y, const float len_x, const float len_y);
		Button(std::string const name, SDL_FRect const button_shape, SDL_Color const background_color);
		Button(std::string const name, SDL_FRect const button_shape, SDL_Color const background_color, std::function<void()> func);
		~Button();

		void	render(SDL_Renderer *renderer);
};

#endif