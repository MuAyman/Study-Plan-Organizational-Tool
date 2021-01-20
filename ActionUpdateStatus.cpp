#include "ActionUpdateStatus.h"
#include "Registrar.h"
#include <iostream>
using namespace std;



ActionUpdateStatus::ActionUpdateStatus(Registrar* p) : Action(p)
{
	
}

bool ActionUpdateStatus::Execute()
{
	GUI* pGUI = pReg->getGUI();
	int dumb = 0, year = 10, iy = 520;
	SEMESTER sem = SEM_CNT;

	pGUI->PrintMsg("Do you want to update that year / semester status? y/n ");
	string yes = pGUI->GetSrting();
	ActionData actData = pGUI->GetUserAction("Choose what you want to set status for");

	int x, y;
		//get coord where user clicked
		x = actData.x;
		y = actData.y;

	if (x > 20 && x < 120)
	{
		dumb = 1;
		if (y > iy && y < iy + (SEM_CNT * PLAN_SEMESTER_HEIGHT))
			year = 1;
		else if (y > (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 1) && y < (iy - (3 * PLAN_SEMESTER_HEIGHT + 10) * 1) + PLAN_SEMESTER_HEIGHT * SEM_CNT)
			year = 2;
		else if (y > (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2) && y < (iy - (3 * PLAN_SEMESTER_HEIGHT + 10) * 2) + (PLAN_SEMESTER_HEIGHT * SEM_CNT))
			year = 3;
		else if (y > (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3) && y < (iy - (3 * PLAN_SEMESTER_HEIGHT + 10) * 3) + (PLAN_SEMESTER_HEIGHT * SEM_CNT))
			year = 4;
		else if (y > (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4) && y < (iy - (3 * PLAN_SEMESTER_HEIGHT + 10) * 4) + (PLAN_SEMESTER_HEIGHT * SEM_CNT))
			year = 5;
	}
	else if (x > 160 && x < 240)
	{
		dumb = 2;
		if (y > iy && y < iy + (SEM_CNT * PLAN_SEMESTER_HEIGHT))
			year = 1;
		else if (y > (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 1) && y < (iy - (3 * PLAN_SEMESTER_HEIGHT + 10) * 1) + PLAN_SEMESTER_HEIGHT * SEM_CNT)
			year = 2;
		else if (y > (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2) && y < (iy - (3 * PLAN_SEMESTER_HEIGHT + 10) * 2) + (PLAN_SEMESTER_HEIGHT * SEM_CNT))
			year = 3;
		else if (y > (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3) && y < (iy - (3 * PLAN_SEMESTER_HEIGHT + 10) * 3) + (PLAN_SEMESTER_HEIGHT * SEM_CNT))
			year = 4;
		else if (y > (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4) && y < (iy - (3 * PLAN_SEMESTER_HEIGHT + 10) * 4) + (PLAN_SEMESTER_HEIGHT * SEM_CNT))
			year = 5;

		if (/* Year1*/ (y >= iy + PLAN_SEMESTER_HEIGHT * 2) && y < (iy + PLAN_SEMESTER_HEIGHT * 3) ||
			/*Year2*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) + PLAN_SEMESTER_HEIGHT * 2) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) + PLAN_SEMESTER_HEIGHT * 3 ||
			/*Year 3*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2 + PLAN_SEMESTER_HEIGHT * 2) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2 + PLAN_SEMESTER_HEIGHT * 3 ||
			/*Year4*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3 + PLAN_SEMESTER_HEIGHT * 2) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3 + PLAN_SEMESTER_HEIGHT * 3 ||
			/*Year5*/ ((y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4 + PLAN_SEMESTER_HEIGHT * 2) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4 + PLAN_SEMESTER_HEIGHT * 3))

		{
			sem = FALL;
		}
		else if (/* Year1*/ (y >= iy + PLAN_SEMESTER_HEIGHT) && y < (iy + PLAN_SEMESTER_HEIGHT * 2) ||
			/*Year2*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) + PLAN_SEMESTER_HEIGHT) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) + PLAN_SEMESTER_HEIGHT * 2 ||
			/*Year 3*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2 + PLAN_SEMESTER_HEIGHT) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2 + PLAN_SEMESTER_HEIGHT * 2 ||
			/*Year4*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3 + PLAN_SEMESTER_HEIGHT) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3 + PLAN_SEMESTER_HEIGHT * 2 ||
			/*Year5*/ ((y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4 + PLAN_SEMESTER_HEIGHT) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4 + PLAN_SEMESTER_HEIGHT * 2))
		{
			sem = SPRING;
		}
		else if ((/*Year1 */ (y >= iy && y < iy + PLAN_SEMESTER_HEIGHT)) ||
			/*Year2*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) + PLAN_SEMESTER_HEIGHT) ||
			/*Year3 */ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2 && y < (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2) + PLAN_SEMESTER_HEIGHT) ||
			/*Year4*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3 && y < (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3) + PLAN_SEMESTER_HEIGHT) ||
			/*Year5*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4 && y < (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4) + PLAN_SEMESTER_HEIGHT))
		{
			sem = SUMMER;
		}
	}



	if (yes == "y")
	{
		pGUI->PrintMsg("Enter the no of new status 1.Done 2.InProgress 3.Pending");
		string xi = pGUI->GetSrting();
		for (int i = 0; i < xi.length(); i++)
		{
			xi[i] = toupper(xi[i]);
		}

		if (xi == "DONE" || xi == "1")
		{
			if (dumb == 1)
				pReg->getStudyPlay()->setStatus(year, FALL, "55555", Done);
			else if (dumb == 2)
				pReg->getStudyPlay()->setStatus(year + 20, sem, "55555", Done);
			return true;
		}
		else if (xi == "INPROGRESS" || xi == "2")
		{
			if (dumb == 1)
				pReg->getStudyPlay()->setStatus(year, FALL, "55555", InProgress);
			else if (dumb == 2)
				pReg->getStudyPlay()->setStatus(year + 20, sem, "55555", InProgress);
			return true;
		}
		else if (xi == "PENDING" || xi == "3")
		{
			if (dumb == 1)
				pReg->getStudyPlay()->setStatus(year, FALL, "55555", Pending);
			else if (dumb == 2)
				pReg->getStudyPlay()->setStatus(year + 20, sem, "55555", Pending);
			return true;
		}
		else
			return false;
	}
}


ActionUpdateStatus::~ActionUpdateStatus()
{

}