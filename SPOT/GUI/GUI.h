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

		ITM_DELETE,		//delete existig cours

		ITM_REPLACE,	//Repplace a course

		ITM_ADD_NOTES,   //ADD NOTES

		ITM_LINKS,		//draw links between courses

		ITM_SAVE,		//Save study plan

		ITM_LOAD,		//import plan

		ITM_DONE,		//Done to check the validity

		ITM_FILTER,		//display filter

		ITM_GPA,		//calculate GPA

		ITM_MINOR,		//Add Minor

		ITM_MAJOR,		//Double Major

		ITM_CONCENT,	//Double Concentration
		
		ITM_LEVEL,	//
		
		ITM_STATUS,	//


		//TODO: Add more items names here
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
	string  WindTitle = "Study-Plan Organizational Tool";
	window* pWind;
	window* pWind1;
	string newGPA;
	string level;
public:
	GUI();
	window* getWindow() const;
	void CreateMenu() const;
	void ClearDrawingArea() const;
	void ClearStatusBar() const;	//Clears the status bar

	//output functions
	void PrintMsg(string msg) const;		//prints a message on status bar

	//Drawing functions
	void UpdateInterface() const;
	void DrawCourse(const Course*);
	void DrawConnectLine(const Course* pCrs);
	void DrawAcademicYear(const AcademicYear*);
	void DrawYearBlock(int year);
	void DrawCourseInfo(const Course* pCrs) const;
	void DrawNotes() const;
	void DrawLiveMessage(string) const;
	void DisplayReport();
	void DrawGPA() const;
	void DrawLevel() const;
	//input functions
	ActionData GUI::GetUserAction(string msg = "") const;
	string GetSrting() const;
	////////helper function for GPA
	void setGPA(string GPA)
	{
		newGPA = GPA;
	}
	void setLevel(string level1)
	{
		level = level1;
	}
	~GUI();
};
