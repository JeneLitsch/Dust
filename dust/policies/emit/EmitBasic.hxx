#pragma once
#include <random>
#include "sfml.hxx"

namespace dust {
	namespace policy {
		// Base utility class for emisson policies
		class EmitBasic {
		public:
			void configEmit(
				float angle,
				float spread,
				float initialSpeed,
				float speedVariation,
				float initialRotation,
				float rotationVariation) {

				this->angle = angle;
				this->spread = spread;
				this->initialSpeed = initialSpeed;
				this->speedVariation = speedVariation;
				this->initialRotation = initialRotation;
				this->rotationVariation = rotationVariation;
			}
		protected:


			EmitBasic() {
				random.seed(std::random_device()());
			}

			inline float randFloat(float from, float to) {
				return std::uniform_real_distribution(from, to)(random);
			}

			static inline sf::Vector2f toVector(float angle) {
				constexpr const float degToRad = float(M_PI) / 180.f;
				float radianAngle = (angle - 90.f) * degToRad;
				return sf::Vector2f(std::cos(radianAngle), std::sin(radianAngle));
			}

			inline float getLifetime() const {
				return 5.0;
			}

			inline void operator()(auto & particle) {

				float spread = randFloat(-1.f, 1.f) * this->spread;
				particle.velocity 
					= toVector(angle + spread)
					* this->initialSpeed 
					* (1.f + randFloat(-this->speedVariation, this->speedVariation));

				particle.rotation 
					= this->initialRotation
					+ (1.f + randFloat(-this->rotationVariation, this->rotationVariation));

				particle.age = 0.f;
				particle.alive = true;
				particle.size = sf::Vector2f(32.f, 32.f);
				particle.lifetime = this->getLifetime();
				particle.color = sf::Color::White;

				for(auto & var : particle.variation) {
					var = this->randFloat(0.f, 1.f);
				}
			}

		private:
			std::mt19937_64 random;
			float angle;
			float spread;
			float initialSpeed;
			float speedVariation;
			float initialRotation;
			float rotationVariation;
		};
	}
}