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

void	Display::addButton(std::string const name, SDL_Renderer *renderer, std::string const button_text, SDL_Color const text_color, TTF_Font *text_font, SDL_Rect const button_shape, SDL_Color const background_color, std::function<void()> func)
{
	this->_button_vec.try_emplace(name, name, renderer, button_text, text_color, text_font, button_shape, background_color, func);
	return ;
}

void	Display::render(SDL_Renderer *renderer)
{
	for (auto &button : this->_button_vec)
	{
		button.second.render(renderer);
	}
	SDL_SetRenderDrawColor(renderer, this->_background_color.r,
									this->_background_color.g,
									this->_background_color.b,
									this->_background_color.a);
	SDL_RenderPresent(renderer);
}

void	Display::_clickAction(SDL_Point const &mouse_pos)
{
	auto but = std::find_if(this->_button_vec.begin(), this->_button_vec.end(),
	[mouse_pos](auto &b)
	{ return SDL_PointInRect(&mouse_pos, b.second.getRect()) == SDL_TRUE; });

	if (but != this->_button_vec.end())
		but->second.click();
	return ;
}

void	Display::generalAction(InputsState &inputs_state)
{
	if (inputs_state.left_click(false))
		this->_clickAction(inputs_state.mouse_pos());
}

std::string const Display::getName(void)
{
	return this->_name;
}