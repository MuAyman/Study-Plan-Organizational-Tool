#pragma once
#include "Actions/Action.h"
#include "Registrar.h"
#include <string>

class ActionStudentLevel : public Action
{
	int NoOfCrd;
	string s;
public:
	ActionStudentLevel(Registrar* p);
	string Executess();
	bool virtual Execute();
	virtual ~ActionStudentLevel();

};