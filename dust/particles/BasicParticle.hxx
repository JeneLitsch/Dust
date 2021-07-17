#pragma once

namespace dust {
	// A basic particle
	struct BasicParticle {
		// Particle evaluates to true if alive
		inline operator bool() const {	return this->alive;	}

		bool alive = false;
		float age = 0.0;
		sf::Vector2f velocity;
		sf::Vector2f size;
		sf::Vector2f position;

		float rotation;
	};
};