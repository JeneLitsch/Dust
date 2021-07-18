#pragma once
#include "sfml.hxx"
namespace dust {
	namespace policy {
		class RenderTexture {
		public:
			inline void operator()(auto & particle, sf::VertexArray & vertexArray) const {
				sf::Transform transform;
				transform
					.translate(particle.position)
					.rotate(particle.rotation);

				const float down = 0.5 * particle.size.x;
				const float top = -down;
				const float right = 0.5 * particle.size.y;
				const float left = -right;

				const float texTop = 0.f;
				const float texDown = texture.getSize().x;
				const float texLeft = 0.f;
				const float texRight = texture.getSize().y;
				
				vertexArray.append(sf::Vertex(
					transform.transformPoint(top, left),
					particle.color,
					sf::Vector2f(texTop, texLeft)));

				vertexArray.append(sf::Vertex(
					transform.transformPoint(top, right),
					particle.color,
					sf::Vector2f(texTop, texRight)));

				vertexArray.append(sf::Vertex(
					transform.transformPoint(down, right),
					particle.color,
					sf::Vector2f(texDown, texRight)));

				vertexArray.append(sf::Vertex(
					transform.transformPoint(down, left),
					particle.color,
					sf::Vector2f(texDown, texLeft)));
			}
		
		const sf::Texture * getTexture() { return &this->texture; }
		const sf::Shader * getShader() { return nullptr; }

		inline void configRender(sf::Texture texture) {
			this->texture = texture;
		}

		private:
			sf::Texture texture;
		};
	}
}