#include "Dust-Colored.hxx"

dust::Colored::Colored(
	float rotationSpeed,
	float lifetime) 
:	rotationSpeed(360.0 * rotationSpeed),
	lifetime(lifetime) {}


void dust::Colored::emit(Particle & particle) const {
	particle.velocity.x = 10.f * float(rand() % 100 - 50);
	particle.velocity.y = 10.f * float(rand() % 100 - 50);

	particle.position.x = 0.f;
	particle.position.y = 0.f;

	particle.size.x = 0.f;
	particle.size.y = 0.f;

	particle.alive = true;
	particle.age = 0.0;
	particle.rotation = 0.0;
}


void dust::Colored::render(Particle & particle, sf::VertexArray & vertexArray) const {
	sf::Transform transform;
	transform
		.translate(particle.position)
		.rotate(particle.rotation);
	
	vertexArray.append(sf::Vertex(
		transform.transformPoint(sf::Vector2f(
			-particle.size.x / 2.f,
			-particle.size.y / 2.f)),
		particle.color));

	vertexArray.append(sf::Vertex(
		transform.transformPoint(sf::Vector2f(
			+particle.size.x / 2.f,
			-particle.size.y / 2.f)),
		particle.color));

	vertexArray.append(sf::Vertex(
		transform.transformPoint(sf::Vector2f(
			+particle.size.x / 2.f,
			+particle.size.y / 2.f)),
		particle.color));

	vertexArray.append(sf::Vertex(
		transform.transformPoint(sf::Vector2f(
			-particle.size.x / 2.f,
			+particle.size.y / 2.f)),
		particle.color));
}
