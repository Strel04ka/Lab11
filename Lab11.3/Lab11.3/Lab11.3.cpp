#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
using namespace std;
enum Spec { KN, In, ME, FI, TN };
string specStr[] = { "KN", "IN", "ME", "FI", "TN" };
struct Student {
	//char LastName[64];
	char LastName[64] = "Peter";

	int kurs;
	Spec spec;
	int Math, Physics, IT;
};
void Create(string filename)
{
	ofstream f(filename, ios::binary);
	int spec;
	char key;
	if (!f)
	{
		cerr << "Error opening file '" << filename << "'" << endl;
		return;
	}

	Student student;
	do
	{
		cout << endl;
		cout << "LastName:"; cin >> student.LastName;
		cout << "Kurs:"; cin >> student.kurs;
		cout << "Spec (KN - 0, In - 1, ME - 2, FI - 3, TN - 4): ";
		cin >> spec;
		student.spec = (Spec)spec;
		cout << "Math: "; cin >> student.Math;
		cout << "Physics: "; cin >> student.Physics;
		cout << "IT: "; cin >> student.IT;

		if (!f.write((char*)&student, sizeof(student))) cerr << "Error writing file." << endl;
		cout << "Continue? (Y/N) "; cin >> key;

	} while (key == 'y' || key == 'Y');
}
void Print(string filename)
{
	ifstream f(filename, ios::binary);
	int i = 1;
	if (!f)
	{
		cout << "Error opening file '" << filename << "'" << endl;
		return;
	}
	Student student;
	cout << "№\t|LN\t|Course\t|Speciality\t|Ph\t|IT\t|Maths" << endl;
	while (f.read((char*)&student, sizeof(student)))
	{
		cout << i
			<< "\t|" << student.LastName
			<< "\t|" << student.kurs
			<< "\t|\t" << specStr[student.spec]
			<< "\t|" << student.Physics
			<< "\t|" << student.IT
			<< "\t|" << student.Math
			<< endl;
		i++;
	}

}
void autoCreate(string filename)
{
	cout << "Enter size:";
	int size; cin >> size;
	ofstream fs(filename, ios::binary);
	for (size_t i = 0; i < size; i++)
	{
		Student st;
		st.IT = rand() % 5 + 1;
		st.Math = rand() % 5 + 1;
		st.Physics = rand() % 5 + 1;
		st.kurs = rand() % 3 + 1;
		st.spec = (Spec)(rand() % 5);
		fs.write((char*)&st, sizeof(st));
	}
	fs.close();
}
void fWrite(fstream& f, int i, Student x)
{
	f.seekp(i * (long)sizeof(Student));
	f.write((char*)&x, sizeof(Student));
}
Student fRead(fstream& f, const int i)
{
	Student x;
	f.seekg(i * sizeof(Student));
	f.read((char*)&x, sizeof(Student));
	return x;
}
void fChange(fstream& f, int i, int j)
{
	Student x = fRead(f, i);
	Student y = fRead(f, j);
	fWrite(f, i, y);
	fWrite(f, j, x);
}
void SortFiz(string FileName)
{
	fstream f(FileName, ios::binary | ios::in | ios::out | ios::ate);
	double ser, ser2;
	int size = f.tellg();
	int k = sizeof(Student);
	f.seekg(0, ios::beg);
	for (int i = 1; i < size / k; i++)
	{
		for (int j = 0; j < size / k - 1; j++)
		{
			Student a = fRead(f, j);
			Student b = fRead(f, j + 1);
			ser = (a.Math);
			ser2 = (b.Math);
			if ((a.spec > b.spec)
				||
				(a.spec == b.spec && ser < ser2)
				||
				(a.spec == b.spec && ser == ser2 && a.LastName > b.LastName))
				fChange(f, j, j + 1);
		}
	}
}
int BinSearch(string FileName, string iprizv)
{
	fstream f(FileName, ios::binary | ios::in | ios::out | ios::ate);
	int size = f.tellg();
	int k = sizeof(Student);
	f.seekg(0, ios::beg);
	double  ser, ser2;
	cout << "Math = "; cin >> ser2;
	int L = 0;
	int R = size / k - 1;
	int n;
	Student m;
	do {
		n = (L + R) / 2;
		m = fRead(f, n);
		ser = 0;
		ser = (m.Math);
		if ((string)m.LastName == (string)iprizv && ser2 == ser)
			return n;
		if (
			(ser > ser2)
			||
			(ser == ser2 && m.LastName < iprizv))	L = n + 1;
		else
		{
			R = n - 1;
		}
	} while (L <= R);
	return -1;
}

