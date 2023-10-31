#pragma once
#include "BasicParticleSystem.hxx"
#include <cmath>
#include <iostream>
namespace dust {
	template<
		std::size_t limit,
		class Particle,
		class Remderer,
		class Emitter,
		typename ...Policies
	>
	class AutomaticParticleSystem 
	:	virtual public BasicParticleSystem<
			limit,
			Particle,
			Remderer,
			Emitter,
			Policies...
		>,
		virtual public IAutomaticParticleSystem {
	public:
		// Set emmision rate
		virtual void emit(double emission) override final {
			this->emission = std::clamp(emission, 0.0, 1.0);
		}

	protected:
		// Emit particles automaticle to keep a constant amount
		// and delegates update to BasicParticle system
		virtual void onUpdate(double dt) override {
			this->timer += dt;

			// figure out emmision rate
			const double lifetime = Emitter::getLifetime();
			const double particlesPerSecond = static_cast<float>(limit) / lifetime * this->emission;
			const std::size_t amount = static_cast<std::size_t>(timer * particlesPerSecond);
			
			if(amount) {
				this->timer = 0.0;
				this->emitParticles(amount);
			}
		}

	private:
		double emission = 0.0;
		double timer = 0.0;
	};
}