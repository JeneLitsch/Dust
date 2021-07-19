#pragma once
#include "BasicParticleSystem.hxx"
#include <cmath>
namespace dust {
	template<
		std::size_t limit,
		class Particle,
		class EmitPolicy,
		class ColorPolicy,
		class MovementPolicy,
		class RotationPolicy,
		class ScalePolicy,
		class RenderPolicy>
	class AutomaticParticleSystem 
	:	virtual public BasicParticleSystem<
			limit, Particle,
			EmitPolicy,
			ColorPolicy,
			MovementPolicy,
			RotationPolicy,
			ScalePolicy,
			RenderPolicy>,
		virtual public IAutomaticParticleSystem {
	public:

		// Emit particles automaticle to keep a constant amount
		// and delegates update to BasicParticle system
		virtual void onUpdate(double dt) override {
			this->timer += dt;

			// figure out emmision rate
			const double currentLimit = double(this->emission * limit);
			const double lifetime = EmitPolicy::getLifetime();
			const double deltaEmit = lifetime / currentLimit;
			
			// emit
			if(deltaEmit > 0.0) {
				std::size_t amount = static_cast<std::size_t>(timer / deltaEmit);
				this->timer -= double(amount) * deltaEmit;
				this->emitParticles(amount);
			}
		}


		// Set emmision rate
		virtual void emit(double emission) override final {
			this->emission = std::clamp(emission, 0.0, 1.0);
		}

	private:
		double emission;
		double timer;
	};
}