#pragma once
#include "sfml.hxx"

namespace dust {
	namespace policy {
		class RenderColor {
		public:
			inline void operator()(auto & particle, sf::VertexArray & vertexArray) const {
				sf::Transform transform;
				transform
					.translate(particle.position)
					.rotate(particle.rotation);

				const float x = 0.5f * particle.scale;
				const float down = x * particle.size.x;
				const float top = -down;
				const float right = x * particle.size.y;
				const float left = -right;
			
				vertexArray.append(sf::Vertex(
					transform.transformPoint(top, left),
					particle.color));

				vertexArray.append(sf::Vertex(
					transform.transformPoint(top, right),
					particle.color));

				vertexArray.append(sf::Vertex(
					transform.transformPoint(down, right),
					particle.color));

				vertexArray.append(sf::Vertex(
					transform.transformPoint(down, left),
					particle.color));
			}

			const sf::Texture * getTexture() { return nullptr; }
			const sf::Shader * getShader() { return nullptr; }
		};
	}
}