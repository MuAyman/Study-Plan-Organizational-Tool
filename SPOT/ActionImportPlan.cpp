#include "ActionImportPlan.h"

ActionImportPlan::ActionImportPlan(Registrar* pReg) :Action(pReg)
{
}
bool ActionImportPlan::FileRead(ifstream& File, string name)
{
	File.open(name, ios::in);
	if (File.fail())
		return false;
	else
	{
		char* psc;
		char* context = nullptr;
		const int size = 300;
		char line[size];
		double x, y;
		SEMESTER sem;
		int semester_i;
		int year;
		int s = 0, ye = 0;
		Rules RegRules = pReg->getRules();
		Course_Code code;
		string Title;
		int crd;
		while (File.getline(line, size))
		{
			int i = 0;
			//For each line:
			//i = 1: Year
			//i = 2: Semester
			//i > 2: Course_Codes; This step includes Validation process + filling the right data for the course
			psc = strtok_s(line, ",", &context);
			i++;

			if (i == 1)
			{
				Years.push_back(psc);
				//cout << endl << Years[s] << endl;
				if (Years[ye] == "Year 1")
				{
					year = 1;
					ye++;
				}

				else if (Years[ye] == "Year 2")
				{
					year = 2;
					ye++;
				}

				else if (Years[ye] == "Year 3")
				{
					year = 3;
					ye++;
				}

				else if (Years[ye] == "Year 4")
				{
					year = 4;
					ye++;
				}

				else if (Years[ye] == "Year 5")
				{
					year = 5;
					ye++;
				}


				while (psc != NULL)
				{
					if (i > 2)
					{
						courses.push_back(psc);
						//filling the course with its data from the course catalouge
						for (auto it = (RegRules.CourseCatalog.begin()); it != (RegRules.CourseCatalog.end()); it++)
						{
							//cout << "PSC:  " << psc << "||" << "it: " << *it;

							if ((*it)->Code == psc)
							{
								code = (*it)->Code;
								Title = (*it)->Title;
								crd = (*it)->Credits;
								Course* CRS = new Course((*it)->Code, Title, crd);

								if (pReg->getStudyPlan()->CheckRepeatance(CRS) == true)

									//Check whether the course is already entered before or not 
								{

									CRS->setCoReqC((*it)->CoReqC);
									CRS->setPreReqC((*it)->PreReqC);
									CRS->setCoReq((*it)->CoReqList);
									CRS->setPreReq((*it)->PreReqList);
									pReg->checkType(CRS);

									//This  is to check the Validity of the offerings
									if (pReg->getStudyPlan()->AddCourse(CRS, year, sem) == true)
									{

										// This is a offering_time validation check for the course
										for (int i = 0; i < RegRules.OffringsList[0].Offerings[sem].size(); i++)
										{
											if (code == RegRules.OffringsList[0].Offerings[sem][i])
											{
												// set the course as valid
												CRS->SetOfferingsValid(true);
												// Setting course status as done (default value)
												pReg->getStudyPlan()->setStatus(5, FALL, code, Done);		
												break;
											}
											else
											{
												//set the course as in valid
												CRS->SetOfferingsValid(false);
											}

										}

									}
								}

							}
						}

					}
					psc = strtok_s(NULL, ",", &context);
					i++;
					if (i == 2)
					{
						Semester.push_back(psc);
						if (Semester[s] == "Fall")
						{
							sem = FALL;
							semester_i = 0;
							s++;
						}

						else if (Semester[s] == "Spring")
						{
							sem = SPRING;
							semester_i = 1;
							s++;
						}

						else if (Semester[s] == "Summer")
						{
							sem = SUMMER;
							semester_i = 2;
							s++;
						}
						else
							sem = FALL;


					}
				}
			}
		}
		return true;
	}
}

bool  ActionImportPlan::Execute()
{
	pReg->getStudyPlan()->DeleteImportPlan();
	ifstream input;
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("Enter File path(e.g. CIE.txt):");
	string name = pGUI->GetSrting();

	FileRead(input, name);
	input.close();
	return true;
}

ActionImportPlan::~ActionImportPlan()
{
}


