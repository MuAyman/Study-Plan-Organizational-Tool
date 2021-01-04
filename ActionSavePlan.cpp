#include "ActionSavePlan.h"
#include "Registrar.h"
#include <fstream>

#include <iostream>
ActionSavePlan::ActionSavePlan(Registrar* p) :Action(p)
{
}

bool ActionSavePlan::Execute()
{
	StudyPlan* pSPlan = pReg->getStudyPlay();
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Enter the file name with adding .txt: ");
	string filename = pGUI->GetSrting();
	
	pSPlan->SaveStudyPlan(filename);

	return true;
}


ActionSavePlan::~ActionSavePlan()
{
}
