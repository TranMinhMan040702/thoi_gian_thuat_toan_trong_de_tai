#include<iostream>
#include<string.h>
#include<stdio.h>
#include<cstdio>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<Windows.h>
#include<time.h>

using namespace std;

// tạo cấu trúc danh bạ
struct Phonebook
{
	char name[30];
	char numberPhone[20];
	char option[10];
};
typedef struct Phonebook PHONEBOOK;

// tạo cấu trúc cho 1 Node trong danh sách liên kết 
struct Node
{
	PHONEBOOK* data;
	Node* pNext;
};
typedef struct Node NODE;

// tạo cấu trúc cho một danh sách liên kết để quản lý danh bạ
struct List
{
	NODE* pHead;
	NODE* pTail;
};
typedef struct List LIST;

// hàm khởi tạo một danh sách liên kết
void Initialize(LIST& list)
{
	list.pHead = nullptr;
	list.pTail = nullptr;
}

void gotoxy(SHORT posX, SHORT posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX;
	Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}
// hàm khởi tạo thông tin của 1 số điện thoại trong danh bạ
PHONEBOOK* input_Phonebook()
{

	PHONEBOOK* pb = new PHONEBOOK;
	cout << "Nhap so dien thoai: ";
	cin.ignore();
	gets_s(pb->numberPhone);
	int m = strlen(pb->numberPhone);
	while (m != 10)
	{
		cout << "So dien thoai khong hop le !\n";
		cout << "Vui long nhap lai so dien thoai: ";
		gets_s(pb->numberPhone);
		m = strlen(pb->numberPhone);
	}
	cout << "Nhap ten: ";
	gets_s(pb->name);
	int n;
	cout << "================================================================\n";
	cout << "|              BAN HAY LUU CHON CHUC NANG LUU                  |\n";
	cout << "================================================================\n";
	cout << "----------------------------------------------------------------\n";
	cout << "|      1.gia dinh      |      2.ban be        |    3.cong viec |\n";
	cout << "----------------------------------------------------------------\n";
	cout << "ban nhap lua chon: ";
	cin >> n;
	if (n == 1)
	{
		strcpy_s(pb->option, "gia dinh");
	}
	else if (n == 2)
	{
		strcpy_s(pb->option, "ban be");
	}
	else
	{
		strcpy_s(pb->option, "cong viec");
	}
	return pb;
}

// hàm khởi tạo một Node trong danh sách liên kết
NODE* CreateNode(PHONEBOOK* pb)
{
	NODE* p = new NODE;
	if (p == nullptr)
	{
		cout << "Not enough memory ! ";
		return nullptr;
	}
	p->data = pb;
	p->pNext = nullptr;
	return p;
}

// hàm thêm 1 số điện thoại vào cuối danh sách
void insertFirst(LIST& list, PHONEBOOK* pb)
{
	NODE* pNode = CreateNode(pb);
	if (list.pHead == nullptr)
	{
		list.pHead = list.pTail = pNode;
	}
	else
	{
		list.pTail->pNext = pNode;
		list.pTail = pNode;
	}
}

// In danh bạ ra màng hình
void printPhonebook(LIST list)
{
	NODE* pNode = list.pHead;
	if (pNode == nullptr)
	{
		cout << "Danh ba rong !\n";
		return;
	}
	else
	{
		cout << "================================================================\n";
		cout << "| So Dien Thoai |               Ten               |   Option   |\n";
		cout << "================================================================\n";
	}
	while (pNode != nullptr)
	{
		int length_name = strlen(pNode->data->name);
		int length_option = strlen(pNode->data->option);
		PHONEBOOK* pb = pNode->data;
		cout << "|  " << pb->numberPhone << "   | " << pb->name;
		int space;
		space = 33 - length_name - 1;
		while (space != 0)
		{
			cout << " ";
			space--;
		}
		cout << "| " << pb->option;
		space = 12 - length_option - 1;
		while (space != 0)
		{
			cout << " ";
			space--;
		}
		cout << "|\n";
		cout << "----------------------------------------------------------------\n";
		pNode = pNode->pNext;
	}
}

