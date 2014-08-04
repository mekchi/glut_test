#ifndef ARC_H
#define ARC_H

#include <memory>
#include <glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

class MekArc2D
{
public:

    MekArc2D(unsigned int segment = 20);
    void Init(float radius, float width, float startAngle, float totalAngle, float t = 1.0f);
    int GetOpenGLDrawType();

    void* GetData();
    unsigned int GetDataSize();
    unsigned int GetCount();
    unsigned int GetStride();

    void Update(float t);

private:

    glm::quat m_Start;
    glm::quat m_End;

    std::unique_ptr<glm::vec3[]> m_Data;

    unsigned int m_NumberSegment;
    unsigned int m_TotalNumberVertex;
    unsigned int m_DataSize;
    unsigned int m_NumberVertex;
};


#endif
