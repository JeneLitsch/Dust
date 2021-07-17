#pragma once
#include "Dust-Colored.hxx"
#include <cmath>
namespace dust {
	template<class ColorSource>
	class MultiColor : public Colored {
	public:
		MultiColor(
			ColorSource colorSource,
			float rotationSpeed,
			float lifetime)
		:	colorSource(colorSource),
			color(color),
			Colored(rotationSpeed, lifetime) {}

		void process(Colored::Particle & particle, double dt) const {
			float arch = float(std::sin(particle.age/this->lifetime * 3.14f));
			
			particle.age += float(dt);
			particle.alive = particle.age <= lifetime;
				
			particle.position += particle.velocity * float(dt) * arch;
			
			particle.size.x = 32.f * arch;
			particle.size.y = 32.f * arch;

			particle.rotation +=  float(dt) * rotationSpeed;
			particle.color = colorSource(particle.age / this->lifetime);
		}
	private:
		const sf::Color color;
		ColorSource colorSource;
	};
}