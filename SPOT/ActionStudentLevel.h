#pragma once
#include "Actions/Action.h"
#include "Registrar.h"
#include <string>

class ActionStudentLevel : public Action
{
	int NoOfCrd = 0;
	string s;
public:
	ActionStudentLevel(Registrar* p);
	bool virtual Execute();
	virtual ~ActionStudentLevel();

};