#include<iostream>
#include<ctime>
#include<math.h>
using namespace std;
float recursive(int x, int n) {
	if (n == 1)return x;
	long long Factorial = 1;
	for (int i = 1; i <= n; i++) {
		Factorial *= i;
	}
	return (1.0 * pow(x, n) / (Factorial)) + recursive(x, n - 1);
}
float notRecursive(int x, int n) {
	float sum = 0;
	for (int i = 1; i <= n; i++) {
		int Factorial = 1;
		for (int j = 1; j <= i; j++) {
			Factorial *= j;
		}
		sum += ((float)pow(x, i) / (Factorial));
	}
	return sum;
}
int main() {
	int x, n; cin >> x >> n;
	clock_t time_start1 = clock();
	cout <<"\nUse recursive: " <<recursive(x, n);
	time_start1 = clock() - time_start1;
	cout << "\nTime using recursive function: " << (float)time_start1 / CLOCKS_PER_SEC;
	clock_t time_start2 = clock();
	cout << "\nNot use recursive: " << notRecursive(x, n);
	time_start2 = clock() - time_start2;
	cout << "\nTime not using recursive function: " << (float)time_start2 / CLOCKS_PER_SEC;
	return 0;
}
