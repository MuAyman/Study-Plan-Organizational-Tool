#pragma once
#include "Actions/Action.h"
//Class responsible for redoing action
class ActionRedo : public Action
{
public:
	ActionRedo(Registrar*);
	bool virtual Execute();
	virtual ~ActionRedo();
};