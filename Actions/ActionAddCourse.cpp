#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"

#include <iostream>
ActionAddCourse::ActionAddCourse(Registrar* p) :Action(p)
{

}

bool ActionAddCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();

	bool check = false;
	Course_Code code;
	string Title = "Test101";
	int crd = 0;
	Course* pC = new Course(code, Title, crd);
	while (!check)
	{
		pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
		for (auto it = pReg->getRules().CourseCatalog.begin(); it != pReg->getRules().CourseCatalog.end(); it++)
		{
			if (it->Code == pGUI->GetSrting());
			{
				code = it->Code;
				Title = it->Title;
				crd = it->Credits;
				pC->setCoReq(it->CoReqList);
				pC->setPreReq(it->PreReqList);
				pReg->checkType(pC); //new
				check = true;
				break;
			}
		}
	}

	//TODO: add input validation

	ActionData actData = pGUI->GetUserAction("Select a year to add coures to");
	//TODO: add input validation
	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		//get coord where user clicked
		x = actData.x;
		y = actData.y;
		graphicsInfo gInfo{ x, y };
		StudyPlan* pS = pReg->getStudyPlay();
		Rules pR = pReg->getRules();
		int year = pS->getYear(x, y);
		SEMESTER sem = pS->getSemester(x, y);
		if (pS->AddCourse(pC, x, y) == true)
		{

			// This is a offering_time validation check for the course
					for (int i = 0; i < pR.OffringsList[year].Offerings[sem].size(); i++)
					{
						if (pC->getCode() == pR.OffringsList[year].Offerings[sem][i])
						{
							// set the course as valid
							pC->SetOfferingsValid(true);
						}
						else
						{
							//set the course as in valid
							pC->SetOfferingsValid(false);
						}
					}
		}
		else
		{
			return false;
		}
		////For the seke of demo, we will add the course to the 1st year, 1st semester
		
		//TODO: given course code, get course title, crd hours from registrar
		//For now, we will add any dummy values


		//TODO: Ask registrar to add course to the year selected by the user
		//TODO: add the course to the correct year obtained from registrar


	}


	//TODO:


	return true;
}


ActionAddCourse::~ActionAddCourse()
{
}
