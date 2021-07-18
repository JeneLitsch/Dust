#pragma once
#include "BasicParticleSystem.hxx"
#include <cmath>
namespace dust {
	template<class TParticleProcessor, std::size_t limit>
	class AutomaticParticleSystem 
	:	virtual public BasicParticleSystem<TParticleProcessor, limit>,
		virtual public IAutomaticParticleSystem {
	public:
		AutomaticParticleSystem(const TParticleProcessor & processor)
		:	BasicParticleSystem<TParticleProcessor, limit>(processor) {}

		// Emit particles automaticle to keep a constant amount
		// and delegates update to BasicParticle system
		virtual void update(double dt) override {
			this->timer += dt;

			// figure out emmision rate
			const double currentLimit = double(this->emission * limit);
			const double lifetime = this->processor.getLifetime();
			const double deltaEmit = lifetime / currentLimit;
			
			// emit
			if(deltaEmit > 0.0) {
				std::size_t amount = std::roundl(timer / deltaEmit);
				this->timer -= double(amount) * deltaEmit;
				this->emitInternal(amount);
			}

			// delegate update
			BasicParticleSystem<TParticleProcessor, limit>::update(dt);
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