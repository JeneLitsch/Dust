#pragma once
namespace dust {
	namespace policy {
		class MovementDampening {
		public:
			MovementDampening() {
				friction = 0.f;
			}
			void configMovement(float friction) {
				this->friction = friction;
			}
		protected:
			void operator()(auto & particle, float dt) {
				particle.velocity -= particle.velocity * dt * friction; 
				particle.position += particle.velocity * dt;
			};
		public:
			float friction; 
		};
	}
}