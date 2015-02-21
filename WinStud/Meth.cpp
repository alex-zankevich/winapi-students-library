#include "StudHead.h"


struct Error{
	std::string err;
	Error(const std::string& str) :err(str){}
};

Student::Student(){
	FirstName = '\0';
	SecondName = '\0';
	Average = Prog = Matan = GA = 0;
}

Student::Student(const std::string& SndName, const std::string& FstName, int group, int id, int p, int m, int g) :SecondName(SndName), FirstName(FstName){
	Group = group;
	ID = id;
	Prog = p;
	Matan = m;
	GA = g;
	Average = (Prog + Matan + GA) / k;
}

double Student::GetAverage(){
	Average = (Prog + Matan + GA) / k;
	return Average;
}

Student StrToStud(char* str){
	int  tmp;
	char* tmptok = new char[MAXSTR];
	Student* stud = new Student;
	tmptok = strtok(str, " ");
	if (tmptok == 0)
		throw Error("Student data is not correct !");
	stud->SecondName = strtok(str, " ");

	tmptok = strtok(0, " ");
	if (tmptok == 0)
		throw Error("Student data is not correct !");
	stud->FirstName = tmptok;

	tmptok = strtok(0, " ");
	if ((tmp = atoi(tmptok)) == 0 || tmptok == 0)
		throw Error("Student data is not correct !");
	stud->Group = tmp;
	tmptok = strtok(0, " ");
	if ((tmp = atoi(tmptok)) == 0 || tmptok == 0)
		throw Error("Student data is not correct !");
	stud->ID = tmp;
	tmptok = strtok(0, " ");
	if ((tmp = atoi(tmptok)) == 0 || tmptok == 0)
		throw Error("Student data is not correct !");
	stud->Prog = tmp;
	tmptok = strtok(0, " ");
	if ((tmp = atoi(tmptok)) == 0 || tmptok == 0)
		throw Error("Student data is not correct !");
	stud->Matan = tmp;
	tmptok = strtok(0, " ");
	if ((tmp = atoi(tmptok)) == 0 || tmptok == 0)
		throw Error("Student data is not correct !");
	stud->GA = tmp;

	stud->GetAverage();
	return *stud;
}

char* StudToStr(Student& st){

	char* buffer = new char[MAXSTR];;

	char* stud = new char[MAXSTR];
	stud[0] = '\0';
	strcat(stud, st.SecondName.c_str());
	strcat(stud, "  ");
	strcat(stud, st.FirstName.c_str());
	strcat(stud, "  ");
	strcat(stud, itoa(st.Group, buffer, 10));
	strcat(stud, "  ");
	strcat(stud, itoa(st.ID, buffer, 10));
	strcat(stud, "  ");
	strcat(stud, itoa(st.Prog, buffer, 10));
	strcat(stud, "  ");
	strcat(stud, itoa(st.Matan, buffer, 10));
	strcat(stud, "  ");
	strcat(stud, itoa(st.GA, buffer, 10));
	delete[] buffer;
	return stud;
}

void List2List(std::deque<Student> List, HWND hlist){
	SendMessage(hList, LB_RESETCONTENT, 0, 0);
	char* stud = new char[MAXSTR];
	for (std::deque<Student>::iterator iter = List.begin(); iter != List.end(); iter++){
		SendMessage(hlist, LB_ADDSTRING, 0, (LPARAM)StudToStr(*iter));
	}
}



void StudentWork::MoveWholeFile(char* path){
	std::ifstream fin(path);
	if (!fin.is_open())
		throw Error("File is not open!");
	while (!fin.eof()){
		fin >> stud.SecondName >> stud.FirstName >> stud.Group >> stud.ID >> stud.Prog >> stud.Matan >> stud.GA;
		stud.GetAverage();
		AddStudBegin(stud);
	}
}

bool StudentWork::AddStudBegin(Student& st){
	for (std::deque<Student>::iterator iter = stList.begin(); iter != stList.end(); iter++){
		if (st.ID == iter->ID)
			return false;
	}
	stList.push_front(st);
	return true;
}

bool cmpSndName(Student& st1, Student& st2){
	return st1.SecondName < st2.SecondName ? true : false;
}

bool cmpID(Student& st1, Student& st2){
	return st1.ID < st2.ID ? true : false;
}

bool cmpGroup(Student& st1, Student& st2){
	return st1.Group < st2.Group ? true : false;
}

bool cmpAverage(Student& st1, Student& st2){
	return st1.Average > st2.Average ? true : false;
}

