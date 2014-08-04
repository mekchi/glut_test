
#include "arc.h"

#include <GL/gl.h>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


MekArc2D::MekArc2D(unsigned int segment)
{
    m_NumberSegment = segment;
    m_TotalNumberVertex = (segment + 1) * 2;
    m_DataSize = sizeof(glm::vec3) * m_TotalNumberVertex;
    m_Data.reset(new glm::vec3[m_TotalNumberVertex]);
}

void* MekArc2D::GetData()
{
    return glm::value_ptr((m_Data.get())[0]);
}

unsigned int MekArc2D::GetDataSize()
{
    return m_DataSize;
}

unsigned int MekArc2D::GetCount()
{
    return m_NumberVertex;
}

unsigned int MekArc2D::GetStride()
{
    return sizeof(glm::vec3);
}

int MekArc2D::GetOpenGLDrawType()
{
    return GL_TRIANGLE_STRIP;
}

void MekArc2D::Init(float radius, float width, float startAngle, float totalAngle, float t)
{
    float tt = 0.0f;
    float t_step = 1.0f / m_NumberSegment;

    m_Start = glm::angleAxis(startAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    m_End = glm::angleAxis(startAngle + totalAngle, glm::vec3(0.0f, 0.0f, 1.0f));


    for (int i = 0; i < m_TotalNumberVertex; ++i, tt += t_step)
    {
        glm::vec3 v = glm::slerp(m_Start, m_End, tt) * glm::vec3(1.0f, 0.0f, 0.0f);

        m_Data[i] = v * radius;
        m_Data[++i] = v * (radius + width);
    }

    m_NumberVertex = ((int)(m_NumberSegment * t) + 1) * 2;
}

void MekArc2D::Update(float t)
{
    m_NumberVertex = ((int)(m_NumberSegment * t) + 1) * 2;
}
