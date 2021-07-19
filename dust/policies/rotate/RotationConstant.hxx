#pragma once

namespace dust {
	namespace policy {
		// Rotate particle with contant speed 
		class RotationConstant {
		public:
			void configRotation(float speed) {
				this->speed = speed;
			}
		
		protected:
			inline void operator()(auto & particle, float dt) {
				particle.rotation += this->speed * dt;
			}

		private:
			float speed;
		};
	}
}