void StudentWork::SortBySndName(){
	std::sort(stList.begin(), stList.end(), cmpSndName);
}

void StudentWork::SortByID(){
	std::sort(stList.begin(), stList.end(), cmpID);
}

void StudentWork::SortByGroup(){
	std::sort(stList.begin(), stList.end(), cmpGroup);
}

void StudentWork::SortByAverage(){
	std::sort(stList.begin(), stList.end(), cmpAverage);
}

void HideItem(HWND* hitem, int n){
	for (int i = 0; i < n; i++)
		ShowWindow(hitem[i], SW_HIDE);
}

void HideAll(){
	HideItem(hButSort, 4);
	HideItem(hButFnd, 2);
	HideItem(hButDel, 2);
	HideItem(FndEdit, 2);
	HideItem(DelEdit, 2);
	HideItem(ChgEdit, 7);
	HideItem(hButChg, 7);
	HideItem(hButSave, 2);
	ShowWindow(ApplyBut, SW_HIDE);
	ShowWindow(SaveEdit, SW_HIDE);
}

void MsgList(const char* msg){
	SendMessage(hListMsg, LB_INSERTSTRING, 0, (LPARAM)msg);
}

void ShowButSort(HWND hwnd){
	hButSort[0] = CreateWindow("BUTTON", "По имени", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 170, 85, 140, 20, hwnd, (HMENU)ID_BUTTON_10, GetModuleHandle(NULL), NULL);
	hButSort[1] = CreateWindow("BUTTON", "По группе", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 170, 110, 140, 20, hwnd, (HMENU)ID_BUTTON_11, GetModuleHandle(NULL), NULL);
	hButSort[2] = CreateWindow("BUTTON", "По номеру зачетки", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 170, 135, 140, 20, hwnd, (HMENU)ID_BUTTON_12, GetModuleHandle(NULL), NULL);
	hButSort[3] = CreateWindow("BUTTON", "По среднему баллу", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 170, 160, 140, 20, hwnd, (HMENU)ID_BUTTON_13, GetModuleHandle(NULL), NULL);
}

void ShowButFnd(HWND hwnd){
	hButFnd[0] = CreateWindow("BUTTON", "По фамилии", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 170, 150, 140, 20, hwnd, (HMENU)ID_BUTTON_14, GetModuleHandle(NULL), NULL);
	hButFnd[1] = CreateWindow("BUTTON", "По номеру зачетки", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 170, 190, 140, 20, hwnd, (HMENU)ID_BUTTON_15, GetModuleHandle(NULL), NULL);
	FndEdit[0] = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 171, 170, 139, 20, hwnd, (HMENU)EDIT_3, GetModuleHandle(NULL), NULL);
	FndEdit[1] = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 171, 210, 139, 20, hwnd, (HMENU)EDIT_4, GetModuleHandle(NULL), NULL);
}

void ShowButDel(HWND hwnd){
	hButDel[0] = CreateWindow("BUTTON", "По фамилии", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 170, 200, 140, 20, hwnd, (HMENU)ID_BUTTON_16, GetModuleHandle(NULL), NULL);
	hButDel[1] = CreateWindow("BUTTON", "По номеру зачетки", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 170, 240, 140, 20, hwnd, (HMENU)ID_BUTTON_17, GetModuleHandle(NULL), NULL);
	DelEdit[0] = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 171, 220, 139, 20, hwnd, (HMENU)EDIT_5, GetModuleHandle(NULL), NULL);
	DelEdit[1] = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 171, 260, 139, 20, hwnd, (HMENU)EDIT_6, GetModuleHandle(NULL), NULL);
}

