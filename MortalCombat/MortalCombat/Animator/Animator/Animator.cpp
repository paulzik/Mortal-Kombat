#include "Animator.h"
#include "AnimatorHolder.h"
#include <time.h>

void Animator::Stop(void) {
	if (!HasFinished()) {
		state = ANIMATOR_STOPPED;
		NotifyStopped();
	}
}

void Animator::Resume()
{
	state = ANIMATOR_RUNNING;
}

void Animator::Pause()
{
	state = ANIMATOR_STOPPED;
}

void Animator::NotifyStopped(void) {
	if (onFinish)
		(*onFinish)(this, finishClosure);
	if (State != NULL)
		State->SetState("Idle");
	//AnimatorHolder::MarkAsSuspended(this);
}

void Animator::TimeShift(timestamp_t offset)
{
	lastTime += offset;
}

Animator::Animator(void) :
	lastTime(0), state(ANIMATOR_FINISHED),
	onFinish((FinishCallback)0), finishClosure((void*)0) {}