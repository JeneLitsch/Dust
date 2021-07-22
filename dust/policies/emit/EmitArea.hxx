#pragma once
#include <random>
#include "sfml.hxx"
#include "EmitBasic.hxx"
namespace dust {
	namespace policy {
		// Base utility class for emisson policies
		class EmitArea : public EmitBasic {
		public:
			void configEmitAngle(float angle, float spread) {
				this->angle = angle;
				this->spread = spread;
			}



		protected:
			inline void operator()(auto & particle) {
				float spread = randFloat(-1.f, 1.f) * this->spread;
				particle.velocity 
					= VectorUtils::toVector(angle + spread)
					* this->initialSpeed 
					* (1.f + randFloat(-this->speedVariation, this->speedVariation));

				this->EmitBasic::operator()(particle);
			}

		private:
			std::mt19937_64 random;
			float angle;
			float spread;
		};
	}
}