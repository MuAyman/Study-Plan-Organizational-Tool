#pragma once
#include "Registrar.h"
#include "ActionImportPlan.h"
#include "StudyPlan/StudyPlan.h"

#include "Actions/Action.h"
#include <iostream>
class ValidityCheck : public Action
{
//	vector <vector<char*>> Concen[1];		// Concen[0][0] = fisrt concen compulsary courses vector
										   // Concen[0][1] = first concen elective courses vector
	ActionImportPlan* pIP;

public:

	ValidityCheck(Registrar* pReg);
	bool ConcenReq(string major);
	bool OverUnderLoadPetition();
	bool checkUnivCred(int cr);
	bool checkTrackCred(int cr);
	bool checkMajCred(int cr);
	bool checkTotalCred(int cr);
	//bool checkConcentCred(int cr);
	bool Execute();

	//bool ValidityCheck::PreReq_CoReq(Course* pC);
	//bool ValidityCheck::petition(int SemCredits);
	//bool ValidityCheck::CreditsCheck(int SemCredits);
	~ValidityCheck();
	window* returnWindow();


};
