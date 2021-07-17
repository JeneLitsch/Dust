#pragma once
#include "Dust-Colored.hxx"
namespace dust {
	class SingleColor : public Colored {
	public:
		SingleColor(
			sf::Color color,
			float rotationSpeed,
			float lifetime);

		void process(Colored::Particle & particle, double dt) const;
	private:
		const sf::Color color;
	};
}