void ShowButChg(HWND hwnd){
	ApplyBut = CreateWindow("BUTTON", "Применить", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 200, 160, 140, 20, hwnd, (HMENU)ID_BUTTON_25, GetModuleHandle(NULL), NULL);

	ChgEdit[0] = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 250, 190, 140, 20, hwnd, (HMENU)EDIT_7, GetModuleHandle(NULL), NULL);
	ChgEdit[1] = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 250, 220, 140, 20, hwnd, (HMENU)EDIT_8, GetModuleHandle(NULL), NULL);
	ChgEdit[2] = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 250, 250, 140, 20, hwnd, (HMENU)EDIT_9, GetModuleHandle(NULL), NULL);
	ChgEdit[3] = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 250, 280, 140, 20, hwnd, (HMENU)EDIT_10, GetModuleHandle(NULL), NULL);
	ChgEdit[4] = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 250, 310, 140, 20, hwnd, (HMENU)EDIT_11, GetModuleHandle(NULL), NULL);
	ChgEdit[5] = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 250, 340, 140, 20, hwnd, (HMENU)EDIT_12, GetModuleHandle(NULL), NULL);
	ChgEdit[6] = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 250, 370, 140, 20, hwnd, (HMENU)EDIT_13, GetModuleHandle(NULL), NULL);

	hButChg[0] = CreateWindow("BUTTON", "Фамилия", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 160, 190, 90, 20, hwnd, (HMENU)ID_BUTTON_18, GetModuleHandle(NULL), NULL);
	hButChg[1] = CreateWindow("BUTTON", "Имя", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 160, 220, 90, 20, hwnd, (HMENU)ID_BUTTON_18, GetModuleHandle(NULL), NULL);
	hButChg[2] = CreateWindow("BUTTON", "№ группы", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 160, 250, 90, 20, hwnd, (HMENU)ID_BUTTON_18, GetModuleHandle(NULL), NULL);
	hButChg[3] = CreateWindow("BUTTON", "№ зачетки", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 160, 280, 90, 20, hwnd, (HMENU)ID_BUTTON_18, GetModuleHandle(NULL), NULL);
	hButChg[4] = CreateWindow("BUTTON", "Прог.", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 160, 310, 90, 20, hwnd, (HMENU)ID_BUTTON_18, GetModuleHandle(NULL), NULL);
	hButChg[5] = CreateWindow("BUTTON", "Мат.Ан.", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 160, 340, 90, 20, hwnd, (HMENU)ID_BUTTON_18, GetModuleHandle(NULL), NULL);
	hButChg[6] = CreateWindow("BUTTON", "Г.А.", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 160, 370, 90, 20, hwnd, (HMENU)ID_BUTTON_18, GetModuleHandle(NULL), NULL);
}

Student& StudentWork::FindStudByName(std::string name){
	if (stList.empty())
		throw Error("List is emty!");
	for (auto iter = stList.begin(); iter != stList.end(); iter++){
		if (iter->SecondName == name || iter->FirstName == name)
			return *iter;
	}
	throw Error("There is no such student!");
}

Student& StudentWork::FindStudByID(int id){
	if (stList.empty())
		throw Error("List is emty!");
	for (auto iter = stList.begin(); iter != stList.end(); iter++){
		if (iter->ID == id)
			return *iter;
	}
	throw Error("There is no such student!");
}

bool StudentWork::DeleteStudByName(std::string name){
	if (stList.empty())
		throw Error("List is emty !");
	for (auto iter = stList.begin(); iter != stList.end(); iter++){
		if (iter->SecondName == name || iter->FirstName == name){
			stList.erase(iter);
			return true;
		}
	}
	return false;
}

bool StudentWork::DeleteStudByID(int id){
	if (stList.empty())
		throw Error("List is emty !");
	for (auto iter = stList.begin(); iter != stList.end(); iter++){
		if (iter->ID == id){
			stList.erase(iter);
			return true;
		}
	}
	return false;
}

void StrToChgEdit(char* buf){
	int i = 0;
	char * tmp = new char[MAXSTR];
	tmp = strtok(buf, " ");
	while (tmp){
		SetWindowText(ChgEdit[i], tmp);
		tmp = strtok(0, " ");
		i++;
	}
}

