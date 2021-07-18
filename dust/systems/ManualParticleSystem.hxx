#pragma once
#include "BasicParticleSystem.hxx"

namespace dust {
	template<class TParticleProcessor, std::size_t limit>
	class ManualParticleSystem 
	:	virtual public BasicParticleSystem<TParticleProcessor, limit>,
		virtual public IManualParticleSystem {
	public:
		ManualParticleSystem(const TParticleProcessor & processor)
		:	BasicParticleSystem<TParticleProcessor, limit>(processor) {}

		// Emit a amount of particles
		virtual void emit(std::size_t amount) override final {
			BasicParticleSystem<TParticleProcessor, limit>::emitInternal(amount);
		}
	};
}