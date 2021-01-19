#include "ActionStudentLevel.h"
#include "Registrar.h"
#include <fstream>
#include <string>

#include <iostream>
ActionStudentLevel::ActionStudentLevel(Registrar* p) :Action(p)
{
}
string ActionStudentLevel::showstatus()
{
	GUI* pGUI = pReg->getGUI();
	StudyPlan* pS = pReg->getStudyPlan();
	list<Course*> CRS = pS->PlanCoursesNeeded();
	for (auto y : CRS)
		if (y->status)
			NoOfCrd += y->getCredits();


	if (NoOfCrd < 32)
		level = "Freshmen";
	else if (NoOfCrd < 64)
		level = "Sophomore";
	else if (NoOfCrd < 96)
		level = "Junior";
	else if (NoOfCrd < 97)
		level = "Senior";

	return level;
}

bool ActionStudentLevel::Execute()
{
	
	return true;
}


ActionStudentLevel::~ActionStudentLevel()
{
}
