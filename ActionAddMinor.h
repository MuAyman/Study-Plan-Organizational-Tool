#pragma once
#include "Actions/Action.h"

class ActionAddMinor : public Action
{
	Action* RequiredAction = nullptr;
public:
	ActionAddMinor(Registrar*);
	bool virtual Execute();
	virtual ~ActionAddMinor();
};