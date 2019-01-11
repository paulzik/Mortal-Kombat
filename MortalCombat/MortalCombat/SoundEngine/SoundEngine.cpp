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

void SoundEngine::Play(const char* audioFile, bool loop = false) {
	if (loop) {
		engine->play2D(audioFile, true);
	}
	else
	{
		engine->play2D(audioFile);
	}
}

void SoundEngine::DeleteSoundEngine() {
	engine->drop();
}
