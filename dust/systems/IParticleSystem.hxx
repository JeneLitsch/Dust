#pragma once
#include "sfml.hxx"

namespace dust {
	class IParticleSystem {
	public:
		virtual ~IParticleSystem() = default;
		virtual void update(double dt) = 0;
		virtual void render(sf::RenderTarget & renderTarget) = 0;

		virtual void setPosition(sf::Vector2f position) = 0;
		virtual void setRotation(double angle) = 0;
	};


	class IManualParticleSystem : virtual public IParticleSystem {
	public:
		virtual ~IManualParticleSystem() = default;
		virtual void emit(std::size_t amount) = 0;
	};

	class IAutomaticParticleSystem : virtual public IParticleSystem {
	public:
		virtual ~IAutomaticParticleSystem() = default;
		virtual void emit(double strenght) = 0;
	};
}