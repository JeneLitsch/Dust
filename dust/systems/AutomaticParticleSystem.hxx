#pragma once
#include "BasicParticleSystem.hxx"

namespace dust {
	template<class TParticleProcessor, std::size_t limit>
	class AutomaticParticleSystem 
	:	virtual public BasicParticleSystem<TParticleProcessor, limit>,
		virtual public IAutomaticParticleSystem {
	public:
		AutomaticParticleSystem(const TParticleProcessor & processor)
		:	BasicParticleSystem<TParticleProcessor, limit>(processor) {}

		virtual void update(double dt) override {
			this->timer += dt;
			double deltaEmit = this->processor.getLifetime() / double(limit);
			if(deltaEmit > 0.0) {
				std::size_t amount = std::size_t(timer / deltaEmit);
				this->timer -= amount * deltaEmit;
				this->emitInternal(amount);
			}
			BasicParticleSystem<TParticleProcessor, limit>::update(dt);
		}

		virtual void emit(double emission) override final {
			this->emission = emission;
		}

	private:
		double emission;
		double timer;
	};
}