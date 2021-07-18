#pragma once

#include "IParticleSystem.hxx"
#include <vector>
#include "sfml.hxx"
#include <future>

namespace dust {
	// Basic particle system for updating and rendering particles
	// Emitting must be implemented by derived classes
	template<class TParticleProcessor, std::size_t limit>
	class BasicParticleSystem : virtual public IParticleSystem {
	public:
		BasicParticleSystem(
			const TParticleProcessor & processor) 
			:	processor(processor) {
			this->position = sf::Vector2f(0,0);
			this->rotation = 0.f;
			this->next = 0;
			vertexArray.setPrimitiveType(sf::PrimitiveType::Quads);
		}
		
		virtual ~BasicParticleSystem() = default;


		// Update all living particles
		virtual void update(double dt) override {
			for(auto & particle : particles) {
				if(particle) {
					processor.process(particle, dt);
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
			states.texture = processor.getTexture();

			// fill vertex array
			this->vertexArray.clear();
			for(std::size_t i = 0; i < limit; i++) {
				// For rendering newest particles on top
				// Start at next and wrap around if nessasary
				std::size_t idx = (this->next + i) % limit;
				if(particles[idx]) {
					processor.render(particles[idx], vertexArray);
				}
			}
			renderTarget.draw(vertexArray, states);
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

		TParticleProcessor & getProcessor() {
			return this->processor;
		}

		const TParticleProcessor & getProcessor() const {
			return this->processor;
		}

	protected:

		inline void emitInternal(std::size_t amount) {
			if(!this->particles[this->next]) {
				for(std::size_t i = 0; i < amount; i++) {
					this->processor.emit(this->particles[this->next]);
					this->next++;
					this->next %= this->particles.size();
				}
			}
		}

		std::array<typename TParticleProcessor::Particle, limit> particles;
		TParticleProcessor processor;

		std::size_t next;
		
		sf::VertexArray vertexArray;
		
		sf::Vector2f position;
		double rotation;
	};
};