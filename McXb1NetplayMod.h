#pragma once
#include "LanternMod.h"
#include "Hooks/SocketOutputStreamLocal.h"
#include "Hooks/Socket.h"

class McXb1NetplayMod : public LanternMod
{
public:
	/// <summary>
	/// Runs when the mod is enabled
	/// </summary>
	void Enable() override;
	/// <summary>
	/// Runs when the mod is disabled
	/// </summary>
	void Disable() override;
	/// <summary>
	/// Gets the mod version
	/// </summary>
	std::wstring GetVersion() override;
	/// <summary>
	/// Gets the mod name
	/// </summary>
	std::wstring GetName() override;
};

