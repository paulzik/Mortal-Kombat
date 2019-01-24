#include "ConfigAPI.h"
#include "ConfigAPIs.h"
#include "../Configuration/JSONParser/json/json.h"
#include <iostream>
#include <fstream>
#include "../SoundEngine/SoundEngine.h"

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

	SetGameSpeed(jsonValue["Configuration"]["GameSpeed"].asInt());
	SetMusicLevel(jsonValue["Configuration"]["MusicLevel"].asInt());
	SetTinyMode(jsonValue["Configuration"]["TinyMode"].asBool());
	SetGodMode(jsonValue["Configuration"]["GodMode"].asBool());
}

void ConfigAPI::ExportConfigurationData()
{
	Json::Value root;
	root["Configuration"]["GameSpeed"] = GetGameSpeed();
	root["Configuration"]["MusicLevel"] = GetMusicLevel();
	root["Configuration"]["TinyMode"] = GetTinyMode();
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

const int ConfigAPI::GetGameSpeed()
{
	return configData.gameSpeed;
}

void ConfigAPI::SetGameSpeed(int speed)
{
	configData.gameSpeed = speed;
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