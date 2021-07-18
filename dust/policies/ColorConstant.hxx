#pragma once
#include "sfml.hxx"
namespace dust {
	namespace policy {
		class ColorConstant {
		public:
			
			inline void operator()(auto & particle) const {
				particle.color = color;
			}

			void configColor(sf::Color color) {
				this->color = color;
			}
		private:
			sf::Color color = sf::Color::White;
		};
	}
}