#pragma once
#include <list>
#include <algorithm>
#include "Animator.h"
#include "FrameRangeAnimator.h"

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

	class ComparatorSuspended : public unary_function<Animator*, void> {
	private:
		int id;
	public:
		void operator()(Animator* a) const {
			if (a->GetID() == id) {
				suspended.remove(a);
				running.push_back(a);
				((FrameRangeAnimator*)a)->GetSprite()->SetVisibility(true);

			}
		}
		ComparatorSuspended(int ID) : id(ID) {}
	};

	class ComparatorRunning : public unary_function<Animator*, void> {
	private:
		int id;
	public:
		void operator()(Animator* a) const {
			if (a->GetID() == id) {
				running.remove(a);
				suspended.push_back(a);
				((FrameRangeAnimator*)a)->GetSprite()->SetVisibility(false);

			}
		}
		ComparatorRunning(int ID) : id(ID) {}
	};


public:
	static std::list<Animator*> running, suspended;

	static void Register(Animator* a) { suspended.push_back(a); a->isSuspended = true; }
	static void Cancel(Animator* a) { suspended.remove(a); }
	static void MarkAsRunning(Animator* a)
	{

		std::list<Animator*> &tmp = suspended;
		std::list<Animator*> &tmpRun = running;

		//std::for_each(tmp.begin(), tmp.end(), ComparatorSuspended(a->GetID()));
		for (std::list<Animator*>::const_iterator it = tmp.begin(); it != tmp.end(); ++it) {
			if (((Animator*)(*it))->GetID() == a->GetID()) {
				//suspended.remove(*it);
				//running.push_back(a);
				tmpRun.insert(tmpRun.end(), *it);
				tmp.remove(*it);
				break;
			}
		}
	}
	static void MarkAsSuspended(Animator* a)
	{

		std::list<Animator*> &tmp = suspended;
		std::list<Animator*> &tmpRun = running;

		//std::for_each(tmp.begin(), tmp.end(), ComparatorSuspended(a->GetID()));
		for (std::list<Animator*>::const_iterator it = tmpRun.begin(); it != tmpRun.end(); ++it) {
			if (((Animator*)(*it))->GetID() == a->GetID()) {
				//suspended.remove(*it);
				//running.push_back(a);
				tmp.insert(tmp.end(), *it);
				tmpRun.remove(*it);
				break;
			}
		}
	}
	static void Progress(timestamp_t currTime) {

		ToBeRunning = NULL;
		ToBeSuspended = NULL;
		std::list<Animator*> &tmp = running;

		std::for_each(
			tmp.begin(), tmp.end(), ProgressFunctor(currTime)
		);
	}

	static void Render(SDL_Renderer* rend) {
		std::list<Animator*> &tmp = running;

		std::for_each(
			tmp.begin(), tmp.end(), RenderFunctor(rend)
		);
	}
};