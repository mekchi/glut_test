#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <memory>
#include <glm/glm.hpp>

class Environment
{

public:

    Environment();

    bool Init();
    void Update(float t);
    void Draw();

private:

    std::unique_ptr<glm::vec3[]> m_heights;

};

#endif // ENVIRONMENT_H
