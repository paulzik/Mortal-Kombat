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
	static ISound* Play(const char* audioFile, bool loop = false);

	//Clear engine
	static void DeleteSoundEngine();

	static void SetVolume(int volumeLevel);

	static void StopAllSounds();
};