#pragma once
#include "EmitArea.hxx"
namespace dust {
	namespace policy {
		// Emits particle in a circle area
		class EmitCircle : public EmitArea {
		public:
			void configEmitCircle(float radius) {
				this->radius = radius;
			}

		protected:
			inline void operator()(auto & particle) {
				EmitArea::operator()(particle);
				const float dist = this->randFloat(0.f, 1.f) * radius;
				const sf::Vector2f direction = VectorUtils::toVector(this->randFloat(0.f, 360.f));
				const sf::Vector2f origin(this->originX, this->originX);
				particle.position = direction * dist + origin;
			}

		private:
			float radius;
		};
	}
}