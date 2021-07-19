#pragma once
#include "sfml.hxx"
namespace dust {
	namespace policy {
		class RenderTexture {
		public:
			inline void configRender(sf::Texture texture) {
				this->texture = texture;
			}

		protected:
			inline void operator()(auto & particle, sf::Vertex * vertexStart) const {
				sf::Transform transform;
				transform
					.translate(particle.position)
					.rotate(particle.rotation);

				const float x = 0.5f * particle.scale;
				const float down = x * particle.size.x;
				const float top = -down;
				const float right = x * particle.size.y;
				const float left = -right;

				const float texTop = 0.f;
				const float texDown = static_cast<float>(texture.getSize().x);
				const float texLeft = 0.f;
				const float texRight = static_cast<float>(texture.getSize().y);
				
				*(vertexStart + 0) = sf::Vertex(
					transform.transformPoint(top, left),
					particle.color,
					sf::Vector2f(texTop, texLeft));

				*(vertexStart + 1) = sf::Vertex(
					transform.transformPoint(top, right),
					particle.color,
					sf::Vector2f(texTop, texRight));

				*(vertexStart + 2) = sf::Vertex(
					transform.transformPoint(down, right),
					particle.color,
					sf::Vector2f(texDown, texRight));

				*(vertexStart + 3) = sf::Vertex(
					transform.transformPoint(down, left),
					particle.color,
					sf::Vector2f(texDown, texLeft));
			}
		
		const sf::Texture * getTexture() { return &this->texture; }
		const sf::Shader * getShader() { return nullptr; }



		private:
			sf::Texture texture;
		};
	}
}