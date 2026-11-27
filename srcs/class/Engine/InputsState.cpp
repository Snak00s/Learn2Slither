#include"Engine/InputsState.hpp"

InputsState::InputsState(void) : _left_click(false), _left_click_hold(false),
_right_click(false), _right_click_hold(false),
_middle_click(false), _middle_click_hold(false),
_esc_key(false), _esc_key_hold(false)
{
	return ;
}

InputsState::~InputsState()
{
	return ;
}

void	InputsState::mouseInputsDown(const Uint8 mouse_input)
{
	switch (mouse_input)
	{
		case 1:
			this->_left_click = true;
			this->_left_click_hold = true;
			break;
		case 2:
			this->_middle_click = true;
			this->_middle_click_hold = true;
			break;
		case 3:
			this->_right_click = true;
			this->_right_click_hold = true;
			break;
		
		default:
			break;
	}
}

void	InputsState::mouseInputsUp(const Uint8 mouse_input)
{
	switch (mouse_input)
	{
		case 1:
			this->_left_click = false;
			this->_left_click_hold = false;
			break;
		case 2:
			this->_middle_click = false;
			this->_middle_click_hold = false;
			break;
		case 3:
			this->_right_click = false;
			this->_right_click_hold = false;
			break;
		
		default:
			break;
	}
}

void	InputsState::updateMousePos(void)
{
	SDL_GetMouseState(&this->_mouse_state.x, &this->_mouse_state.y);
}

void	InputsState::resetInputs(bool reset_holded)
{
	this->_left_click = false;
	this->_right_click = false;
	this->_middle_click = false;
	this->_esc_key = false;

	if (reset_holded)
	{
		this->_left_click_hold = false;
		this->_right_click_hold = false;
		this->_middle_click_hold = false;
		this->_esc_key_hold = false;
	}
}

void	InputsState::keyInputsDown(const SDL_Keycode key_input)
{
	switch (key_input)
	{
		case SDLK_ESCAPE:
			this->_esc_key = true;
			break;
		
		default:
			break;
	}
}

void	InputsState::keyInputsUp(const SDL_Keycode key_input)
{
	switch (key_input)
	{
		case SDLK_ESCAPE:
			this->_esc_key = false;
			break;
		
		default:
			break;
	}
}

bool			InputsState::left_click(bool key_holded) const
{
	if (key_holded)
		return this->_left_click_hold;
	return this->_left_click;
}

bool			InputsState::right_click(bool key_holded) const
{
	if (key_holded)
		return this->_right_click_hold;
	return this->_right_click;
}

bool			InputsState::middle_click(bool key_holded) const
{
	if (key_holded)
		return this->_middle_click_hold;
	return this->_middle_click;
}

bool			InputsState::esc_key(bool key_holded) const
{
	if (key_holded)
		return this->_esc_key_hold;
	return this->_esc_key;
}

SDL_Point const	InputsState::mouse_pos(void) const
{
	return this->_mouse_state;
}
