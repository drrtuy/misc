#include <iostream>
#include <cstdint>
#include <fstream>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <stdlib.h>
#include <string.h>

int le_init();
int le_loadexpr(const char *expr);
double le_eval(int cookie);
void le_unref(int cookie);
void le_setvar(char *name, double value);
double le_getvar(char *name);
double f(double arg, int cookie);

static lua_State *L = NULL;
char indepVar[] = "x";

using namespace std;

int main(int argc, char **argv)
{
    string funcText;
    string lowText;
    string highText;
    string numPointsText;
    ifstream input("input.txt");
    if (input.is_open())
    {
        getline(input, funcText);
        getline(input, lowText);
        getline(input, highText);
        getline(input, numPointsText);
    }
    //string funcText[] = "2*x";
    double low = 1.0;
    double high = 2.0;
    double numPoints = 5000.0; 
    double integral = 0.0;

    le_init();
    int cookie = le_loadexpr(funcText.c_str());

    double step = (high - low) / numPoints;
    high = low;
    for(int i = 0; i < numPoints; i++)
    {
        high += step;
        integral += ( f(high, cookie) + f(low, cookie) ) / 2 * step;
        low += step;
    }

    std::cout << "Приближённое значение интеграла: " << integral << std::endl;

    return 0;
}

// Init Lua interpreter state.
int le_init()
{
    L = luaL_newstate();
    if (L)
    {
        luaL_openlibs(L);
    }
    return !!L;
}

// Load math expression into Lua state. 
int le_loadexpr(const char *expr)
{
    int err;

    if (!L)
    {
        cout << "LE library not initialized" << endl;
        return LUA_NOREF;
    }

    char *buf = new char(strlen(expr)+8);
    
    strcpy(buf, "return ");
    strcat(buf, expr);
    err = luaL_loadstring(L, buf);
    delete buf;
    if (err)
    {
        cerr << lua_tostring(L,-1) << endl;
        lua_pop(L,1);
        return LUA_NOREF;
    }
    
    return luaL_ref(L, LUA_REGISTRYINDEX);
}

// Evaluate math expression using Lua interpreter
double le_eval(int cookie)
{
    int err;
    double ret;

    if (!L)
    {
        cout << "LE library not initialized" << endl;
        return 0;
    }
        
    lua_rawgeti(L, LUA_REGISTRYINDEX, cookie);
    err = lua_pcall(L,0,1,0);
    if (err)
    {
        cerr << lua_tostring(L,-1) << endl;
        lua_pop(L,1);
        return 0;
    }

    ret = static_cast<double>(lua_tonumber(L,-1));
    lua_pop(L,1);
    return ret;
}

// Bind value with math variable 
void le_setvar(char *name, double value)
{
    if (!L)
    {
        return;
    }
    lua_pushnumber(L,value);
    lua_setglobal(L,name);
}

// Bind a value and evaluate the expression
double f(double arg, int cookie)
{
    le_setvar(indepVar, arg);
    return le_eval(cookie);
}
