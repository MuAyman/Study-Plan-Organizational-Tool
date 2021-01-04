#include "ActionUndo.h"
#include "Registrar.h"
#include "Courses/UnivCourse.h"

#include <iostream>
ActionUndo::ActionUndo(Registrar* p) : Action(p)
{

}

bool ActionUndo::Execute()
{
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Undo...");
	if (actData.actType == UNDO && pReg->Memory.size() > 1)
	{
		actData.actType = pReg->Memory[pReg->Memory.size() - 2];
	}
	return true;
}

ActionUndo::~ActionUndo()
{

}