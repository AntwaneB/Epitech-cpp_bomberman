#ifndef LUA_HH_
# define LUA_HH_

extern "C"
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
    #include <lua.hpp>
}

#include <map>
#include <iostream>
#include <vector>
#include <cstdlib>

class Lua
{
public:
	Lua();
	~Lua();

	static int luaGetObjects(lua_State *L);
	static int luaGetExplosion(lua_State *L);
	static int luaGetBomb(lua_State *L);
	static int luaGetEnemy(lua_State *L);
	static int luaGetHistory(lua_State *L);
	static int luaGetWall(lua_State *L);
	static int luaGetDestructible(lua_State *L);
	void registerObject(lua_State *L);

	/* data */
};
#endif /* !LUA_HH_ */