#pragma once
#include "sfml.hxx"

namespace dust {
	class ColorInterpolate {
	public:
		ColorInterpolate(sf::Color colorA, sf::Color colorB);
		sf::Color operator()(double progress) const;
	private:
		sf::Color colorA;
		sf::Color colorB;
	};
}