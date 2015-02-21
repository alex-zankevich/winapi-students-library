#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <deque>
#include <algorithm>
#include <iomanip>

#include <windows.h>
#include <tchar.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#define MAXSTR 80

#define ID_BUTTON_1 3000
#define ID_BUTTON_2 3001
#define ID_BUTTON_3 3002
#define ID_BUTTON_4 3003
#define ID_BUTTON_5 3004
#define ID_BUTTON_6 3005
#define ID_BUTTON_7 3006
#define ID_BUTTON_8 3007
#define ID_BUTTON_9 3008

#define ID_BUTTON_10 3009
#define ID_BUTTON_11 3010
#define ID_BUTTON_12 3011
#define ID_BUTTON_13 3012

#define ID_BUTTON_14 3013
#define ID_BUTTON_15 3014

#define ID_BUTTON_16 3015
#define ID_BUTTON_17 3016

#define ID_BUTTON_18 3017
#define ID_BUTTON_19 3018

#define ID_BUTTON_20 3019
#define ID_BUTTON_21 3020

#define ID_BUTTON_22 3021
#define ID_BUTTON_23 3022
#define ID_BUTTON_24 3023

#define ID_BUTTON_25 3024

#define ID_BUTTON_27 3026
#define ID_BUTTON_28 3027
#define ID_BUTTON_29 3028

#define EDIT_1 4000
#define EDIT_2 4001
#define EDIT_3 4002
#define EDIT_4 4003
#define EDIT_5 4004
#define EDIT_6 4005
#define EDIT_7 4006
#define EDIT_8 4007
#define EDIT_9 4008
#define EDIT_10 4009
#define EDIT_11 4010
#define EDIT_12 4011
#define EDIT_13 4012
#define EDIT_14 4013

#define ID_BUTTON_26 3025

static HWND hList,
hListMsg;

static HWND hButton[9],
hButSort[4],
hButFnd[2],
hButDel[2],
hButSave[2],
hButChg[7],
hButtonSave;

static HWND ApplyBut;

static HWND AddEdit,
CrtEdit,
ResEdit,
FndEdit[2],
DelEdit[2],
ChgEdit[7],
SaveEdit;

const double k = 3.0; //Количество предметов
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
class Student{
public:
	int Prog;
	int Matan;
	int GA;
	double Average;
	std::string SecondName;
	std::string FirstName;
	int ID;
	int Group;
	double GetAverage();
	//Constructors
	Student();
	Student(const std::string& SndName, const std::string& FstName, int group, int id, int p, int m, int g);
};

class StudentWork{
protected:
	//friend class WinView;
	Student stud;
	std::deque<Student> stList;
	std::deque<Student> bstList;
	std::deque<Student> wrList;
	char* path;
	//Добавление
	bool AddStudBegin(Student& st);
	void AddStudEnd(Student& st);
	void AddStudOnPos(Student& st, int);
	//Запись в список
	void MoveWholeFile(char* path);
	//Получение данных о студенте
	Student& GetStud(){
		return stud;
	}
	//Сортировка студентов
	void SortBySndName();
	void SortByID();
	void SortByGroup();
	void SortByAverage();
	//создание список отличников и отстающих
	void CreateBstList();
	void CreateWrsList();
	//Получение общего среднего балла
	double GetGenAver();
	//Удаление и поиск студента
	bool DeleteStudByName(std::string);
	bool DeleteStudByID(int id);
	Student& FindStudByName(std::string);
	Student& FindStudByID(int id);
public:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
};

Student StrToStud(char* str);
char* StudToStr(Student& st);
void List2List(std::deque<Student> List, HWND hlist);
char* ChgEditToStr();
void StrToChgEdit(char* buf);
bool SaveList(std::deque<Student> List, char* path);