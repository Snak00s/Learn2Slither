#include"Engine/Button.hpp"


// Button::Button(std::string const name, const float pos_x, const float pos_y, const float len_x, const float len_y) : _name(name)
// {
// 	this->_button_rect = { pos_x, pos_y, len_x, len_y };
// 	return ;
// }

Button::Button(std::string const name, SDL_Rect const button_shape, SDL_Color const background_color) : _name(name)
{
	this->_button_rect = { button_shape.x, button_shape.y, button_shape.w, button_shape.h };

	this->_background_color.a = background_color.a;
	this->_background_color.r = background_color.r;
	this->_background_color.g = background_color.g;
	this->_background_color.b = background_color.b;
	return ;
}

Button::Button(std::string const name, SDL_Rect const button_shape, SDL_Color const background_color, std::function<void()> func) : _name(name), _func(func)
{
	this->_button_rect = { button_shape.x, button_shape.y, button_shape.w, button_shape.h };

	this->_background_color.a = background_color.a;
	this->_background_color.r = background_color.r;
	this->_background_color.g = background_color.g;
	this->_background_color.b = background_color.b;
	return ;
}

Button::~Button()
{
	return ;
}

void	Button::render(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, this->_background_color.r, this->_background_color.g, this->_background_color.b, this->_background_color.a);
	SDL_RenderFillRect(renderer, &this->_button_rect);
	// SDL_RenderDrawRectF(renderer, &this->_button_rect);
	return ;
}