int r(fstream& FI, int i)
{
	int value;
	FI.seekg(i * sizeof(i));
	FI.read((char*)&value, sizeof(int));
	return value;
}
void w(fstream& FI, int i, int j)
{
	FI.seekg(i * sizeof(i));
	FI.write((char*)&j, sizeof(int));
}

void indexSort(string FileName, string FileNameI)
{
	fstream f(FileName, ios::binary | ios::in | ios::out);
	fstream FI(FileNameI, ios::binary | ios::in | ios::out | ios::trunc);

	f.seekg(0, ios::end);
	int size = f.tellg();
	int k = sizeof(Student);
	f.seekg(0, ios::beg);

	for (int i = 0; i < size / k; i++) {
		w(FI, i, i);
	}
	int i, j, value;
	double ser, ser2;
	for (i = 1; i < size / k; i++)
	{
		value = r(FI, i);
		ser = (fRead(f, r(FI, i)).Math);
		ser2 = (fRead(f, value).Math);
		for (j = i - 1; j >= 0 && ((fRead(f, r(FI, j)).spec > fRead(f, value).spec ||
			((fRead(f, r(FI, j)).spec == fRead(f, value).spec) && (ser > ser2)) ||
			((fRead(f, r(FI, j)).spec == fRead(f, value).spec) && (ser == ser2) && (fRead(f, r(FI, j)).LastName > fRead(f, value).LastName)))); j--)
		{
			w(FI, j + 1, r(FI, j));
		}
		w(FI, j + 1, value);
	}
	for (int i = 0; i < size / k; i++)
		cout << r(FI, i) << endl;
}

void printIndexSort(string FileName, string FileNameI)
{
	fstream f(FileName, ios::binary | ios::in | ios::out);
	fstream FI(FileNameI, ios::binary | ios::in | ios::out);
	f.seekg(0, ios::end);
	int size = f.tellg();
	int k = sizeof(Student);
	f.seekg(0, ios::beg);
	//fRead(f, r(FI, i))
	cout << "№\t|LN\t|Course\t|Speciality\t|Ph\t|IT\t|Maths" << endl;
	for (int i = 0; i < size / k; i++)
	{
		cout << i
			<< "\t|" << fRead(f, r(FI, i)).LastName
			<< "\t|" << fRead(f, r(FI, i)).kurs
			<< "\t|\t" << specStr[fRead(f, r(FI, i)).spec]
			<< "\t|" << fRead(f, r(FI, i)).Physics
			<< "\t|" << fRead(f, r(FI, i)).IT
			<< "\t|" << fRead(f, r(FI, i)).Math
			<< endl;
		i++;
	}
	cout << endl;
}
int main()
{
	string filename;
	string filenameI;
	Student student;
	int ikurs;
	string iLastName;
	int ispec;
	int iMath;
	int menuItem;
	do
	{
		cout << endl;
		cout << "====Menu=====" << endl;
		cout << "1.Create" << endl;
		cout << "2.Print file" << endl;
		cout << "3.Physics sort" << endl;
		cout << "4.Binary find" << endl;
		cout << "5.Index sort " << endl;
		cout << "=============" << endl;
		cout << endl;
		cout << "0.Exit" << endl;
		cout << "Slected value: "; cin >> menuItem;
		cout << endl;
		switch (menuItem)
		{
		case 1:
		{
			cout << "enter file name : "; cin >> filename; cout << endl;
			//Create(filename);
			autoCreate(filename);
			break;

		}
		case 2:
		{
			cout << "enter file name : "; cin >> filename; cout << endl;
			Print(filename);
			break;

		}
		case 3:
		{
			cout << "enter file name : "; cin >> filename; cout << endl;
			SortFiz(filename);
			break;

		}
		case 4:
		{
			cout << "enter file name : "; cin >> filename;
			cin.sync();
			cout << " LastName: "; cin >> iLastName; cin.sync();
			cin.sync();
			cout << endl;
			cout << "Number = " << BinSearch(filename, iLastName) << endl;
			break;

		}
		case 5:
		{
			cout << "enter file name : "; cin >> filename; cout << endl;
			cout << "enter Index file name : "; cin >> filenameI; cout << endl;
			indexSort(filename, filenameI);
			printIndexSort(filename, filenameI);
			break;

		}
		case 0:
			break;
		default:
			cout << "ERROR!!!" << endl;
		}

	} while (menuItem != '0');
	system("pause");
	return 0;
}
