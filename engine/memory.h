#ifndef MEMORY_H
#define MEMORY_H

class Memory
{

public:

    enum MEMORY_TYPE
    {
        VERTEX = 0,
        TEXCOORD,
        NORMAL,
        VELOCITY,
        POSITION,
        ROTATION,
        INDEX,
        UNSPECIFIED
    };

    Memory();

    unsigned int Reserve(MEMORY_TYPE type, unsigned int number);
    void* Request(unsigned int reservation);





};

#endif // MEMORY_H
