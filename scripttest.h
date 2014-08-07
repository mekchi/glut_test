#ifndef SCRIPTTEST_H
#define SCRIPTTEST_H

#include <string>
#include <lua5.2/lua.hpp>
//#include <lua5.2/lualib.h>
//#include <lua5.2/lauxlib.h>

class ScriptTest
{

public:

    ScriptTest();
    ~ScriptTest();

    bool Init();
    bool RunFile(std::string &file);

private:

    lua_State *m_state;
};

#endif // SCRIPTTEST_H
