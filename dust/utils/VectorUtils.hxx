#pragma once
#include "sfml.hxx"
#include <cmath>
namespace dust {
	class VectorUtils {
	public:
		static inline sf::Vector2f toVector(float angle) {
			constexpr const float degToRad = float(M_PI) / 180.f;
			const float radianAngle = (angle - 90.f) * degToRad;
			return sf::Vector2f(std::cos(radianAngle), std::sin(radianAngle));
		}

		static inline sf::Vector2f deg90(sf::Vector2f vector) {
			return sf::Vector2f(vector.y, -vector.x);
		}
	};
}