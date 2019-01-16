#pragma once
#include <list>
#include <algorithm>
#include "Animator.h"

static std::list<Animator*> running, suspended;
static Animator* ToBeRunning, *ToBeSuspended;

template<class ArgumentType, class ResultType>
struct unary_function
{
	typedef ArgumentType argument_type;
	typedef ResultType result_type;
};

class AnimatorHolder {

private:
	class ProgressFunctor : public unary_function<Animator*, void> {
	private:
		timestamp_t t;
	public:
		void operator()(Animator* a) const { 
			//if (!a->GetState() == animatorstate_t::ANIMATOR_FINISHED)
				a->Progress(t); 
			//else {
				//MarkAsSuspended(a);
			//}
		}
		ProgressFunctor(timestamp_t _t) : t(_t) {}
	};

	class RenderFunctor : public unary_function<Animator*, void> {
	private:
		SDL_Renderer* rend;
	public:
		void operator()(Animator* a) const {
			a->Render(rend);
		}
		RenderFunctor(SDL_Renderer* rend) : rend(rend) {}
	};


public:
	static void Register(Animator* a) { suspended.push_back(a); }
	static void Cancel(Animator* a) { suspended.remove(a); }
	static void MarkAsRunning(Animator* a)
	{
		a->isSuspended = false;
		a->Resume();
		suspended.remove(a); 
		running.push_back(a);
	}
	static void MarkAsSuspended(Animator* a)
	{
		a->isSuspended = true;
		a->Pause();
		running.remove(a); 
		suspended.push_back(a);
	}
	static void Progress(timestamp_t currTime) {
		if (ToBeRunning != NULL) {
			MarkAsRunning(ToBeRunning);
		}
		if (ToBeSuspended != NULL) {
			MarkAsSuspended(ToBeSuspended);
		}

		ToBeRunning = NULL;
		ToBeSuspended = NULL;

		std::for_each(
			running.begin(), running.end(), ProgressFunctor(currTime)
		);
	}

	static void Render(SDL_Renderer* rend) {
		std::for_each(
			running.begin(), running.end(), RenderFunctor(rend)
		);
	}
};