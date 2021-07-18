#pragma once
#include "sfml.hxx"
#include <cmath>

namespace dust {
	class InterpolateColor {
	public:
		InterpolateColor(sf::Color colorA, sf::Color colorB) 
		:	colorA(colorA), colorB(colorB) {}

		inline sf::Color operator()(double progress) const {
			return sf::Color(
				static_cast<std::uint8_t>(std::lerp(colorA.r, colorB.r, progress)),
				static_cast<std::uint8_t>(std::lerp(colorA.g, colorB.g, progress)),
				static_cast<std::uint8_t>(std::lerp(colorA.b, colorB.b, progress)),
				static_cast<std::uint8_t>(std::lerp(colorA.a, colorB.a, progress)));
		}

	private:
		sf::Color colorA;
		sf::Color colorB;
	};
}