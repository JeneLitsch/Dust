#pragma once

namespace dust {
	namespace policy {
		// Keep scale of particle constant over entire lifetime
		class ScaleParabola {
		public:
			void configScale(float min, float max) {
				this->scale = max - min;
				this->base = min;
			}

			void configScale(float scale) {
				this->scale = scale;
				this->base = 0.f;
			}
		protected:
			inline void operator()(auto & particle, float) const {
				float x = particle.age / particle.lifetime;
				float y = -(2.f * x -1) * (2.f * x -1.f) + 1.f;
				particle.scale = this->scale * y + this->base;
			}
		private:
			float scale = 1.f;
			float base = 1.f;
		};
	}
}