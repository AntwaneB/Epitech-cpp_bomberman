#include "Core/Lua.hh"
#include "Core/IA.hpp"

extern std::vector<std::vector<IA::Area> > objects;

Lua::Lua()
{

}

Lua::~Lua()
{
    
}

int Lua::luaGetObjects(lua_State *L)
{
    luaL_getmetatable(L, "luaL_Object");
    lua_setmetatable(L, -2);
    return 1;
}

int Lua::luaGetDestructible(lua_State *L)
{
    int key = luaL_checknumber(L, 2);
    int key2 = luaL_checknumber(L, 3);

    lua_pushboolean(L, objects[key - 1][key2 - 1].destructible());

    return 1;
}

int Lua::luaGetExplosion(lua_State *L)
{
    int key = luaL_checknumber(L, 2);
    int key2 = luaL_checknumber(L, 3);

    lua_pushboolean(L, objects[key - 1][key2 - 1].explosion());

    return 1;
}

int Lua::luaGetBomb(lua_State *L)
{
    int key = luaL_checknumber(L, 2);
    int key2 = luaL_checknumber(L, 3);


    lua_pushboolean(L, objects[key - 1][key2 - 1].bomb());

    return 1;
}

int Lua::luaGetEnemy(lua_State *L)
{
    int key = luaL_checknumber(L, 2);
    int key2 = luaL_checknumber(L, 3);

    lua_pushnumber(L, objects[key - 1][key2 - 1].enemy());

    return 1;
}

int Lua::luaGetHistory(lua_State *L)
{
    int key = luaL_checknumber(L, 2);
    int key2 = luaL_checknumber(L, 3);

    lua_pushnumber(L, objects[key - 1][key2 - 1].history());

    return 1;
}

int Lua::luaGetWall(lua_State *L)
{
    int key = luaL_checknumber(L, 2);
    int key2 = luaL_checknumber(L, 3);
    
    lua_pushnumber(L, objects[key - 1][key2 - 1].wall());

    return 1;
}

void Lua::registerObject(lua_State *L)
{
    luaL_Reg regs[] =
    {
        { "getExplosion", this->luaGetExplosion },
        { "getBomb", this->luaGetBomb },
        { "getEnemy", this->luaGetEnemy },
        { "getHistory", this->luaGetHistory },
        { "getWall", this->luaGetWall },
        { "getDestructible", this->luaGetDestructible },
        { NULL, NULL }
    };

    luaL_newmetatable(L, "luaL_Object");
    luaL_setfuncs(L, regs, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
}
