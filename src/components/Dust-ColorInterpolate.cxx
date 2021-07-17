#include "Dust-ColorInterpolate.hxx"
#include <cmath>
dust::ColorInterpolate::ColorInterpolate(sf::Color colorA, sf::Color colorB)
:	colorA(colorA), colorB(colorB) {}

sf::Color dust::ColorInterpolate::operator()(double progress) const {
	return sf::Color(
		std::lerp(colorA.r, colorB.r, progress),
		std::lerp(colorA.g, colorB.g, progress),
		std::lerp(colorA.b, colorB.b, progress));
}