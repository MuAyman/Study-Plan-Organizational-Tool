#pragma once
#include "Actions/Action.h"
//Class responsible for adding course action
class ActionDeleteCourse : public Action
{
public:
	ActionDeleteCourse(Registrar*);
	bool virtual Execute();
	virtual ~ActionDeleteCourse();
};