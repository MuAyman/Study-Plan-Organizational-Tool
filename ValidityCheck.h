#pragma once
#include "Registrar.h"
#include "ActionImportPlan.h"
#include "StudyPlan/StudyPlan.h"

#include <iostream>
class ValidityCheck
{
	vector <vector<char*>> Concen[1];		// Concen[0][0] = fisrt concen compulsary courses vector
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
	bool OverUnderLoadPetition();
	~ValidityCheck();
};