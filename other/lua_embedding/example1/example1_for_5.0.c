#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int main(void){
	char buf[256];
	int err;
	lua_State *L = lua_open() ; /* Opens Lua.                */
	luaopen_base(L);            /* Opens the basic library.  */
	luaopen_table(L);           /* Opens the table library.  */
	luaopen_io(L);              /* Opens the I/O library.    */
	luaopen_string(L);          /* Opens the string library. */
	luaopen_math(L);            /* Opens the math library.   */
	
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
