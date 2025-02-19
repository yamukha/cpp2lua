
#include <string.h>
#include <string>

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// sudo apt-get install liblua5.1-0-dev
// locate lua.h
// locate liblua5.1.a
// g++ -I/usr/include/lua5.1 lua.cpp -llua5.1 -ldl -o luatest
// http://lua-users.org/wiki/JsonModules
// https://github.com/grafi-tt/lunajson

std::string lunajson = R"(
local lunajson = require 'lunajson'
function converter(val)
      local jobj = lunajson.decode(val)
      jobj[1] = 11
      jobj[2] = 22
      jobj[3] = 33
      jobj[4] ['x']= 44
      return lunajson.encode(jobj)
end
)";

int main(int argc, char *argv[])
{
      lua_State *L = luaL_newstate(); // > v5.1
      luaL_openlibs(L);

      int load_stat = luaL_loadbuffer(L, lunajson.c_str(), strlen(lunajson.c_str()), "json");
      lua_pcall(L, 0, 0, 0);

      lua_getglobal(L, "converter");
      if (lua_isfunction(L, -1))
      {
            std::string jstr = R"([1,2,3,{"x":10},{"y":12} ])";
            lua_pushlstring(L, jstr.c_str(), strlen(jstr.c_str()));
            lua_pcall(L, 1, 1, 0);
            const char *pValue;

            if (!lua_isnil(L, -1))
            {
                  pValue = lua_tostring(L, -1);
                  lua_pop(L, 1);
                  printf("res = '%s'\n", pValue);
            }
            else
                  printf("Error in function\n");
      }
      else
            printf("Error in call\n");

      lua_close(L);
      return 0;
}
