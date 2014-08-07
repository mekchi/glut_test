#ifndef SYSTEM_GLOBAL_H
#define SYSTEM_GLOBAL_H

#include <memory>
#include <glm/glm.hpp>

struct Objects
{
    std::unique_ptr<glm::vec3[]> position;

};

#endif // SYSTEM_GLOBAL_H
