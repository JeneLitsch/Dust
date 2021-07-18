#pragma once
#include "Colored.hxx"
namespace dust {
	template<
		class ColorSource,
		class TVelocity>
	class Textured : public Colored<ColorSource, TVelocity> {
	public:
		Textured(
			float lifetime,
			float rotationSpeed,
			float emmisionAngle,
			float emmisionSpread,
			ColorSource colorSource,
			const TVelocity & velocity)
		:	Colored<ColorSource, TVelocity>(
				lifetime,
				rotationSpeed,
				emmisionAngle,
				emmisionSpread,
				colorSource,
				velocity) {}

		void setTexture(const sf::Texture & texture) {
			this->texture = texture;
		}

		// Add vertecies of a colored particle to vertexArray
		inline void render(typename Colored<ColorSource, TVelocity>::Particle & particle, sf::VertexArray & vertexArray) const {
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

		const sf::Texture * getTexture() const {
			return &texture;
		}

	private:
		sf::Texture texture;
	};
}