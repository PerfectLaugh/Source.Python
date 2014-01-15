/**
* =============================================================================
* Source Python
* Copyright (C) 2012 Source Python Development Team.  All rights reserved.
* =============================================================================
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License, version 3.0, as published by the
* Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with
* this program.  If not, see <http://www.gnu.org/licenses/>.
*
* As a special exception, the Source Python Team gives you permission
* to link the code of this program (as well as its derivative works) to
* "Half-Life 2," the "Source Engine," and any Game MODs that run on software
* by the Valve Corporation.  You must obey the GNU General Public License in
* all respects for all other code used.  Additionally, the Source.Python
* Development Team grants this exception to all derivative works.
*/

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "icvar.h"
#include "convar.h"
#include "modules/export_main.h"


//-----------------------------------------------------------------------------
// External variables
//-----------------------------------------------------------------------------
extern ICvar* g_pCVar;


//-----------------------------------------------------------------------------
// Exposes the cvar module.
//-----------------------------------------------------------------------------
void export_cvar_interface();
void export_concommandbase();
void export_convar();
void export_flags();

DECLARE_SP_MODULE(cvar_c)
{
	export_cvar_interface();
	export_concommandbase();
	export_convar();
	export_flags();
}

//-----------------------------------------------------------------------------
// Exposes the CCvar interface.
//-----------------------------------------------------------------------------
void export_cvar_interface()
{
	def("get_cvar_interface", make_getter(&g_pCVar, reference_existing_object_policy()));

	// TODO: Rename it?
	class_<ICvar, boost::noncopyable>("CCvar", no_init)
		.def("register_con_command",
			&ICvar::RegisterConCommand,
			"Registers a console command.",
			args("con_command")
		)

		.def("unregister_con_command",
			&ICvar::UnregisterConCommand,
			"Unregisters a console command.",
			args("con_command")
		)

		.def("find_command_base",
			GET_METHOD(ConCommandBase *, ICvar, FindCommandBase, const char*),
			"Returns a CConCommandBase instance for the given command, if it exists",
			args("szName"),
			reference_existing_object_policy()
		)

		.def("find_var",
			GET_METHOD(ConVar*, ICvar, FindVar, const char *),
			"Returns a CConVar instance for the given cvar, if it exists",
			args("szName"),
			reference_existing_object_policy()
		)
	;
}

//-----------------------------------------------------------------------------
// Exposes the CConCommandBase interface.
//-----------------------------------------------------------------------------
void export_concommandbase()
{
	// TODO: rename?
	class_<ConCommandBase>("CConCommandBase")
		.def(init< const char*, optional< const char*, int> >())

		.def("is_command",
			&ConCommandBase::IsCommand,
			"Returns whether it's a command."
		)

		.def("is_flag_set",
			&ConCommandBase::IsFlagSet,
			"Returns whether the given flag is set or not.",
			args("flag")
		)

		.def("add_flags",
			&ConCommandBase::AddFlags,
			"Adds the given flags to the ConVar.",
			args("flag")
		)

		.def("remove_flags",
			&ConCommandBase::RemoveFlags,
			"Removes the given flags from the ConVar.",
			args("flag")
		)
		
		.def("get_flags",
			&ConCommandBase::GetFlags,
			"Returns its flags."
		)
		
		.def("get_name",
			&ConCommandBase::GetName,
			"Returns its name."
		)

		.def("get_help_text",
			&ConCommandBase::GetHelpText,
			"Returns the help text."
		)

		.def("get_next",
			GET_METHOD(ConCommandBase*, ConCommandBase, GetNext),
			"Returns the next ConCommandBase instance.",
			reference_existing_object_policy()
		)

		.def("is_registered",
			&ConCommandBase::IsRegistered,
			"Returns wheter the ConCommandBase instance is registered."
		)

		.def("get_dll_identifier",
			&ConCommandBase::GetDLLIdentifier,
			"Returns the DLL identifier."
		)
	;

	class_<IConVar, boost::noncopyable>("IConVar", no_init)
		.def("set_string",
			GET_METHOD(void, IConVar, SetValue, const char*),
			args("value")
		)

		.def("set_float",
			GET_METHOD(void, IConVar, SetValue, float),
			args("value")
		)

		.def("set_int",
			GET_METHOD(void, IConVar, SetValue, int),
			args("value")
		)

		.def("get_name",
			&IConVar::GetName,
			"Returns its name."
		)

		.def("is_flag_set",
			&IConVar::IsFlagSet,
			"Returns whether the given flag is set."
		)
	;
}

//-----------------------------------------------------------------------------
// Exposes the CConVar interface.
//-----------------------------------------------------------------------------
class ConVarExt
{
public:
	static ConVar* CreateConVar( const char *pName )
	{
		return new ConVar(pName, "");
	}

