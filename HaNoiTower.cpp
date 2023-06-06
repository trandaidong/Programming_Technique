#include<iostream>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
void HaNoiTower(int n, char Source, char Intermadiary, char Destination) {
	//Nếu có 1 cái đĩa thì chỉ cần chuyển đến tháp Destnation
	if (n == 1) {
		cout << "\nChuyen dia thu " << n << " tu cot " << Source << " den cot " << Destination;
		return;
	}
	else {
		// nếu số đĩa lớn hơn 1 thì ta gọi đệ quy để chuyển n-1 đĩa đến đĩa trung gian
		HaNoiTower(n - 1, Source, Destination, Intermadiary);
		// sau đó t chuyển cái đĩa cuối cùng đến tháp đến
		cout << "\nChuyen dia thu " << n << " tu cot " << Source << " den cot " << Destination;
		// tiếp tục gọi đệ quy chuyển n-1 đĩa ở tháp trung gian về tháp đến
		HaNoiTower(n - 1, Intermadiary, Source, Destination);
		// đệ quy đến khi nào thỏa mãn điều kiện dừng
	}
}
int main(){
  int n;
  cout << "Nhap so luong dia: "; cin >> n;
	HaNoiTower(n, 'A', 'B', 'C');
  return 0;
}
