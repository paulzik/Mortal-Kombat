#pragma once
#include "ConfigData.h"
#include <string>
using namespace std;

class ConfigAPI 
{
private:
	void ImportConfigurationData();
	
	string configFile;
protected:
	//UIComponent* ui;
	ConfigData configData;

public:
	const ConfigData GetConfigData();
	
	void ExportConfigurationData();

	//Tiny Mode
	const int GetTinyMode();
	void SetTinyMode(int tinyMode);

	//Infinite Life
	const int GetGodMode();
	void SetGodMode(int godMode);

	//Music Level
	const int GetMusicLevel();
	void SetMusicLevel(int level);

	//Speed
	const int GetGameSpeed();
	void SetGameSpeed(int speed);

	ConfigAPI(string configFile);

};