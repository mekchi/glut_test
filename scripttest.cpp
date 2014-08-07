
#include "scripttest.h"

ScriptTest::ScriptTest()
{
    m_state = NULL;
}

ScriptTest::~ScriptTest()
{
    lua_close(m_state);
    m_state = NULL;
}

bool ScriptTest::Init()
{
    m_state = lua_newstate();

    static const luaL_Reg luaLibs[] =
    {
        {"base", luaopen_base },
        { NULL,  NULL }
    };

    const luaL_Reg *lib = luaLibs;

    for (; lib->func != NULL; ++lib)
    {
        lib->func(m_state);
        lua_settop(m_state, 0);
    }
}

bool ScriptTest::RunFile(std::string &file)
{
    return !luaL_dofile(m_state, file.c_str());
}
