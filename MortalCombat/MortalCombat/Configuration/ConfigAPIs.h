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
	static void Add(ConfigAPI* api) {
		apis.push_back(api);
	};
	static list<ConfigAPI*>& Get(void) {
		return apis;
	};
};