char* ChgEditToStr(){
	char* stud = new char[MAXSTR];

	char* buf = new char[MAXSTR];
	stud[0] = '\0';
	for (int i = 0; i < 7; i++){
		GetWindowText(ChgEdit[i], buf, GetWindowTextLength(ChgEdit[i]) + 1);
		if (i > 1 && atoi(buf) == 0)
			throw Error("Entered data are incorrect !");
		strcat(stud, buf);
		strcat(stud, " ");
		buf[0] = '\0';
	}
	stud[strlen(stud) - 1] = '\0';
	delete[] buf;
	return stud;
}
bool SaveList(std::deque<Student> List, char* path){
	std::ofstream fout(path);
	if (!fout.is_open())
		throw Error("Saving was failed !");
	for (std::deque<Student>::iterator iter = List.begin(); iter != List.end(); iter++){
		fout << iter->SecondName << " " << iter->FirstName << " " << iter->Group << " " << iter->ID << " " << iter->Prog << " " << iter->Matan << " " << iter->GA << std::endl;
	}

}
bool SaveListAs(std::deque<Student> List, char* path){
	std::ofstream fout(path);
	if (!fout.is_open())
		throw Error("Saving was failed !");
	fout << "____________________________________________________________________\n";
	fout << std::setw(10) << std::left << "Фамилия" << std::setw(10) << "Имя" << std::setw(8) << "Группа" << std::setw(12) << "№ зачетки" << std::setw(6) << "Прог." << std::setw(7) << "Матан." << std::setw(5) << "ГА" << std::setw(7) << "Средний" << std::endl;
	fout << "____________________________________________________________________\n";
	for (std::deque<Student>::iterator iter = List.begin(); iter != List.end(); iter++){
		fout << std::setw(10) << std::left << iter->SecondName << std::setw(10) << iter->FirstName << std::setw(8) << iter->Group << std::setw(12) << iter->ID << std::setw(6) << iter->Prog << std::setw(7) << iter->Matan << std::setw(5) << iter->GA << std::setw(7) << std::setprecision(2) << iter->Average << std::endl;
	}
	fout << "____________________________________________________________________\n";
}

