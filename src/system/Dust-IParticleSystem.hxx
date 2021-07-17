#pragma once
#include "sfml.hxx"

namespace dust {
	class IParticleSystem {
	public:
		virtual ~IParticleSystem() = default;
		virtual void update(double dt) = 0;
		virtual void render(sf::RenderTarget & renderTarget) = 0;
		virtual void setPosition(sf::Vector2f position) = 0;
		virtual void emit(std::size_t amount) = 0;
	};
}