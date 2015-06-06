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

	static int luaGetObjects(lua_State *);
	static int luaGetExplosion(lua_State *);
	static int luaGetBomb(lua_State *);
	static int luaGetEnemy(lua_State *);
	static int luaGetHistory(lua_State *);
	static int luaGetWall(lua_State *);
	static int luaGetDestructible(lua_State *);
	void registerObject(lua_State *);

	/* data */
};
#endif /* !LUA_HH_ */