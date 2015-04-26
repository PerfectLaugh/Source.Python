/**
* =============================================================================
* Source Python
* Copyright (C) 2015 Source Python Development Team.  All rights reserved.
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

#ifndef _CVARS_WRAP_H
#define _CVARS_WRAP_H

//-----------------------------------------------------------------------------
// Includes.
//-----------------------------------------------------------------------------
#include "convar.h"


//-----------------------------------------------------------------------------
// ConVar extension class.
//-----------------------------------------------------------------------------
class ConVarExt
{
public:
	static void Deleter(ConVar *pConVar)
	{
		// Do nothing...
	}

	static boost::shared_ptr<ConVar> __init__(const char *szName, const char *szDefaultValue, int flags,
		const char *szHelpString, bool bMin, float fMin, bool bMax, float fMax)
	{
		ConVar *pConVar = g_pCVar->FindVar(szName);
		if (!pConVar)
		{
			return boost::shared_ptr<ConVar>(new ConVar(strdup(szName), szDefaultValue, flags,
				strdup(szHelpString), bMin, fMin, bMax, fMax), &Deleter);
		}
		return boost::shared_ptr<ConVar>(pConVar, &Deleter);
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


#endif // _CVARS_WRAP_H
