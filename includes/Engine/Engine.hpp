#ifndef ENGINE_HPP
# define ENGINE_HPP

#include"main.hpp"
#include"Display.hpp"

class Engine
{
	private:
		SDL_Renderer												*_renderer;
		SDL_Window													*_win;
		SDL_Event													_event;
		SDL_DisplayMode												_display_config;

		SDL_Point													_mouse_state;
		bool														_left_click;

		int															_displayWidth;
		int															_displayHeight;

		std::unordered_map<std::string, std::shared_ptr<Display>>	_display_vec;
		std::shared_ptr<Display>									_current_display;
		SDL_Texture													*_loadTexture(std::string path, int &imgW, int &imgH);

	public:
		Engine(void);
		~Engine();

		std::shared_ptr<Display>	addDisplay(std::string const display_name, SDL_Color const background_color);
		void						addDisplayButton(std::string const display_name, std::string const name, SDL_Rect const button_shape, SDL_Color const background_color);
		void						addDisplayButton(std::string const display_name, std::string const name, SDL_Rect const button_shape, SDL_Color const background_color, std::function<void ()> func);
		void						addCurrentDisplayButton(std::string const name, SDL_Rect const button_shape, SDL_Color const background_color);

		int							event(void);
		int							action(void);
		int							renderClear(void);
		void						render(void);

		SDL_Renderer				*getRenderer(void);
		SDL_Window					*getWindow(void);
		SDL_Event					&getEvent(void);
		std::shared_ptr<Display>	getCurrentDisplay(void);

		int							getDisplayWidth(void);
		int							getDisplayHeight(void);

		void			setCurrentDisplay(std::string const name);

		class DisplayCreationError : public std::exception
		{
		protected:
			std::string _error;
		public:
			DisplayCreationError(std::string name) { this->_error = "Error : DisplayCreationError \'" + name + "\'."; };
			~DisplayCreationError() = default;
			virtual const char *what() const throw() { return (this->_error.c_str()); }
		};

		class DisplayNotFoundedError : public std::exception
		{
		protected:
			std::string _error;
		public:
			DisplayNotFoundedError(std::string name) { this->_error = "Error : DisplayNotFoundedError \'" + name + "\'."; };
			~DisplayNotFoundedError() = default;
			virtual const char *what() const throw() { return (this->_error.c_str()); }
		};
};

#endif