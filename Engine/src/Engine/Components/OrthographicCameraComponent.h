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

		void SetCenter(float x, float y);
		void SetCenter(sf::Vector2f vec);

		void SetRotation(float r);

		void ZoomIn();
		void ZoomOut();

		inline sf::View GetCamera() const { return m_View; }

		void CalculateView(float x, float y);
		void CalculateView(sf::Vector2f vec);

		float GetZoom() { return m_zoomLevel; }

	public:
		sf::View m_View;
		float m_zoomLevel = 1.0f;

	private:
		sf::Vector2f m_oldCenter = m_View.getCenter();

		float speed = 10.0f;
	};

}