#include "ValidityCheck.h"
#include <fstream>
#include <sstream>
#include "StudyPlan/StudyPlan.h"


ValidityCheck::ValidityCheck(Registrar* pReg) :Action(pReg)
{
	pIP = nullptr;
}

bool ValidityCheck::ConcenReq(string major)
{

	int NoOfConcen = pReg->RegRules.NumOfConcent;

	for (int x = 0; x < NoOfConcen; x++)
	{
		cout << "pReg->RegRules.ConcRequirements[x].CompulsoryCourses: ";
		for (int y = 0;  y < pReg->RegRules.ConcRequirements[x].CompulsoryCourses.size(); y++)		// looping on the compulsory courses vector
			cout << pReg->RegRules.ConcRequirements[x].CompulsoryCourses[y] << endl;
		for (auto y : pReg->RegRules.ConcRequirements[x].CompulsoryCourses)		// looping on the compulsory courses vector
		{
			if (pReg->getStudyPlan()->isCourse(y))
				return true;
			else
				return false;
		}

		cout << "pReg->RegRules.ConcRequirements[x].ElectiveCourses: ";
		for (int y = 0; y < pReg->RegRules.ConcRequirements[x].ElectiveCourses.size(); y++)		// looping on the compulsory courses vector
			cout << pReg->RegRules.ConcRequirements[x].ElectiveCourses[y] << endl;
		for (auto y : pReg->RegRules.ConcRequirements[x].ElectiveCourses)		// looping on the elective courses vector
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


//bool ValidityCheck::CreditsCheck(int SemCredits)
//{
//
//
//}
bool ValidityCheck::checkTotalCred(int cr)
{
	if (cr == pReg->RegRules.TotalCredits)
		return true;
	else
		return false;
}
bool ValidityCheck::checkMajCred(int cr)
{
	if (cr == (pReg->RegRules.MajCommonCompCredits + pReg->RegRules.MajCommonElecCredits))
		return true;
	else
		return false;
}
bool ValidityCheck::checkUnivCred(int cr)
{
	if (cr == (pReg->RegRules.UnivElectiveCredits + pReg->RegRules.UnivCompCredits))
		return true;
	else
		return false;
}
bool ValidityCheck::checkTrackCred(int cr)
{
	if (cr == pReg->RegRules.CompTrackCredits)
		return true;
	else
		return false;
}

bool  ValidityCheck::Execute()
{
	//Number of credits per semester
	//Corequisite, and Prerequisite courses
	StudyPlan* pS = pReg->getStudyPlan();
	//pS->check();
	//program requirements

	if (!checkTotalCred(pReg->getStudyPlan()->getTotalcredits()))			//Total credits
	{
		pS->Set_Total_credits_Check(0);
		cout << "Error in Total credits" << endl;
	}


	if (!checkUnivCred(pReg->getStudyPlan()->getTotalUnivCredits()))		//unversity credits
	{
		pS->Set_unversity_credits_Check(0);
		cout << "Error in unversity credits" << endl;
	}


	if (!checkMajCred(pReg->getStudyPlan()->getTotalMajorCredits()))		//Major credits
	{
		pS->Set_Major_credits_Check(0);
		cout << "Error in Major credits" << endl;
	}


	if (!checkTrackCred(pReg->getStudyPlan()->getTotalTrackCredits()))		//Track credits
	{
		pS->Set_Track_credits_Check(0);
		cout << "Error in Track credits" << endl;
	}
	pS->WarningReport();
	GUI* pGUI = pReg->getGUI();
	//pGUI->DisplayReport();
	return true;
}
ValidityCheck::~ValidityCheck()
{
}


//bool ValidityCheck::PreReq_CoReq(Course* pC)
//{
//	int x_sem = pC->getGfxInfo().x;
//	int y_sem = pC->getGfxInfo().y;
//	Course* prerequisite = nullptr; //course type to get its GfxInfo
//	Course* corequisite = nullptr;
//
//	list<Course_Code> PreReq = pC->getPreReq();	//list of prerequisites
//	list<Course_Code> CoReq = pC->getCoreReq();	//list of coerequisites
//
//	for (auto pre = PreReq.begin(); pre != PreReq.end(); pre++)
//	{
//		delete prerequisite;
//		prerequisite = pReg->getStudyPlan()->getCourse(*pre);
//		if (y_sem > prerequisite->getGfxInfo().y)
//			cout << "Error in prerequisite " << *pre << " and course " << pC->getCode() << endl;
//	}
//
//	for (auto cor = CoReq.begin(); cor != CoReq.end(); cor++)
//	{
//		delete corequisite;
//		corequisite = pReg->getStudyPlan()->getCourse(*cor);
//		if (y_sem != corequisite->getGfxInfo().y && x_sem != corequisite->getGfxInfo().x)
//			cout << "Error in corequisite " << *cor << " and course " << pC->getCode();
//	}
//	return true;
//}

//bool ValidityCheck::petition(int SemCredits)
//{
//	string petition = "no";
//	if (!CreditsCheck(SemCredits))
//	{
//		pGUI->PrintMsg("You can request for a petition for your case! (yes/no)");
//		petition = pGUI->GetSrting();
//	}
//	if (petition == "no")
//		return false;
//	else
//		return true;
//}


//bool ValidityCheck::CreditsCheck(int SemCredits)
//{
//	int cr_min = pReg->RegRules.SemMinCredit;   //12
//	int cr_max = pReg->RegRules.SemMaxCredit;   //21
//	if (SemCredits > cr_max)
//	{
//		pGUI->PrintMsg("Credits is greater than Max credits");
//		return false;
//		//cout << "Credits in semester " << semester << " Year " << year << " is greater than Max_credits";
//	}
//	else if (SemCredits < cr_min)
//	{
//		//cout << "Credits in semester " << semester << " Year " << year << " is less than Min_credits";
//		pGUI->PrintMsg("Credits is less than Min credits");
//		return false;
//	}
//	else
//		return true;
//}
