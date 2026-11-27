#ifndef INPUTSSTATE_HPP
# define INPUTSSTATE_HPP

# include"main.hpp"

class InputsState
{
	private:
		bool		_left_click;
		bool		_left_click_hold;

		bool		_right_click;
		bool		_right_click_hold;

		bool		_middle_click;
		bool		_middle_click_hold;

		bool		_esc_key;
		bool		_esc_key_hold;

		SDL_Point	_mouse_state;

	public:
		InputsState();
		~InputsState();

		void	mouseInputsDown(const Uint8 mouse_input);
		void	mouseInputsUp(const Uint8 mouse_input);
		void	updateMousePos(void);
		void	resetInputs(bool reset_holded);

		void	keyInputsDown(const SDL_Keycode key_input);
		void	keyInputsUp(const SDL_Keycode key_input);

		bool				left_click(bool key_holded) const;
		bool				right_click(bool key_holded) const;
		bool				middle_click(bool key_holded) const;
		bool				esc_key(bool key_holded) const;
		SDL_Point const		mouse_pos(void) const;
};

#endif