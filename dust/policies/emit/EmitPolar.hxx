#pragma once
#include "EmitBasic.hxx"
namespace dust {
	namespace policy {
		template<std::size_t poleCount>
		class EmitPolar : public EmitBasic {
		public:
			EmitPolar() {
				this->poles.fill(0.f);
				this->spread = 0.f;
				this->rotation = 0.f;
			}
			void configEmitPoles(std::array<float, poleCount> poles, float spread, float rotation = 0.f) {
				this->poles = poles;
				this->spread = spread;
				this->rotation = rotation;
			}

			void rotatePoles(float angle) {
				this->rotation += angle;
			}


		protected:
			inline void operator()(auto & particle) {
				EmitBasic::operator()(particle);
				particle.position = sf::Vector2f(0.f, 0.f);
				const float angle = getRandomAngle();
				const float spread = randFloat(-1.f, 1.f) * this->spread;
				particle.velocity 
					= VectorUtils::toVector(angle + spread + this->rotation)
					* this->initialSpeed 
					* (1.f + randFloat(-this->speedVariation, this->speedVariation));
			}


			inline float getRandomAngle() {
				return poles[this->randInt<std::size_t>(0, poles.size() - 1)];
			}
		private:
			std::array<float, poleCount> poles;
			float rotation;
			float spread;
		};
	}
}