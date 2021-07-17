#pragma once
#include "sfml.hxx"
#include "Dust-BasicParticle.hxx"
namespace dust {
	class Colored {
	public:
		struct Particle : public BasicParticle {
			sf::Vector2f velocity;
			sf::Vector2f size;
			sf::Vector2f position;

			float rotation;
			sf::Color color;
		};

		Colored(
			float rotationSpeed,
			float lifetime);

		void emit(Particle & particle) const;
		void render(Particle & particle, sf::VertexArray & vertexArray) const;
	
	protected:
		const float rotationSpeed;
		const float lifetime;
	};
}