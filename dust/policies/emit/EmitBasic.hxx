#pragma once
#include <random>
#include "sfml.hxx"
#include "../../utils/VectorUtils.hxx"

namespace dust {
	namespace policy {
		// Base utility class for emisson policies
		class EmitBasic {
		public:
			void configLifetime(float lifetime) {
				this->lifetime = lifetime;
			}

			void configEmitSize(float sizeX, float sizeY) {
				this->sizeX = sizeX;
				this->sizeY = sizeY;
			}


			void configEmitOrigin(float originX, float originY) {
				this->originX = originX;
				this->originY = originY;
			}

			void configEmitSpeed(float initialSpeed, float speedVariation) {
				this->initialSpeed = initialSpeed;
				this->speedVariation = speedVariation;
			}

			void configEmitRotation(float initialRotation, float rotationVariation) {
				this->initialRotation = initialRotation;
				this->rotationVariation = rotationVariation;
			}

		protected:
			EmitBasic() {
				this->random.seed(std::random_device()());
				this->lifetime = 5.f;
			}

			template<typename T>
			inline T randFloat(T from, T to) {
				return std::uniform_real_distribution<T>(from, to)(this->random);
			}

			template<typename T>
			inline T randInt(T from, T to) {
				return std::uniform_int_distribution<T>(from, to)(this->random);
			}


			inline float getLifetime() const {
				return this->lifetime;
			}

			inline void operator()(auto & particle) {
				particle.rotation 
					= this->initialRotation
					+ (1.f + randFloat(-this->rotationVariation, this->rotationVariation));				

				particle.age = 0.f;
				particle.alive = true;
				particle.size = sf::Vector2f(sizeX, sizeY);
				particle.lifetime = this->getLifetime();
				particle.color = sf::Color::White;

				particle.variation = this->randFloat(-1.f, 1.f);
			}
		protected:
			float initialSpeed;
			float speedVariation;
			float originX = 0.f;
			float originY = 0.f;
		private:
			std::mt19937_64 random;
			float lifetime;
			float initialRotation;
			float rotationVariation;
			float sizeX = 32.f;
			float sizeY = 32.f;
		};
	}
}