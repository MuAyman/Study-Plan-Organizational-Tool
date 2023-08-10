#pragma once
#include "Actions/Action.h"

class CalculateGPA : public Action
{
public:
	CalculateGPA(Registrar*);
	bool virtual Execute();
	virtual ~CalculateGPA();
};