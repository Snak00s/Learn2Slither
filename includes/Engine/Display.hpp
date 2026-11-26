#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include "Button.hpp"

class Display
{
	private:
		std::vector<Button>	_button_vec;
		std::string			_name;

		int					_displayWidth;
		int					_displayHeight;

		int 				_displayCenterX;
		int					_displayCenterY;

		SDL_Color			_background_color;

	public:
		Display(std::string const name, SDL_Color const background_color);
		~Display();


		void	render(SDL_Renderer *renderer);
		void	addButton(std::string const name, SDL_FRect const button_shape, SDL_Color const background_color);
		void	addButton(std::string const name, SDL_FRect const button_shape, SDL_Color const background_color, std::function<void()> func);

		std::string const getName(void);

		std::vector<Button>	&getButtons(void){return this->_button_vec;}

};

#endif