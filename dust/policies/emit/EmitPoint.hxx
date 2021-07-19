#pragma once
#include "EmitBasic.hxx"
namespace dust {
	namespace policy {
		// Emits particle at a point
		class EmitPoint : public EmitBasic {
		public:
		protected:
			inline void operator()(auto & particle) {
				EmitBasic::operator()(particle);
				particle.position = sf::Vector2f(0.f, 0.f);
			}

		private:

		};
	}
}