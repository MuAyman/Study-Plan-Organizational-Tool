#include "ActionStudentLevel.h"
#include "Registrar.h"
#include <fstream>

#include <iostream>
ActionStudentLevel::ActionStudentLevel(Registrar* p) :Action(p)
{
}
string ActionStudentLevel::Executess()
{
	GUI* pGUI = pReg->getGUI();
	StudyPlan* pS = pReg-> getStudyPlan();
	list<Course*> CRS = pS->PlanCoursesNeeded();
	for (auto y : CRS)
	{
		if (y->status)
			NoOfCrd += y->getCredits();
	}


	if (NoOfCrd < 32)
		s = "Freshmen";
	else if (NoOfCrd < 64)
		s = "Sophomore";
	else if (NoOfCrd < 96)
		s = "Junior";
	else if (NoOfCrd < 97)
		s = "Senior";

	return s;
}

bool ActionStudentLevel::Execute()
{
	GUI* pGUI = pReg->getGUI();
	StudyPlan* pS = pReg->getStudyPlan();
	list<Course*> CRS = pS->PlanCoursesNeeded();
	for (auto y : CRS)
	{
		if (y->status)
			NoOfCrd += y->getCredits();
	}

	if (NoOfCrd < 32)
		s = "Freshmen";
	else if (NoOfCrd < 64)
		s = "Sophomore";
	else if (NoOfCrd < 96)
		s = "Junior";
	else if (NoOfCrd < 97)
		s = "Senior";

	pGUI->setLevel(s);
	return true;
}


ActionStudentLevel::~ActionStudentLevel()
{
}