#pragma once

#include "IParticleSystem.hxx"
#include <vector>
#include "sfml.hxx"
#include <future>

namespace dust {
	// Basic particle system for updating and rendering particles
	// Emitting must be implemented by derived classes
	template<
		std::size_t limit,
		class Particle,
		class EmitPolicy,
		class ColorPolicy,
		class MovementPolicy,
		class RotationPolicy,
		class RenderPolicy>
	class BasicParticleSystem : 
		virtual public IParticleSystem,
		public EmitPolicy,
		public ColorPolicy,
		public MovementPolicy,
		public RotationPolicy,
		public RenderPolicy {
	public:
		
		BasicParticleSystem() {}

		virtual ~BasicParticleSystem() = default;


		// Update all living particles
		virtual void update(double dt) override {
			this->onUpdate(dt);
			for(auto & particle : particles) {
				if(particle) {
					ColorPolicy::operator()(particle);
					MovementPolicy::operator()(particle, dt);
					RotationPolicy::operator()(particle, dt);
					particle.age += float(dt);
					particle.alive = particle.age <= particle.lifetime;
				}
			}
		}

		// Render all "living" particles
		virtual void render(sf::RenderTarget & renderTarget) override final {
			// setup render states
			sf::RenderStates states;
			states.transform = sf::Transform()
				.translate(this->position)
				.rotate(static_cast<float>(this->rotation));

			states.texture = RenderPolicy::getTexture();
			states.shader = RenderPolicy::getShader();

			// fill vertex array
			std::size_t vertexCounter = 0;
			for(std::size_t i = 0; i < limit; i++) {
				// For rendering newest particles on top
				// Start at next and wrap around if nessasary
				std::size_t idx = (this->next + i) % limit;
				if(particles[idx]) {
					RenderPolicy::operator()(particles[idx], &vertecies[vertexCounter]);
					vertexCounter += 4U;
				}
			}
			renderTarget.draw(vertecies.data(), vertexCounter, sf::PrimitiveType::Quads, states);
			// std::cout << vertexArray.getVertexCount() / 4 << std::endl;
		}

		// Set center of emission
		virtual void setPosition(sf::Vector2f position) override final {
			this->position = position;
		}

		// Sets rotation in degrees
		virtual void setRotation(double degrees) override final {
			this->rotation = degrees;
		}


	protected:
		inline void emitParticles(std::size_t amount) {
			if(!this->particles[this->next]) {
				for(std::size_t i = 0; i < amount; i++) {
					EmitPolicy::operator()(this->particles[this->next]);
					this->next++;
					this->next %= this->particles.size();
				}
			}
		}

		virtual void onUpdate(double dt) {};

		std::array<Particle, limit> particles;
		std::array<sf::Vertex, limit * 4U> vertecies;
		std::size_t next;
		
		sf::Vector2f position;
		double rotation;
	};
};