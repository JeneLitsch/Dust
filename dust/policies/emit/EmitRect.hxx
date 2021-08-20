#pragma once
#include "EmitArea.hxx"
namespace dust {
	namespace policy {
		// Emits particle in a rectangle area
		class EmitRect : public EmitArea {
		public:
			void configEmitRect(sf::Vector2f size) {
				this->size = size;
			}

			void configEmitRect(float size) {
				this->size = sf::Vector2f(size, size);
			}

		protected:
			inline void operator()(auto & particle) {
				EmitArea::operator()(particle);
				float startX = this->randFloat(-0.5f, 0.5f) * size.x + this->originX;
				float startY = this->randFloat(-0.5f, 0.5f) * size.y + this->originY;
				particle.position = sf::Vector2f(startX, startY);
			}

		private:
			sf::Vector2f size;
		};
	}
}