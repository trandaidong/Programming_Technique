// Viết hàm tính số Fibonacci thứ n không sử dụng đệ qui
#include<iostream>
using namespace std;
int Fibonacci(int n)
{
	int F,F1,F2,F0;
	F0 = 0;
	F1 = F2 = 1;
	for (int i = 3; i <= n; i++)
	{
		F = F1 + F2;
		F1 = F2;
		F2 = F;
	}
	return F;
}
int main()
{
	int n;
	cout << "Nhap vao n = ";
	cin >> n;
	cout << "F" << "(" << n << ")" << " " << "=" << " " << Fibonacci(n);
}
