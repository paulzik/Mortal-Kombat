#include <iostream>
#include <irrKlang.h>
using namespace irrklang;

class SoundEngine
{
private:
	static SoundEngine* instance;
	static ISoundEngine* engine;

public:
	static SoundEngine* Get(void);

	//Play sound
	static void Play(const char* audioFile, bool loop);

	//Clear engine
	static void DeleteSoundEngine();


};