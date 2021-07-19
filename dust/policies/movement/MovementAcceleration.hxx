#pragma once
namespace dust {
	namespace policy {
		class MovementAcceleration {
		public:
			MovementAcceleration() {
				acceleration = 0.f;
			}
			void configMovement(float acceleration) {
				this->acceleration = acceleration;
			}
		protected:
			void operator()(auto & particle, float dt) {
				particle.velocity *= 1.f + acceleration * dt; 
				particle.position += particle.velocity * dt;
			};
		public:
			float acceleration; 
		};
	}
}