#include "ActionDeleteCourse.h"
#include "Registrar.h"
#include "Courses/UnivCourse.h"
#include <iostream>

ActionDeleteCourse::ActionDeleteCourse(Registrar* p) : Action(p)
{
}

bool ActionDeleteCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Click on the course you want to delete...");
	int x, y;
	x = actData.x;
	y = actData.y;
	StudyPlan* pS = pReg->getStudyPlay();
	Course* CRS = pS->select(x,y);
	pS->DeleteCourse(CRS, x, y);
	return true;
}


ActionDeleteCourse::~ActionDeleteCourse()
{

}