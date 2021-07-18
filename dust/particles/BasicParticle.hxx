#pragma once
#include "sfml.hxx"
namespace dust {
	struct BasicParticle {

		inline operator bool() const {
			return alive;
		}
		bool alive = false;
		float age = 0.f;
		float lifetime = 0.f;
		float rotation = 0.f;
		float scale = 1.f;

		sf::Vector2f position = sf::Vector2f(0.f, 0.f);
		sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
		sf::Vector2f size = sf::Vector2f(1.f, 1.f);

		sf::Color color = sf::Color::White;
	};
}