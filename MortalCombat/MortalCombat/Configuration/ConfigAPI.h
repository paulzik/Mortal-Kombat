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

	//Gravity
	const float GetGravity();
	void SetGravity(float grav);

	//Infinite Life
	const bool GetInfiniteLife();
	void SetInfiniteLife(bool infinite);

	//Music Level
	const float GetMusicLevel();
	void SetMusicLevel(float level);

	//Speed
	const float GetGameSpeed();
	void SetGameSpeed(float speed);

	ConfigAPI(string configFile);

};