#pragma once
#include "Registrar.h"
#include "Actions/Action.h"
#include <iostream>
class ValidityCheck : public Action
{
	window* win;
public:
	ValidityCheck(Registrar* pReg);
	bool checkUnivCred(int cr);
	bool checkTrackCred(int cr);
	bool checkMajCred(int cr);
	bool checkTotalCred(int cr);
	bool checkConcentCred(int cr);
	bool OverUnderLoadPetition();
	bool ConcenReq(string major);
	bool Execute();
	//bool ValidityCheck::PreReq_CoReq(Course* pC);
	//bool ValidityCheck::petition(int SemCredits);
	//bool ValidityCheck::CreditsCheck(int SemCredits);
	~ValidityCheck();
	window* returnWindow();
	

};