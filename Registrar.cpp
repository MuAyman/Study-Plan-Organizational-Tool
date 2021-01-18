#include "Registrar.h"

#include "Actions/ActionAddCourse.h"
#include "ActionImportPlan.h"
#include "ActionExit.h"
#include "ActionAddNotes.h"
#include "ActionSavePlan.h"
#include "ActionInfo.h"
#include "ActionDeleteCourse.h"
#include "Drag_DropAction.h"
#include "ActionChangeCourse.h"
#include "ValidityCheck.h"
#include "ActionFilter.h"
#include "ActionLinks.h"
#include "CalculateGPA.h"
#include "ActionDoubleMajor.h"
#include "ActionDoubleConcenteration.h"
#include "ActionStudentLevel.h"
#include "ActionUpdateStatus.h"
#include "ActionAddMinor.h"
#include <sstream>
#include <cctype>

Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
	
}
//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}

bool Registrar::ExecuteOfferings()					//OFFEREINGS **************************************		AYMAN
{
	GUI* pGUI = this->getGUI();
	ifstream OfferingsData;
	OfferingsData.open("tt.txt");

	if (OfferingsData.fail())
	{
		return false;
	}
	else
	{
		char* psc = nullptr;
		const int size = 500;
		char line[size];
		AcademicYearOfferings as;
		while (OfferingsData.getline(line, size))
		{

			int static i = 0; i++;
			char* context = nullptr;							// YEAR
			psc = strtok_s(line, ",", &context);
			as.Year = psc;
			cout << as.Year << endl;
			cout << i << endl;
			char* context2 = nullptr;							// FALL
			psc = strtok_s(context, ",", &context2);
			char* context3 = nullptr;
			while (psc != NULL)							// FALL/SPRING/SUMMER COURSES
			{
				cout << "before: " << psc << endl;
				psc = strtok_s(NULL, ",", &context2);
				if (psc != NULL)
				{
					cout << "after: " << psc << endl;
					cout << i << endl;
					as.Offerings[i - 1].push_back(psc);
				}
			}

		}
		this->RegRules.OffringsList.push_back(as);
		OfferingsData.close();
		return true;
	}
	
}

//returns the study plan
StudyPlan* Registrar::getStudyPlay() const
{
	return pSPlan;
}
Rules Registrar::getRules()
{
	return RegRules;
}
void Registrar::checkType(Course* pC) //new
{
	int t = 0; // variable to check whether the course type is declared or not yet
	// to not enter each loop 

	if (t == 0) //UnivCompulsory
	{
		for (auto type = RegRules.UnivCompulsory.begin(); type != RegRules.UnivCompulsory.end(); type++)
		{
			if (pC->getCode() == *type)
			{
				pC->setType("UnivCompulsory");
				t = 1;
				break;
			}
		}
	}

	if (t == 0) // UnivElective
	{
		for (auto type = RegRules.UnivElective.begin(); type != RegRules.UnivElective.end(); type++)
		{
			if (pC->getCode() == *type)
			{
				pC->setType("UnivElective");
				t = 1;
				break;
			}
		}
	}

	if (t == 0) //TrackCompulsory
	{
		for (auto type = RegRules.TrackCompulsory.begin(); type != RegRules.TrackCompulsory.end(); type++)
		{
			if (pC->getCode() == *type)
			{
				pC->setType("TrackCompulsory");
				t = 1;
				break;
			}
		}
	}

	if (t == 0) //MajorCompulsory
	{
		for (auto type = RegRules.MajorCompulsory.begin(); type != RegRules.MajorCompulsory.end(); type++)
		{
			if (pC->getCode() == *type)
			{
				pC->setType("MajorCompulsory");
				t = 1;
				break;
			}
		}
	}

	if (t == 0) //MajorElective
	{
		for (auto type = RegRules.MajorElective.begin(); type != RegRules.MajorElective.end(); type++)
		{
			if (pC->getCode() == *type)
			{
				pC->setType("MajorElective");
				t = 1;
				break;
			}
		}
	}

}

