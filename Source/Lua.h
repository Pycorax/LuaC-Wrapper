#pragma once

// STL Includes
#include <string>
#include <vector>

// LUA Includes
extern "C"
{
	#include "Lua/include/lua.h"
	#include "Lua/include/lualib.h"
	#include "Lua/include/lauxlib.h"
}

// Other Includes
#include "LuaType.h"

// Using Directives
using std::string;
using std::vector;

namespace Lua
{
	// Type Definitions
	typedef vector<LuaTypePtr> LuaFuncList;

	class LuaFile
	{
	private:
		lua_State* m_luaState;
		bool m_scriptExecuted;

	public:
		LuaFile(string luaFile);
		~LuaFile(void);

		// Life time
		bool RunScript(void);

		/*
		 * Variable Acquisition
		 */
		 // Functions to get values from the stack
		LuaTypePtr GetValue(string varName);
		double GetNumber(string varName);
		bool GetBoolean(string varName);
		string GetString(string varName);

		/*
		 * Lua Function Importing
		 */
		LuaTypePtr Call(string functionName, int expectedResults, vector<LuaTypePtr> params);

		/*
		 * C++ Function Exporting
		 */
		void RegisterFunction(string funcName, lua_CFunction func);

	private:
		// For script loading
		bool loadScript(string filename);
		// For converting the top value in the stack into a LuaTypePtr
		LuaTypePtr getTopLuaValue(void);
	};
}