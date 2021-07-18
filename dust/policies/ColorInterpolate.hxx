#pragma once
#include "sfml.hxx"
#include <cmath>

namespace dust {
	namespace policy {
		class ColorInterpolate {
		public:
			inline void operator()(auto & particle) const {
				particle.color = sf::Color(
					static_cast<std::uint8_t>(std::lerp(colorA.r, colorB.r, particle.age / 5.0)),
					static_cast<std::uint8_t>(std::lerp(colorA.g, colorB.g, particle.age / 5.0)),
					static_cast<std::uint8_t>(std::lerp(colorA.b, colorB.b, particle.age / 5.0)),
					static_cast<std::uint8_t>(std::lerp(colorA.a, colorB.a, particle.age / 5.0)));
			}

			void configColor(sf::Color colorA, sf::Color colorB) {
				this->colorA = colorA;
				this->colorB = colorB;
			}

		private:
			sf::Color colorA = sf::Color::White;
			sf::Color colorB = sf::Color::White;
		};
	}
}