#pragma once
#include "BasicParticle.hxx"
#include "BasicProcessor.hxx"

namespace dust {
	// Particle Processor Base for particles with any form of simple color 
	class Colored : public BasicProcessor<BasicParticle> {
	public:
		struct Particle : public BasicParticle {

			sf::Color color;
		};

		Colored(
			float lifetime,
			float rotationSpeed,
			float emmisionAngle,
			float emmisionSpread)
		:	BasicProcessor<BasicParticle>(
				lifetime,
				rotationSpeed,
				emmisionAngle,
				emmisionSpread) {}



		inline void render(Particle & particle, sf::VertexArray & vertexArray) const {
			sf::Transform transform;
			transform
				.translate(particle.position)
				.rotate(particle.rotation);
			
			vertexArray.append(sf::Vertex(
				transform.transformPoint(sf::Vector2f(
					-particle.size.x / 2.f,
					-particle.size.y / 2.f)),
				particle.color));

			vertexArray.append(sf::Vertex(
				transform.transformPoint(sf::Vector2f(
					+particle.size.x / 2.f,
					-particle.size.y / 2.f)),
				particle.color));

			vertexArray.append(sf::Vertex(
				transform.transformPoint(sf::Vector2f(
					+particle.size.x / 2.f,
					+particle.size.y / 2.f)),
				particle.color));

			vertexArray.append(sf::Vertex(
				transform.transformPoint(sf::Vector2f(
					-particle.size.x / 2.f,
					+particle.size.y / 2.f)),
				particle.color));
		}


	protected:

	};
}