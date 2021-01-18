#pragma once


namespace Engine {

	class OrthographicCameraComponent
	{
	public:
		OrthographicCameraComponent();
		OrthographicCameraComponent(float sizeX, float sizeY);
		~OrthographicCameraComponent();

		void OnEvent(sf::Event& event);
		void OnUpdate(float& ts);

		void SetSize(float x, float y);

		inline sf::View GetCamera() const { return m_View; }

	public:
		sf::View m_View;
		void CalculateView(float x, float y);

	private:
		sf::Vector2f m_oldCenter = m_View.getCenter();

		float m_OldWidth = 1280;
		float m_OldHeight = 720;
		float m_zoomLevel = 1.0f;
		float speed = 3.0f;
	};

}