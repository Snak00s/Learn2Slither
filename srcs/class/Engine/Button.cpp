#include"Engine/Button.hpp"


Button::Button(std::string const name, SDL_Renderer *renderer,
	std::string const button_text, SDL_Color const text_color, TTF_Font *text_font,
	SDL_Rect const button_shape, SDL_Color const background_color, std::function<void()> func) : _name(name), _button_text(button_text), _func(func)
{
	this->_button_rect = { button_shape.x, button_shape.y, button_shape.w, button_shape.h };

	this->_background_color.a = background_color.a;
	this->_background_color.r = background_color.r;
	this->_background_color.g = background_color.g;
	this->_background_color.b = background_color.b;

	this->_text_color.a = text_color.a;
	this->_text_color.r = text_color.r;
	this->_text_color.g = text_color.g;
	this->_text_color.b = text_color.b;

	SDL_Surface *surface = TTF_RenderUTF8_Blended(text_font, button_text.c_str(), text_color);
	if (!surface)
	{
		std::cerr << "TTF_RenderText_Solid : " << TTF_GetError() << std::endl;
		throw std::runtime_error("");
	}

	this->_text_texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!this->_text_texture)
	{
		std::cerr << "SDL_CreateTextureFromSurface : " << SDL_GetError() << std::endl;
		throw std::runtime_error("");
	}


    this->_text_rect.w = surface->w;
    this->_text_rect.h = surface->h;
    this->_text_rect.x = this->_button_rect.x + (this->_button_rect.w - this->_text_rect.w) / 2;
    this->_text_rect.y = this->_button_rect.y + (this->_button_rect.h - this->_text_rect.h) / 2;

	SDL_FreeSurface(surface);

	return ;
}

Button::~Button()
{
	std::cout << this->_name << std::endl;
	SDL_DestroyTexture(this->_text_texture);
	return ;
}

void	Button::render(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, this->_background_color.r, this->_background_color.g, this->_background_color.b, this->_background_color.a);
	SDL_RenderFillRect(renderer, &this->_button_rect);

	// std::cout << this->_name << ' '<< this->_text_rect.y << std::endl;
	SDL_RenderCopy(renderer, this->_text_texture, NULL, &this->_text_rect);

	// SDL_RenderDrawRectF(renderer, &this->_button_rect);
	return ;
}

void	Button::click(void)
{
	this->_func();
}

SDL_Rect const *Button::getRect(void) const
{
	return &this->_button_rect;
}