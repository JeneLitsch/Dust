#pragma once
#include "sfml.hxx"
#include <mutex>
#include <atomic>
#include <future>
#include <iostream>
#include <functional>
#include <chrono>
namespace dust {
	// Decorator  
	template<class ParticleSystem>
	class ThreadParticleSystem : public ParticleSystem {
	public:
		ThreadParticleSystem() {
			this->tps = 60;
		}

		void start() {
			this->running = true;
			this->thread = std::thread(std::bind(&ThreadParticleSystem::run, this));
		}

		void setTickLimit(unsigned tps) {
			this->tps = tps;
		}

		virtual void update(double dt) override {
			(void)(dt);
		}
		
		virtual void render(sf::RenderTarget & renderTarget) override {
			const std::lock_guard<std::mutex> lock(mutex);
			this->ParticleSystem::draw(renderTarget, this->vertexCount);
		}

		virtual ~ThreadParticleSystem() {
			this->running = false;
			thread.join();
		}
	private:
		void run() {
			while(running) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1000/this->tps));
				const std::lock_guard<std::mutex> lock(mutex);
				this->ParticleSystem::update(1.f/float(this->tps));
				this->vertexCount = this->ParticleSystem::fillVertexArray();
			}
		}
		unsigned tps;
		std::mutex mutex;
		std::atomic<bool> running;
		std::atomic<std::size_t> vertexCount;
		std::thread thread;
	};
}