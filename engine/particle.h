#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>
#include <memory>

struct Particle
{
    std::unique_ptr<glm::vec3> position;

};


#endif // PARTICLE_H
