#pragma once
#include "Actions/Action.h"

class ActionAddMinor : public Action
{
public:
	ActionAddMinor(Registrar*);
	bool virtual Execute();
	virtual ~ActionAddMinor();
};
