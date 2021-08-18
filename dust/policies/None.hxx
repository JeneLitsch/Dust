#pragma once

namespace dust {
	namespace policy {
		template<unsigned x>
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