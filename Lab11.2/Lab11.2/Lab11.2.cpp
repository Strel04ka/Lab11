#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
using namespace std;
enum Special { KN, IN, ME, FI, WT };
string Specialities[5] = { "KN","IN","ME","FI","TTI" };
struct Student {
	char LastName[60];
	int Curs;
	int Fiz;
	int Math;
	int IT;
	Special Type_Special;
};

void Print();
void AutoInput();
void UserInput();
void Vidminniki();
void HighMark();
int main()
{
	srand(time(NULL));
	int choice;
	do
	{
		cout << "====Menu====" << endl;
		cout << "1.Create a file of students." << endl;
		cout << "2.Print array" << endl;
		cout << "3.Vidminniki" << endl;
		cout << "4.Get count of cons in Physics" << endl;
		cout << endl;
		cout << "Enter your choice: "; cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
		{
			UserInput();
			//AutoInput();
			break;
		}
		case 2:
		{
			Print();
			break;
		}
		case 3:
		{
			Vidminniki();
			break;
		}
		case 4:
		{
			HighMark();
			break;
		}
		default:
		{
			cout << "You entered the incorrect command." << endl;
			break;
		}
		}
	} while (choice != 0);
	system("pause");
}

void Print()//HERE
{
	string filename;
	cout << "Enter filename: "; cin >> filename;
	ifstream fin;
	fin.open(filename, ios::binary);

	cout << endl;
	cout << "========================================================" << endl;
	cout << "Number \t|Name\t|Course   |\tSpec\t | Phys|Math |Progr.|" << endl;
	cout << "========================================================" << endl;
	int i = 0;
	Student st;
	while (fin.read((char*)&st, sizeof(Student)))
	{
		cout << i << "\t| " << st.LastName;
		cout << " |\t" << st.Curs;
		cout << " |\t" << Specialities[(int)st.Type_Special] << "\t";
		cout << " |" << setw(3) << st.Fiz << setw(3);
		cout << " |" << setw(3) << st.Math << setw(3);
		cout << " | " << setw(3) << st.IT << setw(3);
		cout << endl;
		i++;
	}
	cout << "=======================================================" << endl;
	cout << endl << endl;
	fin.close();
}
void AutoInput()
{
	int size, i = 0; string filename;
	cout << "Enter size: "; cin >> size;
	cout << "Filename: "; cin >> filename;
	ofstream fout(filename, ios::binary);

	Student st;
	while (i < size)
	{
		st.Curs = rand() % 5 + 1;
		st.Fiz = rand() % 5 + 1;
		st.Math = rand() % 5 + 1;
		st.Type_Special = (Special)(rand() % 5);
		st.IT = rand() % 5 + 1;
		fout.write((char*)&st, sizeof(st));
		i++;
	}
	fout.close();
}
void UserInput()
{
	string filename;
	cout << "Filename: "; cin >> filename;
	ofstream fout(filename, ios::binary);
	Student st;
	char ch = 'y';
	do
	{
		cout << "Last Name: "; cin >> st.LastName;
		cout << "Course: "; cin >> st.Curs;
		int t;
		cout << "(O.KN\t1.IN\t2.ME\t3.FI\t4.TTI)";
		cout << "Speciality: "; cin >> t;
		switch (t)
		{
		case 0:
		{
			st.Type_Special = Special::KN;
			break;
		}
		case 1:
		{
			st.Type_Special = Special::IN;
			break;
		}
		case 2:
		{
			st.Type_Special = Special::ME;
			break;
		}
		case 3:
		{
			st.Type_Special = Special::FI;
			break;
		}
		case 4:
		{
			st.Type_Special = Special::WT;
			break;
		}
		default:
		{
			cout << "You entered the incorrect data!" << endl;
			return;
		}
		}
		cout << "Physeics mark: "; cin >> st.Fiz;
		cout << "Math mark: "; cin >> st.Math;
		int mark;
		cout << "IT mark: "; cin >> mark;
		st.IT = mark;
		fout.write((char*)&st, sizeof(st));
		cout << "Continue?:(y/n)"; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	fout.close();
}
void Vidminniki()
{
	string filename;
	cout << "Enter filename: "; cin >> filename;
	ifstream fin(filename, ios_base::binary);
	int i = 0;
	Student st;
	while (fin.read((char*)&st, sizeof(Student)))
	{
		if (st.Fiz == 5)
			cout << st.LastName << " , ";
	}
	cout << "are studying exelent." << endl;
	fin.close();
}
void HighMark()
{
	int k = 0;;
	string filename;
	cout << "Enter filename: "; cin >> filename;
	ifstream fin(filename, ios_base::binary);
	Student st;
	while (fin.read((char*)&st, sizeof(Student)))
	{
		if (fin.eof()) break;
		if (st.Fiz > 4 && st.Math > 4 && st.IT > 4)
			k++;
	}
	cout << k << "students have 5 " << endl;
}
