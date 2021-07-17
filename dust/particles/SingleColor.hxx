#pragma once
#include "Colored.hxx"
namespace dust {
	// Particle processor for simple single colored particles
	class SingleColor : public Colored {
	public:
		SingleColor(
			float lifetime,
			float rotationSpeed,
			float emmisionAngle,
			float emmisionSpread,
			sf::Color color)
		:	color(color),
			Colored(
				lifetime,
				rotationSpeed,
				emmisionAngle,
				emmisionSpread) {}

		inline void process(Colored::Particle & particle, double dt) const{
			Colored::process(particle, dt);
			particle.color = this->color;
		}
	private:
		const sf::Color color;
	};
}