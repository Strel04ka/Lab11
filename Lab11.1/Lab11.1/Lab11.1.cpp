#include <iostream>
#include <fstream> 
#include <string> 
#include <Windows.h>
/*Варіант 5.
Сформувати файл даних, компонентами якого є цілі числа.
Переписати в інший файл даних ті компоненти, які можуть бути значеннями функції
cos x.
Вивести на екран вміст результуючого файлу.*/
using namespace std;

void CreateBIN(string filename)
{
	ofstream fout(filename, ios::binary);
	char ch;
	double s;
	do {
		cin.sync();
		cout << "enter number: ";
		cin >> s;
		fout.write((char*)&s, sizeof(s));
		cout << "continue? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << endl;
}

void PrintBIN(string filename)
{
	ifstream fin(filename, ios::binary);
	double c;
	cout << "==========" << filename << "==========" << endl << endl;
	while (fin.read((char*)&c, sizeof(c)))
	{
		cout << c << " ";
	}
	cout << endl;
	cout << endl << "============================" << endl;
}

void ProcessBIN1(string filename)
{
	ifstream fin(filename, ios::binary);
	filename.insert(filename.end() - 4, '2');
	ofstream fout(filename, ios::binary);
	double c;
	while (fin.read((char*)&c, sizeof(c)))
	{
		if (c >= -1 && c <= 1)
			fout.write((char*)&c, sizeof(c));
	}
	fin.close();
	fout.close();
	PrintBIN(filename);
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string filename;
	cout << "Enter file name: "; cin >> filename;;
	cout << "1.Create a file and process\n2.Only file processing" << endl;
	int ch; cin >> ch;
	switch (ch)
	{
	case 1:
	{
		CreateBIN(filename);
		PrintBIN(filename);
		ProcessBIN1(filename);
		break;
	}
	case 2:
	{
		PrintBIN(filename);
		ProcessBIN1(filename);
		break;
	}
	default:
		break;
	}
	system("pause");
}
