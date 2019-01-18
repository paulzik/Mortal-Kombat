#pragma once
#include "SDL.h"
typedef long float timestamp_t;


enum animatorstate_t {
	ANIMATOR_FINISHED = 0,
	ANIMATOR_RUNNING = 1,
	ANIMATOR_STOPPED = 2
};

enum animatortype_t {
	action,
	movement,
	idle
};

class Animator {
public:
	typedef void(*FinishCallback)(Animator*, void*);

	void Stop(void);

	void Resume();

	void Pause();

	bool HasFinished(void) const
	{
		return state != ANIMATOR_RUNNING;
	}

	virtual void TimeShift(timestamp_t offset);

	virtual void Progress(timestamp_t currTime) = 0;

	virtual void Render(SDL_Renderer* rend) = 0;

	void SetOnFinish(FinishCallback f, void* c = (void*)0)
	{
		onFinish = f, finishClosure = c;
	}

	animatorstate_t GetState() {
		return state;
	}

	animatortype_t GetType() {
		return type;
	}

	int GetID() {
		return ID;
	}

	bool isSuspended = true;

	Animator(void); 
	virtual ~Animator() {};

protected:
	timestamp_t lastTime;
	animatorstate_t state;
	animatortype_t type;
	FinishCallback onFinish;
	void* finishClosure;
	void NotifyStopped(void);
	int ID;
};