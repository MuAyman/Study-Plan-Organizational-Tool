#include "ActionCheckReport.h"
#include "Registrar.h"
#include <fstream>

#include <iostream>
ActionCheckReport::ActionCheckReport(Registrar* p) :Action(p)
{
}

bool ActionCheckReport::Execute()
{
	StudyPlan* pSPlan = pReg->getStudyPlan();
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Enter the file name with adding .txt: ");
	string filename = pGUI->GetSrting();

	pSPlan->SaveStudyPlan(filename);

	return true;
}


ActionCheckReport::~ActionCheckReport()
{
}
