#include "ValidityCheck.h"


ValidityCheck::ValidityCheck()
{
}

bool ValidityCheck::CreditsCheck(int SemCredits)
{
	int cr_min = pReg->getRules().SemMinCredit;
	int cr_max = pReg->getRules().SemMaxCredit;
	if (SemCredits > cr_max)
	{
		pGUI->PrintMsg("Credits is greater than Max credits");
		return false;
		//cout << "Credits in semester " << semester << " Year " << year << " is greater than Max_credits";
	}
	else if (SemCredits < cr_min)
	{
		//cout << "Credits in semester " << semester << " Year " << year << " is less than Min_credits";
		pGUI->PrintMsg("Credits is less than Min credits");
		return false;
	}
	else
		return true;
}

bool ValidityCheck::PreReq_CoReq(Course* pC)
{
	int x_sem = pC->getGfxInfo().x;
	int y_sem = pC->getGfxInfo().y;
	Course* prerequisite = nullptr; //course type to get its GfxInfo
	Course* corequisite = nullptr;

	list<Course_Code> PreReq = pC->getPreReq();	//list of prerequisites
	list<Course_Code> CoReq = pC->getCoreReq();	//list of coerequisites

	for (auto pre = PreReq.begin(); pre != PreReq.end(); pre++)
	{
		delete prerequisite;
		prerequisite = pReg->getStudyPlay()->getCourse(*pre);
		if (y_sem > prerequisite->getGfxInfo().y)
			cout << "Error in prerequisite " << *pre << " and course " << pC->getCode() << endl;
	}

	for (auto cor = CoReq.begin(); cor != CoReq.end(); cor++)
	{
		delete corequisite;
		corequisite = pReg->getStudyPlay()->getCourse(*cor);
		if (y_sem != corequisite->getGfxInfo().y && x_sem != corequisite->getGfxInfo().x)
			cout << "Error in corequisite " << *cor << " and course " << pC->getCode();
	}
	return true;
}



bool ValidityCheck::petition(int SemCredits)
{
	string petition = "no";
	if (!CreditsCheck(SemCredits))
	{
		pGUI->PrintMsg("You can request for a petition for your case! (yes/no)");
		petition = pGUI->GetSrting();
	}
	if (petition == "no")
		return false;
	else
		return true;
}

ValidityCheck::~ValidityCheck()
{
}