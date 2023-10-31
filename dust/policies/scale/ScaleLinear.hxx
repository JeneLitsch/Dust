#pragma once
#include <cmath>
namespace dust {
	namespace policy {
		// Linear interpolation of scale over lifetime of particle
		class ScaleLinear {
		public:
			void configScale(float scaleA, float scaleB) {
				this->scaleA = scaleA;
				this->scaleB = scaleB;
			}
		protected:
			inline void operator()(auto & particle, float) const {
				const float progress = particle.age / particle.lifetime;
				particle.scale = std::lerp(scaleA, scaleB, progress);
			}
		private:
			float scaleA = 1.f;
			float scaleB = 1.f;
		};
	}
}