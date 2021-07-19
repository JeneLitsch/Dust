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
	class MainualParticleSystem 
	:	virtual public BasicParticleSystem<
			limit, Particle,
			EmitPolicy,
			ColorPolicy,
			MovementPolicy,
			RotationPolicy,
			ScalePolicy,
			RenderPolicy>,
		virtual public IManualParticleSystem {
	public:

		virtual void emit(std::size_t amount) override final {
			this->emitParticles(amount);
		}

	};
}