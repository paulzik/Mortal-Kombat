#include "ConfigAPI.h"
#include "ConfigAPIs.h"
#include "../Configuration/JSONParser/json/json.h"
#include <iostream>
#include <fstream>

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

	SetGravity(jsonValue["Configuration"]["Gravity"].asFloat());
	SetGameSpeed(jsonValue["Configuration"]["GameSpeed"].asFloat());
	SetMusicLevel(jsonValue["Configuration"]["MusicLevel"].asFloat());
	SetInfiniteLife(jsonValue["Configuration"]["InfiniteLife"].asBool());
}

void ConfigAPI::ExportConfigurationData()
{
	Json::Value root;
	root["Configuration"]["Gravity"] = GetGravity();
	root["Configuration"]["GameSpeed"] = GetGameSpeed();
	root["Configuration"]["MusicLevel"] = GetMusicLevel();
	root["Configuration"]["InfiniteLife"] = GetInfiniteLife();

	ofstream file;
	file.open(configFile);
	file << root;
	file.close();
}

const ConfigData ConfigAPI::GetConfigData()
{
	return configData;
}

const float ConfigAPI::GetGravity()
{
	return configData.gravity;
}

void ConfigAPI::SetGravity(float grav)
{
	configData.gravity = grav;
}

const bool ConfigAPI::GetInfiniteLife()
{
	return configData.infiniteLife;
}

void ConfigAPI::SetInfiniteLife(bool infinite)
{
	configData.infiniteLife = infinite;
}

const float ConfigAPI::GetMusicLevel()
{
	return configData.musicLevel;
}

void ConfigAPI::SetMusicLevel(float level)
{
	configData.musicLevel = level;
}

const float ConfigAPI::GetGameSpeed()
{
	return configData.gameSpeed;
}

void ConfigAPI::SetGameSpeed(float speed)
{
	configData.gameSpeed = speed;
}
