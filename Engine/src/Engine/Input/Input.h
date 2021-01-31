#pragma once

#include "Engine/Graphics/window.h"

namespace Engine {

	class Input
	{
	public:
		static bool IsKeyPressed(int keycode);

		static bool IsMouseButtonPressed(int keycode);
		static std::pair<float, float> GetMousePosition();
		static std::pair<float, float> GetMousePosition(Window* window);

		static float GetMouseX();
		static float GetMouseY();
		static float GetMouseX(Window* window);
		static float GetMouseY(Window* window);

	private:
		static Input* s_Instance;
	};

}
