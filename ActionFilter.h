#pragma once
#include "Actions/Action.h"
class ActionFilter : public Action
{
public:
	ActionFilter(Registrar*);
	bool virtual Execute();
	virtual ~ActionFilter();
	
};

