#pragma once
#include "Commons.h"
namespace PlayerCount
{
	namespace
	{
		void SetPlayers(PLAYERS players) { players = _players; };
		PLAYERS GetPlayers() { return _players; };

		static PLAYERS _players;
	}
}