#pragma once
#include "Actions/Action.h"
/// <summary>
/// This action to make the user see the only items he want to see MAjor , year , semester
/// </summary>
class ActionFilter : public Action
{
public:
	ActionFilter(Registrar*);
	bool virtual Execute();
	virtual ~ActionFilter();

};
