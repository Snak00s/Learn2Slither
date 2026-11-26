#include "Engine/Engine.hpp"

Engine::Engine(void) : _mouse_state({0, 0}), _left_click(false), _display_vec({{"Default", std::make_shared<Display>("Default", (SDL_Color){0, 0, 0, 0})}}),
	_current_display(this->_display_vec["Default"])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init : " << SDL_GetError() << std::endl;
		exit(1);
	}
	int n = SDL_GetNumRenderDrivers();
	for (int i = 0; i < n; i++)
	{
		SDL_RendererInfo	openInfo;
		SDL_GetRenderDriverInfo(i, &openInfo);
		std::string name(openInfo.name);
		if (name == "opengles2")
		{
			n = i;
			break;
		}
	}
	if (SDL_GetDesktopDisplayMode(0, &this->_display_config) != 0)
	{
		std::cout << "Display : " << SDL_GetError() << std::endl;
		exit(1);
	}

	this->_displayWidth = this->_display_config.w / 2;
	this->_displayHeight = this->_display_config.h / 2;

	this->_win = SDL_CreateWindow(
		"Learn2Slither",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->_displayWidth, this->_displayHeight,
		SDL_WINDOW_SHOWN
	);

	if (!this->_win)
	{
		std::cout << "Window : " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
	this->_renderer = SDL_CreateRenderer(this->_win, n, SDL_RENDERER_ACCELERATED);
	if (!this->_renderer) {
		std::cout << "Render :" << SDL_GetError() << std::endl;
		SDL_DestroyWindow(this->_win);
		SDL_Quit();
		exit(1);
	}
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	SDL_EventState(SDL_KEYUP, SDL_ENABLE);
}

SDL_Texture	*Engine::_loadTexture(std::string path, int &imgW, int &imgH)
{

	//we firs need to load the image into a surface
	SDL_Surface *image = SDL_LoadBMP(path.c_str());
	if (!image)
	{
		std::string	error = "Image " + path + " load failed ! SDL_Error: " + SDL_GetError();
		throw std::runtime_error(error);
	}

	//convert it into texture
	SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_renderer, image);
	if (!texture)
	{
		SDL_FreeSurface(image);
		std::string error = "Texture " + path + " conversion failed ! SDL_Error:" + SDL_GetError();
		throw std::runtime_error(error);
	}

	imgW = image->w;
	imgH = image->h;

	//dont need surface anymore after conversion
	SDL_FreeSurface(image);
	return (texture);
}

Engine::~Engine()
{
	SDL_DestroyRenderer(this->_renderer);
	SDL_DestroyWindow(this->_win);
	SDL_Quit();
	return ;
}

std::shared_ptr<Display>	Engine::addDisplay(std::string const name, SDL_Color const background_color)
{
	auto new_display_pair = this->_display_vec.try_emplace(name, std::make_shared<Display>(name, background_color));

	if (new_display_pair.second == false)
		throw DisplayCreationError(name);
	else
		return (new_display_pair.first->second);
}

void	Engine::addDisplayButton(std::string const display_name, std::string const name, SDL_FRect const button_shape, SDL_Color const background_color)
{
	if (this->_display_vec.find(display_name) == this->_display_vec.end())
		throw DisplayNotFoundedError(display_name);
	this->_display_vec[name]->addButton(name, button_shape, background_color);
	return ;
}

void	Engine::addDisplayButton(std::string const display_name, std::string const name, SDL_FRect const button_shape, SDL_Color const background_color, std::function<void ()> func)
{
	if (this->_display_vec.find(display_name) == this->_display_vec.end())
		throw DisplayNotFoundedError(display_name);
	this->_display_vec[name]->addButton(name, button_shape, background_color, func);
	return ;
}

void	Engine::addCurrentDisplayButton(std::string const name, SDL_FRect const button_shape, SDL_Color const background_color)
{
	this->_current_display->addButton(name, button_shape, background_color);
	return ;
}

int	Engine::event(void)
{
	while (SDL_PollEvent(&this->_event))
	{
		if (this->_event.type == SDL_QUIT)
			return (0);
		else if (this->_event.type == SDL_KEYDOWN)
		{
			if (this->_event.key.keysym.sym == SDLK_ESCAPE)
				return (0);
		}
		else if (this->_event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (this->_event.button.button == 1) // 1 = lclick, 2 = scroll click, 3 = right click
				this->_left_click = true;
		}
		else if (this->_event.type == SDL_MOUSEBUTTONUP)
		{
			if (this->_event.button.button == 1)
				this->_left_click = false;
		}
	}
	return (1);
}

// int	Engine::action(void)
// {
// 	auto &actual = this->getCurrentDisplay()->getButtons();
// 	if (this->_left_click)
// 	{
// 		std::find_if(actual.begin(), actual.end(), SDL_PointInRect(static_cast<SDL_FPoint>(&this->_mouse_state), [](){}))
// 	}
// }

int		Engine::renderClear(void)
{
	return (SDL_RenderClear(this->_renderer));
}

void	Engine::render(void)
{
	this->_current_display->render(this->_renderer);
}

void	Engine::setCurrentDisplay(std::string const name)
{
	if (this->_display_vec.find(name) == this->_display_vec.end())
		throw DisplayNotFoundedError(name);
	this->_current_display = this->_display_vec[name];
	return ;
}

std::shared_ptr<Display>	Engine::getCurrentDisplay(void) { return this->_current_display; }

SDL_Window		*Engine::getWindow(void) { return this->_win; }
SDL_Renderer	*Engine::getRenderer(void) { return this->_renderer; }
SDL_Event		&Engine::getEvent(void) { return this->_event; }

int				Engine::getDisplayWidth(void) { return this->_displayWidth; }
int				Engine::getDisplayHeight(void) { return this->_displayHeight; }
