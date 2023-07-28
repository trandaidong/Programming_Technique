//Bài 2. Cho trước một tập tin lưu các số nguyên.Viết chương trình đọc và hiển thị các số
//nguyên trên màn hình.Để tiện theo dõi, hãy hiển thị các số nguyên này trên nhiều dòng,
//mỗi dòng gồm 15 số.
#include<iostream>
#include<fstream>
using namespace std;
int main() {
	int a[10000];
	int i = 0;
	ifstream filein;
	filein.open("GHI.TXT", ios_base::in);
	filein.seekg(0, ios_base::beg);
	while (filein.eof() != true) {
		filein >> a[i++];
	}
	int k = 0;
	int n = 10000 / 15;
	int b[10000 / 15];
	for (int i = 0; i < n; i++) {
		b[i] = i+1;
	}
	for (int i = 0; i < 10000; i++) {
			cout << a[i] << " ";
			if (i == b[k] * 15 - 1) {
				cout << endl;
				k++;
			}
	}
	filein.close();
	return 0;
}
