#pragma once

namespace dust {
	namespace policy {
		struct None {
			inline void operator()(auto & particle) const {
				(void)(particle);
			}
			void operator()(auto & particle, double dt) {
				(void)(particle);
				(void)(dt);
			};
		};
	}
}