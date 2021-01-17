#include "GUI.h"
#include "../Courses/Course.h"
#include "../StudyPlan/AcademicYear.h"
#include <sstream>
#include <iostream>

GUI::GUI()
{
	pWind = new window(WindWidth, WindHeight, wx, wy);
	pWind->ChangeTitle(WindTitle);
	ClearDrawingArea();
	ClearStatusBar();
	CreateMenu();
}
window* GUI::getWindow() const
{
	return pWind;
}


//Clears the status bar
void GUI::ClearDrawingArea() const
{
	pWind->SetBrush(BkGrndColor);
	pWind->SetPen(BkGrndColor);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);

}

void GUI::ClearStatusBar() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);

}

void GUI::CreateMenu() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);

	//You can draw the menu icons any way you want.

	//First prepare List of images paths for menu item
	string MenuItemImages[ITM_CNT];
	MenuItemImages[ITM_ADD] = "GUI\\Images\\Menu\\add.jpg";
	MenuItemImages[ITM_ADD_NOTES] = "GUI\\Images\\Menu\\display.jpg";
	MenuItemImages[ITM_OFFER] = "GUI\\Images\\Menu\\offer.jpg";
	MenuItemImages[ITM_FILTER] = "GUI\\Images\\Menu\\redo.jpg";
	MenuItemImages[ITM_DONE] = "GUI\\Images\\Menu\\undo.jpg";
	MenuItemImages[ITM_DELETE] = "GUI\\Images\\Menu\\delete.jpg";
	MenuItemImages[ITM_REPLACE] = "GUI\\Images\\Menu\\replace.jpg";
	MenuItemImages[ITM_SAVE] = "GUI\\Images\\Menu\\save.jpg";
	MenuItemImages[ITM_LOAD] = "GUI\\Images\\Menu\\upload.jpg";
	MenuItemImages[ITM_EXIT] = "GUI\\Images\\Menu\\exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu items one image at a time
	for (int i = 0; i < ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);
}

////////////////////////    Output functions    ///////////////////

//Prints a message on the status bar
void GUI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
						// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, WindHeight - MsgY, msg);
}

//////////////////////////////////////////////////////////////////////////
void GUI::UpdateInterface() const
{

	pWind->SetBuffering(true);
	//Redraw everything
	CreateMenu();
	ClearStatusBar();
	ClearDrawingArea();
	pWind->UpdateBuffer();
	pWind->SetBuffering(false);

}

////////////////////////    Drawing functions    ///////////////////
void GUI::DrawCourse(const Course* pCrs)
{
	
	if (pCrs->isSelected())
	{
		pWind->SetPen(HiColor, 2);
	}
	else
	{
		pWind->SetPen(BLACK, 2);
		if (pCrs->getType() == "UnivCompulsory" || pCrs->getType() == "UnivElective")
		{
			pWind->SetPen(PINK, 2);
		}
		else if (pCrs->getType() == "TrackCompulsory" || pCrs->getType() == "TrackElective")
		{
			pWind->SetPen(BLUE, 2);
		}
		else if (pCrs->getType() == "MajorCompulsory" || pCrs->getType() == "MajorElective")
		{
			pWind->SetPen(PURPLE, 2);
		}
		else if (pCrs->getType() == "Concentration")
		{
			pWind->SetPen(SKYBLUE, 2);
		}
		else if (pCrs->getType() == "Minor")
		{
			pWind->SetPen(LIGHTCYAN, 2);
		}
		else if (pCrs->getType() == "Extra")
		{
			pWind->SetPen(DARKGOLDENROD, 2);
		}
		
	}
	pWind->SetBrush(DARKGREEN);
	if (pCrs->IsOfferingsValid() == false)
	{
		pWind->SetBrush(YELLOW);
	}
	if (pCrs ->IsPreValid() == false || pCrs->IsCoValid() == false)
	{
		pWind->SetBrush(RED);
	}
	
	graphicsInfo gInfo = pCrs->getGfxInfo();
	
	if (pCrs->getType() == "UnivElective" || pCrs->getType() == "TrackElective" || pCrs->getType() == "MajorElective")
	{
		pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT, FILLED, 7, 7);
	}
	else
	{
		pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
	}
	
	pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);
	
	//Write the course code and credit hours.
	int Code_x = gInfo.x + CRS_WIDTH * 0.15;
	int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
	pWind->SetFont(CRS_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(WHITE);
	if (pCrs->IsOfferingsValid() == false)
	{
		pWind->SetPen(BLACK);
	}
	ostringstream crd;
	crd << "crd:" << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT / 2, crd.str());


}


