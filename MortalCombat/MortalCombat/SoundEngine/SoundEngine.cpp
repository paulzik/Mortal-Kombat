#include "SoundEngine.h"

SoundEngine* SoundEngine::instance;
ISoundEngine* SoundEngine::engine;

SoundEngine* SoundEngine::Get() {
	if (!instance) {
		//Initialize IrrKlang Engine
		engine = createIrrKlangDevice();
		if (!engine) {
			std::cout << "Error initializing irrklang" << std::endl;
			return 0;
		}
		instance = new SoundEngine;
	}

	return instance;
};

ISound* SoundEngine::Play(const char* audioFile, bool loop) {
	ISound* sound;
	if (loop) {
		sound = engine->play2D(audioFile, true);
	}
	else
	{
		sound = engine->play2D(audioFile);
	}

	return sound;
}

void SoundEngine::DeleteSoundEngine() {
	engine->drop();
}

void SoundEngine::SetVolume(int volumeLevel)
{
	engine->setSoundVolume(volumeLevel * 0.33);
}

void SoundEngine::StopAllSounds()
{
	engine->stopAllSounds();
}
