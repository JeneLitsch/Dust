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
		// Emit a amount of particles once
		// Implemntation can ignore any amount if emission is not possible
		virtual void emit(std::size_t amount) = 0;
	};

	class IAutomaticParticleSystem : virtual public IParticleSystem {
	public:
		virtual ~IAutomaticParticleSystem() = default;
		// Set emmision rate from 0.0 - 1.0 to determines percentage of emitted and used particles
		// e.g limit = 10000 and emission = 0.5 means 5000 used particles 
		virtual void emit(double strenght) = 0;
	};
}