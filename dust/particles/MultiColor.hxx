#pragma once
#include "Colored.hxx"
namespace dust {
	// Particle Processor for particles with changing color
	template<class ColorSource>
	class MultiColor : public Colored {
	public:
		MultiColor(
			float lifetime,
			float rotationSpeed,
			float emmisionAngle,
			float emmisionSpread,
			ColorSource colorSource)
		:	colorSource(colorSource),
			color(color),
			Colored(
				lifetime,
				rotationSpeed,
				emmisionAngle,
				emmisionSpread) {}

		inline void process(Colored::Particle & particle, double dt) const {
			Colored::process(particle, dt);
			particle.color = colorSource(particle.age / this->lifetime);
		}
	private:
		const sf::Color color;
		ColorSource colorSource;
	};
}