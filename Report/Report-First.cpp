#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include"Windows.h"
using namespace std;
struct SinhVien {
	char* hoten;
	char* id;
	float diemLT;
	float diemTH;
	float avg;
};
struct DArray {
	int sz;
	int capacity;
	SinhVien* ptr;
};
void gotoXY(int x, int y);
void cpychar(char s1[], char s2[]);
void inputOneStudent(SinhVien& sv);
void inputStudentList(DArray& student);
void outputStudentList(DArray student);
void cpyStudent(SinhVien& sv1, SinhVien& sv2);
void addStudent(DArray& student);
void ViewListStudent(SinhVien* sv, int n);
void ViewListStudent1(SinhVien* sv, int n);
void deleteStudent(DArray& student);
void deleteStudentWeakLearningCapacity(DArray& studen);
void CapPhatLaiBoNho(DArray& student, int vungnhothem);
void CapPhat(DArray& student);
void WriteFile(ofstream& fileout, DArray& student);
void read_File(ifstream& filein, char s[], char ktdk);
void ReadFile(ifstream& filein, DArray& student);
int main() {
	int lc;
	DArray student;
	ifstream filein;
	ofstream fileout;
	filein.open("inputStudentList.txt", ios_base::in);
	CapPhat(student);
	do {
		system("cls");
		cout << "\t\tMENU" << endl;
		cout << "1. Enter array student from keyboard." << endl;
		cout << "2. Enter array student from read file." << endl;
		cout << "3. View student list." << endl;
		cout << "4. View student sort." << endl;
		cout << "5. Add student. " << endl;
		cout << "6. Delete weak learning capacity." << endl;
		cout << "7. Delete position." << endl;
		cout << "8. Exit" << endl;
		cout << "--------------------------------------" << endl;
		cout << "Enter selection: "; cin >> lc;
		cin.ignore();
		if (lc >= 8)break;
		else {
			switch (lc) {
			case 1:
				system("cls");
				inputStudentList(student);
				//outputStudentList(student);
				ViewListStudent(student.ptr, student.sz);
				fileout << student.sz;
				WriteFile(fileout, student);
				cout << endl;
				system("pause");
				break;
			case 2:
				system("cls");
				ReadFile(filein, student);
				//outputStudentList(student);
				ViewListStudent(student.ptr, student.sz);
				fileout << student.sz;
				WriteFile(fileout, student);
				cout << endl;
				system("pause");
				break;
			case 3:
				system("cls");
				ViewListStudent(student.ptr, student.sz);
				cout << endl;
				system("pause");
				break;
			case 4:
				system("cls");
				ViewListStudent1(student.ptr, student.sz);
				cout << endl;
				system("pause");
				break;
			case 5:
				system("cls");
				addStudent(student);
				fileout << student.sz;
				WriteFile(fileout, student);
				system("cls");
				cout << "\nArray student after adding: ";
				//outputStudentList(student);
				ViewListStudent(student.ptr, student.sz);
				cout << endl;
				system("pause");
				break;
			case 6:
				system("cls");
				cout << "\nArray student after delete student weak learning capacity: ";
				deleteStudentWeakLearningCapacity(student);
				fileout << student.sz;
				WriteFile(fileout, student);
				//outputStudentList(student);
				ViewListStudent(student.ptr, student.sz);
				cout << endl;
				system("pause");
				break;
			case 7:
				system("cls");
				deleteStudent(student);
				fileout << student.sz;
				WriteFile(fileout, student);
				//outputStudentList(student);
				ViewListStudent(student.ptr, student.sz);
				cout << endl;
				system("pause");
				break;
			}

		}
	} while (true);
	if (filein.is_open() == true) {
		filein.close();
	}
	if (fileout.is_open() == true) {
		fileout.close();
	}
	cout << endl;
	system("pause");
	return 0;
}
void gotoXY(int x, int y) {
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x,y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void cpychar(char s1[], char s2[]) {
	int n = strlen(s2);
	for (int i = 0; i < n; i++) {
		s1[i] = s2[i];
	}
	s1[n] = '\0';
}
void inputOneStudent(SinhVien& sv) {
	char temp1[100];
	cout << "Enter full name: "; gets_s(temp1);
	sv.hoten = new char[strlen(temp1)];
	cpychar(sv.hoten, temp1);
	char temp2[100];
	cout << "Enter student code: "; gets_s(temp2);
	sv.id = new char[strlen(temp2)];
	cpychar(sv.id, temp2);
	cout << "Enter score theory: "; cin >> sv.diemLT;
	cout << "Enter score practice: "; cin >> sv.diemTH;
	cin.ignore();
	sv.avg = sv.diemLT * 0.7 + sv.diemTH * 0.3;
}
void inputStudentList(DArray& student) {
	int n;
	cout << "Enter the number of student in the array: ";
	cin >> n;
	cin.ignore();
	CapPhatLaiBoNho(student, n);
	//student.ptr = new SinhVien[student.sz];
	for (int i = student.sz - n; i < student.sz; i++) {
		cout << "\n\t\tSTUDENT " << i - (student.sz - n) + 1 << endl;
		inputOneStudent(student.ptr[i]);
	}
}
void outputStudent(SinhVien sv) {
	cout << "\n=======STUDENT========";
	cout << "\nName: " << sv.hoten;
	cout << "\nCode: " << sv.id;
	cout << "\nScore theory: " << sv.diemLT;
	cout << "\nScore practice: " << sv.diemTH;
	cout << "\nTotal score: " << sv.avg;
	cout << "\n======================";
}
void outputStudentList(DArray student) {
	for (int i = 0; i < student.sz; i++) {
		if (i == 0) {
			cout << "\n\t\tEXCELLENT STUDENT";
		}
		if (student.ptr[i].avg >= 8) {
			outputStudent(student.ptr[i]);
		}
		/*cout << "\n=======STUDENT========";
		cout << "\nName: " << (student.ptr + i)->hoten;
		cout << "\nCode: " << student.ptr[i].id;
		cout << "\nScore theory: " << (student.ptr + i)->diemLT;
		cout << "\nScore practice: " << (student.ptr + i)->diemTH;
		cout << "\nTotal score: " << student.ptr[i].avg;
		cout << "\n======================"; */
	}

	for (int i = 0; i < student.sz; i++) {
		if (i == 0) {
			cout << "\n\t\tGOOD STUDENT";
		}
		if (student.ptr[i].avg >= 6.5 && student.ptr[i].avg < 8) {
			outputStudent(student.ptr[i]);
		}
	}
	for (int i = 0; i < student.sz; i++) {
		if (i == 0) {
			cout << "\n\t\tAVERAGE STUDENT";
		}
		if (student.ptr[i].avg >= 5 && student.ptr[i].avg < 6.5) {
			outputStudent(student.ptr[i]);
		}
	}
	for (int i = 0; i < student.sz; i++) {
		if (i == 0) {
			
			cout << "\n\t\tWEAK STUDENT";
		}
		if (student.ptr[i].avg < 5) {
			outputStudent(student.ptr[i]);
		}
	}
}
void cpyStudent(SinhVien& sv1, SinhVien& sv2) {
	int n1 = strlen(sv2.hoten);
	sv1.hoten = new char[n1];
	cpychar(sv1.hoten, sv2.hoten);
	int n2 = strlen(sv2.id);
	sv1.id = new char[n2];
	cpychar(sv1.id, sv2.id);
	sv1.diemLT = sv2.diemLT;
	sv1.diemTH = sv2.diemTH;
	sv1.avg = sv2.avg;
}
void addStudent(DArray& student) {
	DArray temp;
	temp.ptr = new SinhVien[student.sz];
	for (int i = 0; i < student.sz; i++) {
		cpyStudent(temp.ptr[i], student.ptr[i]);
	}
	temp.sz = student.sz;
	delete[]student.ptr;
	student.ptr = NULL;
	student.sz++;
	student.ptr = new SinhVien[student.sz];
	for (int i = 0; i < student.sz - 1; i++) {
		int n1 = strlen(temp.ptr[i].hoten);
		cpyStudent(student.ptr[i], temp.ptr[i]);
	}
	cout << "\n\t\tSTUDENT ADD " << endl;
	inputOneStudent(student.ptr[student.sz - 1]);
	delete[]temp.ptr;
	temp.ptr = NULL;
}
void ViewListStudent1(SinhVien* sv, int n) {
	int cnt = 1;
	int x = 2, y = 2;
	gotoXY(x, y); cout << "STT"; x += 5;
	gotoXY(x, y); cout << "MSSV"; x += 20;
	gotoXY(x, y); cout << "Ho va Ten"; x += 27;
	gotoXY(x, y); cout << "Diem LT"; x += 10;
	gotoXY(x, y); cout << "Diem TH"; x += 11;
	gotoXY(x, y); cout << "Diem TB";;
	x = 2; y++;
	cout << "\n\t\tEXCELLENT STUDENT";
	for (int i = 0; i < n; i++) {
		if (sv[i].avg >= 8) {
			x = 2; y++;
			gotoXY(x, y); cout << cnt++; x += 5;
			gotoXY(x, y); cout << sv[i].id; x += 20;
			gotoXY(x, y); cout << sv[i].hoten; x += 30;
			gotoXY(x, y); cout << sv[i].diemLT; x += 10;
			gotoXY(x, y); cout << sv[i].diemTH; x += 10;
			gotoXY(x, y); cout << sv[i].avg;
		}
	}
	x = 2; y++;
	cout << "\n\t\tGOOD STUDENT";
	for (int i = 0; i < n; i++) {	
		if (sv[i].avg >= 6.5 && sv[i].avg < 8) {
			x = 2; y++;
			gotoXY(x, y); cout << cnt++; x += 5;
			gotoXY(x, y); cout << sv[i].id; x += 20;
			gotoXY(x, y); cout << sv[i].hoten; x += 30;
			gotoXY(x, y); cout << sv[i].diemLT; x += 10;
			gotoXY(x, y); cout << sv[i].diemTH; x += 10;
			gotoXY(x, y); cout << sv[i].avg;
		}
	}
	x = 2; y++;
	cout << "\n\t\tAVERAGE STUDENT";
	for (int i = 0; i < n; i++) {
		if (sv[i].avg >= 5 && sv[i].avg < 6.5) {
			x = 2; y++;
			gotoXY(x, y); cout << cnt++; x += 5;
			gotoXY(x, y); cout << sv[i].id; x += 20;
			gotoXY(x, y); cout << sv[i].hoten; x += 30;
			gotoXY(x, y); cout << sv[i].diemLT; x += 10;
			gotoXY(x, y); cout << sv[i].diemTH; x += 10;
			gotoXY(x, y); cout << sv[i].avg;
		}
	}
	x = 2; y++;
	cout << "\n\t\tWEAK STUDENT";
	for (int i = 0; i < n; i++) {		
		if (sv[i].avg < 5) {
			x = 2; y++;
			gotoXY(x, y); cout << cnt++; x += 5;
			gotoXY(x, y); cout << sv[i].id; x += 20;
			gotoXY(x, y); cout << sv[i].hoten; x += 30;
			gotoXY(x, y); cout << sv[i].diemLT; x += 10;
			gotoXY(x, y); cout << sv[i].diemTH; x += 10;
			gotoXY(x, y); cout << sv[i].avg;
		}
	}
}
void ViewListStudent(SinhVien* sv, int n) {
	int x = 2, y = 2;
	gotoXY(x, y); cout << "STT"; x += 5;
	gotoXY(x, y); cout << "MSSV"; x += 20;
	gotoXY(x, y); cout << "Ho va Ten"; x += 27;
	gotoXY(x, y); cout << "Diem LT"; x += 10;
	gotoXY(x, y); cout << "Diem TH"; x += 11;
	gotoXY(x, y); cout << "Diem TB";
	for (int i = 0; i < n; i++) {
		x = 2; y++;
		gotoXY(x, y); cout << i + 1; x += 5;
		gotoXY(x, y); cout << sv[i].id; x += 20;
		gotoXY(x, y); cout << sv[i].hoten; x += 30;
		gotoXY(x, y); cout << sv[i].diemLT; x += 10;
		gotoXY(x, y); cout << sv[i].diemTH; x += 10;
		gotoXY(x, y); cout << sv[i].avg;
	}
}
void deleteStudent(DArray& student) {
	int pos; cout << "\nEnter position delete: "; cin >> pos;
	pos--;
	DArray tmp;
	tmp.ptr = new SinhVien[student.sz];
	for (int i = 0; i < student.sz; i++) {
		cpyStudent(tmp.ptr[i], student.ptr[i]);
	}
	tmp.sz = student.sz;
	student.sz--;
	delete[]student.ptr;
	student.ptr = new SinhVien[student.sz];
	for (int i = 0; i < pos; i++) {
		cpyStudent(student.ptr[i], tmp.ptr[i]);
	}
	for (int i = pos; i < student.sz; i++) {
		cpyStudent(student.ptr[i], tmp.ptr[i+1]);
	}
	delete[]tmp.ptr;
	/*for (int i = 0; i < student.sz; i++) {
		if (student.ptr[i].avg < 5) {
			DArray temp;
			temp.ptr = new SinhVien[student.sz];
			for (int j = 0; j < student.sz; j++) {
				cpyStudent(temp.ptr[j], student.ptr[j]);
			}
			temp.sz = student.sz;
			student.sz--;
			delete[]student.ptr;
			student.ptr = NULL;
			student.ptr = new SinhVien[student.sz];
			for (int j = 0; j < i; j++) {
				cpyStudent(student.ptr[j], temp.ptr[j]);
			}
			for (int j = i; j < student.sz; j++) {
				cpyStudent(student.ptr[j], temp.ptr[j + 1]);
			}
			delete[]temp.ptr;
		}
	}*/
}
void deleteStudentWeakLearningCapacity(DArray& student) {
	for (int i = 0; i < student.sz; i++) {
		if (student.ptr[i].avg < 5) {
			DArray temp;
			temp.ptr = new SinhVien[student.sz];
			for (int j = 0; j < student.sz; j++) {
				cpyStudent(temp.ptr[j], student.ptr[j]);
			}
			temp.sz = student.sz;
			student.sz--;
			delete[]student.ptr;
			student.ptr = NULL;
			student.ptr = new SinhVien[student.sz];
			for (int j = 0; j < i; j++) {
				cpyStudent(student.ptr[j], temp.ptr[j]);
			}
			for (int j = i; j < student.sz; j++) {
				cpyStudent(student.ptr[j], temp.ptr[j + 1]);
			}
			delete[]temp.ptr;
		}
	}
}
void WriteFile(ofstream& fileout, DArray& student) {
	fileout.open("studentList.txt", ios_base::out);
	for (int i = 0; i < student.sz; i++) {
		fileout << "\n=====STUDENT=======";
		fileout << "\nName: " << (student.ptr + i)->hoten;
		fileout << "\nCode: " << student.ptr[i].id;
		fileout << "\nScore theory: " << (student.ptr + i)->diemLT;
		fileout << "\nScore practice: " << (student.ptr + i)->diemTH;
		fileout << "\nTotal score: " << student.ptr[i].avg;
		fileout << "\n===================";
	}
	fileout.close();
}
void read_File(ifstream& filein, char s[], char ktdk) {
	int i = 0;
	while (filein.eof() != true) {
		filein.get(s[i]);
		if (s[i] == ktdk || filein.eof() == true) {
			s[i] = '\0';
			break;
		}
		i++;
	}
}
void CapPhat(DArray& student) {
	student.sz = 0;
	student.ptr = new SinhVien[student.sz];
}
void CapPhatLaiBoNho(DArray& student, int vungnhothem) {
	DArray temp;
	temp.ptr = new SinhVien[student.sz];
	for (int i = 0; i < student.sz; i++) {
		cpyStudent(temp.ptr[i], student.ptr[i]);
	}
	temp.sz = student.sz;
	delete[]student.ptr;
	student.ptr = NULL;
	student.sz += vungnhothem;
	student.ptr = new SinhVien[student.sz];
	for (int i = 0; i < student.sz - vungnhothem; i++) {
		int n1 = strlen(temp.ptr[i].hoten);
		cpyStudent(student.ptr[i], temp.ptr[i]);
	}
	delete[]temp.ptr;
	temp.ptr == NULL;
}
void ReadFile(ifstream& filein, DArray& student) {
	int n;
	filein >> n;
	CapPhatLaiBoNho(student, n);
	//student.ptr = new SinhVien[student.sz];
	char temp[100];
	char s;
	filein.get(s);
	for (int i = (student.sz - n); i < student.sz; i++) {
		read_File(filein, temp, '\n');
		read_File(filein, temp, ':');
		filein.get(s);
		read_File(filein, temp, '\n');
		student.ptr[i].hoten = new char[strlen(temp)];
		cpychar(student.ptr[i].hoten, temp);
		read_File(filein, temp, ':');
		filein.get(s);
		read_File(filein, temp, '\n');
		student.ptr[i].id = new char[strlen(temp)];
		cpychar(student.ptr[i].id, temp);
		read_File(filein, temp, ':');
		filein >> student.ptr[i].diemLT;
		filein >> s;
		read_File(filein, temp, ':');
		filein >> student.ptr[i].diemTH;
		student.ptr[i].avg = student.ptr[i].diemLT * 0.7 + student.ptr[i].diemTH * 0.3;
	}
	filein.close();
}
