#pragma once
#include "EmitBasic.hxx"
namespace dust {
	namespace policy {
		// Emits particle in a circle area
		class EmitCircle : public EmitBasic {
		public:
			void configEmitCircle(float radius) {
				this->radius = radius;
			}

		protected:
			inline void operator()(auto & particle) {
				EmitBasic::operator()(particle);
				const float dist = this->randFloat(0.f, 1.f) * radius;
				const sf::Vector2f direction = toVector(this->randFloat(0.f, 360.f)) ;
				particle.position = direction * dist;
			}

		private:
			float radius;
		};
	}
}