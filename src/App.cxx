#include "App.hxx"
#include <array>
#include <memory>
#include <iostream>
#include "sfml.hxx"
#include "Dust-BasicParticleSystem.hxx"
#include "Dust-SingleColor.hxx"
#include "Dust-MultiColor.hxx"
#include "Dust-ColorInterpolate.hxx"

sf::FloatRect calcViewPort(sf::Window & window, sf::View view) {
	float aspectRatioWindow =
			float(window.getSize().x)
			/ float(window.getSize().y);

	float aspectRatioBuffer =
			float(view.getSize().x)
			/ float(view.getSize().y);

	if(aspectRatioBuffer > aspectRatioWindow){
			float relHeight = aspectRatioWindow/aspectRatioBuffer;
			float offset = (1.f - relHeight) / 2.f;
			return sf::FloatRect(0.f, offset, 1.f, relHeight);
	}
	else{
			float relWidth = aspectRatioBuffer/aspectRatioWindow;
			float offset = (1.f - relWidth) / 2.f;
			return sf::FloatRect(offset, 0.f, relWidth, 1.f);
	}
}

App::App(){
}

void App::run() {
	sf::Vector2u resolution = sf::Vector2u(1920, 1080);

	sf::RenderWindow window;
	window.create(sf::VideoMode(resolution.x, resolution.y), "Particles");
	window.setVerticalSyncEnabled(false);

	sf::Clock clock;
	sf::Time now = clock.getElapsedTime();
	sf::Time then;

	sf::RectangleShape rect;

	
	std::unique_ptr<dust::IParticleSystem> particleSystem
		= std::make_unique<
			dust::BasicParticleSystem<dust::MultiColor<dust::ColorInterpolate>, 25000>
		>(	dust::MultiColor<dust::ColorInterpolate>(dust::ColorInterpolate(sf::Color::Cyan, sf::Color::Red), 0.25, 5.0));

	particleSystem->setPosition({500.f, 500.f});
	
	double timer;
	while(window.isOpen()) {
		then = now;
		now = clock.getElapsedTime();
		double dt = (now - then).asSeconds();

		sf::Event evt;
		while(window.pollEvent(evt)) {
			if(evt.type == sf::Event::Closed){
				window.close();
			}
			if(evt.type == sf::Event::Resized){
				sf::View view = sf::View(
					sf::Vector2f(resolution)/2.f,
					sf::Vector2f(resolution));
				view.setViewport(calcViewPort(window, view));
				window.setView(view);
			}
		}
		timer += dt;
		if(timer >= 0.1) {
			particleSystem->emit(500);
			timer = 0.0;
		}

		std::cout << 1.0 / dt << std::endl;
		window.clear(sf::Color::Black);
		particleSystem->update(dt);
		particleSystem->render(window);
		window.display();
	}
}

