#pragma once

namespace dust {
	namespace policy {
		// Keep scale of particle constant over entire lifetime
		class ScaleConstant {
		public:
			void configScale(float scale) {
				this->scale = scale;
			}
		protected:
			inline void operator()(auto & particle) const {
				particle.scale = this->scale;
			}
		private:
			float scale = 1.f;
		};
	}
}