#pragma once
#include "Registrar.h"
#include "ActionImportPlan.h"
#include "StudyPlan/StudyPlan.h"

#include "Actions/Action.h"
#include <iostream>
class ValidityCheck : public Action
{
	/*vector <vector<char*>> Concen[1];		// Concen[0][0] = fisrt concen compulsary courses vector
										   // Concen[0][1] = first concen elective courses vector
	int* semcrd[4];					// semcrd [year][sem] => num of crd in that sem of that year
	ActionImportPlan* pIP;
	Registrar* pReg;
	GUI* pGUI = pReg->getGUI();

public:
	ValidityCheck();
	bool ConcenReq(string major);
	bool PreReq_CoReq(Course* pC);
	bool CreditsCheck(int SemCredits);
	bool petition(int semesterSemCredits);
	bool OverUnderLoadPetition();*/
public:
	ValidityCheck(Registrar* pReg);
	bool checkUnivCred(int cr);
	bool checkTrackCred(int cr);
	bool checkMajCred(int cr);
	bool checkTotalCred(int cr);
	bool checkConcentCred(int cr);
	bool Execute();
	//bool ValidityCheck::PreReq_CoReq(Course* pC);
	//bool ValidityCheck::petition(int SemCredits);
	//bool ValidityCheck::CreditsCheck(int SemCredits);
	~ValidityCheck();


};
