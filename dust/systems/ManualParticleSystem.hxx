#pragma once
#include "BasicParticleSystem.hxx"
#include <cmath>
namespace dust {
	template<
		std::size_t limit,
		class Particle,
		class Rendered,
		class Emitter,
		typename ...Policies

	>
	class ManualParticleSystem 
	:	virtual public BasicParticleSystem<
			limit,
			Particle,
			Rendered,
			Emitter,
			Policies...
		>,
		virtual public IManualParticleSystem {
	public:

		virtual void emit(std::size_t amount) override final {
			this->emitParticles(amount);
		}

	};
}