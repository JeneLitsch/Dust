#pragma once
#include "EmitArea.hxx"
namespace dust {
	namespace policy {
		// Emits particle at a point
		class EmitPoint : public EmitArea {
		public:
		protected:
			inline void operator()(auto & particle) {
				EmitArea::operator()(particle);
				particle.position = sf::Vector2f(0.f, 0.f);
			}

		private:

		};
	}
}