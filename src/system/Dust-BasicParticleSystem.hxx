#pragma once

#include "Dust-IParticleSystem.hxx"
#include <vector>
#include "sfml.hxx"
#include <future>

namespace dust {
	template<class TParticleProcessor, std::size_t limit>
	class BasicParticleSystem : public IParticleSystem {
	public:
		BasicParticleSystem(
			const TParticleProcessor & processor) 
			:	processor(processor) {
			this->position = sf::Vector2f(0,0);
			this->next = 0;
			vertexArray.setPrimitiveType(sf::PrimitiveType::Quads);
		}
		
		virtual ~BasicParticleSystem() = default;

		virtual void update(double dt) override final {
			for(auto & particle : particles) {
				if(particle) {
					processor.process(particle, dt);
				}
			}
		}


		virtual void render(sf::RenderTarget & renderTarget) override final {
			this->vertexArray.clear();
			sf::RenderStates states;
			states.transform = sf::Transform().translate(this->position);
			for(std::size_t i = 0; i < limit; i++) {
				std::size_t idx = (this->next + i) % limit;
				if(particles[idx]) {
					processor.render(particles[idx], vertexArray);
				}
			}
			renderTarget.draw(vertexArray, states);
		}


		virtual void setPosition(sf::Vector2f position) override final{
			this->position = position;
		}


		virtual void emit(std::size_t amount) override final {
			if(!this->particles[this->next]) {
				for(std::size_t i = 0; i < amount; i++) {
					processor.emit(this->particles[this->next]);
					this->next++;
					this->next %= this->particles.size();
				}
			}
		}

	private:
		std::array<typename TParticleProcessor::Particle, limit> particles;
		TParticleProcessor processor;
		std::size_t next;
		sf::Vector2f position;
		sf::VertexArray vertexArray;
	};
};