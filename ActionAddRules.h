#pragma once
#include "Actions//Action.h"
#include "Registrar.h"

class ActionAddRules : public  Action
{
public:
	ActionAddRules(Registrar*);
	bool  ExecuteRules();
	bool virtual Execute();
	virtual ~ActionAddRules();
	bool catalogRead(ifstream& File, string name, Rules& R);
	bool RulesRead(ifstream& File, string name, Rules& R1);
	Rules R = pReg->getRules();

	//Major mymajor;
};
