/*                Agrument function main
*   Ý nghĩa: chương trình sử dụng các đối số dòng lệnh như dữ liệu vào của chương trình
*   Chương trình exe chạy ở chế độ Command Line
*/   

#include<iostream>
#include<string>
#include<cstring>
using namespace std;
int ChangeNumber(char* s) {
	int i = 0;
	int dau = 1;
	if (*s == '-') {
		dau = -1;
		i++;
	}
	int so = 0;
	while (i < strlen(s)) {
		so *= 10;
		so += (int)(s[i++] - '0');
	}
	return so * dau;
}
/*
* Đối argc (argument count) đầu tiên là số lượng đối dòng lệnh,
* Đối argv (argument vector) thứ hai là con trỏ trỏ tới mảng xâu ký tự, 
*                            mảng này chứa danh sách các đối số dòng lệnh, mỗi đối là một xâu. 
*                            Khi gõ vào từ dòng lệnh các tham số phải cách nhau bởi dấu cách
*/
int main(int argc, char* argv[]) {
	int tong = 0;
	char s[100];
	int n;
	for (int i = 0; i < argc; i++) {
		cout << "\nDoi so " << i << " = " << argv[i] << " : do dai: " << strlen(argv[i]);
		if (i == 0)continue;
		strcpy_s(s,argv[i]);
		n = ChangeNumber(s);
		tong += n;
	}

	cout <<"\n"<<tong << endl;
	return 0;
}
