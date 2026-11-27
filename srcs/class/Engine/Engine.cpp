#include "Engine/Engine.hpp"

Engine::Engine(void) : _running(false), _mouse_state({0, 0}), _display_vec({{"Default", std::make_shared<Display>("Default", (SDL_Color){0, 0, 0, 0})}}),
	_current_display(this->_display_vec["Default"])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL_Init : " << SDL_GetError() << std::endl;
		throw std::runtime_error("");
	}

	if (TTF_Init() != 0)
	{
		std::cerr << "TTF_Init : " << TTF_GetError() << std::endl;
		throw std::runtime_error("");
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
		std::cerr << "Display : " << SDL_GetError() << std::endl;
		throw std::runtime_error("");
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
		std::cerr << "Window : " << SDL_GetError() << std::endl;
		TTF_Quit();
		SDL_Quit();
		throw std::runtime_error("");
	}

	this->_renderer = SDL_CreateRenderer(this->_win, n, SDL_RENDERER_ACCELERATED);
	if (!this->_renderer) {
		std::cerr << "Render :" << SDL_GetError() << std::endl;
		TTF_Quit();
		SDL_DestroyWindow(this->_win);
		SDL_Quit();
		throw std::runtime_error("");
	}
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	SDL_EventState(SDL_KEYUP, SDL_ENABLE);
	this->_font = TTF_OpenFont("ttf_font/04B_03__.TTF", 32);
	if (this->_font == NULL) {
		std::cerr << "TTF_Font :" << TTF_GetError() << std::endl;
		throw std::runtime_error("");
	}
}

int		Engine::start(void)
{
	this->_running = true;
	while(this->_running == true)
	{
		this->event();
		this->displayAction();
		this->renderClear();
		this->render();
	}
	return (1);
}

void	Engine::quit(void)
{
	this->_running = false;
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
	TTF_Quit();
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

void	Engine::addDisplayButton(std::string const display_name, std::string const name, SDL_Renderer *renderer, std::string const button_text, SDL_Color const text_color, TTF_Font *text_font, SDL_Rect const button_shape, SDL_Color const background_color, std::function<void ()> func)
{
	if (this->_display_vec.find(display_name) == this->_display_vec.end())
		throw DisplayNotFoundedError(display_name);
	this->_display_vec[display_name]->addButton(name, renderer, button_text, text_color, text_font, button_shape, background_color, func);
	return ;
}

void	Engine::addCurrentDisplayButton(std::string const name, SDL_Renderer *renderer, std::string const button_text, SDL_Color const text_color, TTF_Font *text_font, SDL_Rect const button_shape, SDL_Color const background_color, std::function<void ()> func)
{
	this->_current_display->addButton(name, renderer, button_text, text_color, text_font, button_shape, background_color, func);
	return ;
}

int	Engine::event(void)
{
	this->_inputs_state.updateMousePos();
	this->_inputs_state.resetInputs(false);
	while (SDL_PollEvent(&this->_event))
	{
		switch (this->_event.type)
		{
			case SDL_QUIT:
				this->_running = false;
				break;
			case SDL_KEYDOWN:
				this->_inputs_state.keyInputsDown(this->_event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				this->_inputs_state.keyInputsUp(this->_event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->_inputs_state.mouseInputsDown(this->_event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				this->_inputs_state.mouseInputsUp(this->_event.button.button);
				break;
			
			default:
				break;
		}
	}
	return (1);
}

int	Engine::displayAction(void)
{
	this->_current_display->generalAction(this->_inputs_state);
	return (1);
}

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
TTF_Font		*Engine::getFont(void) { return this->_font; }
