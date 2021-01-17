#pragma once
#include <string>
#include <fstream>
using namespace std;

#include "..\DEFs.h"
#include "CMUgraphicsLib\CMUgraphics.h"

class Course;
class AcademicYear;
class StudyPlan;
//user interface class
class GUI
{

	enum MENU_ITEM //The items of the menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in the menu
		//If you want to change the menu items order, just change the order here
		ITM_ADD,		//Add a new course

		ITM_DELETE,

		ITM_REPLACE,

		ITM_ADD_NOTES,   //ADD NOTES

		ITM_OFFER,

		ITM_SAVE,

		ITM_LOAD,

		ITM_UNDO,

		ITM_REDO,
		//TODO: Add more items names here
		ITM_GPA,

		ITM_DMajor,

		ITM_DConcentration,

		ITM_EXIT,		//Exit item



		ITM_CNT			//no. of menu items ==> This should be the last line in this en   um
	};

	//Some constants for GUI
	static const int	WindWidth = 1300, WindHeight = 700,	//Window width and height
		wx = 15, wy = 15,		//Window starting coordinates
		StatusBarHeight = 50,	//Status Bar Height
		MenuBarHeight = 50,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
		MenuItemWidth = 50;		//Width of each item in the menu



	color DrawColor = BLACK;		//Drawing color
	color FillColor = BLACK;		//Filling color (for courses)
	color HiColor = RED;			//Highlighting color
	color ConnColor = GREEN;		//Connector color
	color MsgColor = BLACK;			//Messages color
	color BkGrndColor = BLACK;	//Background color
	color StatusBarColor = WHITE;//statusbar color
	string WindTitle = "Study-Plan Organizational Tool";

	window* pWind;

public:
	GUI();
	window* getWindow() const;
	void CreateMenu() const;
	void ClearDrawingArea() const;
	void ClearStatusBar() const;	//Clears the status bar

	//output functions
	void PrintMsg(string msg) const;		//prints a message on status bar

	//Drawing functions
	void DrawCourse(const Course*);
	void DrawAcademicYear(const AcademicYear*);
	void DrawYearBlock(int year);
	void UpdateInterface() const;
	void DrawCourseInfo(const Course* pCrs) const;
	void DrawNotes() const;
	void DrawLiveMessage(const Course*) const;
	
	//input functions
	ActionData GUI::GetUserAction(string msg = "") const;
	string GetSrting() const;




	~GUI();
};

