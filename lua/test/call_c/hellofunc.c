#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>

static int isquare(lua_State *L){
	float rtrn = lua_tonumber(L, -1) ; /* Getthe single number argument. */
	printf("Top of square(), nbr=%f\n", rtrn);
	lua_pushnumber(L, rtrn*rtrn); /* Push the return. */
	return 1 ; /* One return value. */
}

static int icube(lua_State *L){
	float rtrn = lua_tonumber(L, -1) ;
	printf("Top of cube(), number=%f\n", rtrn);
	lua_pushnumber(L, rtrn*rtrn*rtrn);
	return 1 ;
}

int luaopen_power(lua_State *L){
	puts("C:Registering 'isquare'");
	lua_register(
			L,          /* Lua statement. */
			"square",   /* Function name to use in Lua. */
			isquare     /* Function pointer. */
	);

	puts("C:Registering 'icube'");
	lua_register(L, "cube", icube);
	return 0 ;
}
