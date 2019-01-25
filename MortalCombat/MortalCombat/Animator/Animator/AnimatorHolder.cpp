#include "AnimatorHolder.h"

bool AnimatorHolder::clap;
std::list<Animator*> AnimatorHolder::running, AnimatorHolder::suspended;
