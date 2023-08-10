#include "ActionStudentLevel.h"
#include "Registrar.h"
#include <fstream>

#include <iostream>
ActionStudentLevel::ActionStudentLevel(Registrar* p) :Action(p)
{
}

bool ActionStudentLevel::Execute()
{
	NoOfCrd = 0;
	GUI* pGUI = pReg->getGUI();
	StudyPlan* pS = pReg->getStudyPlay();
	list<Course*> CRS = pS->PlanCoursesNeeded();
	
	for (auto y = CRS.begin(); y != CRS.end(); y++)
	{
		if ((*y)->status == Done )
			NoOfCrd += (*y)->getCredits();
	}
	cout << NoOfCrd << endl;
	if (NoOfCrd < 32)
		s = "Freshmen";
	else if (NoOfCrd < 64)
		s = "Sophomore";
	else if (NoOfCrd <= 96)
		s = "Junior";
	else if (NoOfCrd > 96)
		s = "Senior";
	else
		s = "error";
	pGUI->setLevel(s);
	return true;
}


ActionStudentLevel::~ActionStudentLevel()
{
}