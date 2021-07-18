#include "App.hxx"
#include <array>
#include <memory>
#include <iostream>
#include "sfml.hxx"
#include "Dust.hxx"

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

	// sf::Texture iceTexture;
	// iceTexture.loadFromFile("ice.png");
	// std::unique_ptr iceParticleSystem = std::make_unique<
	// 	dust::AutomaticParticleSystem<dust::Textured<dust::InterpolateColor>, 25000>>(
	// 		dust::Textured(
	// 			10.0, 0.5, 90.0, 45.0,
	// 			dust::InterpolateColor(sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 0))));

	// iceParticleSystem->setPosition({960.f, 540.f});
	// iceParticleSystem->setRotation(0.0);
	// iceParticleSystem->emit(0.01);
	// iceParticleSystem->getProcessor().setTexture(iceTexture);


	// sf::Texture fireTexture;
	// fireTexture.loadFromFile("fire.png");
	// std::unique_ptr fireParticleSystem = std::make_unique<
	// 	dust::AutomaticParticleSystem<dust::Textured<dust::InterpolateColor>, 25000>>(
	// 		dust::Textured(
	// 			10.0, 0.0, -90.0, 45.0,
	// 			dust::InterpolateColor(sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 0))));

	// fireParticleSystem->setPosition({960.f, 540.f});
	// fireParticleSystem->setRotation(0.0);
	// fireParticleSystem->emit(0.01);
	// fireParticleSystem->getProcessor().setTexture(fireTexture);

	std::unique_ptr particleSystem = std::make_unique<
		dust::AutomaticParticleSystem<
			
			dust::Colored<
				dust::InterpolateColor,
				dust::ConstantVelocity>, 25000>>(
			
			dust::Colored(
				10.0, 0.0, -90.0, 45.0,
				dust::InterpolateColor(sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 0)),
				dust::ConstantVelocity(100.f)));

	particleSystem->setPosition({960.f, 540.f});
	particleSystem->setRotation(0.0);
	particleSystem->emit(1.0);
	
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
			timer = 0.0;
		}

		std::cout << 1.0 / dt << std::endl;
		window.clear(sf::Color::Black);
		// iceParticleSystem->update(dt);
		// fireParticleSystem->update(dt);
		// iceParticleSystem->render(window);
		// fireParticleSystem->render(window);

		particleSystem->update(dt);
		particleSystem->render(window);
		window.display();
	}
}

