/*
  Tran Dai Dong
*/
#include<iostream>
using namespace std;
struct Node {
	int data;
	int Priority;
	Node* Next;
	Node* Prev;
};
struct Queue {
	Node* Head;
	Node* Tail;
};
void init(Queue& Que) {
	Que.Head = Que.Tail = NULL;
}
Node* makeNode(int value, int priority) {
	Node* tmp = new Node;
	tmp->Next = NULL;
	tmp->Prev = NULL;
	tmp->Priority = priority;
	tmp->data = value;
	return tmp;
}
void enQueue(Queue& Que, Node* tmp) {
	if (Que.Head == NULL) {
		Que.Tail = Que.Head = tmp;
	}
	else {
		if (tmp->Priority <= Que.Tail->Priority) {
			Que.Tail->Next = tmp;
			tmp->Prev = Que.Tail;
			Que.Tail = tmp;
			return;
		}
		for (Node* k = Que.Tail->Prev; k != NULL; k = k->Prev) {
			if (tmp->Priority <= k->Priority) {
				tmp->Next = k->Next;
				k->Next = tmp;
				tmp->Prev = k;
				k->Next->Prev = tmp;
				return;
			}
		}
		tmp->Next = Que.Head;
		Que.Head->Prev = tmp;
		Que.Head = tmp;
	}
}
int deQueue(Queue& Que) {
	if (Que.Head == NULL)return 0;
	else {
		Node* tmp = Que.Head;
		int ans = tmp->data;
		Que.Head = tmp->Next;
		Que.Head->Prev = NULL;
		delete tmp;
		return ans;
	}
}
int front(Queue Que) {
	if (Que.Head == NULL)return 0;
	return Que.Head->data;
}
int sQueue(Queue& Que) {
	int cnt = 0;
	Node* tmp = Que.Head;
	while (tmp != NULL) {
		cnt++;
		tmp = tmp->Next;
	}
	return cnt;
}
bool isEmpty(Queue Que) {
	return Que.Head == NULL;
}
void print(Queue Que) {
	for (Node* i = Que.Head; i != NULL; i = i->Next) {
		cout << i->data << "-(" << i->Priority << ") ";
	}
}
int main() {
	Queue Que;
	init(Que);
	Node* tmp = NULL;
	int choose, value, priority;
	while (true) {
		system("cls");
		cout << "\n\t\tMENU\n";
		cout << "0. Thoat\n";
		cout << "1. Them phan tu vao hang doi\n";
		cout << "2. Xoa va tra ve mot phan tu hang doi\n";
		cout << "3. Tra ve phan tu o dau hang doi\n";
		cout << "4. Kiem tra hang doi co rong hay khong\n";
		cout << "5. Xuat Queue\n";
		cout << "Nhap lua chon: "; cin >> choose;
		if (choose == 0 || choose > 5)break;
		else {
			switch (choose) {
			case 1:
				system("cls");
				cout << "Nhap gia tri them: "; cin >> value;
				cout << "Nhap do uu tien: "; cin >> priority;
				tmp = makeNode(value, priority);
				enQueue(Que, tmp);
				cout << endl; system("pause");
				break;
			case 2:
				system("cls");
				cout << "Phan tu da xoa la: " << deQueue(Que);
				cout << endl; system("pause");
				break;
			case 3:
				system("cls");
				cout << "Phan tu dau hang doi la: "; cout << front(Que);
				cout << endl; system("pause");
				break;
			case 4:
				system("cls");
				if (isEmpty(Que)) {
					cout << "EMPTY";
				}
				else {
					cout << "NOT EMPTY";
				}
				cout << endl; system("pause");
				break;
			case 5:
				system("cls");
				print(Que);
				cout << endl; system("pause");
				break;
			}
		}
	}
}
