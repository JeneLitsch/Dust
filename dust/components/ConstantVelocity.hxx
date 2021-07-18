#pragma once
#include "sfml.hxx"
namespace dust {
	class ConstantVelocity {
	public:
		ConstantVelocity(float speed) : speed(speed) {}
		sf::Vector2f operator()(double progress, sf::Vector2f direction) const {
			(void)(progress);
			return direction * speed;
		}
	private:
		float speed;
	};
}