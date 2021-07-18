#pragma once
#include "sfml.hxx"
#include <random>
namespace dust {
	namespace policy {
		class EmitPoint {
		public:
			EmitPoint() {
				random.seed(std::random_device()());
			}

			inline void operator()(auto & particle) {
				constexpr const float degToRad = float(M_PI) / 180.f;

				float spread = randFloat(-1.f, 1.f) * this->spread;
				float radianAngle = (angle + spread - 90.f) * degToRad;
				particle.velocity 
					= sf::Vector2f(std::cos(radianAngle), std::sin(radianAngle)) 
					* this->initialSpeed 
					* (1.f + randFloat(-this->speedVariation, this->speedVariation));

				particle.rotation 
					= this->initialRotation
					* (1.f + randFloat(-this->rotationVariation, this->rotationVariation));

				particle.age = 0.f;
				particle.alive = true;
				particle.position = sf::Vector2f(0.f, 0.f);
				particle.size = sf::Vector2f(32.f, 32.f);
				particle.lifetime = this->getLifetime();
				particle.color = sf::Color::White;
			}

			virtual float getLifetime() const {
				return 5.0;
			}

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


		private:
			inline float randFloat(float from, float to) {
				return std::uniform_real_distribution(from, to)(random);
			} 
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