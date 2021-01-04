#pragma once
#include "Registrar.h"
#include "Actions/Action.h"
class Drag_DropAction : public Action
{
private:
	int x, y;
	buttonstate buttState;
	Course* course;
public:
	Drag_DropAction(Registrar*, int newx, int newy);
	bool virtual Execute();
	virtual ~Drag_DropAction();
};

