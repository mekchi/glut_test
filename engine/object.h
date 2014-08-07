#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace mekchi
{

struct Objects
{
    std::unique_ptr<glm::vec3[]> position;
};

//struct Object
//{
//    glm::vec3 position;
//    glm::quat rotation;
//};

}

#endif // OBJECT_H
