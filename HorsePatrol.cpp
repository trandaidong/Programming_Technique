#include<iostream>
#include<cmath>
#include<string>
#include<cstdlib>
#define N 8
using namespace std;
// Bài toán con mã đi tuần
int tick = 0;// Khởi tạo biến đếm toàn cục ban đầu có giá trị bằng 0
// define N = 8 ( bàn cờ có 8 hàng 8 cột)
int Arr[N][N] = { 0 };// Khởi tạo matran có giá trị mỗi phần tử = 0
// khởi tạo 2 mảng 1 chiều lưu tuần tự lần lượt mà con mã có thể đi xung quanh vị trí đang đứng
// tương ứng với vị trí (-2,-1)
const int X[] = { -2,-2,-1,-1,1,1,2,2 };
const int Y[] = { -1,1,-2,2,-2,2,-1,1 };
// viết hàm in ra ma trận
void chessBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Arr[i][j] < 10)cout << "0";
			cout << Arr[i][j] << " ";
		}
		cout << endl;
	}
}
// Hàm sử lí với tham số đầu vào là vị trí con mã đang đứng trong bàn cờ
void HorsePatrol(int x, int y) {
	// mỗi lần hàm HorsePatrol được gọi thì biến tick tăng thêm một đơn vị và gán biến tick
	// cho vị trí con mã đang đứng, tương ứng với đó là số thứ tự mà con mã đã đi chuyển để
	// lại trên bàn cờ
	++tick;
	Arr[x][y] = tick;
	// tạo một vòng for để duyệt lần lượt từng giá trị của 2 mảng 1 chiều tương ứng
	for (int i = 0; i < 8; i++) {
		// nếu biến tick được tăng lên bằng số ô của bàn cờ, nghĩa là nó đã đi full bàn cờ
		// thì ta in ra bàn cờ (với giá trị của từng phần tử trong bàn cờ là số thứ tự mà 
		// con mã đã đi ) và ta kết thúc bài toán
		if (tick == N * N) {
			cout << "Duong ma di la: " << endl;
			chessBoard();
			exit(0);
		}
		// nếu biến tick chưa bằng số ô của bàn cờ thì ta tiếp tục tìm vị trí tiếp theo mà 
		// con mã có thể đi
		int x_new = x + X[i];// biến x_new và y_new sẽ lưu vị trí tiếp theo của con mã
		int y_new = y + Y[i];// với 2 mảng X Y chứa lần lượt vị trí tương ứng của con mã đến ô tiếp theo
		// ta sẽ kiểm tra vị trí tiếp theo đó có thỏa mãn vị trí của bàn cờ 
		// vị trí của bàn cờ chỉ chạy từ 1 ->8 tương ứng trong ma trận là 0 -> 7 
		// và kiểm tra vị trí đó con mã đã đi qua chưa, nếu nó đi qua rồi thì trên ma trận ứng 
		// với vị trí nó đang đứng đã lưu số thứ tự mà con mã đã đi được, nếu chưa đi qua thì
		// vị trí đó vẫn có giá trị là 0 như đã được khởi tạo ban đầu
		if (x_new >= 0 && y_new >= 0 && x_new < N && y_new < N && Arr[x_new][y_new] == 0) {
			// nếu thỏa mã các điều kiện trên thì ta gọi đệ quy lại hàm và tiếp tục xét các vị trí
			// tiếp theo đến khi nào điều kiện dừng ở trên thỏa mãn
			HorsePatrol(x_new, y_new);
		}
	}
	// nếu xét hết vị trí xung quanh con mã mà không có vị trí nào con mã đi được thì ta quay lùi 
	// lại vị trí trước đó và cho chương trình xét tiếp vị trí tiếp theo
	--tick;// biến tick sẽ giảm đi 1 đơn vị 
	Arr[x][y] = 0;// trả lại giá trị mà con mã đang đứng là 0 để cho những lần sau chương trình
	// biết là vị trí này con mã chưa đi qua (được tính là đi qua)
}
int main(){
  int x,y;
  cout << "Nhap vi tri con ma bat dau di chuyen (x,y)(1->8): "; cin >> x >> y;
	HorsePatrol(x - 1, y - 1);
  return 0;
}
