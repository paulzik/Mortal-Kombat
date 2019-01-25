#pragma once
#include <list>
#include "ConfigAPI.h"

using namespace std;

//Singleton class to hold APIs
class ConfigAPIs
{
private:
	//Singleton instance
	static list<ConfigAPI*> apis;

public:
	static void Add(ConfigAPI* api);
	static list<ConfigAPI*>& Get();
};