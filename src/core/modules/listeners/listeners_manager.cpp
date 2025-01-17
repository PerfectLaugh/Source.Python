/**
* =============================================================================
* Source Python
* Copyright (C) 2012-2015 Source Python Development Team.  All rights reserved.
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
// Includes.
//-----------------------------------------------------------------------------
#include "listeners_manager.h"
#include "sp_main.h"
#include "utilities/sp_util.h"


//-----------------------------------------------------------------------------
// External variables.
//-----------------------------------------------------------------------------
extern ICvar* g_pCVar;
extern CServerOutputListenerManager* GetOnServerOutputListenerManager();


//-----------------------------------------------------------------------------
// Extern functions
//-----------------------------------------------------------------------------
extern CConVarChangedListenerManager* GetOnConVarChangedListenerManager();


//-----------------------------------------------------------------------------
// Adds a callable to the end of the CListenerManager vector.
//-----------------------------------------------------------------------------
void CListenerManager::RegisterListener(PyObject* pCallable)
{
	// Get the object instance of the callable
	object oCallable = object(handle<>(borrowed(pCallable)));

	// Is the callable already in the vector?
	if( !IsRegistered(oCallable) )
	{
		if (!GetCount())
			Initialize();

		m_vecCallables.AddToTail(oCallable);
	}
	else {
		BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Callback already registered.")
	}
}


//-----------------------------------------------------------------------------
// Removes all instances of a callable from the CListenerManager vector.
//-----------------------------------------------------------------------------
void CListenerManager::UnregisterListener(PyObject* pCallable)
{
	// Get the object instance of the callable
	object oCallable = object(handle<>(borrowed(pCallable)));

	int index = FindCallback(oCallable); //m_vecCallables.Find(oCallable);

	if (index == -1) {
		BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Callback not registered.")
	}
	else {
		m_vecCallables.Remove(index);

		if (!GetCount())
			Finalize();
	}
}


//-----------------------------------------------------------------------------
// Notifies all registered callbacks.
//-----------------------------------------------------------------------------
void CListenerManager::Notify(tuple args, dict kwargs)
{
	for(int i = 0; i < m_vecCallables.Count(); i++)
	{
		BEGIN_BOOST_PY()
			m_vecCallables[i](*args, **kwargs);
		END_BOOST_PY_NORET()
	}
}


//-----------------------------------------------------------------------------
// Return the number of registered callbacks.
//-----------------------------------------------------------------------------
int CListenerManager::GetCount()
{
	return m_vecCallables.Count();
}


//-----------------------------------------------------------------------------
// Called when the first callback is being registered.
//-----------------------------------------------------------------------------
void CListenerManager::Initialize()
{
	override initialize = get_override("initialize");
	if (!initialize.is_none())
		initialize();
}


//-----------------------------------------------------------------------------
// Called when the last callback is being unregistered.
//-----------------------------------------------------------------------------
void CListenerManager::Finalize()
{
	override finalize = get_override("finalize");
	if (!finalize.is_none())
		finalize();
}


//-----------------------------------------------------------------------------
// Return whether or not the given callback is registered.
//-----------------------------------------------------------------------------
bool CListenerManager::IsRegistered(object oCallback)
{
	return FindCallback(oCallback) != -1;
	//return m_vecCallables.HasElement(oCallback);
}

int CListenerManager::FindCallback(object oCallback)
{
	for (int i=0; i < m_vecCallables.Count(); ++i) {
		object oCurrent  = m_vecCallables[i];
		if (is_same_func(oCallback, oCurrent)) {
			return i;
		}
	}
	return -1;
}

object CListenerManager::__getitem__(unsigned int index)
{
	if (index >= (unsigned int) m_vecCallables.Count())
		BOOST_RAISE_EXCEPTION(PyExc_IndexError, "Index out of range.")

	return m_vecCallables[index];
}

void CListenerManager::clear()
{
	if (GetCount()) {
		m_vecCallables.RemoveAll();
		Finalize();
	}
}


//-----------------------------------------------------------------------------
// Convar changed callback.
//-----------------------------------------------------------------------------
void ConVarChangedCallback(IConVar* var, const char* pOldValue, float flOldValue)
{
	static CConVarChangedListenerManager* on_convar_changed_listener_manager = GetOnConVarChangedListenerManager();
	CALL_LISTENERS_WITH_MNGR(on_convar_changed_listener_manager, ptr(static_cast<ConVar*>(var)), pOldValue);
}


//-----------------------------------------------------------------------------
// Called when the first callback is being registered.
//-----------------------------------------------------------------------------
void CConVarChangedListenerManager::Initialize()
{
	g_pCVar->InstallGlobalChangeCallback(ConVarChangedCallback);
}


//-----------------------------------------------------------------------------
// Called when the last callback is being unregistered.
//-----------------------------------------------------------------------------
void CConVarChangedListenerManager::Finalize()
{
	g_pCVar->RemoveGlobalChangeCallback(ConVarChangedCallback);
}


//-----------------------------------------------------------------------------
// Server output hook.
//-----------------------------------------------------------------------------
#if defined(ENGINE_ORANGEBOX) || defined(ENGINE_BMS) || defined(ENGINE_GMOD)
SpewRetval_t SP_SpewOutput( SpewType_t spewType, const tchar *pMsg )
{
	static CServerOutputListenerManager *pManager = GetOnServerOutputListenerManager();

	if (!pManager->CallCallbacks((MessageSeverity)spewType, pMsg) && pManager->m_pOldSpewOutputFunc) {
		return pManager->m_pOldSpewOutputFunc(spewType, pMsg);
	}

	return SPEW_CONTINUE;
}
#else
class SPLoggingListener: public ILoggingListener
{
public:
	virtual void Log( const LoggingContext_t *pContext, const tchar *pMessage )
	{
		static CServerOutputListenerManager *pManager = GetOnServerOutputListenerManager();

		if (!pManager->CallCallbacks((MessageSeverity)pContext->m_Severity, pMessage))
		{
			// Restore the old logging state before SP has been loaded
			LoggingSystem_PopLoggingState(false);

			// Resend the log message. Our listener won't get called anymore
			LoggingSystem_LogDirect(
					pContext->m_ChannelID,
					pContext->m_Severity,
					pContext->m_Color,
					pMessage);

			// Create a new logging state with only our listener being active
#if defined(ENGINE_LEFT4DEAD2)
			LoggingSystem_PushLoggingState(false);
#else
			LoggingSystem_PushLoggingState(false, true);
#endif
			LoggingSystem_RegisterLoggingListener(this);

		}
	}
} g_LoggingListener;

#endif


//-----------------------------------------------------------------------------
// CServerOutputListenerManager constructor.
//-----------------------------------------------------------------------------
CServerOutputListenerManager::CServerOutputListenerManager()
#if defined(ENGINE_ORANGEBOX) || defined(ENGINE_BMS) || defined(ENGINE_GMOD)
	:m_pOldSpewOutputFunc(NULL)
#endif
{
}


//-----------------------------------------------------------------------------
// Called when the first callback is being registered.
//-----------------------------------------------------------------------------
void CServerOutputListenerManager::Initialize()
{
#if defined(ENGINE_ORANGEBOX) || defined(ENGINE_BMS) || defined(ENGINE_GMOD)
	DevMsg(1, MSG_PREFIX "Retrieving old output function...\n");
	m_pOldSpewOutputFunc = GetSpewOutputFunc();

	DevMsg(1, MSG_PREFIX "Setting new output function...\n");
	SpewOutputFunc(SP_SpewOutput);
#else
	DevMsg(1, MSG_PREFIX "Registering logging listener...\n");
#if defined(ENGINE_LEFT4DEAD2)
	LoggingSystem_PushLoggingState(false);
#else
	LoggingSystem_PushLoggingState(false, true);
#endif
	LoggingSystem_RegisterLoggingListener(&g_LoggingListener);
#endif
}


//-----------------------------------------------------------------------------
// Called when the last callback is being unregistered.
//-----------------------------------------------------------------------------
void CServerOutputListenerManager::Finalize()
{
#if defined(ENGINE_ORANGEBOX) || defined(ENGINE_BMS) || defined(ENGINE_GMOD)
	if (m_pOldSpewOutputFunc) {
		DevMsg(1, MSG_PREFIX "Restoring old output function...\n");
		SpewOutputFunc(m_pOldSpewOutputFunc);
	}
#else
	DevMsg(1, MSG_PREFIX "Restoring old logging state...\n");
	LoggingSystem_PopLoggingState(false);
#endif
}


//-----------------------------------------------------------------------------
// Calls all registered server output callbacks.
//-----------------------------------------------------------------------------
bool CServerOutputListenerManager::CallCallbacks(MessageSeverity severity, const tchar *pMsg)
{
	bool block = false;
	m_Mutex.Lock(); {
		FOR_EACH_VEC(m_vecCallables, i) {
			try {
				object return_value = m_vecCallables[i](severity, pMsg);

				if (!return_value.is_none() && extract<OutputReturn>(return_value) == OUTPUT_BLOCK)
					block = true;
			} catch (...) {
				PrintCurrentException(false);
			}
		}
	} m_Mutex.Unlock();
	return block;
}


//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------
bool is_same_func(object f1, object f2)
{
	object self1, self2;
	try {
		self1 = f1.attr("__self__");
	}
	catch (...) {
		PyErr_Clear();
		return f1 == f2;
	}

	try {
		self2 = f2.attr("__self__");
	}
	catch (...) {
		PyErr_Clear();
		return f1 == f2;
	}

	return self1.ptr() == self2.ptr() && f1.attr("__func__") == f2.attr("__func__");
}
