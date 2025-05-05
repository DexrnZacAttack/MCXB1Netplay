#include "pch.h"
#include "McXb1NetplayMod.h"
#include "Util/HookHelper.h"
#include <winrt/Windows.Foundation.h>

std::vector<std::tuple<PVOID*, PVOID>> hooks;

void McXb1NetplayMod::Enable()
{
	registerHook(&(PVOID&)SocketOutputStreamLocal_write, &SocketOutputStreamLocal::write);
	registerHook(&(PVOID&)Socket_Initialise, &Socket::Initialise);
}

void McXb1NetplayMod::Disable()
{
	unregisterHooks(hooks);
}

std::wstring McXb1NetplayMod::GetVersion()
{
	// When connecting and hosting works, we go to 1.0.0
	return L"0.0.1";
}

std::wstring McXb1NetplayMod::GetName()
{
	return L"Minecraft: Xbox One Edition Netplay mod";
}
