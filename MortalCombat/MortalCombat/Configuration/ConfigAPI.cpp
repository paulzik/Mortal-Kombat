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
	SetTinyMode(jsonValue["Configuration"]["TinyMode"].asBool());
	SetGodMode(jsonValue["Configuration"]["GodMode"].asBool());
	SetPlayerWins(1,jsonValue["Configuration"]["Player1Wins"].asInt());
	SetPlayerWins(2,jsonValue["Configuration"]["Player2Wins"].asInt());
}

void ConfigAPI::ExportConfigurationData()
{
	Json::Value root;
	root["Configuration"]["MusicTrack"] = GetMusicTrack();
	root["Configuration"]["MusicLevel"] = GetMusicLevel();
	root["Configuration"]["TinyMode"] = GetTinyMode();
	root["Configuration"]["GodMode"] = GetGodMode();
	root["Configuration"]["Player1Wins"] = GetPlayerWins(1);
	root["Configuration"]["Player2Wins"] = GetPlayerWins(2);

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

void ConfigAPI::AddPlayerWin(int playerId)
{
	if (playerId == 1)
		player1Wins++;
	else if (playerId == 2)
		player2Wins++;
}

const int ConfigAPI::GetTinyMode()
{
	return configData.tinyMode;
}

void ConfigAPI::SetTinyMode(int tinyMode)
{
	configData.tinyMode = tinyMode;
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