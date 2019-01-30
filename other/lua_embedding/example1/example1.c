#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "luajit.h"

int main(void){
	char buf[256];
	int err;
	lua_State *L = luaL_newstate() ; /* Opens Lua.                */
	luaL_openlibs(L);
	
	while(  fgets( buf, sizeof(buf), stdin ) != NULL  ){
		err = luaL_loadbuffer(L, buf, strlen(buf), "line")\
			  || lua_pcall(L, 0, 0, 0)
		;
		if(err){
			fprintf(stderr, "%s", lua_tostring(L, -1));
			lua_pop(L, 1); /* Pop error message from the stack. */
		}
	}

	/* Successful exit. */
	lua_close(L);
	return 0 ;
}
