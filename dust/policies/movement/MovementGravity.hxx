#pragma once
#include <cmath>
#include "sfml.hxx"
#include "VectorUtils.hxx"
namespace dust {
	namespace policy {
		class MovementGravity {
		public:
			MovementGravity() {
				this->force = sf::Vector2f(0.f, 1.f) * 9.81f * 100.f;
			}
			
			void configGravity(float angle, float power) {
				this->force = VectorUtils::toVector(angle) * power;
			}

		protected:
			void operator()(auto & particle, float dt) {
				particle.velocity += force * dt;
				particle.position += particle.velocity * float(dt);
			};

		private:
			sf::Vector2f force;
		};
	}
}