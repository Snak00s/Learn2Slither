#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include "Button.hpp"
#include "InputsState.hpp"

class Display
{
	private:
		std::unordered_map<std::string, Button>	_button_vec;
		std::string			_name;

		int					_displayWidth;
		int					_displayHeight;

		int 				_displayCenterX;
		int					_displayCenterY;

		SDL_Color			_background_color;

		void				_clickAction(SDL_Point const &mouse_pos);

	public:
		Display(std::string const name, SDL_Color const background_color);
		~Display();


		void	render(SDL_Renderer *renderer);
		void	addButton(std::string const name, SDL_Renderer *renderer, std::string const button_text, SDL_Color const text_color, TTF_Font *text_font, SDL_Rect const button_shape, SDL_Color const background_color, std::function<void()> func);
		void	generalAction(InputsState &inputs_state);


		std::string const getName(void);
};

#endif