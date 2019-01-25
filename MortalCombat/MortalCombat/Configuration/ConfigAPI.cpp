#include "ConfigAPI.h"
#include "ConfigAPIs.h"
#include "../Configuration/JSONParser/json/json.h"
#include <iostream>
#include <fstream>
#include "../SoundEngine/SoundEngine.h"
#include "../UI/UIManager.h"

ConfigAPI::ConfigAPI(string configFilename)
{
	configFile = configFilename;
	ImportConfigurationData();

	ConfigAPIs::Add(this);
}

void ConfigAPI::ImportConfigurationData()
{
	Json::Value jsonValue;
	ifstream file;
	file.open(configFile);
	file >> jsonValue;
	file.close();

	SetMusicTrack(jsonValue["Configuration"]["MusicTrack"].asInt());
	SetMusicLevel(jsonValue["Configuration"]["MusicLevel"].asInt());
	SetBetWinMode(jsonValue["Configuration"]["BetWin"].asInt());
	SetGodMode(jsonValue["Configuration"]["GodMode"].asBool());
}

void ConfigAPI::ExportConfigurationData()
{
	Json::Value root;
	root["Configuration"]["MusicTrack"] = GetMusicTrack();
	root["Configuration"]["MusicLevel"] = GetMusicLevel();
	root["Configuration"]["BetWin"] = GetBetWinMode();
	root["Configuration"]["GodMode"] = GetGodMode();

	ofstream file;
	file.open(configFile);
	file << root;
	file.close();
}

const ConfigData ConfigAPI::GetConfigData()
{
	return configData;
}

const int ConfigAPI::GetMusicTrack()
{
	return configData.musicTrack;
}

void ConfigAPI::SetMusicTrack(int trackID)
{
	configData.musicTrack = trackID;
	if (UIManager::Get()->currentScene == NULL)
		return;

	SoundEngine::Get()->StopAllSounds();
	string file = "./SoundEngine/Sounds/BattleMusic" + to_string(trackID) + ".mp3";
	SoundEngine::Get()->Play(file.c_str(), true);
}

const int ConfigAPI::GetPlayerWins(int playerId)
{
	if (playerId == 1)
		return player1Wins;
	else
		return player2Wins;
}

void ConfigAPI::SetPlayerWins(int playerId, int wins)
{
	if (playerId == 1)
		player1Wins = wins;
	else if (playerId == 2)
		player2Wins = wins;
}

void ConfigAPI::AddPlayerWin(int playerId, int winsToAdd)
{
	if (playerId == 1)
		player1Wins+=winsToAdd;
	else if (playerId == 2)
		player2Wins+=winsToAdd;

	if (player1Wins < 0)
		player1Wins = 0;
	if (player2Wins < 0)
		player2Wins = 0;
}

const int ConfigAPI::GetBetWinMode()
{
	return configData.BetWinMode;
}


void ConfigAPI::SetBetWinMode(int betmode)
{
	configData.BetWinMode = betmode;
}

const int ConfigAPI::GetPlayerBet(int playerId)
{
	if (playerId == 1)
		return player1Bet;
	else
		return player2Bet;
}

const int ConfigAPI::GetGodMode()
{
	return configData.godMode;
}

void ConfigAPI::SetGodMode(int godMode)
{
	configData.godMode = godMode;
}

const int ConfigAPI::GetMusicLevel()
{
	return configData.musicLevel;
}

void ConfigAPI::SetMusicLevel(int level)
{
	configData.musicLevel = level;
	//Set volume
	SoundEngine::Get()->SetVolume(level);
}