#include<iostream>
using namespace std;
long long FibonacciRecursive(int n) {
	if (n == 1 || n == 2)return 1;
	return FibonacciRecursive(n - 1) + FibonacciRecursive(n - 2);
}
long long Fibonacci(int n) {
	long long fn = 0, f1 = 1, f2 = 1;
	for (int i = 3; i <= n; i++) {
		fn = f1 + f2;
		f1 = f2;
		f2 = fn;
	}
	return fn;
}
int main() {
	int  n; 
	do {
		cout << "\nNhap n: "; cin >> n;
		if (n <= 2)cout << "Nhap lai";
	} while (n <= 2);
	clock_t time_start1 = clock();
	cout << "\nUse recursive: " << FibonacciRecursive(n);
	time_start1 = clock() - time_start1;
	cout << "\nTime using recursive function: " << (float)time_start1 / CLOCKS_PER_SEC;
	clock_t time_start2 = clock();
	cout << "\nNot use recursive: " << Fibonacci(n);
	time_start2 = clock() - time_start2;
	cout << "\nTime not using recursive function: " << (float)time_start2 / CLOCKS_PER_SEC;
	return 0;
}
