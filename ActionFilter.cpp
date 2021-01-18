#include "ActionFilter.h"
#include "Registrar.h"
ActionFilter::ActionFilter(Registrar* p) : Action(p)
{

}
bool ActionFilter::Execute()
{
	GUI* pGUI = pReg->getGUI();
	StudyPlan* pS = pReg->getStudyPlay();
	//ask about the filter type
	pGUI->PrintMsg("Filter with year or semester: year: y / semester:s ");
	string optionfilter = pGUI->GetSrting();
	//get the string upper to avoid user error
	for (int i = 0; i < optionfilter.length(); i++)
	{
		optionfilter[i] = toupper(optionfilter[i]);
	}

	if (optionfilter == "Y")
	{
		//display year
		ActionData actData = pGUI->GetUserAction("Click on the item you want to display filter with");
		int x, y;
		x = actData.x;
		y = actData.y;
		pS->AddYear(x, y);  //put the dummy year
		pReg->UpdateInterface();
		ActionData actData1 = pGUI->GetUserAction("Click again to end the display filter");
		pS->original();  // return every thing as it was

	}
	else
	{
		//display semester
		ActionData actData = pGUI->GetUserAction("Click on the item you want to display filter with");
		int x, y;
		x = actData.x;
		y = actData.y;
		pS->AddSemester(x, y); // put the dummy semester in each year
		pReg->UpdateInterface();
		ActionData actData1 = pGUI->GetUserAction("Click again to end the display filter");
		pS->SemOriginal(); // return every thing as it was


	}
		


	return true;
}
ActionFilter::~ActionFilter()
{

}
