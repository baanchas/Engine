#pragma once


namespace Engine {

	class OrthographicCamera
	{
	public:
		OrthographicCamera();
		OrthographicCamera(float sizeX, float sizeY);
		~OrthographicCamera();

		void Move(float x, float y);
		void Move(sf::Vector2f vec2f);
		
		void SetSize(float x, float y);

		void Zoom(float factor);

		void Rotate(float angle);
		
		void SetCenter(float x, float y);
		void SetCenter(sf::Vector2f vec2f);

		inline void GetCenter() const;


		inline sf::View GetCamera() const { return m_View; }
	public:
		float speed = 3.0f;

		sf::View m_View;
	private:
	};

}