void GUI::DrawAcademicYear(const AcademicYear* pY)
{
	graphicsInfo gInfo = pY->getGfxInfo();
	// Drawing a rectangle for the year
	int YearRectWidth = 120;

	// Drawing the semesters in each year
	pWind->SetBrush(WHITE);
	pWind->SetPen(WHITE);
	pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + PLAN_YEAR_WIDTH, (SEM_CNT * PLAN_SEMESTER_HEIGHT) + gInfo.y);
	pWind->SetBrush(GOLD);
	pWind->SetPen(GOLD);
	pWind->DrawRectangle(gInfo.x - 180, gInfo.y, YearRectWidth, (SEM_CNT * PLAN_SEMESTER_HEIGHT) + gInfo.y);
	//////////////////
	for (int sem = 0; sem < SEM_CNT; sem++)
	{
		string semester;
		pWind->SetBrush(WHITE);
		pWind->SetPen(DARKGREEN, 2);
		pWind->DrawRectangle(gInfo.x, gInfo.y + (((SEM_CNT * PLAN_SEMESTER_HEIGHT) / SEM_CNT) * sem), gInfo.x + PLAN_YEAR_WIDTH, gInfo.y + ((SEM_CNT * PLAN_SEMESTER_HEIGHT) / SEM_CNT) * (sem + 1));
		pWind->SetBrush(ORANGE);
		pWind->SetPen(BLACK, 2);
		pWind->DrawRectangle(gInfo.x - 40, gInfo.y + (((SEM_CNT * PLAN_SEMESTER_HEIGHT) / SEM_CNT) * sem), gInfo.x + SemRectWidth, gInfo.y + ((SEM_CNT * PLAN_SEMESTER_HEIGHT) / SEM_CNT) * (sem + 1));
		//Draw string on semester
		if (sem == 2)
			semester = "FALL";
		else if (sem == 1)
			semester = "SPRING";
		else if (sem == 0)
			semester = "SUMMER";
		pWind->SetFont(PLAN_SEMESTER_HEIGHT * 0.5, BOLD, BY_NAME, "Gramound");
		pWind->SetPen(BLACK);
		pWind->DrawString((gInfo.x - 40 + 7), (gInfo.y + (7 + ((SEM_CNT * PLAN_SEMESTER_HEIGHT) / SEM_CNT) * sem)), semester);
	}
}


void GUI::DrawYearBlock(int year)
{
	int ix = 200;
	int iy = 520 - ((SEM_CNT * PLAN_SEMESTER_HEIGHT) + 10) * year;
	ostringstream Year;
	Year << "Year:" << year + 1;
	pWind->SetFont(CRS_HEIGHT * 0.9, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK);
	pWind->DrawString(ix - 165, iy - 15 + (PLAN_SEMESTER_HEIGHT * 3) / 2, Year.str());
}

////////////////////////    Input functions    ///////////////////
//This function reads the position where the user clicks to determine the desired action
//If action is done by mouse, actData will be the filled by mouse position
ActionData GUI::GetUserAction(string msg) const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;
	const button butt = RIGHT_BUTTON;
	buttonstate buttstate;
	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();

	PrintMsg(msg);

	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);
		buttstate = pWind->GetButtonState(butt, x, y);
		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}


		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				case ITM_ADD: return ActionData{ ADD_CRS };	//Add course
				case ITM_DELETE: return ActionData{ DEL_CRS };	//delete course
				case ITM_REPLACE: return ActionData{ REP_CRS }; //Replace course
				case ITM_SAVE: return ActionData{ SAVE };	//Save the data to a file
				case ITM_LOAD: return ActionData{ LOAD };	//Load the data from a file
				case ITM_DONE: return ActionData{ DONE };	//DONE Check
				case ITM_FILTER: return ActionData{ FILTER };	//Redo
				case ITM_EXIT: return ActionData{ EXIT };		//Exit
				case ITM_ADD_NOTES: return ActionData{ NOTES };		//Notes
				case ITM_OFFER: return ActionData{ OFFER };		//Notes


				default: return ActionData{ MENU_BAR };	//A click on empty place in menu bar
				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}

			//[3] User clicks on the status bar
			return ActionData{ STATUS_BAR };
		}

		if (buttstate == BUTTON_DOWN)
		{
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAG,x,y };	//user want clicks inside drawing area
			}
		}
		if (ctInput == RIGHT_CLICK)
		{
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DROP,x,y };	//user want clicks inside drawing area
			}
		}


	}//end while

}
string GUI::GetSrting() const
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar



	string userInput;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);

		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input

		case 13:		//ENTER key is pressed
			return userInput;

		case 8:		//BackSpace is pressed
			if (userInput.size() > 0)
				userInput.resize(userInput.size() - 1);
			break;

		default:
			userInput += Key;
		};

		PrintMsg(userInput);
	}

}

