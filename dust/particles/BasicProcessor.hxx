#pragma once
#include <cmath>
#include "sfml.hxx"

namespace dust {
	template<
		class TParticle,
		class TVelocity>
	class BasicProcessor {
	public:

		BasicProcessor(
			float lifetime,
			float rotationSpeed,
			float emmisionAngle,
			float emmisionSpread,
			const TVelocity & velocity)
		:	lifetime(lifetime),
			rotationSpeed(360.f * rotationSpeed),
			emmisionAngle(emmisionAngle),
			emmisionSpread(emmisionSpread),
			velocity(velocity) {}

		// Setup configuration and set alive to true to emit particle 
		inline void emit(TParticle & particle) const {
			float spread = (float(rand() % 2000 - 1000) / 1000.f) * this->emmisionSpread;
			float radianAngle = (emmisionAngle + spread - 90.f) * float(M_PI) / 180.f;
			particle.velocity.x = std::cos(radianAngle);
			particle.velocity.y = std::sin(radianAngle);

			particle.position.x = 0.f;
			particle.position.y = 0.f;

			particle.size.x = 0.f;
			particle.size.y = 0.f;

			particle.alive = true;
			particle.age = 0.0;
			particle.rotation = 0.0;
		}

		// Update particle attributes
		// e.g. age, position, size...
		inline void process(TParticle & particle, double dt) const{
			const float arch = float(std::sin(particle.age/this->lifetime * 3.14f));
			
			particle.age += float(dt);
			particle.alive = particle.age <= lifetime;
				
			particle.position += this->velocity(particle.age, particle.velocity) * float(dt);
			
			particle.size.x = 32.f * arch;
			particle.size.y = 32.f * arch;

			particle.rotation +=  float(dt) * rotationSpeed;
		}

		// in seconds
		inline void setLifetime(float lifetime) {
			this->lifetime = lifetime;
		}

		// in seconds
		inline float getLifetime() const {
			return this->lifetime;
		}

		// revolution per second
		inline void setRotationSpeed(float rotationSpeed) {
			this->rotationSpeed = rotationSpeed;
		}

		// revolution per second
		inline float getRotationSpeed() {
			return this->rotationSpeed;
		}

		const sf::Texture * getTexture() const {
			return nullptr;
		}

	protected:
		float lifetime;
		float rotationSpeed;
		float emmisionAngle;
		float emmisionSpread;
		TVelocity velocity;
	};
}