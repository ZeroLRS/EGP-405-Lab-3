#include "InputManager.h"
#include <Windows.h>

InputManager::InputManager()
{
	
	std::fill(state.begin(), state.end(), 0);
	std::fill(prevState.begin(), prevState.end(), 0);
}

InputManager::~InputManager()
{}


void InputManager::updateKeyStates()
{
	for (int i = 0; i < 256; ++i)
	{
		prevState[i] = state[i];

		state[i] = GetAsyncKeyState(i);
	}
}

/* V CODES: http://www.quickmacros.com/help/Tables/IDP_VIRTUALKEYS.html */
bool InputManager::getKeyDown(int _vCode)
{
	if (!prevState[_vCode])
		if (state[_vCode])
			return true;

	return false;
}

bool InputManager::getKey(int _vCode)
{
	return state[_vCode];
}

bool InputManager::getKeyUp(int _vCode)
{
	if (prevState[_vCode])
		if (!state[_vCode])
			return true;

	return false;
}