LRESULT CALLBACK  StudentWork::WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	static PAINTSTRUCT ps;
	static RECT rect;

	static StudentWork stw;
	static char* path = new char[MAXSTR];
	static char* pathSave = new char[MAXSTR];
	static char* buf = new char[MAXSTR];
	static char* ChgStud = new char[MAXSTR];
	static Student cChgStud;

	static int exit;

	switch (iMsg)
	{
	case WM_CREATE:

		hButton[0] = CreateWindow("BUTTON", "Создать", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 10, 20, 140, 30, hwnd, (HMENU)ID_BUTTON_1, GetModuleHandle(NULL), NULL);
		hButton[1] = CreateWindow("BUTTON", "Добавить", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 10, 70, 140, 30, hwnd, (HMENU)ID_BUTTON_2, GetModuleHandle(NULL), NULL);
		hButton[2] = CreateWindow("BUTTON", "Отсортировать", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 10, 120, 140, 30, hwnd, (HMENU)ID_BUTTON_3, GetModuleHandle(NULL), NULL);
		hButton[3] = CreateWindow("BUTTON", "Найти", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 10, 170, 140, 30, hwnd, (HMENU)ID_BUTTON_4, GetModuleHandle(NULL), NULL);
		hButton[4] = CreateWindow("BUTTON", "Удалить", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 10, 220, 140, 30, hwnd, (HMENU)ID_BUTTON_5, GetModuleHandle(NULL), NULL);
		hButton[5] = CreateWindow("BUTTON", "Изменить", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 10, 270, 140, 30, hwnd, (HMENU)ID_BUTTON_6, GetModuleHandle(NULL), NULL);
		hButton[6] = CreateWindow("BUTTON", "Выйти", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 10, 370, 140, 30, hwnd, (HMENU)ID_BUTTON_7, GetModuleHandle(NULL), NULL);
		hButtonSave = CreateWindow("BUTTON", "Сохранить", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 10, 320, 140, 30, hwnd, (HMENU)ID_BUTTON_26, GetModuleHandle(NULL), NULL);

		EnableWindow(hButton[5], FALSE);

		hList = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER, 420, 20, 350, 440, hwnd, NULL, GetModuleHandle(NULL), NULL);
		ResEdit = CrtEdit = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | ES_READONLY, 160, 20, 240, 20, hwnd, (HMENU)EDIT_3, GetModuleHandle(NULL), NULL);
		hListMsg = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER, 150, 400, 250, 60, hwnd, NULL, GetModuleHandle(NULL), NULL);

		CrtEdit = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 11, 50, 139, 20, hwnd, (HMENU)EDIT_1, GetModuleHandle(NULL), NULL);
		AddEdit = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 11, 100, 139, 20, hwnd, (HMENU)EDIT_2, GetModuleHandle(NULL), NULL);

		return 0;

	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{
			switch (wParam){
			case ID_BUTTON_1:
				HideAll();
				try{
					GetWindowText(CrtEdit, path, GetWindowTextLength(CrtEdit) + 1);
					if (path[0] == '\0'){
						MsgList("There is no path entered !");
						MessageBox(hwnd, "There is no path entered !", "Error", MB_OK | MB_ICONEXCLAMATION);
						return 0;
					}
					stw.MoveWholeFile(path);
					List2List(stw.stList, hList);
					UpdateWindow(hList);
				}
				catch (Error& error){
					MsgList("Path is not correct !");
					MessageBox(hwnd, error.err.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);
					return 0;
				}
				MsgList("List has been successfully created !");
				EnableWindow(hButton[0], FALSE);
				return 0;
			case ID_BUTTON_2:
				HideAll();
				try{
					GetWindowText(AddEdit, buf, GetWindowTextLength(AddEdit) + 1);
					if (buf[0] == '\0'){
						MsgList("There is nothing entered !");
						MessageBox(hwnd, "There is nothing entered !", "Error", MB_OK | MB_ICONEXCLAMATION);
						return 0;
					}
					if (stw.AddStudBegin(StrToStud(buf)) == 0){
						MsgList("Student with this ID is already in the list !");
						MessageBox(hwnd, "Student with this ID is already in the list !", "Error", MB_OK | MB_ICONEXCLAMATION);
						return 0;
					}
					List2List(stw.stList, hList);
					UpdateWindow(hList);
				}
				catch (Error& error){
					MsgList(error.err.c_str());
					MessageBox(hwnd, error.err.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);
				}
				MsgList("Student has been successfully added!");
				return 0;
			case ID_BUTTON_3:
				HideAll();
				ShowButSort(hwnd);
				UpdateWindow(hwnd);
				return 0;
			case ID_BUTTON_4:
				HideAll();
				ShowButFnd(hwnd);
				UpdateWindow(hwnd);
				return 0;
			case ID_BUTTON_5:
				HideAll();
				ShowButDel(hwnd);
				UpdateWindow(hwnd);
				return 0;
			case ID_BUTTON_10:
				stw.SortBySndName();
				List2List(stw.stList, hList);
				MsgList("List has been sorted !");
				return 0;
			case ID_BUTTON_11:
				stw.SortByGroup();
				List2List(stw.stList, hList);
				MsgList("List has been sorted !");
				return 0;
			case ID_BUTTON_12:
				stw.SortByID();
				List2List(stw.stList, hList);
				MsgList("List has been sorted !");
				return 0;
			case ID_BUTTON_13:
				stw.SortByAverage();
				List2List(stw.stList, hList);
				MsgList("List has been sorted !");
				return 0;
			case ID_BUTTON_14:
				try{
					GetWindowText(FndEdit[0], buf, GetWindowTextLength(FndEdit[0]) + 1);
					if (buf[0] == '\0'){
						MsgList("There is nothing entered !");
						MessageBox(hwnd, "There is nothing entered !", "Error", MB_OK | MB_ICONEXCLAMATION);
						return 0;
					}
					SetWindowText(ResEdit, StudToStr(stw.FindStudByName(buf)));
					UpdateWindow(hList);
				}
				catch (Error& error){
					MsgList(error.err.c_str());
					MessageBox(hwnd, error.err.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);
					return 0;
				}
				MsgList("Student has been found !");
				EnableWindow(hButton[5], TRUE);
				return 0;
			case ID_BUTTON_15:
				try{
					GetWindowText(FndEdit[1], buf, GetWindowTextLength(FndEdit[1]) + 1);
					if (buf[0] == '\0'){
						MsgList("There is nothing entered !");
						MessageBox(hwnd, "There is nothing entered !", "Error", MB_OK | MB_ICONEXCLAMATION);
						return 0;
					}
					if (atoi(buf) == NULL){
						MsgList("ID is not correct");
						MessageBox(hwnd, "ID is not correct", "Error", MB_OK | MB_ICONEXCLAMATION);
						return 0;
					}
					SetWindowText(ResEdit, StudToStr(stw.FindStudByID(atoi(buf))));
					UpdateWindow(hList);
				}
				catch (Error& error){
					MsgList(error.err.c_str());
					MessageBox(hwnd, error.err.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);
					return 0;
				}
				MsgList("Student has been found !");
				EnableWindow(hButton[5], TRUE);
				return 0;
			case ID_BUTTON_16:
				try{
					GetWindowText(DelEdit[0], buf, GetWindowTextLength(DelEdit[0]) + 1);
					if (buf[0] == '\0'){
						MsgList("There is nothing entered !");
						MessageBox(hwnd, "There is nothing entered !", "Error", MB_OK | MB_ICONEXCLAMATION);
						return 0;
					}
					if (stw.DeleteStudByName(buf))
						MsgList("Student has been deleted !");
					else
						MsgList("Student has not been deleted !");
					List2List(stw.stList, hList);
					UpdateWindow(hList);
				}
				catch (Error& error){
					MsgList(error.err.c_str());
					MessageBox(hwnd, error.err.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);
					return 0;
				}
				return 0;
			case ID_BUTTON_17:
				try{
					GetWindowText(DelEdit[1], buf, GetWindowTextLength(DelEdit[1]) + 1);
					if (buf[0] == '\0'){
						MsgList("There is nothing entered !");
						MessageBox(hwnd, "There is nothing entered !", "Error", MB_OK | MB_ICONEXCLAMATION);
						return 0;
					}
					if (atoi(buf) == NULL){
						MsgList("ID is not correct");
						MessageBox(hwnd, "ID is not correct", "Error", MB_OK | MB_ICONEXCLAMATION);
						return 0;
					}
					if (stw.DeleteStudByID(atoi(buf)))
						MsgList("Student has been deleted !");
					else
						MsgList("Student has not been deleted !");
					List2List(stw.stList, hList);
					UpdateWindow(hList);
				}
				catch (Error& error){
					MsgList(error.err.c_str());
					MessageBox(hwnd, error.err.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);
					return 0;
				}
				return 0;
			case ID_BUTTON_6:
				HideAll();
				ShowButChg(hwnd);
				GetWindowText(ResEdit, buf, GetWindowTextLength(ResEdit) + 1);
				if (buf[0] == '\0'){
					MsgList("There is nothing entered !");
					MessageBox(hwnd, "There is nothing entered !", "Error", MB_OK | MB_ICONEXCLAMATION);
					return 0;
				}
				strcpy(ChgStud, buf);
				cChgStud = StrToStud(ChgStud);
				StrToChgEdit(buf);
				return 0;
			case ID_BUTTON_25:
				try{
					stw.DeleteStudByID(cChgStud.ID);
					stw.AddStudBegin(StrToStud(ChgEditToStr()));
					List2List(stw.stList, hList);
					SetWindowText(ResEdit, "");
				}
				catch (Error& error){
					MsgList(error.err.c_str());
					MessageBox(hwnd, error.err.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);
					return 0;
				}
				MsgList("Student has been successfully changed !");
				return 0;
			case ID_BUTTON_7:
				exit = MessageBox(hwnd, "Вы точно хотите выйти ?", "Error", MB_YESNO | MB_ICONEXCLAMATION);
				if (exit == IDYES){
					exit = MessageBox(hwnd, "Вы уверены, что хотите выйти ?", "Error", MB_YESNO | MB_ICONEXCLAMATION);
					if (exit == IDYES){
						exit = MessageBox(hwnd, "Полностью уверены ?", "Error", MB_YESNO | MB_ICONEXCLAMATION);
						if (exit == IDYES){
							exit = MessageBox(hwnd, "Последний шанс! Вы точно хотите выйти ?", "Error", MB_YESNO | MB_ICONEXCLAMATION);
							if (exit == IDYES)
								PostQuitMessage(0);
						}
					}
				}
				return 0;
			case ID_BUTTON_26:
				HideAll();
				hButSave[0] = CreateWindow("BUTTON", "Сохранить", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 170, 310, 140, 20, hwnd, (HMENU)ID_BUTTON_27, GetModuleHandle(NULL), NULL);
				hButSave[1] = CreateWindow("BUTTON", "Сохранить как ...", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 170, 340, 140, 20, hwnd, (HMENU)ID_BUTTON_28, GetModuleHandle(NULL), NULL);
				SaveEdit = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 171, 360, 139, 20, hwnd, (HMENU)EDIT_14, GetModuleHandle(NULL), NULL);
				return 0;
			case ID_BUTTON_27:
				try{
					SaveList(stw.stList, path);
				}
				catch (Error& error){
					MsgList(error.err.c_str());
					MessageBox(hwnd, error.err.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);
					return 0;
				}
				return 0;
			case ID_BUTTON_28:
				try{
					GetWindowText(SaveEdit, pathSave, GetWindowTextLength(SaveEdit) + 1);
					if (pathSave[0] == '\0'){
						MsgList("There is no path entered !");
						MessageBox(hwnd, "There is no path entered !", "Error", MB_OK | MB_ICONEXCLAMATION);
						return 0;
					}
					SaveListAs(stw.stList, pathSave);
				}
				catch (Error& error){
					MsgList(error.err.c_str());
					MessageBox(hwnd, error.err.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);
					return 0;
				}
				return 0;
			}
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, iMsg, wParam, lParam);
	}
}