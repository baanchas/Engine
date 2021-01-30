#include "enpch.h"
#include "Input.h"

namespace Engine {

	Input* Input::s_Instance = new Input();

	bool Input::IsKeyPressed(int keycode)
	{
		return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keycode);
	}

	bool Input::IsMouseButtonPressed(int keycode)
	{
		return sf::Mouse::isButtonPressed((sf::Mouse::Button)keycode);
	}

	std::pair<float, float>  Input::GetMousePosition()
	{
		return { sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };
	}

	float Input::GetMouseX()
	{
		return sf::Mouse::getPosition().x;
	}

	float Input::GetMouseY()
	{
		return sf::Mouse::getPosition().y;
	}

}