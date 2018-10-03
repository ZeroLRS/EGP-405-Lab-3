#pragma once
#include <array>

class InputManager
{
private:
	std::array<unsigned short, 256> state;
	std::array<unsigned short, 256> prevState;


public:
	InputManager();
	~InputManager();

	void updateKeyStates();

	/* V CODES: http://www.quickmacros.com/help/Tables/IDP_VIRTUALKEYS.html */
	bool getKeyDown(int _vCode);
	bool getKey(int _vCode);
	bool getKeyUp(int _vCode);
};