//bool Registrar::catalogRead(ifstream& File, string name, Rules& R)
//{
//	File.open(name, ios::in);
//	if (File.fail())
//		return false;
//	else
//	{
//		char* psc;
//		char* context1 = nullptr;
//		const int size = 300;
//		char line[size];
//		while (File.getline(line, size))
//		{
//			int i = 0, j = 0, k = 0;
//			psc = strtok_s(line, ",", &context1);
//			CourseInfo c;
//			c.Code = psc;
//			i++;
//			while (psc != NULL)
//			{
//				if (i == 1)
//				{
//					psc = strtok_s(NULL, ",", &context1);
//					c.Title = psc;
//				}
//				if (i == 2)
//				{
//					psc = strtok_s(NULL, ",", &context1);
//					const string A = psc;
//					c.Credits = stoi(A);
//				}
//				if (i > 2 && i < 5)
//				{
//					while (psc != NULL)
//					{
//						psc = strtok_s(NULL, ",", &context1);
//						if (psc != NULL)
//						{
//							string s = psc;
//							if (s.substr(0, 7) == "Coreq: ")
//							{
//								string h = s.substr(7);
//								stringstream ss(h);
//								string temp, code, num, m;
//								int i = 0;
//								while (ss >> temp)
//								{
//									if (temp != "AND")
//									{
//										if (isdigit(temp[0]))
//										{
//											num = temp;
//											i++;
//										}
//										else
//										{
//											code = temp;
//											i++;
//										}
//										if (i == 2)
//										{
//											m = code + " " + num;
//											c.CoReqList.push_back(m);
//											
//											i = 0;
//										}
//									}
//								}
//							}
//							if (s.substr(0, 8) == "Prereq: ")
//							{
//								string h = s.substr(8);
//								stringstream ss(h);
//								string temp, code, num, m;
//								int i = 0;
//								while (ss >> temp)
//								{
//									if (temp != "AND")
//									{
//										if (isdigit(temp[0]))
//										{
//											num = temp;
//											i++;
//										}
//										else
//										{
//											code = temp;
//											i++;
//										}
//										if (i == 2)
//										{
//											m = code + " " + num;
//											c.PreReqList.push_back(m);
//											i = 0;
//										}
//									}
//								}
//							}
//						}
//					}
//				}
//				i++;
//			}
//			R.CourseCatalog.push_back(c);
//		}
//	}
//	return true;
//}
bool Registrar::catalogRead(ifstream& File, string name, Rules& R)
{
	File.open(name, ios::in);
	if (File.fail())
		return false;
	else
	{
		char* psc;
		char* context1 = nullptr;
		const int size = 300;
		char line[size];
		while (File.getline(line, size))
		{
			int i = 0, j = 0, k = 0;
			psc = strtok_s(line, ",", &context1);
			CourseInfo* c = new CourseInfo;
			c->Code = psc;
			i++;
			while (psc != NULL)
			{
				if (i == 1)
				{
					psc = strtok_s(NULL, ",", &context1);
					c->Title = psc;
				}
				if (i == 2)
				{
					psc = strtok_s(NULL, ",", &context1);
					const string A = psc;
					c->Credits = stoi(A);
				}
				if (i > 2 && i < 5)
				{
					while (psc != NULL)
					{
						psc = strtok_s(NULL, ",", &context1);
						if (psc != NULL)
						{
							string s = psc;
							if (s.substr(0, 7) == "Coreq: ")
							{
								string h = s.substr(7);
								stringstream ss(h);
								string temp, code, num, m;
								int i = 0;
								while (ss >> temp)
								{
									if (temp != "AND")
									{
										if (isdigit(temp[0]))
										{
											num = temp;
											i++;
										}
										else
										{
											code = temp;
											i++;
										}
										if (i == 2)
										{
											m = code + " " + num;
											c->CoReqList.push_back(m);

											i = 0;
										}
									}
								}
							}
							if (s.substr(0, 8) == "Prereq: ")
							{
								string h = s.substr(8);
								stringstream ss(h);
								string temp, code, num, m;
								int i = 0;
								while (ss >> temp)
								{
									if (temp != "AND")
									{
										if (isdigit(temp[0]))
										{
											num = temp;
											i++;
										}
										else
										{
											code = temp;
											i++;
										}
										if (i == 2)
										{
											m = code + " " + num;
											c->PreReqList.push_back(m);
											i = 0;
										}
									}
								}
							}
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
bool Registrar::PreCoCourse(Rules& R)
{
	for (int i = 0; i < R.CourseCatalog.size(); i++)
	{
		for (auto j = 0; j < R.CourseCatalog[i]->PreReqList.size(); j++)
		{
		Course* CRS = pSPlan->getCourse(R.CourseCatalog[i]->PreReqList[j]);
		if (CRS != NULL)
		{
		R.CourseCatalog[i]->PreReqC.push_back(CRS);
		}

		}
		for (auto j = 0; j < R.CourseCatalog[i]->CoReqList.size(); j++)
		{
			Course* CRS = pSPlan->getCourse(R.CourseCatalog[i]->CoReqList[j]);
			if (CRS != NULL)
			{
			R.CourseCatalog[i]->CoReqC.push_back(CRS);
			}

		}
	}
	
		
	return true;
}
bool Registrar::RulesRead(ifstream& File, string name, Rules& R1)
{
	File.open(name, ios::in);
	if (File.fail())
		return false;
	else
	{
		char* psc;
		string Read;
		char* context = nullptr;
		const int size = 400;
		char line[size];
		int i = 0;
		while (File.getline(line, size))
		{
			psc = strtok_s(line, ",", &context);
			if (i == 0) //Total credits
			{
				R1.TotalCredits = stoi(psc);
			}
			if (i == 1) //UnivCompCredit
			{
				R1.UnivCompCredits = stoi(psc);
				i++;
				psc = strtok_s(NULL, ",", &context);
			}
			if (i == 2) //univElectiveCredit
			{
				R1.UnivElectiveCredits = stoi(psc);
			}
			else if (i == 3) //CompulsoryTrackCredit
			{
				R1.CompTrackCredits = stoi(psc);
			}
			else if (i == 4) //Magor common compulsory credits
			{
				R1.MajCommonCompCredits = stoi(psc);
				i++;
				psc = strtok_s(NULL, ",", &context);
			}
			else if (i == 5) //Magor common Elective credits
			{
				R1.MajCommonElecCredits = stoi(psc);
			}
			else if (i == 6) //Number of concentrations
			{
				R1.NumOfConcent = stoi(psc);
				Concentration dummyConcent;
				for (int i = 0; i < R1.NumOfConcent; i++)
				{
					R1.ConcRequirements.push_back(dummyConcent);
				}
			}
			else if (i == 7) //Concentrations Credits
			{
				for (int i = 0; i < R1.NumOfConcent; i++)
				{
					R1.ConcRequirements[i].comp_credits = stoi(psc);
					psc = strtok_s(NULL, ",", &context);
					R1.ConcRequirements[i].elective_credits = stoi(psc);
					psc = strtok_s(NULL, ",", &context);
				}
			}

			else if (i == 8) //University Compulsory courses
			{
				while (psc != NULL)
				{
					R1.UnivCompulsory.push_back(psc);
					psc = strtok_s(NULL, ",", &context);
				}
			}
			else if (i == 9) //University Elective courses
			{
				while (psc != NULL)
				{
					R1.UnivElective.push_back(psc);
					psc = strtok_s(NULL, ",", &context);
				}
			}
			else if (i == 10) // Track compulsory courses
			{
				while (psc != NULL)
				{
					R1.TrackCompulsory.push_back(psc);
					psc = strtok_s(NULL, ",", &context);
				}
			}
			else if (i == 11) // Magor common compulsory courses
			{
				while (psc != NULL)
				{
					R1.MajorCompulsory.push_back(psc);
					psc = strtok_s(NULL, ",", &context);
				}
			}
			else if (i == 12) // Magor common elective courses
			{
				while (psc != NULL)
				{
					R1.MajorElective.push_back(psc);
					psc = strtok_s(NULL, ",", &context);
				}
			}
			else if (i == 13) // Concentrations courses
			{
				for (int i = 0; i < R1.NumOfConcent; i++)
				{
					//compulsory courses
					while (psc != NULL)
					{
						if (R1.ConcRequirements[i].comp_credits != 0)
							R1.ConcRequirements[i].CompulsoryCourses.push_back(psc);
						psc = strtok_s(NULL, ",", &context);
					}
					//elective courses 
					while (psc != NULL)
					{
						if (R1.ConcRequirements[i].elective_credits != 0)
							R1.ConcRequirements[i].ElectiveCourses.push_back(psc);
						psc = strtok_s(NULL, ",", &context);
					}
					R1.ConcRequirements[i].elective_credits = stoi(psc);
				}
			}

			psc = strtok_s(NULL, ",", &context);
			i++;
		}
	}
	return true;
}
bool Registrar::RulesReset(Rules& R)
{
	R.CourseCatalog.clear();
	R.OffringsList.clear();

	R.UnivCompulsory.clear();
	R.UnivElective.clear();
	R.TrackCompulsory.clear();
	R.MajorCompulsory.clear();
	R.MajorElective.clear();

	R.ConcRequirements.clear();

	R.TotalCredits = 0;
	R.UnivCompCredits = 0;
	R.UnivElectiveCredits = 0;
	R.CompTrackCredits = 0;
	R.MajCommonCompCredits = 0;
	R.MajCommonElecCredits = 0;
	R.NumOfConcent = 0;
	return true;
}
bool Registrar::ExecuteRules()
{
	pGUI = this->getGUI();
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
		for (int i = 0; i < major.length(); i++)
		{
			major[i] = toupper(major[i]);
		}
	}
	RulesReset(RegRules);

	ifstream input;
	if (major == "CIE")
	{
		RulesRead(input, "CIE-Requirements.txt", RegRules);
	}
	else if (major == "SPC")
		RulesRead(input, "SPC-Requirements.txt", RegRules);
	else if (major == "ENV")
		RulesRead(input, "ENV-Requirements.txt", RegRules);
	else if (major == "REE")
		RulesRead(input, "REE-Requirements.txt", RegRules);
	else if (major == "BMS")
		RulesRead(input, "Rules.txt", RegRules);
	else if (major == "PEU")
		RulesRead(input, "PEU-Requirements.txt", RegRules);
	else if (major == "NANENG")
		RulesRead(input, "NANENG-Requirements.txt", RegRules);
	else if (major == "NANSCIE")
		RulesRead(input, "Rules.txt", RegRules);
	else if (major == "MATSCIE")
		RulesRead(input, "Rules.txt", RegRules);

	input.close();

	ifstream catalogFile;
	catalogRead(catalogFile, "Source.txt", RegRules);
	catalogFile.close();
	
	return true;
}



Action* Registrar::CreateRequiredAction() 
{	
	//ActionAddRules(this).Execute(); // Why wrong 
	actData = pGUI->GetUserAction("Pick and action...");
	
	Action* RequiredAction = nullptr;
	//RequiredAction = new ActionAddRules(this);
	
	switch (actData.actType)
	{
	case ADD_CRS:	//add_course action
		RequiredAction = new ActionAddCourse(this);
		//RequiredAction = new ActionAddRules(this);
		break;
	case LOAD:	//add_course action
		RequiredAction = new ActionImportPlan(this);
		break;
	case SAVE:	//save study plan action
		RequiredAction = new ActionSavePlan(this);
		break;
	//TODO: Add case for each action
	case NOTES:	//add_course action
		RequiredAction = new ActionAddNotes(this);
		break;
	case DEL_CRS :	//Delete_course action
		RequiredAction = new ActionDeleteCourse(this);
		break;
	case REP_CRS:	//replace course action
		RequiredAction = new ActionChangeCourse(this);
		break;
	case DRAG:	//Drag and drop action
		RequiredAction = new Drag_DropAction(this, actData.x, actData.y);
		break;
	case FILTER:	//Filter action
		RequiredAction = new ActionFilter(this);
		break;
	case DONE:  //Check done
		RequiredAction = new ValidityCheck(this);
		break;
	case LINKS: // draw links between co and pre requisite
		RequiredAction = new ActionLinks(this);
		break;
	case EXIT: //exit
		RequiredAction = new ActionExit(this);
		break;
	case GPA: //GPA
		RequiredAction = new CalculateGPA(this);
		break;
	case LEVEL: //Student Level
		RequiredAction = new ActionStudentLevel(this);
		break;
	case STATUS: //Student status
		RequiredAction = new ActionUpdateStatus(this, actData.x, actData.y);
		break;
	case ADDMINOR: //Student status
		RequiredAction = new ActionAddMinor(this);
		break;
	case DOUBLECONCENT: //Student double concentration
		RequiredAction = new ActionDoubleConcenteration(this);
		break;
	case DOUBLEMAJOR: //Student Double concentration
		RequiredAction = new ActionDoubleMajor(this);
		break;
	case DRAW_AREA: //draw info of the course
		RequiredAction = new ActionInfo(this, actData.x, actData.y);
		break;
	}
	return RequiredAction;
}
bool Registrar::ExecuteDoubleMajor(GUI* pGUI)
{
	pGUI->PrintMsg("Enter major name: ");
	major2 = pGUI->GetSrting();

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
	}
	while (major2 == major)
	{
		pGUI->PrintMsg("It is the first major! Enter another major name: ");
		major2 = pGUI->GetSrting();
	}
	RulesReset(RegRules2);

	ifstream input;
	if (major2 == "CIE")
	{
		RulesRead(input, "CIE-Requirements.txt", RegRules2);
	}
	else if (major2 == "SPC")
		RulesRead(input, "SPC-Requirements.txt", RegRules2);
	else if (major2 == "ENV")
		RulesRead(input, "ENV-Requirements.txt", RegRules2);
	else if (major2 == "REE")
		RulesRead(input, "REE-Requirements.txt", RegRules2);
	else if (major2 == "BMS")
		RulesRead(input, "Rules.txt", RegRules2);
	else if (major2 == "PEU")
		RulesRead(input, "PEU-Requirements.txt", RegRules2);
	else if (major2 == "NANENG")
		RulesRead(input, "NANENG-Requirements.txt", RegRules2);
	else if (major2 == "NANSCIE")
		RulesRead(input, "Rules.txt", RegRules2);
	else if (major2 == "MATSCIE")
		RulesRead(input, "Rules.txt", RegRules2);

	input.close();

	ifstream catalogFile;
	catalogRead(catalogFile, "Source.txt", RegRules2);
	catalogFile.close();
	bool found = true;
	Course_Code code1 = " ";

	/////I commented it because it needs to be edited////
	/*for (int i = 0; i < RegRules.UnivCompulsory.size(); i++)
	{
	  for (int j = 0; j < RegRules2.UnivCompulsory.size(); j++)
	  {
		if (RegRules.UnivCompulsory[i] != RegRules2.UnivCompulsory[j])
		{
		  code1 = RegRules2.UnivCompulsory[j];
		  found = false;
		}
	  }
	}
	if (found == false)
	{
	  RegRulesDoubleMajor.UnivCompulsory.push_back(code1);
	  RegRulesDoubleMajor.UnivCompCredits += RegRules2.UnivCompCredits;
	}

	for (int i = 0; i < RegRules.UnivElective.size(); i++)
	{
	  for (int j = 0; j < RegRules2.UnivElective.size(); j++)
	  {
		if (RegRules.UnivElective[i] != RegRules2.UnivElective[j])
		{
		  RegRulesDoubleMajor.UnivElective.push_back(RegRules2.UnivElective[j]);
  }
	  }
	}
	for (int i = 0; i < RegRules.TrackCompulsory.size(); i++)
	{
	  for (int j = 0; j < RegRules2.TrackCompulsory.size(); j++)
	  {
		if (RegRules.TrackCompulsory[i] != RegRules2.TrackCompulsory[j])
		{
		  RegRulesDoubleMajor.TrackCompulsory.push_back(RegRules2.TrackCompulsory[j]);
		}
	  }
	}
	for (int i = 0; i < RegRules.MajorCompulsory.size(); i++)
	{
	  for (int j = 0; j < RegRules2.MajorCompulsory.size(); j++)
	  {
		if (RegRules.MajorCompulsory[i] != RegRules2.MajorCompulsory[j])
		{
		  RegRulesDoubleMajor.MajorCompulsory.push_back(RegRules2.MajorCompulsory[j]);
		}
	  }
	}
	for (int i = 0; i < RegRules.MajorElective.size(); i++)
	{
	  for (int j = 0; j < RegRules2.MajorElective.size(); j++)
	  {
		if (RegRules.MajorElective[i] != RegRules2.MajorElective[j])
		{
		  RegRulesDoubleMajor.MajorElective.push_back(RegRules2.MajorElective[j]);
		}
	  }
	}
	for (int i = 0; i < RegRules.ConcRequirements.size(); i++)
	{
	  for (int j = 0; j < RegRules2.ConcRequirements.size(); j++)
	  {
		bool found = false;
		for (int i = 0; i < RegRules2.UnivCompulsory.size(); i++)
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
			RegRulesDoubleMajor.UnivCompulsory.push_back(RegRules2.UnivCompulsory[i];);
			RegRulesDoubleMajor.UnivCompCredits += RegRules2.UnivCompCredits;
		  }
		  else
			break;
		}
		bool found = false;
		for (int i = 0; i < RegRules2.UnivCompulsory.size(); i++)
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
			RegRulesDoubleMajor.UnivCompulsory.push_back(RegRules2.UnivCompulsory[i];);
			RegRulesDoubleMajor.UnivCompCredits += RegRules2.UnivCompCredits;
		  }
		  else
			break;
		}
	  }
	}*/
	pGUI->PrintMsg("Now You can add the courses of double majors! Ok?..Enter Ok");
	string x = pGUI->GetSrting();
	return true;
}
bool Registrar::ExecuteDoubleConcentration(GUI* pGUI)
{
	if (RegRules.NumOfConcent == 0)
	{
		pGUI->PrintMsg("Your major don't have this option! ok?..Enter ok");
		string x = pGUI->GetSrting();
	}
	else
	{
		pGUI->PrintMsg("Add one course from this concentration! then, You can add the courses of double majors! Ok?..Enter Ok");
		string x = pGUI->GetSrting();
		RegRules.doubleConcentration = true;
	}
	//RegRules.doubleConcentration = false;
	return true;
}
Rules Registrar::getRules2() const
{
	return RegRules2;
}
Rules Registrar::getRulesDoubleMajor() const
{
	return RegRulesDoubleMajor;
}
//Rules Registrar::getRules()
//{
//	return RegRules;
//}


//Executes the action, Releases its memory, and return true if done, false if cancelled
bool Registrar::ExecuteAction(Action* pAct)
{
	bool done = pAct->Execute();
	PreCoCourse(RegRules);
	delete pAct;	//free memory of that action object (either action is exec or cancelled)
	return done;
}


void Registrar::Run()
{
	Registrar::ExecuteRules();
	Registrar::ExecuteOfferings();
		while (true)
		{
			//update interface here as CMU Lib doesn't refresh itself
			//when window is minimized then restored
			/*ActionAddRules(this).Execute();*/
			UpdateInterface();

			Action* pAct = CreateRequiredAction();
			if (pAct)	//if user doesn't cancel
			{
				if (ExecuteAction(pAct))	//if action is not cancelled
					UpdateInterface();
			}
		}
		//ActionAddRules(this).ExecuteRules();		//EXECUTERULES
}


void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	pGUI->DrawNotes();
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
	pSPlan->DrawLiveMessage(pGUI);
	pSPlan->SetPreCoIssue();
	if (actData.actType == DRAW_AREA)
	{
		pSPlan->DrawInfo(pGUI, actData.x, actData.y);
	}
	if (actData.actType == LINKS)
	{
		pSPlan->DrawConnectLine(pGUI);
	}
	if (actData.actType == GPA)
	{
		pGUI->DrawGPA();
	}
	if (actData.actType == LEVEL)
	{
		pGUI->DrawLevel();
	}
}


Registrar::~Registrar()
{
	delete pGUI;
}