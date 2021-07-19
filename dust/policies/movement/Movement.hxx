#pragma once
namespace dust {
	namespace policy {
		class Movement {
		protected:
			void operator()(auto & particle, float dt) {
				particle.position += particle.velocity * float(dt);
			};
		};
	}
}