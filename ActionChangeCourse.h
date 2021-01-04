#pragma once
#include "Actions/Action.h"
//Class responsible for adding course action
class ActionChangeCourse : public Action
{
public:
	ActionChangeCourse(Registrar*);
	bool virtual Execute();
	virtual ~ActionChangeCourse();
};