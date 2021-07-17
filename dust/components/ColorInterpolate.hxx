#pragma once
#include "sfml.hxx"
#include <cmath>

namespace dust {
	class ColorInterpolate {
	public:
		ColorInterpolate(sf::Color colorA, sf::Color colorB) 
		:	colorA(colorA), colorB(colorB) {}

		inline sf::Color operator()(double progress) const {
			return sf::Color(
				std::lerp(colorA.r, colorB.r, progress),
				std::lerp(colorA.g, colorB.g, progress),
				std::lerp(colorA.b, colorB.b, progress));
		}

	private:
		sf::Color colorA;
		sf::Color colorB;
	};
}