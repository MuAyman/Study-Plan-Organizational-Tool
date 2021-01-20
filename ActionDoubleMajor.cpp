#include "ActionDoubleMajor.h"
#include "Registrar.h"
#include <iostream>

ActionDoubleMajor::ActionDoubleMajor(Registrar* p) :Action(p)
{

}
bool ActionDoubleMajor::Execute()
{
	GUI* pGUI = pReg->getGUI();
	Rules RegRules = pReg->getRules();
	Rules RegRules2 = pReg->getRules2();
	Rules RegRulesDoubleMajor = pReg->getRules();

	pGUI->PrintMsg("Enter major name: ");
	string major2 = pGUI->GetSrting();
	RegRules.major2 = major2;

	for (int i = 0; i < major2.length(); i++)
	{
		major2[i] = toupper(major2[i]);
	}

	while (major2 != "CIE"
		&& major2 != "SPC"
		&& major2 != "ENV"
		&& major2 != "REE"
		&& major2 != "BMS"
		&& major2 != "PEU"
		&& major2 != "NANENG"
		&& major2 != "NANSCIE"
		&& major2 != "MATSCIE")
	{
		pGUI->PrintMsg("Enter a valid major name");
		major2 = pGUI->GetSrting();
		for (int i = 0; i < major2.length(); i++)
			major2[i] = toupper(major2[i]);
	}
	while (major2 == RegRules.major)
	{
		pGUI->PrintMsg("It is the first major! Enter another major name: ");
		major2 = pGUI->GetSrting();
		for (int i = 0; i < major2.length(); i++)
			major2[i] = toupper(major2[i]);
	}
	pReg->RulesReset(RegRules2);
	ifstream input;
	if (major2 == "CIE")
	{
		pReg->RulesRead(input, "CIE-Requirements.txt", RegRules2);
	}
	else if (major2 == "SPC")
		pReg->RulesRead(input, "SPC-Requirements.txt", RegRules2);
	else if (major2 == "ENV")
		pReg->RulesRead(input, "ENV-Requirements.txt", RegRules2);
	else if (major2 == "REE")
		pReg->RulesRead(input, "REE-Requirements.txt", RegRules2);
	else if (major2 == "BMS")
		pReg->RulesRead(input, "Rules.txt", RegRules2);
	else if (major2 == "PEU")
		pReg->RulesRead(input, "PEU-Requirements.txt", RegRules2);
	else if (major2 == "NANENG")
		pReg->RulesRead(input, "NANENG-Requirements.txt", RegRules2);
	else if (major2 == "NANSCIE")
		pReg->RulesRead(input, "Rules.txt", RegRules2);
	else if (major2 == "MATSCIE")
		pReg->RulesRead(input, "Rules.txt", RegRules2);

	input.close();

	ifstream catalogFile;
	pReg->catalogRead(catalogFile, "Source.txt", RegRules2);
	catalogFile.close();
	bool found = false;
	/////I commented it because it needs to be edited////
	for (int i = 0; i < RegRules2.UnivCompulsory.size(); i++) //univCompulsory
	{
		found = false;
		for (int j = 0; j < RegRules.UnivCompulsory.size(); j++)
		{
			if (RegRules2.UnivCompulsory[i] == RegRules.UnivCompulsory[j])
			{
				found = true;
				break;
			}
		}
		if (found == false)
		{
			RegRulesDoubleMajor.UnivCompulsory.push_back(RegRules2.UnivCompulsory[i]);
			RegRulesDoubleMajor.UnivCompCredits += RegRules2.UnivCompCredits;
			RegRulesDoubleMajor.TotalCredits += RegRules2.UnivCompCredits;
		}
	}
	for (int i = 0; i < RegRules2.UnivElective.size(); i++) //univelective
	{
		found = false;
		for (int j = 0; j < RegRules.UnivElective.size(); j++)
		{
			if (RegRules2.UnivElective[i] == RegRules.UnivElective[j])
			{
				found = true;
				break;
			}
		}
		if (found == false)
		{
			RegRulesDoubleMajor.UnivElective.push_back(RegRules2.UnivElective[i]);
			RegRulesDoubleMajor.UnivElectiveCredits += RegRules2.UnivElectiveCredits;
			RegRulesDoubleMajor.TotalCredits += RegRules2.UnivElectiveCredits;
		}
	}

	for (int i = 0; i < RegRules2.TrackCompulsory.size(); i++) //trackcompulsory
	{
		found = false;
		for (int j = 0; j < RegRules.TrackCompulsory.size(); j++)
		{
			if (RegRules2.TrackCompulsory[i] == RegRules.TrackCompulsory[j])
			{
				found = true;
				break;
			}
		}
		if (found == false)
		{
			RegRulesDoubleMajor.TrackCompulsory.push_back(RegRules2.TrackCompulsory[i]);
			RegRulesDoubleMajor.CompTrackCredits += RegRules2.CompTrackCredits;
			RegRulesDoubleMajor.TotalCredits += RegRules2.CompTrackCredits;
		}
	}

	for (int i = 0; i < RegRules2.MajorCompulsory.size(); i++) //majorcompulsory
	{
		found = false;
		for (int j = 0; j < RegRules.MajorCompulsory.size(); j++)
		{
			if (RegRules2.MajorCompulsory[i] == RegRules.MajorCompulsory[j])
			{
				found = true;
				break;
			}
		}
		if (found == false)
		{
			RegRulesDoubleMajor.MajorCompulsory.push_back(RegRules2.MajorCompulsory[i]);
			RegRulesDoubleMajor.MajCommonCompCredits += RegRules2.MajCommonCompCredits;
			RegRulesDoubleMajor.TotalCredits += RegRules2.MajCommonCompCredits;
		}
	}


	for (int i = 0; i < RegRules2.MajorElective.size(); i++) //majorelective
	{
		found = false;
		for (int j = 0; j < RegRules.MajorElective.size(); j++)
		{
			if (RegRules2.MajorElective[i] == RegRules.MajorElective[j])
			{
				found = true;
				break;
			}
		}
		if (found == false)
		{
			RegRulesDoubleMajor.MajorElective.push_back(RegRules2.MajorElective[i]);
			RegRulesDoubleMajor.MajCommonElecCredits += RegRules2.MajCommonElecCredits;
			RegRulesDoubleMajor.TotalCredits += RegRules2.MajCommonElecCredits;
		}
	}

	if (RegRules2.NumOfConcent == 0)
		RegRulesDoubleMajor.NumOfConcent = RegRules.NumOfConcent;
	else if (RegRules.NumOfConcent == 0 && RegRules2.NumOfConcent != 0)
	{
		RegRulesDoubleMajor.NumOfConcent = RegRules2.NumOfConcent;
		for (int i = 0; i < RegRules2.NumOfConcent; i++)
			RegRulesDoubleMajor.ConcRequirements.push_back(RegRules2.ConcRequirements[i]);
	}
	else
	{
		RegRulesDoubleMajor.NumOfConcent += RegRules2.NumOfConcent;
		for (int j = 0; j < RegRules2.NumOfConcent; j++)
			RegRulesDoubleMajor.ConcRequirements.push_back(RegRules2.ConcRequirements[j]);
	}
	//====================
	pReg->setdoubleMajor(true);
	pGUI->PrintMsg("Now You can add the courses of double majors! Ok?..Enter Ok");
	string x = pGUI->GetSrting();
	return true;
}
ActionDoubleMajor::~ActionDoubleMajor()
{

}