void GUI::DrawCourseInfo(const Course* pCrs) const  /////Me
{
	//Draw a rectangle for the info
	pWind->SetBrush(DARKGREEN);
	pWind->SetPen(YELLOW);
	int ix = WindWidth - 360;
	int iy = 86;
	pWind->DrawRectangle(ix, iy, ix + INFO_WIDTH, iy + INFO_HEIGHT);/*200 should be changed according to the gInfo that should be specified */
	
	int NumData = 3;
	for (int i = 1; i < 3; i++)
	{
		pWind->DrawLine(ix, iy + INFO_HEIGHT * i / 3, ix + INFO_WIDTH, iy + INFO_HEIGHT * i / 3);
	}
	///Write the course code and credit hours.
	int Info_x = ix + INFO_WIDTH * 0.07;
	int Info_y = iy + INFO_HEIGHT * 0.1;
	pWind->SetFont(INFO_HEIGHT * 0.15, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(WHITE);

	ostringstream Title;
	ostringstream Code;
	ostringstream Credits;
	Code << "Cource Code:" << pCrs->getCode();
	pWind->DrawString(Info_x, Info_y, Code.str());
	Credits << "Cource Credits:" << pCrs->getCredits();
	pWind->DrawString(Info_x, Info_y + INFO_HEIGHT / 3, Credits.str());
	Title << "Cource Title:" << pCrs->getTitle();
	pWind->DrawString(Info_x, Info_y + INFO_HEIGHT * 2 / 3, Title.str());
}

void GUI::DrawNotes() const
{
	char* note;
	// display notes
	fstream Notes;
	Notes.open("Notes.txt", ios::in);

	//Draw a rectangle for the Notes
	pWind->SetBrush(DARKGREEN);
	pWind->SetPen(YELLOW);
	int ix = WindWidth - 360;
	int iy = 116 + 3 * SEM_CNT * PLAN_SEMESTER_HEIGHT;
	pWind->DrawRectangle(ix, iy, ix + INFO_WIDTH, iy + INFO_HEIGHT);
	

	char* context = nullptr;
	const int size = 300;
	char line[size];
	int Info_x = ix + 15;
	int Info_y = iy + 5;
	while (Notes.getline(line, size))
	{
		pWind->SetFont(INFO_HEIGHT * 0.1, BOLD, BY_NAME, "Gramound");
		pWind->SetPen(WHITE);
		note = strtok_s(line, "", &context);
		///Write the Notes

		pWind->DrawString(Info_x, Info_y, note);
		pWind->SetPen(YELLOW);
		for (int i = 1; i < 7; i++)
		{
			pWind->DrawLine(ix, iy + INFO_HEIGHT * i / 7, ix + INFO_WIDTH, iy + INFO_HEIGHT * i / 7);
		}
		Info_y = Info_y + 29;
	}
	Notes.close();
	
}

void GUI::DrawLiveMessage(const Course* pC) const
{
	int ix = WindWidth - 360;
	int Info_x = ix + INFO_WIDTH * 0.07;
	int Info_y = 330 ;
	pWind->SetFont(INFO_HEIGHT * 0.2, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(WHITE);
	pWind->SetBrush(GREY);
	pWind->DrawRectangle(ix, 302, ix + INFO_WIDTH, 300 + SEM_CNT * PLAN_SEMESTER_HEIGHT);
	if (pC->ModerateIssue() == true)
	{
		pWind->SetBrush(RED);
		pWind->DrawRectangle(ix + 5, 302, ix + INFO_WIDTH - 5 , (300 + SEM_CNT * PLAN_SEMESTER_HEIGHT));
		pWind->DrawString(Info_x, Info_y, "Moderate Issue");
	}
	if (pC -> CriticalIssue() == true)
	{
		pWind->SetBrush(YELLOW);
		pWind->DrawRectangle(ix + 5, (300 + SEM_CNT * PLAN_SEMESTER_HEIGHT) / 2, ix + INFO_WIDTH - 5 , 300 + SEM_CNT * PLAN_SEMESTER_HEIGHT);
		pWind->DrawString(Info_x, Info_y + (300 + SEM_CNT * PLAN_SEMESTER_HEIGHT) / 2, "Critical Issue");
	}

}
void GUI::DisplayReport() const
{
	int WindW = 700;
	int WindH = 700;
	window*pWind1 = new window(WindW, WindH, wx, wy);
	pWind1->ChangeTitle("Warnings Report");
	pWind1->SetBrush(BkGrndColor);
	pWind1->SetPen(BkGrndColor);
	pWind1->DrawRectangle(0, 0, WindW, WindH);
	char* Warning;
	// display Report
	fstream Warnings;
	Warnings.open("WarningReport.txt", ios::in);
	pWind1->SetPen(YELLOW);
	char* context = nullptr;
	const int size = 800;
	char line[size];
	int Info_x =  15;
	int Info_y =  5;
	while (Warnings.getline(line, size))
	{
		pWind1->SetFont(INFO_HEIGHT * 0.1, BOLD, BY_NAME, "Gramound");
		pWind1->SetPen(WHITE);
		Warning = strtok_s(line, "", &context);
		///Write the warning on the screen

		pWind1->DrawString(Info_x, Info_y, Warning);
		pWind1->SetPen(YELLOW);
		for (int i = 1; i < 20; i++)
		{
			pWind1->DrawLine(0,  WindH * i / 20,  WindW, WindH * i / 20);
		}
		Info_y = Info_y + 36;
	}
	Warnings.close();
	Warnings.clear();
	//delete pWind1;
}
GUI::~GUI()
{
	delete pWind;
	
}
