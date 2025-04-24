#include "config.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

struct Vec2 {
    float x;
    float y;

    Vec2() : x(0.0f), y(0.0f) {}
    Vec2(float x, float y) : x(x), y(y) {}
    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }
    Vec2 operator*(float scalar) const {
        return Vec2(x * scalar, y * scalar);;
    }
};

struct Particle {
    Vec2 position;
    Vec2 velocity;
    float mass;
    float lifetime;
    float age;
    float brightness;
};



void launchFirework(std::vector<Particle>& particles, Vec2 origin, int count = 50) {
    for (int i = 0; i < count; ++i) {
        float angle = ((float)i / count) * 2.0f * M_PI;
        float speed = ((rand() % 100) / 100.0f) * 100.0f;
        Particle p;
        p.position = origin;
        p.velocity = Vec2(cos(angle), sin(angle)) * speed;
        p.mass = 1.0f;
        p.lifetime = 3.0f;
        p.age = 0.0f;
        p.brightness = 1.0f;
        
        particles.push_back(p);

    }
}
void updateParticles(std::vector<Particle>& particles, float dt) {

    Vec2 gravity(0.0f, -9.8f);
    
    for (std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it) {
        Particle& p = *it;
        Vec2 airResistance = p.velocity * -0.1f; // Simple linear drag
        Vec2 acceleration = gravity + airResistance * (1.0f / p.mass);

        p.velocity = p.velocity + acceleration * dt;
        p.position = p.position + p.velocity * dt;
        p.age += dt;
        p.brightness = 1.0f - (p.age / p.lifetime);
    }

    // Remove dead particles
    particles.erase(
        std::remove_if(particles.begin(), particles.end(), [](const Particle& p) {
            return p.age >= p.lifetime;
        }),
        particles.end()
    );
}

void drawParticles(const std::vector<Particle>& particles) {

}
int main() {
    GLFWwindow* window;

    if(!glfwInit()) {
        std::cout << "GLFW couldn't be initialized" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    window = glfwCreateWindow(640, 480, "My Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    #ifndef GL_SILENCE_DEPRECATION
    #define GL_SILENCE_DEPRECATION
    #endif
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(3.0f);
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
    std::vector<Particle> particles;
    while (!glfwWindowShouldClose(window)) {

        float dt = 1.0f / 60.0f;
        glClear(GL_COLOR_BUFFER_BIT);

        // updateParticles(particles, dt);
        // drawParticles(particles);

        // launchFirework(particles, Vec2(0.0f, 0.0f));
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}