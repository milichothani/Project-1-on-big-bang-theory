#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PARTICLE_COUNT = 300; // Number of particles in the explosion
const float MAX_SPEED = 200.0f; // Maximum speed of particles
const float PLANET_RADIUS = 20.0f; // Radius of the Earth-like planet
const float ORBIT_RADIUS = 100.0f; // Radius of the planet's orbit

struct Particle {
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Particle(float x, float y) {
        shape.setRadius(2.0f);
        shape.setFillColor(sf::Color::White);
        shape.setPosition(x, y);
        float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159f; // Random angle
        float speed = static_cast<float>(rand()) / RAND_MAX * MAX_SPEED; // Random speed
        velocity = sf::Vector2f(speed * cos(angle), speed * sin(angle));
    }

    void update(float deltaTime) {
        sf::Vector2f position = shape.getPosition();
        position += velocity * deltaTime;
        shape.setPosition(position);
    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Big Bang Simulation with Planet");

    // Create particles for explosion
    std::vector<Particle> particles;
    for (int i = 0; i < PARTICLE_COUNT; ++i) {
        particles.emplace_back(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    }

    // Create the planet (Earth-like)
    sf::CircleShape planet(PLANET_RADIUS);
    planet.setFillColor(sf::Color(0, 100, 255)); // Earth color
    planet.setPosition(WINDOW_WIDTH / 2 - PLANET_RADIUS, WINDOW_HEIGHT / 2 - PLANET_RADIUS); // Start at the center

    // Planet orbit variables
    float planetAngle = 0.0f; // Initial angle for orbit
    float planetSpeed = 20.0f; // Reduced speed of the planet's orbit

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Update particles
        float deltaTime = clock.restart().asSeconds();
        for (auto& particle : particles) {
            particle.update(deltaTime);
            window.draw(particle.shape);
        }

        // Update planet position (circular motion)
        planetAngle += planetSpeed * deltaTime; // Update angle
        float planetX = WINDOW_WIDTH / 2 + ORBIT_RADIUS * cos(planetAngle) - PLANET_RADIUS;
        float planetY = WINDOW_HEIGHT / 2 + ORBIT_RADIUS * sin(planetAngle) - PLANET_RADIUS;
        planet.setPosition(planetX, planetY);

        // Draw the planet
        window.draw(planet);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
