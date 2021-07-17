#include "Dust-SingleColor.hxx"
#include <cmath>

dust::SingleColor::SingleColor(
	sf::Color color,
	float rotationSpeed,
	float lifetime) 
:	color(color),
	Colored(rotationSpeed, lifetime) {}


void dust::SingleColor::process(Particle & particle, double dt) const {
	float arch = float(std::sin(particle.age/this->lifetime * 3.14f));
	
	particle.age += float(dt);
	particle.alive = particle.age <= lifetime;
		
	particle.position += particle.velocity * float(dt) * arch;
	
	particle.size.x = 32.f * arch;
	particle.size.y = 32.f * arch;

	particle.rotation +=  float(dt) * rotationSpeed;
	particle.color = this->color;
}



