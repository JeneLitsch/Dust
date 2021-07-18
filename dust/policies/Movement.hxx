#pragma once
namespace dust {
	namespace policy {
		class Movement {
		public:
			void operator()(auto & particle, double dt) {
				particle.position += particle.velocity * float(dt);
			};
		};
	}
}