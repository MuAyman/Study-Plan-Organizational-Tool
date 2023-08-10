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
	pGUI->PrintMsg("Filter with year or semester: year: y / semester:s / type : t ");
	string optionfilter = pGUI->GetSrting();
	//get the string upper to avoid user error
	for (int i = 0; i < optionfilter.length(); i++)
	{
		optionfilter[i] = toupper(optionfilter[i]);
	}

	if (optionfilter == "Y")
	{
		//display year
		ActionData actData = pGUI->GetUserAction("Click on the year you want to display filter with");
		int x, y;
		x = actData.x;
		y = actData.y;
		pS->AddYear(x, y);  //put the dummy year
		pReg->UpdateInterface();
		ActionData actData1 = pGUI->GetUserAction("Click again to end the display filter");
		pS->original();  // return every thing as it was

	}
	else if (optionfilter == "S")
	{
		//display semester
		ActionData actData = pGUI->GetUserAction("Click on the semester you want to display filter with");
		int x, y;
		x = actData.x;
		y = actData.y;
		pS->AddSemester(x, y); // put the dummy semester in each year
		pReg->UpdateInterface();
		ActionData actData1 = pGUI->GetUserAction("Click again to end the display filter");
		pS->SemOriginal(); // return every thing as it was


	}
	//display type option
	else if (optionfilter == "T")
	{
		ActionData actData = pGUI->GetUserAction("Click on the course you want to display filter with its type");
		int x, y;
		x = actData.x;
		y = actData.y;
		Course* pCRS = pS->select(x, y);
		if (pCRS != NULL)
		{
			pS->AddType(pCRS->getType());
			pReg->UpdateInterface();
			ActionData actData1 = pGUI->GetUserAction("Click again to end the display filter");
			pS->OriginalType(); // return every thing as it was
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}


	return true;
}
ActionFilter::~ActionFilter()
{

}
