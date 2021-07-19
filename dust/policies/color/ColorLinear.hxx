#pragma once
#include "sfml.hxx"
#include <cmath>

namespace dust {
	namespace policy {
		// Linear interpolation of color over lifetime of particle
		class ColorLinear {
		public:
			void configColor(sf::Color colorA, sf::Color colorB) {
				this->colorA = colorA;
				this->colorB = colorB;
			}

		protected:
			inline void operator()(auto & particle) const {
				const float progress = particle.age / particle.lifetime;
				particle.color = sf::Color(
					static_cast<std::uint8_t>(std::lerp(colorA.r, colorB.r, progress)),
					static_cast<std::uint8_t>(std::lerp(colorA.g, colorB.g, progress)),
					static_cast<std::uint8_t>(std::lerp(colorA.b, colorB.b, progress)),
					static_cast<std::uint8_t>(std::lerp(colorA.a, colorB.a, progress)));
			}


		private:
			sf::Color colorA = sf::Color::White;
			sf::Color colorB = sf::Color::White;
		};
	}
}