extern "C" {
	#include <lua5.2/lua.h>
	#include <lua5.2/lauxlib.h>
	#include <lua5.2/lualib.h>
}

int main(int argc, char **argv){
	lua_State *L = luaL_newstate() ;
	luaL_dostring(L, "a = 10 + 5");
	lua_getglobal(L, "a");
	int i=lua_tointeger(L, -1);
	printf("%d\n", i);

	lua_close(L);

	return 0 ;
}