//sắp xếp danh bạ theo tên
int Test(char c1[], char c2[])
{
	// chuyển từ chữi hoa sang chữi thường

	int length1 = strlen(c1);
	int length2 = strlen(c2);
	char str1[30] = "/0";
	char str2[30] = "/0";
	int i;

	for (i = 0; i < length1; i++)
	{
		str1[i] = c1[i];
		if (str1[i] >= 65 && str1[i] <= 90)
			str1[i] = str1[i] + 32;
	}


	for (i = 0; i < length2; i++)
	{
		str2[i] = c2[i];
		if (str2[i] >= 65 && str2[i] <= 90)
			str2[i] = str2[i] + 32;
	}


	// bắt đầu so sánh
	if (strcmp(str1, str2) > 0)
		return 1;
	else if (strcmp(str1, str2) < 0)
		return 2;
	return 0;
}
LIST insertionSort_List(LIST list)
{
	NODE* curr = list.pHead;
	LIST sort;
	Initialize(sort);
	while (curr != nullptr)
	{
		NODE* currNext = curr->pNext;
		if (sort.pHead == nullptr ||
			Test(sort.pHead->data->name, curr->data->name) == 1 ||
			Test(sort.pHead->data->name, curr->data->name) == 0)
		{
			curr->pNext = sort.pHead;
			sort.pHead = curr;
		}
		else
		{
			NODE* currTemp = sort.pHead;
			while (currTemp->pNext != nullptr && Test(currTemp->pNext->data->name, curr->data->name) == 2)
			{
				currTemp = currTemp->pNext;
			}
			curr->pNext = currTemp->pNext;
			currTemp->pNext = curr;

		}
		curr = currNext;
	}
	return sort;
}
void ghi_fie(LIST list, char filename[])
{
	FILE* f;
	fopen_s(&f, filename, "wb");
	if (f == NULL)
		return;
	NODE* pNode = list.pHead;
	while (pNode != nullptr)
	{
		fwrite(pNode->data, sizeof(Phonebook), 1, f);
		pNode = pNode->pNext;
	}
	fclose(f);
}
void insertion_PhoneBook(LIST& list, PHONEBOOK* pb)
{

	NODE* pNode = CreateNode(pb);
	if (list.pHead == nullptr)
	{
		list.pHead = list.pTail = pNode;
	}
	else
	{
		NODE* temp = list.pHead;
		if (strcmp(temp->data->name, pNode->data->name) >= 0)
		{
			pNode->pNext = list.pHead;
			list.pHead = pNode;
			return;
		}
		while (temp->pNext != nullptr)
		{
			if (strcmp(temp->pNext->data->name, pNode->data->name) >= 0)
			{
				break;
			}
			else
				temp = temp->pNext;
		}
		pNode->pNext = temp->pNext;
		temp->pNext = pNode;
	}
}
LIST Handle(LIST list, char c[])
{
	LIST option;
	Initialize(option);
	NODE* k;
	for (k = list.pHead; k != nullptr; k = k->pNext)
	{
		if (Test(k->data->option, c) == 0)
		{
			insertFirst(option, k->data);
		}
	}
	option = insertionSort_List(option);
	return option;
}
void file_out(LIST& l, char filename[])
{
	FILE* f;
	fopen_s(&f, filename, "rb");
	PHONEBOOK pb;
	PHONEBOOK s[10000];
	if (f == NULL)
		return;

	fread(&pb, sizeof(pb), 1, f);
	int i = 0;
	while (!feof(f))
	{
		s[i] = pb;
		fread(&pb, sizeof(pb), 1, f);
		insertFirst(l, &s[i]);
		i++;
	}

	fclose(f);

}
LIST Delete(LIST list, int cnt)
{

	if (cnt == 1)
	{
		NODE* remove = list.pHead;
		if (list.pHead->pNext == NULL) list.pHead = NULL;
		else list.pHead = list.pHead->pNext;
		delete remove;
		cout << "\nXoa thanh cong !\n";
		return list;
	}
	NODE* temp = list.pHead;
	for (int i = 1; i < cnt - 1; i++) {
		temp = temp->pNext;
	}
	NODE* remove = temp->pNext;
	temp->pNext = temp->pNext->pNext;
	delete remove;
	return list;
}
void xoamanhinh()
{
	for (int i = 0; i < 67; i = i + 22)
	{
		for (int j = 0; j < 50; j++)
		{
			gotoxy(i, j); cout << "                      ";
		}
	}
}
void Change(int cnt)
{

	fstream file;
	PHONEBOOK pb;
	file.open("data.txt", ios::ate | ios::in | ios::out | ios::binary);
	file.seekg(0, ios::beg);
	char nm[30];
	char telno[20];
	int found = 0;
	int location = (cnt - 1) * sizeof(pb);
	if (file.eof())
		file.clear();
	cout << "Nhap ten: ";
	cin.ignore();
	gets_s(nm);
	cout << "Nhap so dien thoai: ";
	gets_s(telno);
	int m = strlen(telno);
	while (m != 10)
	{
		cout << "So dien thoai khong hop le !\n";
		cout << "Vui long nhap lai so dien thoai: ";
		gets_s(telno);
		m = strlen(telno);
	}
	int n;
	cout << "================================================================\n";
	cout << "|              BAN HAY LUU CHON CHUC NANG LUU                  |\n";
	cout << "================================================================\n";
	cout << "----------------------------------------------------------------\n";
	cout << "|      1.gia dinh      |      2.ban be        |    3.cong viec |\n";
	cout << "----------------------------------------------------------------\n";
	cout << "ban nhap lua chon: ";
	cin >> n;
	if (n == 1)
	{
		strcpy_s(pb.option, "gia dinh");
	}
	else if (n == 2)
	{
		strcpy_s(pb.option, "ban be");
	}
	else
	{
		strcpy_s(pb.option, "cong viec");
	}
	file.seekp(location);
	strcpy_s(pb.name, nm);
	strcpy_s(pb.numberPhone, telno);
	file.write((char*)&pb, sizeof(pb));
	file.flush();
}

