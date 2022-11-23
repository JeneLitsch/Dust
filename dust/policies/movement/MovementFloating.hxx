#pragma once
#include <cmath>
#include "sfml.hxx"
#include "../../utils/VectorUtils.hxx"

#include "MovementGravity.hxx"
#include "MovementDampening.hxx"
namespace dust {
	namespace policy {
		class MovementFloating :
			public MovementGravity,
			public MovementDampening {
		public:
			MovementFloating() {
				this->wiggleStrength = 1.f;
				this->wiggleSpeed = 10.f;
			}
			void configWiggle(float strength, float speed) {
				this->wiggleSpeed = speed;
				this->wiggleStrength = strength;

			}
		protected:
			void operator()(auto & particle, float dt) {
				MovementGravity::operator()(particle, dt);
				MovementDampening::operator()(particle, dt);
				const sf::Vector2f wiggle 
					= VectorUtils::deg90(particle.velocity) 
					* deflection(particle.age / particle.lifetime, particle.variation);

				particle.position += (particle.velocity + wiggle) * dt;
			};
		private:


			inline float deflection(float progress, float offset) const {
				return std::sin((progress + offset) * static_cast<float>(M_PI) * 2.f * this->wiggleSpeed) * this->wiggleStrength;
			}

			float wiggleStrength;
			float wiggleSpeed;
		};
	}
}