/*

    Tran Dai Dong
    MSSV: 22120065

*/
#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};
struct SinhVien {
    char* maso;
    char* hoten;
    Date ns;
    float diem;
};
struct Node {
    SinhVien sv;
    Node* Next;
};
void cpychar(char*& Destination, char Course[]) {
    int n = strlen(Course);
    Destination = new char[n];
    for (int i = 0; i < n; i++) {
        Destination[i] = Course[i];
    }
    Destination[n] = '\0';
}
Node* makeNode(SinhVien sv) {
    Node* ans = new Node;
    ans->sv = sv;
    ans->Next = NULL;
    return ans;
}
bool checkCode(char Source[]) {
    int n = strlen(Source);
    if (n != 8)return false;
    return true;
}
SinhVien makeSinhVien() {
    char s[100];
    SinhVien sv;
    cin.ignore();
    cout << "Nhap mssv: ";
    do {
        gets_s(s);
        if (checkCode(s) == false) {
            cout << "Nhap lai mssv: ";
        }
    } while (checkCode(s)==false);
    cpychar(sv.maso, s);
    cout << "Nhap ten: "; gets_s(s);
    cpychar(sv.hoten, s);
    cout << "Nhap nam sinh\n";
    cout << "Nhap ngay: "; cin >> sv.ns.day;
    cout << "Nhap thang: "; cin >> sv.ns.month;
    cout << "Nhap nam: "; cin >> sv.ns.year;
    cout << "Nhap diem: "; cin >> sv.diem;
    return sv;
}
void addLast(Node*& Head, Node* p) {
    p->Next = NULL;
    if (Head == NULL) {
        Head = p;
    }
    else {
        Node* k = Head;
        while (k->Next != NULL) {
            k = k->Next;
        }
        k->Next = p;
    }
}
void addStudentSort(Node*& Head, Node* p) {
    if (Head == NULL) {
        Head = p;
        return;
    }
    long long mssv = atol(p->sv.maso);
    if (mssv < atol(Head->sv.maso)) {
        p->Next = Head;
        Head = p;
        return;
    }
    Node* k = NULL;
    for (k = Head; k->Next != NULL; k = k->Next) {
        long long mssvTemporary = atol(k->Next->sv.maso);
        if (mssv < mssvTemporary) {
            p->Next = k->Next;
            k->Next = p;
            return;
        }
    }
    k->Next = p;
}
void ReadToTheList1(Node*& Head) {
    char s[100];
    char x;
    ifstream filein;
    char ss[] = "dssv.dat";
    filein.open(ss, ios_base::in);
    if (filein.fail()) {
        cout << "\nOpen file fail!" << endl;
    }
    else {
        while (filein.eof() != true) {
            SinhVien sv;
            filein.getline(s, 10, ',');
            cpychar(sv.maso, s);
            filein.getline(s, 30, ',');
            cpychar(sv.hoten, s);
            filein >> sv.ns.day;
            filein.get(x);//doc ki tu '/'
            filein >> sv.ns.month;
            filein.get(x);//doc ki tu '/'
            filein >> sv.ns.year;
            filein.get(x);
            filein >> sv.diem;
            filein.get(x);
            Node* k = makeNode(sv);
            addLast(Head, k);
        }
    }
    filein.close();
}
void ReadToTheList2(Node*& Head) {
    char s[100];
    char x;
    ifstream filein;
    filein.open("dssv_lowAvg.dat", ios_base::in);
    if (filein.fail()) {
        cout << "\nOpen file fail!" << endl;
    }
    else {
        while (filein.eof() != true) {
            SinhVien sv;
            filein.getline(s, 10, ',');
            cpychar(sv.maso, s);
            filein.getline(s, 30, ',');
            cpychar(sv.hoten, s);
            filein >> sv.ns.day;
            filein.get(x);//doc ki tu '/'
            filein >> sv.ns.month;
            filein.get(x);//doc ki tu '/'
            filein >> sv.ns.year;
            filein.get(x);
            filein >> sv.diem;
            filein.get(x);
            Node* k = makeNode(sv);
            addLast(Head, k);
        }
    }
    filein.close();
}
int s_List(Node* Head) {
    int cnt = 0;
    Node* k = Head;
    while (k != NULL) {
        k = k->Next;
        cnt++;
    }
    return cnt;
}
void XepLoaiSinhVienTheoDiem(Node* Head) {
    int cnt = 0;
    cout << "Sinh vien gioi: \n";
    for (Node* k = Head; k != NULL; k = k->Next) {
        if (k->sv.diem >= 8) {
            cout << ++cnt << ". " << k->sv.maso << "\t" << k->sv.hoten << '\t' << k->sv.ns.day << "/" << k->sv.ns.month << "/" << k->sv.ns.year << "\t" << k->sv.diem << endl;
        }
    }
    cout << "\nSinh vien kha: \n";
    for (Node* k = Head; k != NULL; k = k->Next) {
        if (k->sv.diem >= 6.5 && k->sv.diem < 8) {
            cout << ++cnt << ". " << k->sv.maso << "\t" << k->sv.hoten << '\t' << k->sv.ns.day << "/" << k->sv.ns.month << "/" << k->sv.ns.year << "\t" << k->sv.diem << endl;
        }
    }
    cout << "\nSinh vien trung binh: \n";
    for (Node* k = Head; k != NULL; k = k->Next) {
        if (k->sv.diem >= 5 && k->sv.diem < 6.5) {
            cout << ++cnt << ". " << k->sv.maso << "\t" << k->sv.hoten << '\t' << k->sv.ns.day << "/" << k->sv.ns.month << "/" << k->sv.ns.year << "\t" << k->sv.diem << endl;
        }
    }
    cout << "\nSinh vien yeu: \n";
    for (Node* k = Head; k != NULL; k = k->Next) {
        if (k->sv.diem < 5) {
            cout << ++cnt << ". " << k->sv.maso << "\t" << k->sv.hoten << '\t' << k->sv.ns.day << "/" << k->sv.ns.month << "/" << k->sv.ns.year << "\t" << k->sv.diem << endl;
        }
    }
}
float MarkAverage(Node* Head) {
    float dtb = 0;
    for (Node* k = Head; k != NULL; k = k->Next) {
        dtb += k->sv.diem;
    }
    return dtb / s_List(Head);
}
void SortListMark(Node*& Head) {
    for (Node* k = Head; k->Next != NULL; k = k->Next) {
        for (Node* g = k->Next; g != NULL; g = g->Next) {
            if (k->sv.diem < g->sv.diem) {
                SinhVien tmp = k->sv;
                k->sv = g->sv;
                g->sv = tmp;
            }
        }
    }
}
void SortList(Node*& Head) {
    for (Node* k = Head; k->Next != NULL; k = k->Next) {
        for (Node* g = k->Next; g != NULL; g = g->Next) {
            long long mssv1 = atol(k->sv.maso);
            long long mssv2 = atol(g->sv.maso);
            if (mssv1 > mssv2) {
                SinhVien tmp = k->sv;
                k->sv = g->sv;
                g->sv = tmp;
            }
        }
    }
}
SinhVien* SaveToArray(Node* Head, int& cnt) {
    for (Node* k = Head; k != NULL; k = k->Next) {
        if (k->sv.diem < s_List(Head)) {
            cnt++;
        }
    }
    SinhVien* sv = new SinhVien[cnt];
    cnt = 0;
    for (Node* k = Head; k != NULL; k = k->Next) {
        if (k->sv.diem < s_List(Head)) {
            sv[cnt++] = k->sv;
        }
    }
    return sv;
}
void DeletePosition(Node*& Head, int pos) {
    if (pos == 1) {
        if (Head == NULL)return;
        else {
            Node* x = Head;
            Head = Head->Next;
            delete x;
        }
    }
    else if (pos == s_List(Head)) {
        if (Head == NULL)return;
        else {
            Node* k = Head;
            while (k->Next->Next != NULL) {
                k = k->Next;
            }
            Node* x = k->Next;
            k->Next = NULL;
            delete x;
        }
    }
    else {
        Node* k = Head;
        for (int i = 1; i < pos - 1; i++) {
            k = k->Next;
        }
        Node* x = k->Next;
        k->Next = k->Next->Next;
        delete x;
    }
}
void DeleteMSSV(Node*& Head) {
    char s[100];
    char* ss;
    cin.ignore();
    cout << "\nNhap mssv xoa: "; gets_s(s);
    int i = 0;
    for (Node* k = Head; k != NULL; k = k->Next) {
        i++;
        if (strcmp(k->sv.maso, s) == 0) {
            DeletePosition(Head, i);
            i = 0;
            k = Head;
        }
    }
}
int checkDay(Date a, Date b) {
    if (a.year > b.year)return 1;
    if (a.year < b.year)return -1;

    if (a.month > b.month)return 1;
    if (a.month < b.month)return -1;

    if (a.day > b.day)return 1;
    if (a.day < b.day)return -1;
    return 0;
}
Node* SameBirtday(Node* Head) {
    int n = s_List(Head);
    int* a = new int[n + 1];
    for (int i = 0; i < n + 1; i++) {
        a[i] = 0;
    }
    Node* tmp = NULL;
    int i1 = 0, i2;
    for (Node* k = Head; k != NULL; k = k->Next) {
        i1++; i2 = 0;
        for (Node* g = Head; g != NULL; g = g->Next) {
            i2++;
            if (checkDay(k->sv.ns, g->sv.ns) == 0 && k != g && a[i2] == 0) {
                a[i2] = 1;
                if (a[i1] == 0) {
                    a[i1] = -1;
                }
                SinhVien tmp1 = g->sv;
                Node* ans1 = makeNode(tmp1);
                addLast(tmp, ans1);
            }
        }
        if (a[i1] == -1) {
            a[i1] = 1;
            SinhVien tmp2 = k->sv;
            Node* ans2 = makeNode(tmp2);
            addLast(tmp, ans2);
        }
    }
    return tmp;
}
void GhiSinhVien(Node* Head) {
    ofstream fileout;
    int n = MarkAverage(Head);
    bool check = false;
    fileout.open("dssv_lowAvg.dat", ios_base::out);
    for (Node* k = Head; k != NULL; k = k->Next) {
        if (check == true && k->sv.diem < n) {
            fileout << "\n" << k->sv.maso << "," << k->sv.hoten << "," << k->sv.ns.day << "," << k->sv.ns.month << "," << k->sv.ns.year << "," << k->sv.diem;
        }
        else if (k->sv.diem < n) {
            fileout << k->sv.maso << "," << k->sv.hoten << "," << k->sv.ns.day << "," << k->sv.ns.month << "," << k->sv.ns.year << "," << k->sv.diem;
            check = true;
        }
    }
    fileout.close();
}
void output(Node* Head) {
    int cnt = 0;
    for (Node* k = Head; k != NULL; k = k->Next) {
        cout << ++cnt << " " << k->sv.maso << "\t" << k->sv.hoten << '\t' << k->sv.ns.day << "/" << k->sv.ns.month << "/" << k->sv.ns.year << "\t" << k->sv.diem << endl;
    }
    cout << endl;
}
int main() {
    Node* Head = NULL;
    Node* tmp = NULL;
    Node* ans = NULL;
    Node* ans1 = NULL;
    int choose;
    int cnt = 0;
    SinhVien* sv, svv;
    while (true) {
        system("cls");
        cout << "\t\tMENU";
        cout << "\n0. Doc danh sach sinh vien";
        cout << "\n1. Dem so luong NODE";
        cout << "\n2. Them mot sinh vien vao list";
        cout << "\n3. Tinh diem trung binh";
        cout << "\n4. Xep loai sinh vien theo diem";
        cout << "\n5. Luu sinh vien diem be hon diem trung binh";
        cout << "\n6. Xoa sinh vien voi mssv";
        cout << "\n7. Sap xep danh sach sinh vien";
        cout << "\n8. Thong ke sinh vien cung ngay sinh nhat";
        cout << "\n9. Ghi sinh vien diem be hon trung binh";
        cout << "\n10. Doc danh sach sinh vien diem be hon trung binh";
        cout << "\n11. Xuat danh sach sinh vien";
        cout << "\n12. Thoat";
        cout << "\nNhap lua chon: "; cin >> choose;
        if (choose >= 12)break;
        else {
            switch (choose) {
            case 0:
                system("cls");
                ReadToTheList1(Head);
                output(Head);
                cout << endl; system("pause");
                break;
            case 1:
                system("cls");
                cout << "So luong NODE: " << s_List(Head);
                cout << endl; system("pause");
                break;
            case 2:
                system("cls");
                svv = makeSinhVien();
                ans = makeNode(svv);
                addStudentSort(Head, ans);
                output(Head);
                cout << endl; system("pause");
                break;
            case 3:
                system("cls");
                cout << "Diem trung binh: " << MarkAverage(Head);
                cout << endl; system("pause");
                break;
            case 4:
                system("cls");
                SortListMark(Head);
                cout << "\tXEP LOAI SINH VIEN THEO DIEM \n";
                XepLoaiSinhVienTheoDiem(Head);
                cout << endl; system("pause");
                break;
            case 5:
                system("cls");
                sv = SaveToArray(Head, cnt);
                for (int i = 0; i < cnt; i++) {
                    cout << i + 1 << " " << sv[i].maso << " " << sv[i].hoten << " " << sv[i].ns.day << "/" << sv[i].ns.month << "/" << sv[i].ns.year << " " << sv[i].diem << endl;
                }
                cout << endl; system("pause");
                break;
            case 6:
                system("cls");
                output(Head);
                DeleteMSSV(Head);
                cout << "\tDANH SACH SINH VIEN SAU KHI XOA\n";
                output(Head);
                cout << endl; system("pause");
                break;
            case 7:
                system("cls");
                output(Head);
                cout << "\tDANH SACH SINH VIEN SAU KHI SAP XEP \n";
                SortList(Head);
                output(Head);
                cout << endl; system("pause");
                break;
            case 8:
                system("cls");
                cout << "\tDANH SACH SINH VIEN TRUNG NGAY SINH NHAT\n";
                ans1 = SameBirtday(Head);
                output(ans1);
                cout << endl; system("pause");
                break;
            case 9:
                system("cls");
                GhiSinhVien(Head);
                cout << "Ghi sinh vien co diem nho hon diem trung binh thanh cong!";
                cout << "\nChon 10 de doc danh sach!";
                cout << endl; system("pause");
                break;
            case 10:
                system("cls");
                cout << "\tDANH SACH SINH VIEN DUOC GHI\n ";
                ReadToTheList2(tmp);
                output(tmp);
                cout << endl; system("pause");
                break;
            case 11:
                system("cls");
                cout << "\t\tDANH SACH SINH VIEN \n";
                output(Head);
                cout << endl; system("pause");
                break;
            }
        }
    }
    system("pause");
    return 0;
}
