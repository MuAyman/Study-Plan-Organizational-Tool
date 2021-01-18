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
	int LineNum = 1, NoOfConcen = 0;

	const int size = 5000;
	char line[size];
	char* psc = nullptr;
	char* context = nullptr;
	major = pIP->major;
	for (int i = 0; i < major.length(); i++)
	{
		major[i] = toupper(major[i]);
	}

	if (major == "CIE"
		|| major == "SPC"
		|| major == "ENV"
		|| major == "REE"
		|| major == "BMS"
		|| major == "PEU"
		|| major == "NANENG"
		|| major == "NANSCIE"
		|| major == "MATSCIE")
		major = major + "-Requirements.txt";
	else
		return false;

	ifstream ReqFile;
	ReqFile.open(major);

	/****************************************  The filling process ****************************************/

	while (ReqFile.getline(line, size))
	{
		if (LineNum == 5)
		{
			ReqFile >> NoOfConcen;
			Concen->resize(NoOfConcen);
		}

		if (LineNum == 6)
		{
			psc = strtok_s(line, ",", &context);
			while (psc != NULL)
			{
				int a = 0; int static b = 0;
				double static y = 0;
				stringstream geek(psc);		// casting from char to int
				geek >> a;

				if (b == 0 || b == 1)		// checks b is not our of range
					Concen[(int)trunc(y)][b].resize(a);
				else
				{
					b = 0;
					Concen[(int)trunc(y)][b].resize(a);
				}
				b++; y = y + 0.5;
				psc = strtok_s(NULL, ",", &context);
			}
		}
		if (LineNum >= 12)
		{
			for (int c = 0; c < NoOfConcen; c++)
			{
				if (LineNum == (12 + 2 * c))		// Compulsary courses line
				{
					psc = strtok_s(line, ",", &context);
					while (psc != NULL)
					{
						Concen[c][0].push_back(psc);				// filling the compulsary courses vector
						psc = strtok_s(NULL, ",", &context);
					}
				}
				if (LineNum == (12 + (2 * c) + 1))	// elective courses line
				{
					psc = strtok_s(line, ",", &context);
					while (psc != NULL)
					{
						Concen[c][1].push_back(psc);				// filling the elective courses vector
						psc = strtok_s(NULL, ",", &context);
					}
				}
			}
		}
		LineNum++;
	}
	/****************************************  The Checking process ****************************************/

	for (int x = 0; x < NoOfConcen; x++)
	{
		for (auto y : Concen[x][0])		// looping on the compulsary courses vector
		{
			if (pReg->getStudyPlay()->isCourse(y))
				return true;
			else
				return false;
		}
		for (auto y : Concen[x][1])		// looping on the elective courses vector
		{
			if (pReg->getStudyPlay()->isCourse(y))
				return true;
			else
				return false;
		}
	}

}

bool ValidityCheck::OverUnderLoadPetition()
{
	pReg->getStudyPlay()->getYearCrd(semcrd);
	int cr_min = pReg->RegRules.SemMinCredit;
	int cr_max = pReg->RegRules.SemMaxCredit;
	for (int z = 0; z < 4; z++)
		for (int c = 0; c < 4; c++)
			if (semcrd[z][c] > cr_max)
			{
				pGUI->PrintMsg("Credits is greater than Max credits in year");		// year z+1 & sem c+1	??!!
				return true;
			}
			else if (semcrd[z][c] < cr_min)
			{
				pGUI->PrintMsg("Credits is less than Min credits");					// year z+1 & sem c+1	??!!
				return true;
			}
			else
				return false;
}



bool ValidityCheck::CreditsCheck(int SemCredits)
{
	int cr_min = pReg->RegRules.SemMinCredit;
	int cr_max = pReg->RegRules.SemMaxCredit;
	if (SemCredits > cr_max)
	{
		pGUI->PrintMsg("Credits is greater than Max credits");

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
	StudyPlan* pS = pReg->getStudyPlay();
	pS->check();
	//program requirements

	if (!checkTotalCred(pReg->getStudyPlay()->getTotalcredits()))   //Total credits
	{
		pS->Set_Total_credits_Check(0);
		cout << "Error in Total credits" << endl;
	}


	if (!checkUnivCred(pReg->getStudyPlay()->getTotalUnivCredits()))  //unversity credits
	{
		pS->Set_unversity_credits_Check(0);
		cout << "Error in unversity credits" << endl;
	}


	if (!checkMajCred(pReg->getStudyPlay()->getTotalMajorCredits()))  //Major credits
	{
		pS->Set_Major_credits_Check(0);
		cout << "Error in Major credits" << endl;
	}


	if (!checkTrackCred(pReg->getStudyPlay()->getTotalTrackCredits()))  //Track credits
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
// int x_sem = pC->getGfxInfo().x;
// int y_sem = pC->getGfxInfo().y;
// Course* prerequisite = nullptr; //course type to get its GfxInfo
// Course* corequisite = nullptr;
//
// list<Course_Code> PreReq = pC->getPreReq(); //list of prerequisites
// list<Course_Code> CoReq = pC->getCoreReq(); //list of coerequisites
//
// for (auto pre = PreReq.begin(); pre != PreReq.end(); pre++)
// {
//  delete prerequisite;
//  prerequisite = pReg->getStudyPlay()->getCourse(*pre);
//  if (y_sem > prerequisite->getGfxInfo().y)
//   cout << "Error in prerequisite " << *pre << " and course " << pC->getCode() << endl;
// }
//
// for (auto cor = CoReq.begin(); cor != CoReq.end(); cor++)
// {
//  delete corequisite;
//  corequisite = pReg->getStudyPlay()->getCourse(*cor);
//  if (y_sem != corequisite->getGfxInfo().y && x_sem != corequisite->getGfxInfo().x)
//   cout << "Error in corequisite " << *cor << " and course " << pC->getCode();
// }
// return true;
//}

//bool ValidityCheck::petition(int SemCredits)
//{
// string petition = "no";
// if (!CreditsCheck(SemCredits))
// {
//  pGUI->PrintMsg("You can request for a petition for your case! (yes/no)");
//  petition = pGUI->GetSrting();
// }
// if (petition == "no")
//  return false;
// else
//  return true;
//}

//bool ValidityCheck::CreditsCheck(int SemCredits)
//{
// int cr_min = pReg->RegRules.SemMinCredit;   //12
// int cr_max = pReg->RegRules.SemMaxCredit;   //21
// if (SemCredits > cr_max)
// {
//  pGUI->PrintMsg("Credits is greater than Max credits");
//  return false;
//  //cout << "Credits in semester " << semester << " Year " << year << " is greater than Max_credits";
// }
// else if (SemCredits < cr_min)
// {
//  //cout << "Credits in semester " << semester << " Year " << year << " is less than Min_credits";
//  pGUI->PrintMsg("Credits is less than Min credits");
//  return false;
// }
// else
//  return true;
//}
