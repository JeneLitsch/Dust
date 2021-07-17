#pragma once
#include <cmath>
#include "sfml.hxx"

namespace dust {
	template<class TParticle>
	class BasicProcessor {
	public:

		BasicProcessor(
			float lifetime,
			float rotationSpeed,
			float emmisionAngle,
			float emmisionSpread)
		:	lifetime(lifetime),
			rotationSpeed(360.0 * rotationSpeed),
			emmisionAngle(emmisionAngle),
			emmisionSpread(emmisionSpread) {}

		inline void emit(TParticle & particle) const  {
			float spread = (float(rand() % 2000 - 1000) / 1000.f) * this->emmisionSpread;
			float radianAngle = (emmisionAngle + spread - 90.f - 45.f) * M_PI / 180.f;
			particle.velocity.x = std::cos(radianAngle) * 100.f;
			particle.velocity.y = std::sin(radianAngle) * 100.f;

			particle.position.x = 0.f;
			particle.position.y = 0.f;

			particle.size.x = 0.f;
			particle.size.y = 0.f;

			particle.alive = true;
			particle.age = 0.0;
			particle.rotation = 0.0;
		}

		inline void process(TParticle & particle, double dt) const{
			const float arch = float(std::sin(particle.age/this->lifetime * 3.14f));
			
			particle.age += float(dt);
			particle.alive = particle.age <= lifetime;
				
			particle.position += particle.velocity * float(dt) * arch;
			
			particle.size.x = 32.f * arch;
			particle.size.y = 32.f * arch;

			particle.rotation +=  float(dt) * rotationSpeed;
		}

		inline void setLifetime(float lifetime) {
			this->lifetime = lifetime;
		}

		inline float getLifetime() const {
			return this->lifetime;
		}

		inline void setRotationSpeed(float rotationSpeed) {
			this->rotationSpeed = rotationSpeed;
		}

		inline float getRotationSpeed() {
			return this->rotationSpeed;
		}

	protected:
		float lifetime;
		float rotationSpeed;
		float emmisionAngle;
		float emmisionSpread;
	};
}