#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
using namespace std;
void Cpy(char*& Destination, char* Source) {
	int capacity = strlen(Source);
	delete[]Destination;
	Destination = new char[capacity];
	for (int i = 0; i < capacity; i++) {
		Destination[i] = Source[i];
	}
	Destination[capacity] = '\0';
}
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
	long long lengthPart = (length / numPart)+numPart;
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

		fileout.open(nameFile, ios::out | ios::binary);
		if (i == numPart - 1) {
			temporary = new char[(length - lengthPart * (numPart - 1)) + 1];
			for (int j = 0; j < (length - lengthPart * (numPart - 1)); j++) {
				temporary[j] = content[i * lengthPart + j];
			
			}
			temporary[length - lengthPart * (numPart - 1)] = '\0';
			fileout.write((char*)temporary, sizeof(char) * ((length - lengthPart * (numPart - 1)) + 1));
		}
		else {
			temporary = new char[lengthPart+1];
			for (int j = 0; j < lengthPart; j++) {
				temporary[j] = content[i * lengthPart + j];
				if (j == lengthPart - 1) {
					temporary[lengthPart] = '\0';
				}
			}
			fileout.write((char*)temporary, sizeof(char) * lengthPart);
		}	
		delete[]temporary;
		fileout.close();
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
	while (true) {
		i++;
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
			if (flag == false)break;
			flag = false;
		}
		else {
			count++;
			filein.seekg(0, SEEK_END);
			length+= filein.tellg();
		}
		filein.close();
		// xóa đi đường dẫn tạm thời 
		delete[]pathTemporary;
	}
	if (count == i - 2) {
		contain = new char[length];
		for (int j = 1; j <= count; j++) {
			delete[]pathTemporary;
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
			int len = filein.tellg();
			containTemporary = new char[len];
			filein.seekg(0, ios::beg);
			filein.read((char*)containTemporary, sizeof(char) * len);
			strcpy(contain, containTemporary);
			filein.close();
			delete[]containTemporary;
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
	cout << argv[1] << endl;
	if (strcmp(argv[1], "MYCOPYFILE") == 0) {
		CopyFile(argv[2], argv[3]);
		cout << "\nCopy file successfully!";
	}
	if (strcmp(argv[1], "MYSPLITFILE") == 0) {
		cout << "Ok" << endl;
		int numPart = atoi(argv[4]);
		SplitFile(argv[2], argv[3], numPart);
		cout << "\nSplit file successfully!";
	}
	if (strcmp(argv[1], "MYMERGEFILE") == 0) {
		cout << "ok" << endl;
		if (MergeFile(argv[2], argv[3])) {
			cout << "\nMerge file successfully!";
		}
		
	}
	cout << endl;system("pause");
}