	static bool HasMin(ConVar* pConVar)
	{
		float fMin;
		return pConVar->GetMin(fMin);
	}

	static bool HasMax(ConVar* pConVar)
	{
		float fMax;
		return pConVar->GetMax(fMax);
	}

	static float GetMin(ConVar* pConVar)
	{
		float fMin;
		pConVar->GetMin(fMin);
		return fMin;
	}

	static bool GetMax(ConVar* pConVar)
	{
		float fMax;
		pConVar->GetMax(fMax);
		return fMax;
	}

	static void SetValue(ConVar* pConVar, bool bValue)
	{
		pConVar->SetValue(bValue);
	}
};

void export_convar()
{
	// TODO: Rename it?
	class_<ConVar, bases<ConCommandBase, IConVar>, boost::noncopyable >("CConVar", init<const char *, const char *, optional< int > >())
		.def(init<const char *, const char *, int, const char *>())
		.def(init<const char *, const char *, int, const char *, bool, float, bool , float>())
		.def("__init__", make_constructor(&ConVarExt::CreateConVar))
		
		.def("get_float",
			&ConVar::GetFloat,
			"Returns the value as a float."
		)

		.def("__float__",
			&ConVar::GetFloat,
			"Returns the value as a float."
		)

		.def("get_int",
			&ConVar::GetInt,
			"Returns the value as an int."
		)

		.def("__int__",
			&ConVar::GetInt,
			"Returns the value as an int."
		)

		.def("get_bool",
			&ConVar::GetBool,
			"Returns the value as a bool."
		)

		.def("__bool__",
			&ConVar::GetBool,
			"Returns the value as a bool."
		)

		.def("get_string",
			&ConVar::GetString,
			"Returns the value as a string."
		)

		.def("__str__",
			&ConVar::GetString,
			"Returns the value as a string."
		)

		.def("revert",
			&ConVar::Revert,
			"Resets to default value."
		)

		.def("get_default",
			&ConVar::GetDefault,
			"Returns the default value."
		)

		.def("has_min",
			&ConVarExt::HasMin,
			"Returns wether the ConVar has a minimum value."
		)

		.def("has_max",
			&ConVarExt::HasMax,
			"Returns wether the ConVar has a maximum value."
		)

		.def("get_min",
			&ConVarExt::GetMin,
			"Returns the minimum value."
		)

		.def("get_max",
			&ConVarExt::GetMax,
			"Returns the maximum value."
		)

		.def("set_bool",
			&ConVarExt::SetValue,
			"Sets a bool value.",
			args("value")
		)
	;
}

void export_flags()
{
	scope().attr("FCVAR_NONE")                  = FCVAR_NONE;
	scope().attr("FCVAR_UNREGISTERED")          = FCVAR_UNREGISTERED;
	scope().attr("FCVAR_DEVELOPMENTONLY")       = FCVAR_DEVELOPMENTONLY;
	scope().attr("FCVAR_GAMEDLL")               = FCVAR_GAMEDLL;
	scope().attr("FCVAR_CLIENTDLL")             = FCVAR_CLIENTDLL;
	scope().attr("FCVAR_PROTECTED")             = FCVAR_PROTECTED;
	scope().attr("FCVAR_ARCHIVE")               = FCVAR_ARCHIVE;
	scope().attr("FCVAR_NOTIFY")                = FCVAR_NOTIFY;
	scope().attr("FCVAR_USERINFO")              = FCVAR_USERINFO;
	scope().attr("FCVAR_PRINTABLEONLY")         = FCVAR_PRINTABLEONLY;
	scope().attr("FCVAR_UNLOGGED")              = FCVAR_UNLOGGED;
	scope().attr("FCVAR_NEVER_AS_STRING")       = FCVAR_NEVER_AS_STRING;
	scope().attr("FCVAR_REPLICATED")            = FCVAR_REPLICATED;
	scope().attr("FCVAR_CHEAT")                 = FCVAR_CHEAT;
	scope().attr("FCVAR_DEMO")                  = FCVAR_DEMO;
	scope().attr("FCVAR_DONTRECORD")            = FCVAR_DONTRECORD;
	scope().attr("FCVAR_NOT_CONNECTED")         = FCVAR_NOT_CONNECTED;
	scope().attr("FCVAR_ARCHIVE_XBOX")          = FCVAR_ARCHIVE_XBOX;
	scope().attr("FCVAR_SERVER_CAN_EXECUTE")    = FCVAR_SERVER_CAN_EXECUTE;
	scope().attr("FCVAR_SERVER_CANNOT_QUERY")   = FCVAR_SERVER_CANNOT_QUERY;
	scope().attr("FCVAR_CLIENTCMD_CAN_EXECUTE") = FCVAR_CLIENTCMD_CAN_EXECUTE;
}
