#pragma once
#include "Registrar.h"
#include <iostream>
class ValidityCheck
{
	Registrar* pReg;
	GUI* pGUI = pReg->getGUI();
public:
	ValidityCheck();

	bool PreReq_CoReq(Course* pC);
	bool CreditsCheck(int SemCredits);
	bool petition(int semesterSemCredits);

	~ValidityCheck();
};