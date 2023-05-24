/*
    
	Trần Đại Đồng

*/
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

void CopyFile(char* pathOfSource, char* pathOfDestination) {
	ifstream filein;
	ofstream fileout;
	filein.open(pathOfSource, ios::in | ios::binary);
	filein.seekg(0, SEEK_END);
	long long length = filein.tellg();// Lấy độ dài của file
	char* content = new char[length + 1];
	filein.seekg(0, ios::beg);// Đưa con trỏ chỉ vị về đầu file
	filein.read((char*)content, sizeof(char) * length);
	fileout.open(pathOfDestination, ios::out | ios::binary);
	fileout.write((char*)content, sizeof(char) * length);
	fileout.close();
	filein.close();
}

void SplitFile(char* pathOfSource, char* pathOfDestination, int numPart) {
	ifstream filein;
	ofstream fileout;
	long long length;

	int lengthPathOfSource = strlen(pathOfSource);
	int lengthFileExtension = 0;
	// Lấy độ dài của đuôi file
	for (int i = lengthPathOfSource - 1; i >= 0; i--) {
		if (pathOfSource[i+1] == '/')break;
		lengthFileExtension++;
	}
	char* fileExtension = new char[lengthFileExtension];
	for (int i = 0; i < lengthFileExtension; i++) {
		fileExtension[i] = pathOfSource[lengthPathOfSource - lengthFileExtension + i];
	}
	fileExtension[lengthFileExtension] = '\0';

	filein.open(pathOfSource, ios::in | ios::binary);
	filein.seekg(0, SEEK_END);
	length = filein.tellg();
	if (numPart==1|| numPart >= length)return;
	long long lengthPart = (length / numPart);//773
	char* content = new char[length+1];
	filein.seekg(0, ios::beg);
	// Đọc toàn bộ data vào biến lưu trữ content
	filein.read((char*)content, sizeof(char) * length);
	filein.close();

	char s[] = { ".part" };
	char* convert = new char;
	char* temporary = NULL;
	for (int i = 0; i < numPart; i++) {
		char* nameFile = new char[strlen(pathOfDestination) + lengthFileExtension + 10];
		for (int j = 0; j < strlen(pathOfDestination); j++) {
			nameFile[j] = pathOfDestination[j];
		}
		nameFile[strlen(pathOfDestination)] = '\0';
		_itoa(i + 1, convert, 10);
		strcat(nameFile, fileExtension);
		strcat(nameFile, s);
		if (i < 9) {
			strcat(nameFile, "0");
		}
		strcat(nameFile, convert);	
		if (i == numPart - 1) {
			temporary = new char[(length - lengthPart * (numPart - 1)) + 1];
			for (int j = 0; j < (length - lengthPart * (numPart - 1)); j++) {
				temporary[j] = content[i * lengthPart + j];
			}
			temporary[length - lengthPart * (numPart - 1)] = '\0';
			fileout.open(nameFile, ios::out | ios::binary);
			fileout.write((char*)temporary, sizeof(char) * ((length - lengthPart * (numPart - 1))));
			fileout.close();
		}
		else {
			temporary = new char[lengthPart+1];
			for (int j = 0; j < lengthPart; j++) {
				temporary[j] = content[i * lengthPart + j];
				if (j == lengthPart - 1) {
					temporary[lengthPart] = '\0';
				}
			}
			fileout.open(nameFile, ios::out | ios::binary);
			fileout.write((char*)temporary, sizeof(char) * lengthPart);
			fileout.close();
		}	
		delete[]temporary;
		
	}
}

bool MergeFile(char* pathOfPath, char* pathOfDestination){
	char* contain = NULL;
	char* containTemporary = NULL;
	long long length=0;
	long long lengthTemporary = 0;
	int i = 0;
	int count = 0;
	char* convert = new char;
	char* pathTemporary=NULL; 
	ifstream filein;
	ofstream fileout;
	bool flag = true;
	int i1, i2;
	while (true) {
		i++;// đếm số lần mở file
		pathTemporary = new char[strlen(pathOfPath) + 10];
		for (int k = 0; k < strlen(pathOfPath); k++) {
			pathTemporary[k] = pathOfPath[k];
		}
		pathTemporary[strlen(pathOfPath)] = '\0';

		_itoa(i, convert, 10);
		if (i < 10) {
			strcat(pathTemporary, "0");
		}
		strcat(pathTemporary, convert);
		// mở đường dẫn tạm thời 
		filein.open(pathTemporary, ios::in| ios::binary);
		if (!filein.is_open()) {
			if (i == 1)return false;// không tồn tại file 
			if (flag == false) {
				i2 = i;
				break;
			}
			flag = false;
			i1 = i;
		}
		else {
			count++;// số file mở thành công
			filein.seekg(0, SEEK_END);
			length+= filein.tellg();
		}
		filein.close();
		// xóa đi đường dẫn tạm thời 
		delete[]pathTemporary;
	}
	if (count == i - 2&& i2-i1==1) {
		contain = new char[length+1];
		long long lenTemporary;
		for (int j = 1; j <= count; j++) {
			pathTemporary = new char[strlen(pathOfPath) + 10];
			for (int k = 0; k < strlen(pathOfPath); k++) {
				pathTemporary[k] = pathOfPath[k];
			}
			pathTemporary[strlen(pathOfPath)] = '\0';

			_itoa(j, convert, 10);
			if (j < 10) {
				strcat(pathTemporary, "0");
			}
			strcat(pathTemporary, convert);
			filein.open(pathTemporary, ios::in | ios::binary);
			filein.seekg(0, ios::end);
			long long len = filein.tellg();
			containTemporary = new char[len+1];
			filein.seekg(0, ios::beg);
			filein.read((char*)containTemporary, sizeof(char) * len);
			for (int k = 0; k < len; k++) {
				if (j == count) {
					contain[(lenTemporary * (j - 1)) + k] = containTemporary[k];
				}
				else {
					contain[(len * (j - 1)) + k] = containTemporary[k];
				}
			}
			lenTemporary = len;
			filein.close();
			delete[]containTemporary;
			delete[]pathTemporary;
		}
		fileout.open(pathOfDestination, ios::out | ios::binary);
		fileout.write((char*)contain, sizeof(char) * length);
		fileout.close();
		return true;
	}
	else {
		cout << "Error!";
		return false;
	}	
}
int main(int argc, char* argv[]) {
	if (strcmp(argv[1], "MYCOPYFILE") == 0) {
		CopyFile(argv[2], argv[3]);
		cout << "\nCopy file successfully!";
	}
	if (strcmp(argv[1], "MYSPLITFILE") == 0) {
		int numPart = atoi(argv[4]);
		SplitFile(argv[2], argv[3], numPart);
		cout << "\nSplit file successfully!";
	}
	if (strcmp(argv[1], "MYMERGEFILE") == 0) {
		if (MergeFile(argv[2], argv[3])) {
			cout << "\nMerge file successfully!";
		}
	}
	cout << endl;system("pause");
}
