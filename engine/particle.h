#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>
#include <memory>

struct Particle
{
    std::unique_ptr<glm::vec3[]> position;
    std::unique_ptr<glm::quat[]> rotation;

};


#endif // PARTICLE_H
