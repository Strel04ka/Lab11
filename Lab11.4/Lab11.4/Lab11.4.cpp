#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
struct departuretime;
struct departuretime
{
	departuretime() { HH = MM = 0; }
	departuretime(unsigned int hh, unsigned int mm)
	{
		HH = hh, MM = mm;
	}
	unsigned int HH : 5;
	unsigned int MM : 6;
};
struct Grafik
{
	string Caption;
	enum type { normal, comfortplus, speedexpres } Type;
	departuretime Deaprturetime;
};
Grafik Parse(string str);
void savetofile(Grafik* arr, int size, string filename);
void Add();
void AutoFill();
void StartMenu();
void Print(string str);
void Remove();
void Change();
void SortRoutes();
void SeekByTime();
Grafik* addroutetolis(Grafik* arr, int& size, Grafik obj);

void fWrite(fstream& f, int i, Grafik x)
{
	f.seekp(i * (long)sizeof(Grafik));
	f.write((char*)&x, sizeof(Grafik));
}
Grafik fRead(fstream& f, const int i)
{
	Grafik x;
	f.seekg(i * sizeof(Grafik));
	f.read((char*)&x, sizeof(Grafik));
	return x;
}
void fChange(fstream& f, int i, int j)
{
	Grafik x = fRead(f, i);
	Grafik y = fRead(f, j);
	fWrite(f, i, y);
	fWrite(f, j, x);
}
void main()
{
	srand(time(NULL));
	setlocale(LC_CTYPE, "ukr");
	AutoFill();
	StartMenu();


	system("pause");
}
void AutoFill()
{
	string filename;
	cout << "Filename:"; cin >> filename;
	ofstream fout;
	fout.open(filename, ios::binary);

	cout << "Enter the count of marchroots in the array:"; int size; cin >> size;
	for (size_t i = 0; i < size; i++)
	{
		Grafik gr;
		gr.Caption = "Binych" + to_string(i);
		gr.Type = Grafik::normal;
		gr.Deaprturetime = departuretime((unsigned int)(rand() % 24), (unsigned int)(rand() % 60));
		string serialize = gr.Caption + "^" + to_string((int)gr.Type) + "^" + to_string((int)gr.Deaprturetime.HH) + "^" + to_string((int)gr.Deaprturetime.MM);
		fout << serialize << endl;
	}
	fout.close();
}
void Print(string filename = "")
{
	if (filename == "")
		cout << "Filename:"; cin >> filename;
	ifstream fin;
	fin.open(filename, ios::binary);
	string str; int i = 0;
	cout << "№\t|Name\t|Type\t|Departure Time |" << endl;
	while (getline(fin, str))
	{
		Grafik gr = Parse(str);
		cout << i << "\t|";
		cout << gr.Caption << "\t|";
		switch (gr.Type)
		{
		case Grafik::normal: { cout << "normal\t|";			break; }
		case Grafik::speedexpres: { cout << "fastexpress\t|";	break; }
		case Grafik::comfortplus: { cout << "comfortplus\t|";	break; }
		default:
			break;
		}
		cout << gr.Deaprturetime.HH << ":" << gr.Deaprturetime.MM << "|";
		cout << endl;
		i++;
	}
}
Grafik Parse(string str)
{
	Grafik gr;
	gr.Caption = str.substr(0, str.find_first_of("^"));
	str.erase(0, str.find_first_of("^") + 1);
	if (str[0] == '0')
		gr.Type = Grafik::type::normal;
	else if (str[0] == '1')
		gr.Type = Grafik::type::comfortplus;
	else
		gr.Type = Grafik::type::speedexpres;
	str.erase(0, str.find_first_of("^") + 1);
	string hh = str.substr(0, 2);
	gr.Deaprturetime.HH = atoi(hh.c_str());
	str.erase(0, 3);
	gr.Deaprturetime.MM = atoi(str.c_str());
	return gr;
}
void Add()
{
	string filename;
	cout << "Filename:"; cin >> filename;
	ifstream fin;
	fin.open(filename, ios::binary);
	string str; int i = 0;
	Grafik newgrafik;
	cout << "Caption:"; cin >> newgrafik.Caption;
	cout << "Type:(0.normal\t1.fastexpress\t 2.comfortplus)\n";
	int ch; cin >> ch;
	switch (ch)
	{
	case 0:
	{
		newgrafik.Type = (Grafik::type)ch;
		break;
	}
	case 1:
	{
		newgrafik.Type = (Grafik::type)ch;
		break;
	}
	case 2:
	{
		newgrafik.Type = (Grafik::type)ch;
		break;
	}
	default:
		break;
	}
	cout << "Departure time:\n";
	int hh, mm;
	cout << "Hours:"; cin >> hh;
	cout << "Minutes: "; cin >> mm;
	if (hh > 24) hh %= 24;
	if (mm > 60)mm %= 60;
	newgrafik.Deaprturetime = departuretime(hh, mm);

	while (getline(fin, str))
	{
		i++;
	}
	Grafik* newroutes = new Grafik[i + 2];
	fin.close();
	ifstream fin2;
	fin2.open(filename);
	int j = 0;
	while (getline(fin2, str))
	{
		newroutes[j] = Parse(str);
		j++;
	}
	newroutes[i] = newgrafik;
	fin2.close();
	savetofile(newroutes, i + 1, filename);
}
void Remove()
{
	string filename;
	cout << "Filename:"; cin >> filename;
	ifstream fin;
	fin.open(filename, ios::binary);
	Grafik* routes = new Grafik[0];
	int size = 0;
	string str;
	while (getline(fin, str))
	{
		routes = addroutetolis(routes, size, Parse(str));
	}
	Grafik* newroutes = new Grafik[size];
	cout << "Enter the index of a marchroot which you want to remove: ";
	int index;
	cin >> index;
	bool moved = false;
	for (size_t i = 0; i < size - 1; i++)
	{
		if (i == index)  	moved = true;
		if (moved)	newroutes[i] = routes[i + 1];
		else	newroutes[i] = routes[i];
	}
	--size;
	savetofile(newroutes, size, filename);
}
void StartMenu()
{
	int choice;
	do
	{
		cout << "------------Menu------------" << endl;
		cout << "1.Додати маршрут.\n" <<
			"2.Видалити маршрут\n" <<
			"3.Редагувати маршрут\n" <<
			"4.Сортувати розклад\n" <<
			"5.Ввести час.\n" <<
			"6.Показати всі маршрути\n" <<
			"7.Exit.\n" << endl << endl;
		cout << "Your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			Add();
			break;
		}
		case 2:
		{
			Remove();
			break;
		}
		case 3:
		{
			Change();
			break;
		}
		case 4:
		{
			SortRoutes();
			break;
		}
		case 5:
		{
			SeekByTime();
			break;
		}
		case 6:
		{
			Print("");
			break;
		}
		default:
			break;
		}
	} while (choice != 7);
}
void Change()
{
	string filename;
	cout << "Filename:"; cin >> filename;
	string str;
	//Print(filename);
	ifstream fin;
	cout << endl << endl;
	cout << "Enter the index of the element which you want to change: ";
	int choice; cin >> choice;
	fin.open(filename, ios::binary);
	Grafik* routes = new Grafik[0];
	int size = 0, i = 0;
	while (getline(fin, str))
	{
		routes = addroutetolis(routes, size, Parse(str));
		if (i == choice)
		{
			cout << "Name of route:"; cin >> routes[choice].Caption; cout << endl;
			short int ch;
			cout << "type of route:"; cin >> ch; cout << endl;
			switch (ch)
			{
			case 0: { routes[choice].Type = Grafik::normal;	  break; }
			case 1: { routes[choice].Type = Grafik::comfortplus; break; }
			case 2: { routes[choice].Type = Grafik::speedexpres; break; }
			default: {
				cout << "Invalid command.The property is defined as normal." << endl;
				routes[choice].Type = Grafik::normal;
				break;
			}
			}
			int a, b;
			cout << "Departure time: "; cin >> a >> b;
			routes[choice].Deaprturetime = departuretime(a, b);
		}
		i++;
	}
	savetofile(routes, i, filename);
}
Grafik* addroutetolis(Grafik* arr, int& size, Grafik obj)
{
	Grafik* arr2 = new Grafik[size + 1];
	for (size_t i = 0; i < size; i++)
	{
		arr2[i] = arr[i];
	}
	arr2[size] = obj;
	size++;
	return arr2;
}
void SortRoutes()
{

	string filename;
	cout << "Filename:"; cin >> filename;
	fstream f(filename, ios::binary | ios::in | ios::out | ios::ate);
	int size = f.tellg();
	int k = sizeof(Grafik);
	f.seekg(0, ios::beg);
	Grafik* arr = new Grafik[0];
	Grafik sl;
	int choice;
	system("cls");
	cout << "===sorting menu===" << endl << endl;
	cout << "1.Sort by name of stations.\n" <<
		"2.Sort by departure time." << endl;
	cout << "Enter the method which you want to sort the list: ";
	cin >> choice; cout << endl;
	switch (choice)
	{
	case 1:
	{
		for (int i = 1; i < size / k; i++)
		{
			for (int j = 0; j < size / k - 1; j++)
			{
				Grafik a = fRead(f, j);
				Grafik b = fRead(f, j + 1);
				if (a.Caption > b.Caption)
					fChange(f, j, j + 1);

			}

		}
		cout << "done." << endl;
		break;
	}
	case 2:
	{
		for (int i = 1; i < size / k; i++)
		{
			for (int j = 0; j < size / k - 1; j++)
			{
				Grafik a = fRead(f, j);
				Grafik b = fRead(f, j + 1);
				if ((a.Deaprturetime.HH >= b.Deaprturetime.HH))
					fChange(f, j, j + 1);
			}
		}
		cout << "done." << endl;
		break;
	}
	default:
		break;
	}
}
void SeekByTime()
{
	string filename;
	cout << "Filename:"; cin >> filename;
	string str;
	ifstream fin;
	fin.open(filename, ios::binary);
	cout << "Enter the time after which you want to see the routes: ";
	int hh, mm;
	cin >> hh, mm;
	cout << endl << endl;
	int i = 0;
	cout << "№\t|Name\t|Type\t|Departure Time |" << endl;
	while (getline(fin, str))
	{
		Grafik route = Parse(str);
		if ((route.Deaprturetime.HH > hh))
		{
			cout << i << "\t|";
			cout << route.Caption << "\t|";
			switch (route.Type)
			{
			case Grafik::normal: { cout << "normal\t|";			break; }
			case Grafik::speedexpres: { cout << "fastexpress\t|";	break; }
			case Grafik::comfortplus: { cout << "comfort plus\t|";	break; }
			default:break;
			}
			cout << route.Deaprturetime.HH << ":" << route.Deaprturetime.MM << "|" << endl;

		}
		i++;
	}
}
void savetofile(Grafik* arr, int size, string filename)
{
	ofstream fout;
	fout.open(filename, ios::binary);
	for (size_t i = 0; i < size; i++)
	{
		Grafik gr = arr[i];
		string serialize = gr.Caption + "^" + to_string((int)gr.Type) + "^" + to_string((int)gr.Deaprturetime.HH) + "^" + to_string((int)gr.Deaprturetime.MM);
		fout << serialize << endl;
	}
	fout.close();
}
