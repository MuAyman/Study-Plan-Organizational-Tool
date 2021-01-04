#include "ActionAddRules.h"
#include<iostream>
#include <string>
using namespace std;
ActionAddRules::ActionAddRules(Registrar*) :Action(pReg)
{
}

ActionAddRules::~ActionAddRules()
{
}

bool ActionAddRules::catalogRead(ifstream& File, string name, Rules& R)		//Still working on the part of (" And ")..Mariam
{
	File.open(name, ios::in);
	if (File.fail())
		return false;
	else
	{
		char* psc, * pssc, * psA;
		char* context1 = nullptr;
		char* context2 = nullptr;
		char* context3 = nullptr;
		const int size = 300;
		char line[size];
		string read;

		while (File.getline(line, size))
		{
			int i = 0;
			int j = 0, k = 0;

			psc = strtok_s(line, ",", &context1);

			CourseInfo c;
			c.Code = psc;
			i++;
			while (psc != NULL)
			{
				psc = strtok_s(NULL, ",", &context1);
				if (i == 1)
				{
					c.Title = psc;
				}
				if (i == 2)
				{
					c.Credits = stoi(psc);
				}

				if (i > 2 && i < 5)
				{
					pssc = strtok_s(psc, ": ", &context2);
					read = pssc;
					if (read == "Coreq")
					{
						psA = strtok_s(context2, " And ", &context3);
						while (psA != NULL)
						{
							c.CoReqList.push_back(psA);
							psA = strtok_s(NULL, " And ", &context3);
						}
					}
					else if (read == "Prereq")
					{
						psA = strtok_s(context2, " And ", &context3);
						while (psA != NULL)
						{
							c.PreReqList.push_back(psA);
							psA = strtok_s(NULL, " And ", &context3);
						}
					}

				}
				
				i++;
			}
			R.CourseCatalog.push_back(c);
		}
	}
	return true;
}

bool ActionAddRules::Execute()
{
	fstream OfferingsData;
	do {
		GUI* pGUI = pReg->getGUI();
		pGUI->PrintMsg("Enter a correct file path: ");
		string filePath = pGUI->GetSrting();
		OfferingsData.open(filePath, ios::in);
	} while (OfferingsData.fail());

	char* psc;
	char* context = nullptr;
	const int size = 500;
	char line[size];

	while (OfferingsData.getline(line, size))
	{
		int static year = 0;
		psc = strtok_s(line, ",", &context);
		R.OffringsList[year].Year = psc;
		year++;

		psc = strtok_s(line, ",", &context);

		if (psc == "Fall")
		{
			R.OffringsList[year].Offerings[FALL];
			psc = strtok_s(line, ",", &context);
			while (psc != "Spring")
			{
				R.OffringsList[year].Offerings[FALL].push_back(psc);
				psc = strtok_s(line, ",", &context);
			}
		}
		else if (psc == "Spring")
		{
			R.OffringsList[year].Offerings[SPRING];
			psc = strtok_s(line, ",", &context);
			while (psc != "Summer")
			{
				R.OffringsList[year].Offerings[SPRING].push_back(psc);
				psc = strtok_s(line, ",", &context);
			}
		}
		else if (psc == "Summer")
		{
			R.OffringsList[year].Offerings[SUMMER];
			psc = strtok_s(line, ",", &context);
			while (psc != NULL)
			{
				R.OffringsList[year].Offerings[SUMMER].push_back(psc);
				psc = strtok_s(line, ",", &context);
			}
		}
	}
	OfferingsData.close();
	return true;
}

bool ActionAddRules::RulesRead(ifstream& File, string name, Rules& R1)
{
	File.open(name, ios::in);
	if (File.fail())
		return false;
	else
	{
		char* psc;
		string Read;
		char* context = nullptr;
		const int size = 300;
		char line[size];
		while (File.getline(line, size))
		{
			int i = 0;
			psc = strtok_s(line, ",", &context);
			Read = psc;
			i++;
			if (i == 1)
			{
				while (psc != NULL)
				{
					if (i > 1)
					{
						if (Read == "Total credits")
						{
							R1.ReqUnivCredits = stoi(psc);
						}
						else if (Read == "Required track credits")
						{
							//R1.ReqTrackCredits = stoi(psc);
						}
						else if (Read == "max cred/sem")
						{
							R1.SemMaxCredit = stoi(psc);
						}
						else if (Read == "min cred/sem")
						{
							R1.SemMinCredit = stoi(psc);
						}
						else if (Read == "Required major credits")
						{
							//R1.ReqMajorCredits = stoi(psc);
						}
						else if (Read == "Comp Courses")
						{
							R1.UnivCompulsory.push_back(psc);
						}
						else if (Read == " Elec Courses")
						{
							R1.UnivElective.push_back(psc);
						}
						else if (Read == "Track Comp Courses")
						{
							R1.TrackCompulsory.push_back(psc);
						}
						else if (Read == "Track Elec Courses")
						{
							R1.TrackElective.push_back(psc);
						}
						else if (Read == "Major courses Elec")
						{
							R1.MajorElective.push_back(psc);
						}
						else if (Read == "Major courses comp")
						{
							R1.MajorCompulsory.push_back(psc);
						}
						//else if (Read == "Number of concentration")
							//R1.NumOfCon = stoi(psc);
					}
					psc = strtok_s(NULL, ",", &context);
					i++;

				}
			}
		}
		return true;
	}
}

bool ActionAddRules::ExecuteRules()
{
	string major;
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("enter your major name: ");
	major = pGUI->GetSrting();

	for (int i = 0; i < major.length(); i++)
	{
		major[i] = toupper(major[i]);
	}

	while (major != "CIE"
		&& major != "SPC"
		&& major != "ENV"
		&& major != "REE"
		&& major != "BMS"
		&& major != "PEU"
		&& major != "NANENG"
		&& major != "NANSCIE"
		&& major != "MATSCIE")
	{
		pGUI->PrintMsg("enter a valid major name");
		major = pGUI->GetSrting();
	}

	ifstream input;

	if (major == "CIE")
		RulesRead(input, "Rules.txt", R);
	else if (major == "SPC")
		RulesRead(input, "Rules.txt", R);
	else if (major == "ENV")
		RulesRead(input, "Rules.txt", R);
	else if (major == "REE")
		RulesRead(input, "Rules.txt", R);
	else if (major == "BMS")
		RulesRead(input, "Rules.txt", R);
	else if (major == "PEU")
		RulesRead(input, "Rules.txt", R);
	else if (major == "NANENG")
		RulesRead(input, "Rules.txt", R);
	else if (major == "NANSCIE")
		RulesRead(input, "Rules.txt", R);
	else if (major == "MATSCIE")
		RulesRead(input, "Rules.txt", R);

	input.close();

	ifstream entering;
	catalogRead(entering, "Catalog - 2020 12 19.txt", R);
	cout << R.CourseCatalog[0].Code;
	entering.close();

	return true;
}