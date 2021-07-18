#pragma once
#include "sfml.hxx"
#include <cmath>

namespace dust {
	class ColorInterpolate {
	public:
		ColorInterpolate(sf::Color color) 
		:	color(color) {}

		inline sf::Color operator()(double progress) const {
			(void)(progress); // ignore
			return this->color;
		}

	private:
		sf::Color color;
	};
}