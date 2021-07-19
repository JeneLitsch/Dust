#pragma once
#include "EmitBasic.hxx"
namespace dust {
	namespace policy {
		// Emits particle in a rectangle area
		class EmitRect : public EmitBasic {
		public:
			void configEmitRect(sf::Vector2f size) {
				this->size = size;
			}

			void configEmitRect(float size) {
				this->size = sf::Vector2f(size, size);
			}

		protected:
			inline void operator()(auto & particle) {
				EmitBasic::operator()(particle);
				float startX = this->randFloat(-0.5f * size.x, 0.5f * size.x);
				float startY = this->randFloat(-0.5f * size.y, 0.5f * size.y);
				particle.position = sf::Vector2f(startX, startY);
			}

		private:
			sf::Vector2f size;
		};
	}
}