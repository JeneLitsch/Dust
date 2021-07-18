#pragma once

namespace dust {
	namespace policy {
		class RotationConstant {
		public:
			inline void operator()(auto & particle, double dt) {
				particle.rotation += this->speed * dt;
			}

			void configRotation(float speed) {
				this->speed = speed;
			}
		private:
			float speed;
		};
	}
}