void lienhe(int cnt, LIST& l)
{
	fstream file;
	PHONEBOOK pb;
	file.open("data.txt", ios::ate | ios::in | ios::out | ios::binary);
	file.seekg(0, ios::beg);
	int location = (cnt - 1) * sizeof(pb);
	file.seekp(location);
	file.read((char*)&pb, sizeof(pb));
	xoamanhinh();
	gotoxy(0, 0);
	cout << "============================================\n";
	cout << "|                 Lien he                  |\n";
	cout << "============================================";
	gotoxy(0, 3); cout << "| So dien thoai: " << pb.numberPhone; gotoxy(43, 3); cout << "|";
	gotoxy(0, 4); cout << "| Ten          : " << pb.name; gotoxy(43, 4); cout << "|";
	gotoxy(0, 5); cout << "| Option       : " << pb.option; gotoxy(43, 5); cout << "|\n";
	cout << "============================================\n";
	cout << "| 1. Xoa     | 2. Chinh sua  | 0.Thoat     |\n";
	cout << "============================================\n\n";
	cout << "Nhap lua chon: ";
	int select;
	cin >> select;
	file.close();
	if (select == 1)
	{
		char filename2[] = "data.txt";
		ghi_fie(Delete(l, cnt), filename2);
		cout << "\nXoa thanh cong !\n";
	}
	else if (select == 2)
	{
		Change(cnt);
		cout << "\nChinh sua thanh cong !\n";
	}
	else if (select == 0) {
		return;
	}
	else
	{
		cout << "\nLua chon khong hop le, vui long chon lai !\n";
		system("pause");
	}

}
void search(char key[], LIST& l)
{
	clock_t start, end;   // Khai báo biến thời gian
	double time_use;      // Thời gian sử dụng
	start = clock();

	fstream file;
	PHONEBOOK pb;
	file.open("data.txt", ios::ate | ios::in | ios::out | ios::binary);
	file.seekg(0, ios::beg);
	int found = 0; int cnt = 0;
	int stt = 0;//stt dieenj thoai
	vector <int> diachi;
	xoamanhinh();
	gotoxy(0, 0);
	cout << "\nKet qua cua tu khoa tim kiem '" << key << "':\n\n";
	cout << "===================================================================\n";
	cout << "|  | So Dien Thoai |               Ten               |   Option   |\n";
	cout << "===================================================================\n";
	while (file.read((char*)&pb, sizeof(pb)))
	{
		int test = 0;
		cnt++;
		for (int i = 0; i < strlen(key); i++)
		{
			if (key[i] == pb.name[i] || key[i] == pb.numberPhone[i])
			{
				test++;
			}
		}
		if (test == strlen(key))
		{
			diachi.push_back(cnt);
			stt++;
			found = 1;
			cout << stt;
			cout << "|" << pb.numberPhone;
			gotoxy(19, 4 + 2 * stt); cout << "|  " << pb.name;
			gotoxy(53, 4 + 2 * stt); cout << "| " << pb.option;
			gotoxy(66, 4 + 2 * stt); cout << "|";
			cout << "\n-------------------------------------------------------------------\n";
		}
	}

	end = clock();
	time_use = (double)(end - start) / CLOCKS_PER_SEC;
	cout << time_use;

	if (found == 0)
	{
		cout << "|     Khong tim thay danh ba                                      |\n";
		cout << "-------------------------------------------------------------------\n";

		end = clock();
		time_use = (double)(end - start) / CLOCKS_PER_SEC;
		cout << time_use;
	}
	else
	{

		int chon;
		file.close();
		cout << "Chon danh ba ban muon thao tac: ";
		cin >> chon;
		if (chon > 0 && chon <= stt)
		{
			lienhe(diachi[chon - 1], l);

		}
		else {
			cout << "khong co lien he";
		}
	}
}
void FreeUpMemory(LIST& list)
{
	NODE* pNode = new NODE;
	while (list.pHead != nullptr)
	{
		pNode = list.pHead;
		list.pHead = list.pHead->pNext;
		delete pNode;
	}
}
void Menu(LIST& list)
{
	int key;
	char keysearch[30];
	while (true)
	{

		system("cls");
		cout << "\n\n\t\t========== Menu ==========";
		cout << "\n\t\t1.Them mot so dien thoai";
		cout << "\n\t\t2.Xuat danh ba";
		cout << "\n\t\t3.Xuat danh ba voi lua chon la FAMILY";
		cout << "\n\t\t4.Xuat danh ba voi lua chon la FRIEND";
		cout << "\n\t\t5.Xuat danh ba voi lua chon la WORK";
		cout << "\n\t\t6.Tim kiem";
		cout << "\n\t\t0.Thoat";

		cout << "\n\n\t\t========== End ==========";
		cout << "\nNhap lua chon: ";
		cin >> key;

		switch (key)
		{
		case 0:
		{
			exit(1);
		}
		case 1:
		{
			char filename2[] = "data.txt";
			file_out(list, filename2);
			PHONEBOOK* pb = input_Phonebook();
			double tong = 0;
			double max = INT_MIN;
			double min = INT_MAX;
			for (int i = 0; i < 1000; i++)//số lần đo
			{
				clock_t start, end;   // Khai báo biến thời gian
				double time_use;      // Thời gian sử dụng
				start = clock();
				for (int i = 0; i < 5; i++)//số phần tử chèn mỗi lần đo
				{
					insertion_PhoneBook(list, pb);
					ghi_fie(list, filename2);
				}
				end = clock();
				time_use = (double)(end - start) / CLOCKS_PER_SEC;
				cout << time_use << "\n";
				if (time_use > max)
				{
					max = time_use;
				}
				if (time_use < min)
				{
					min = time_use;
				}

				tong += time_use;
			}
			cout << "min:" << min << "\n";
			cout << "max:" << max << "\n";
			cout << "mean:" << tong / 1000;
			//printPhonebook(list);
			system("pause");
			FreeUpMemory(list);
			break;
		}
		case 2:
		{
			char filename2[] = "data.txt";
			LIST listn;
			Initialize(listn);
			file_out(listn, filename2);

			clock_t start, end;   // Khai báo biến thời gian
			double time_use;      // Thời gian sử dụng
			start = clock();

			listn = insertionSort_List(listn);
			end = clock();
			time_use = (double)(end - start) / CLOCKS_PER_SEC;
			printPhonebook(listn);
			cout << time_use;

			system("pause");
			break;
		}
		case 3:
		{

			char filename2[] = "data.txt";
			char c[] = "gia dinh";
			LIST family;
			Initialize(family);
			file_out(family, filename2);
			family = Handle(family, c);

			printPhonebook(family);
			system("pause");
			break;
		}
		case 4:
		{

			char filename2[] = "data.txt";
			char c[] = "ban be";
			LIST family;
			Initialize(family);
			file_out(family, filename2);
			family = Handle(family, c);

			printPhonebook(family);
			system("pause");
			break;
		}
		case 5:
		{

			char filename2[] = "data.txt";
			char c[30] = "cong viec";
			LIST family;
			Initialize(family);
			file_out(family, filename2);
			family = Handle(family, c);
			printPhonebook(family);
			system("pause");
			break;
		}
		case 6:
		{
			cout << "Nhap tu khoa tim kiem:";
			char key[100];
			cin >> key;
			char filename2[] = "data.txt";
			LIST l;
			Initialize(l);
			file_out(l, filename2);
			search(key, l);
			system("pause");
			break;
		}
		default:
		{
			cout << "Lua chon khong hop le, vui long chon lai !\n";
			system("pause");
			break;
		}
		}
	}
}
int main()
{
	//ifstream myFile;
	LIST list;
	Initialize(list);
	Menu(list);
	return 0;
}