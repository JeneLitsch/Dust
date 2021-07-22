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

	sf::Texture fireTexture;
	fireTexture.loadFromFile("ice.png");

	std::unique_ptr particleSystem = std::make_unique<
		dust::AutomaticParticleSystem<
			250, dust::BasicParticle,
			dust::policy::EmitPolar<4>,
			dust::policy::ColorLinear,
			dust::policy::MovementFloating,
			dust::policy::RotationConstant,
			dust::policy::ScaleParabola,
			dust::policy::RenderTexture
		>>();


	particleSystem->configColor(sf::Color::Cyan, sf::Color(64, 0, 128));
	particleSystem->configRender(fireTexture);
	particleSystem->configLifetime(2.f);
	// particleSystem->configEmitAngle(90.f, 180.0);
	particleSystem->configEmitSpeed(128.f, 1.0f);
	particleSystem->configEmitRotation(0.0, 360.0);
	particleSystem->configEmitPoles({0, 90, 180, 270}, 10.0);
	// particleSystem->configEmitRect(sf::Vector2f(1920, 0));
	// particleSystem->configEmitCircle(256.f);
	particleSystem->configRotation(46.f);
	particleSystem->configScale(0.f, 1.f);
	particleSystem->configGravity(180.f, 100.f);
	particleSystem->configMovement(0.5f);
	particleSystem->configWiggle(1.f, 1.f);
	// particleSystem->configMovement(0.25f);

	particleSystem->setPosition({960.f, 540.f});
	particleSystem->setRotation(0.0);
	particleSystem->emit(1.0);
	// particleSystem->setTickLimit(60);
	
	// particleSystem->start();

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

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			return;
		}
		// particleSystem->rotatePoles(180.f * float(dt));

		std::cout << 1.0 / dt << std::endl;
		particleSystem->update(dt);

		window.clear(sf::Color::Black);
		particleSystem->render(window);
		window.display();
	}
}

