#include "ValidityCheck.h"
#include "StudyPlan\StudyPlan.h"
ValidityCheck::ValidityCheck(Registrar* pReg) :Action(pReg)
{
}

bool ValidityCheck::checkTotalCred(int cr)
{
	if (cr == pReg->getRules().TotalCredits)
		return true;
	else
		return false;
}
bool ValidityCheck::checkMajCred(int cr)
{
	if (cr == (pReg->getRules().MajCommonCompCredits + pReg->getRules().MajCommonElecCredits))
		return true;
	else
		return false;
}
bool ValidityCheck::checkUnivCred(int cr)
{
	if (cr == (pReg->getRules().UnivElectiveCredits + pReg->getRules().UnivCompCredits))
		return true;
	else
		return false;
}
bool ValidityCheck::checkTrackCred(int cr)
{
	if (cr == pReg->getRules().CompTrackCredits)
		return true;
	else
		return false;
}
bool ValidityCheck::ConcenReq(string major)
{

	int NoOfConcen = pReg->getRules().NumOfConcent;

	for (int x = 0; x < NoOfConcen; x++)
	{
		cout << "pReg->RegRules.ConcRequirements[x].CompulsoryCourses: ";
		for (int y = 0; y < pReg->getRules().ConcRequirements[x].CompulsoryCourses.size(); y++)		// looping on the compulsory courses vector
			cout << pReg->getRules().ConcRequirements[x].CompulsoryCourses[y] << endl;
		for (auto y : pReg->getRules().ConcRequirements[x].CompulsoryCourses)		// looping on the compulsory courses vector
		{
			if (pReg->getStudyPlan()->isCourse(y))
				return true;
			else
				return false;
		}

		cout << "pReg->RegRules.ConcRequirements[x].ElectiveCourses: ";
		for (int y = 0; y < pReg->getRules().ConcRequirements[x].ElectiveCourses.size(); y++)		// looping on the compulsory courses vector
			cout << pReg->getRules().ConcRequirements[x].ElectiveCourses[y] << endl;
		for (auto y : pReg->getRules().ConcRequirements[x].ElectiveCourses)		// looping on the elective courses vector
		{
			if (pReg->getStudyPlan()->isCourse(y))
				return true;
			else
				return false;
		}
	}
}

bool ValidityCheck::OverUnderLoadPetition()
{
	GUI* pGUI = pReg->getGUI();
	int* semcrd[4];					// semcrd [year][sem] => num of crd in that sem of that year

	pReg->getStudyPlan()->getYearCrd(semcrd);
	int cr_min = 12;
	int cr_max = 18;
	for (int z = 0; z < 4; z++)
		for (int c = 0; c < 4; c++)
			if (semcrd[z][c] > cr_max)
			{
				pReg->getStudyPlan()->OverUnderLoad_up_down_Check(1);	// to inform him it is overload
				pReg->getStudyPlan()->OverUnderLoad_Check_Check(0);
				return false;
			}
			else if (semcrd[z][c] < cr_min)
			{
				pReg->getStudyPlan()->OverUnderLoad_up_down_Check(0);	// to inform him it is underload
				pReg->getStudyPlan()->OverUnderLoad_Check_Check(0);
				return false;
			}
			else
				return true;
}
bool  ValidityCheck::Execute()
{
	//Number of credits per semester
	//Corequisite, and Prerequisite courses
	StudyPlan* pS = pReg->getStudyPlan();
	pS->check();
	//program requirements

	if (!checkTotalCred(pReg->getStudyPlan()->getTotalcredits()))			//Total credits
		pS->Set_Total_credits_Check(0);

	if (!checkUnivCred(pReg->getStudyPlan()->getTotalUnivCredits()))		//unversity credits
	{
		pS->Set_unversity_credits_Check(0);
		pS->CheckList(pReg->getRules().UnivCompulsory, "University Compulsory");
		pS->CheckList(pReg->getRules().UnivElective, "University Elective");
	}

	if (!checkMajCred(pReg->getStudyPlan()->getTotalMajorCredits()))		//Major credits
	{
		pS->Set_Major_credits_Check(0);
		pS->CheckList(pReg->getRules().MajorElective, "Major Elective");
		pS->CheckList(pReg->getRules().MajorCompulsory, "Major Compulsory");
	}

	if (!checkTrackCred(pReg->getStudyPlan()->getTotalTrackCredits()))		//Track credits
	{
		pS->Set_Track_credits_Check(0);
		pS->CheckList(pReg->getRules().TrackCompulsory, "Track Compulsory");
	}


	pS->WarningReport();
	GUI* pGUI = pReg->getGUI();
	pGUI->DisplayReport();
	return true;
}
ValidityCheck::~ValidityCheck()
{
}