#ifndef BUTTON_HPP
# define BUTTON_HPP

#include"main.hpp"

class Button
{
	private:
		std::string				_name;

		SDL_Rect				_button_rect;
		SDL_Color				_background_color;

		std::string				_button_text;
		SDL_Color				_text_color;
		SDL_Texture				*_text_texture;
		SDL_Rect				_text_rect;

		std::function<void()>	_func;

	public:
		// Button(std::string const name, const float pos_x, const float pos_y, const float len_x, const float len_y);
		Button(std::string const name, SDL_Renderer *renderer,
			std::string const button_text, SDL_Color const text_color, TTF_Font *text_font,
			SDL_Rect const button_shape, SDL_Color const background_color, std::function<void()> func);
		~Button();

		void	render(SDL_Renderer *renderer);
		void	click(void);

		SDL_Rect const *getRect(void) const;
};

#endif