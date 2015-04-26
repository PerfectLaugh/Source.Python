/**
* =============================================================================
* Source Python
* Copyright (C) 2014 Source Python Development Team.  All rights reserved.
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

#ifndef _ENGINES_WRAP_CSGO_H
#define _ENGINES_WRAP_CSGO_H

//-----------------------------------------------------------------------------
// Includes.
//-----------------------------------------------------------------------------
#include "engine/IEngineSound.h"


//-----------------------------------------------------------------------------
// IEngineSound extension class.
//-----------------------------------------------------------------------------
class IEngineSoundExt
{
public:
	static void EmitSound(IEngineSound* pEngineSound, IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSample, 
		float flVolume, float flAttenuation, int iFlags = 0, int iPitch = PITCH_NORM, const Vector *pOrigin = NULL, const Vector *pDirection = NULL,
		tuple origins = tuple(), bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1)
	{
		CUtlVector<Vector> *pUtlVecOrigins = NULL;
		CUtlVector<Vector> vecOrigins;
		if (len(origins) > 0)
		{
			pUtlVecOrigins = &vecOrigins;
			for(int i=0; i < len(origins); i++)
			{
				vecOrigins.AddToTail(extract<Vector>(origins[i]));
			}
		}
		
		pEngineSound->EmitSound(filter, iEntIndex, iChannel, pSample, -1, pSample, flVolume, flAttenuation, 0, iFlags, iPitch, pOrigin, pDirection,
			pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity);
	}
};


//---------------------------------------------------------------------------------
// IEngineTrace
//---------------------------------------------------------------------------------
inline int GetPointContents(const Vector &vecAbsPosition, IHandleEntity** ppEntity)
{
	return enginetrace->GetPointContents(vecAbsPosition, MASK_ALL, ppEntity);
}


#endif // _ENGINES_WRAP_CSGO_H
