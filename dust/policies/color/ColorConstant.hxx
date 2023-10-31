#pragma once
#include "sfml.hxx"
namespace dust {
	namespace policy {
		// Constant color for particle over entire lifetime
		class ColorConstant {
		public:
			void configColor(sf::Color color) {
				this->color = color;
			}
		
		protected:
			inline void operator()(auto & particle, float) const {
				particle.color = color;
			}

		private:
			sf::Color color = sf::Color::White;
		};
	}
}