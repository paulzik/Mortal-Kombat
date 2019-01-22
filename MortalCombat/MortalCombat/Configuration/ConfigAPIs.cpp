#include "ConfigAPIs.h"
#include <iostream>
#include <list>

list<ConfigAPI*> ConfigAPIs::apis;

void ConfigAPIs::Add(ConfigAPI * api)
{
	apis.push_back(api);
}

//Return singleton instance
list<ConfigAPI*>& ConfigAPIs::Get(void)
{
	return apis;
}


