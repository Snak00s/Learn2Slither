#include "Engine/Display.hpp"

Display::Display(std::string const name, SDL_Color const background_color) : _name(name)
{
	this->_background_color.a = background_color.a;
	this->_background_color.r = background_color.r;
	this->_background_color.g = background_color.g;
	this->_background_color.b = background_color.b;

	return ;
}

Display::~Display()
{
	return ;
}

void	Display::addButton(std::string const name, SDL_Rect const button_shape, SDL_Color const background_color, std::function<void()> func)
{
	this->_button_vec.emplace_back(name, button_shape, background_color, func);
	return ;
}

void	Display::addButton(std::string const name, SDL_Rect const button_shape, SDL_Color const background_color)
{
	this->_button_vec.emplace_back(name, button_shape, background_color);
	return ;
}

void	Display::render(SDL_Renderer *renderer)
{
	for (auto &button : this->_button_vec)
	{
		button.render(renderer);
	}
	SDL_SetRenderDrawColor(renderer, this->_background_color.r,
									this->_background_color.g,
									this->_background_color.b,
									this->_background_color.a);
	SDL_RenderPresent(renderer);
}

std::string const Display::getName(void)
{
	return this->_name;
}