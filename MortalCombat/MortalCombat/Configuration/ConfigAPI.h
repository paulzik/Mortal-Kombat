#pragma once
#include "ConfigData.h"
#include <string>
using namespace std;

class ConfigAPI 
{
private:
	void ImportConfigurationData();
	string configFile;
	int player1Wins, player2Wins;
	bool player1Bet, player2Bet;
protected:
	//UIComponent* ui;
	ConfigData configData;

public:
	const ConfigData GetConfigData();
	
	void ExportConfigurationData();

	//BetWin Mode
	const int GetBetWinMode();
	void SetBetWinMode(int value);
	const int GetPlayerBet(int playerId);

	//Infinite Life
	const int GetGodMode();
	void SetGodMode(int godMode);

	//Music Level
	const int GetMusicLevel();
	void SetMusicLevel(int level);

	//Speed
	const int GetMusicTrack();
	void SetMusicTrack(int trackId);

	//Wins
	const int GetPlayerWins(int playerId);
	void SetPlayerWins(int playerId, int wins);
	void AddPlayerWin(int playerId, int winsToAdd);

	ConfigAPI(string configFile);

};