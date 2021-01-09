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

		Course_Code code;
		string Title;
		int crd;
		while (File.getline(line, size))
		{
			int i = 0;
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
							cout << "PSC:  " << psc << "||"<<endl;

							//filling the course with its data from the course catalouge
							for (auto it = (pReg->RegRules.CourseCatalog.begin()); it != (pReg->RegRules.CourseCatalog.end()); it++)
							{
								//cout << "PSC:  " << psc << "||" << "it: " << *it;
								if (it->Code == psc)
								{
									code = it->Code;
									Title = it->Title;
									crd = it->Credits;
									Course* CRS = new Course(it->Code, Title, crd);
									CRS->setCoReq(it->CoReqList);
									CRS->setPreReq(it->PreReqList);
									pReg->checkType(CRS); //new
									//pReg->getStudyPlay()->AddCourse(CRS, year, sem);
										//This  is to check the Validity of the offerings
									Rules pR = pReg->RegRules;

									if (pReg->getStudyPlay()->AddCourse(CRS, year, sem) == true)
									{

										// This is a offering_time validation check for the course
										for (int i = 0; i < pR.OffringsList[1].Offerings[sem].size(); i++)
										{
											if (code == pR.OffringsList[1].Offerings[sem][i])
											{
												// set the course as valid
												CRS->SetOfferingsValid(true);
												break;
											}
											else
											{
												//set the course as in valid
												CRS->SetOfferingsValid(false);
											}
										}
										
									}
									/*else
									{
										return false;
									}*/
									//break;
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
	pReg->getStudyPlay()->DeleteImportPlan();
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


