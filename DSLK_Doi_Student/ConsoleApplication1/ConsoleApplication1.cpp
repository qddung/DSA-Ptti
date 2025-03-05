#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct Sinhvien {
	int maso;
	char ho[51];
	char ten[11];
};

struct node {
	Sinhvien sv;
	node* lk1, * lk2;
};
typedef node* PTR;

void insertStudent(PTR& head, Sinhvien sv);
void deleteStudent(PTR& head, int maso);
PTR searchStudent(PTR head, int maso);
void displayByStudent(PTR head);

void SapXepTheoTen(PTR head, int size);

void SapXepTheoMaSv(PTR head, int size);

int studentNumber = 0;

void SapXepTheoTen(PTR head, int size)
{
	for (int step = 0; step < size - 1; ++step) {
		PTR start = head;
		for (int i = 0; i < size - step - 1; ++i) {
			Sinhvien temp1 = start->sv;
			Sinhvien temp2 = start->lk2->sv;
			if (temp1.ten > temp2.ten) {
				start->sv = temp2;
				start->lk2->sv = temp1;
			}
			start = start->lk2;
		}
	}
}

void SapXepTheoMaSv(PTR head, int size) {
	for (int step = 0; step < size - 1; ++step) {
		PTR start = head;
		for (int i = 0; i < size - step - 1; ++i) {
			Sinhvien temp1 = start->sv;
			Sinhvien temp2 = start->lk2->sv;
			if (temp1.maso > temp2.maso) {
				start->sv = temp2;
				start->lk2->sv = temp1;
			}
			start = start->lk2;
		}
	}
}

int main() {
	PTR head = nullptr;
	int choice;
	do {
		cout << "\n1. Nhap danh sach sinh vien";
		cout << "\n2. Xoa sinh vien theo ma so";
		cout << "\n3. Tim sinh vien theo ma so";
		cout << "\n4. Liet ke DSSV tang dan theo ma so";
		cout << "\n5. Liet ke DSSV tang dan theo ten";
		cout << "\n6. Ket thuc";
		cout << "\nChon chuc nang: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			Sinhvien sv;
			do {
				cout << "Nhap ma so: "; cin >> sv.maso;
				if (searchStudent(head, sv.maso)) {
					cout << "Ma so da ton tai! Vui long nhap ma khac.\n";
				}
			} while (searchStudent(head, sv.maso));
			cout << "Nhap ho: "; cin.ignore(); cin.getline(sv.ho, 51);
			cout << "Nhap ten: "; cin.getline(sv.ten, 11);
			insertStudent(head, sv);
			break;
		}
		case 2: {
			int maso;
			cout << "Nhap ma so sinh vien can xoa: "; cin >> maso;
			deleteStudent(head, maso);
			break;
		}
		case 3: {
			int maso;
			cout << "Nhap ma so sinh vien can tim: "; cin >> maso;
			PTR found = searchStudent(head, maso);
			if (found) {
				cout << "Tim thay: " << found->sv.ho << " " << found->sv.ten << "\n";
			}
			else {
				cout << "Khong tim thay sinh vien!\n";
			}
			break;
		}
		case 4:
			SapXepTheoMaSv(head, studentNumber);
			displayByStudent(head);
			break;
		case 5:
			SapXepTheoTen(head, studentNumber);
			displayByStudent(head);
			break;
		}
	} while (choice != 6);
	return 0;
}

void insertStudent(PTR& head, Sinhvien sv) {
	PTR newNode = new node{ sv, nullptr, nullptr };

	if (!head || sv.maso < head->sv.maso) {
		newNode->lk2 = head;
		if (head) head->lk1 = newNode;
		head = newNode;
	}
	else {
		PTR p = head;
		while (p->lk2 && p->lk2->sv.maso < sv.maso) {
			p = p->lk2;
		}
		newNode->lk2 = p->lk2;
		if (p->lk2) p->lk2->lk1 = newNode;
		p->lk2 = newNode;
		newNode->lk1 = p;
	}
	studentNumber++;
}

void deleteStudent(PTR& head, int maso) {
	if (studentNumber == 0) return;
	PTR p = head;
	while (p && p->sv.maso != maso) {
		p = p->lk2;
	}
	if (!p) return;
	if (p->lk1) p->lk1->lk2 = p->lk2;
	if (p->lk2) p->lk2->lk1 = p->lk1;
	if (p == head) head = p->lk2;
	p->lk1 = nullptr;
	p->lk2 = nullptr;
	delete p;
	studentNumber--;
}

PTR searchStudent(PTR head, int maso) {
	while (head && head->sv.maso != maso) {
		head = head->lk2;
	}
	return head;
}

void displayByStudent(PTR head) {
	while (head) {
		cout << head->sv.maso << ": " << head->sv.ho << " " << head->sv.ten << "\n";
		head = head->lk2;
	}
}

