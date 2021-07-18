#pragma once
#include "BasicParticle.hxx"
#include "BasicProcessor.hxx"

namespace dust {
	// Particle Processor Base for particles with any form of simple color 
	template<
		class ColorSource,
		class TVelocity>
	class Colored : public BasicProcessor<BasicParticle, TVelocity> {
	public:
		struct Particle : public BasicParticle {

			sf::Color color;
		};

		Colored(
			float lifetime,
			float rotationSpeed,
			float emmisionAngle,
			float emmisionSpread,
			const ColorSource & colorSource,
			const TVelocity & velocity)
		:	BasicProcessor<BasicParticle, TVelocity>(
				lifetime,
				rotationSpeed,
				emmisionAngle,
				emmisionSpread,
				velocity),
			colorSource(colorSource) {}


		inline void process(Colored::Particle & particle, double dt) const {
			BasicProcessor<BasicParticle, TVelocity>::process(particle, dt);
			particle.color = colorSource(particle.age / this->lifetime);
		}


		// Add vertecies of a colored particle to vertexArray
		inline void render(Particle & particle, sf::VertexArray & vertexArray) const {
			sf::Transform transform;
			transform
				.translate(particle.position)
				.rotate(particle.rotation);

			const float down = 0.5 * particle.size.x;
			const float top = -down;
			const float right = 0.5 * particle.size.y;
			const float left = -right;
		
			vertexArray.append(sf::Vertex(
				transform.transformPoint(top, left),
				particle.color));

			vertexArray.append(sf::Vertex(
				transform.transformPoint(top, right),
				particle.color));

			vertexArray.append(sf::Vertex(
				transform.transformPoint(down, right),
				particle.color));

			vertexArray.append(sf::Vertex(
				transform.transformPoint(down, left),
				particle.color));
		}

	protected:
		ColorSource colorSource;
	};
}