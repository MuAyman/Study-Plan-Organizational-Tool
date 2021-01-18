#include "ActionChangeCourse.h"
#include "Registrar.h"
#include "Courses/UnivCourse.h"
#include <iostream>

ActionChangeCourse::ActionChangeCourse(Registrar* p) : Action(p)
{
}

bool ActionChangeCourse::Execute()
{

	GUI* pGUI = pReg->getGUI();

	StudyPlan* pS = pReg->getStudyPlay();
	ActionData actData = pGUI->GetUserAction("Choose the course you want to change");
	pGUI->PrintMsg("Enter the new course code if you want to replace this course: ");
	Course_Code code = pGUI->GetSrting();
	Course* CRS = pS->select(actData.x, actData.y);
	pS->DeleteCourse(CRS, actData.x, actData.y);
	string Title = "Test101";
	int crd = 0;
	Course* pC = new Course(code, Title, crd);

	// Added to check the offerings Validity 

	int year = pS->getYear(actData.x, actData.y);
	SEMESTER sem = pS->getSemester(actData.x, actData.y);
	Rules pR = pReg->RegRules;
	if (pS->AddCourse(pC, actData.x, actData.y) == true)
	{

		// This is a offering_time validation check for the course
		for (int i = 0; i < pR.OffringsList[0].Offerings[sem].size(); i++)
		{
			if (pC->getCode() == pR.OffringsList[0].Offerings[sem][i])
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
	return true;
}

ActionChangeCourse::~ActionChangeCourse()
{
}