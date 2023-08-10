#include "ActionRedo.h"
#include "Registrar.h"
#include "Courses/UnivCourse.h"

#include <iostream>
ActionRedo::ActionRedo(Registrar* p) : Action(p)
{

}

bool ActionRedo::Execute()
{
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Redo...");
	if (actData.actType == REDO)
	{
		for (unsigned int i = pReg->Memory.size(); i >= 0; i++)
		{
			if (pReg->Memory[i] == UNDO)
			{
				actData.actType = pReg->Memory[i - i];
			}
		}
	}
	return true;
}

ActionRedo::~ActionRedo()
{

}