//UTF-8
#include<iostream>
#include<fstream>//for file io
#include<io.h>//for using function access()
#include"SIM.h"

//private
//link list func
bool SIM::savedb()
{
	using namespace std;
	if (head == NULL)
	{
		cout << "Nothing there.\n";
		return true;
	}
	Stu* p;
	p = head;
	//check si.txt
	ofstream file("si.txt");//delete and write file
	if (!file)
	{
		cout << "Unknown error. Saving canceled.\n";
		return false;//file doesn't exist
	}
	cout << "Checking complete.";
	//start save file
	p = head;
	cout << "Saving...\n" << endl;
	while (p)
	{
		file << '0' << p->id << p->name << '\t' << p->sex << p->building << '\t' << p->room << endl;
		p = p->next;
	}
	file << '1';
	file.close();
	return true;//complete saving
}

bool SIM::push(Stu* p)
{
	if (head == NULL)
	{
		head = tail = p;
		head->next = NULL;
	}
	else
	{
		tail->next = p;
		tail = p;
	}
	tail->next = NULL;
	return true;
}

bool SIM::remove(Stu* p)
{
	if (p == head)//if p is head of list
	{
		head = head->next;
		free(p);
		return true;
	}
	//if p isn't head of list
	Stu* pre;
	pre = head;
	while (pre->next != p)
	{
		pre = pre->next;
	}
	pre->next = p->next;
	free(p);
	return true;
}

//special member func
SIM::Stu* SIM::findById(int id)
{
	Stu* p;
	if (head == NULL)
		return NULL;
	p = head;
	while (p && (p->id != id))
	{
		p = p->next;
	}
	return p;
}

SIM::Stu* SIM::findByName(string name)
{
	Stu* p;
	p = head;
	while (p && name==p->name)
	{
		p = p->next;
	}
	return p;
}

//public
//special member func
SIM::SIM()
{
	using namespace std;
	//check if si.txt exits 
	if (_access("si.txt", 02))
	{
		cout << "\"si.txt\" appears not exist or permission denied!." << endl;
		cout << "If it does not exsit, please make a new one where program locate." << endl;
		cout << "Press enter to exit." << endl;
		cin.get();//pause
		exit(1);
	}
	//build link list
	head = tail = NULL;
	Stu* p;
	ifstream file("si.txt");
	char test;
	file >> test;
	while (test == '0')
	{
		p = (Stu*)malloc(sizeof(Stu));
		if (p == NULL)
		{
			cout << "Data loading failed. Exiting...\n";
			exit(1);
		}
		file >> p->id;
		file >> p->name;
		file >> p->sex;
		file >> p->building;
		file >> p->room;
		push(p);
		file >> test;
	}
	file.close();
}

SIM::~SIM()
{
	if (head == NULL)
	{
		return;
	}
	Stu* p, * d;
	p = head;
	d = p;
	while (p)
	{
		p = p->next;
		free(d);
		d = p;
	}
	return;
}

//output func
inline void SIM::printStu(Stu* p)
{
	std::cout << "Id:" << p->id << "\tName:" << p->name << "\tSex:" << p->sex << "\tBuilding:" << p->building << "\tRoom:" << p->room << '\n';
	return;
}

void SIM::printRoom(int building, int room)
{
	Stu* p;
	p = head;
	while (p)
	{
		if ((p->building == building) && (p->room == room))
			printStu(p);
		p = p->next;
	}
	return;
}

//interaction func
void SIM::lookUp()
{
	using namespace std;
	cout << "Which way do you want to look up by?\n";
	cout << "Press 1 by id.\n";
	cout << "Press 2 by name.\n";
	cout << "Press any other key to go back to the main menu.\n";

	Stu* target;
	target = NULL;
	switch (scask())
	{
	case '1':
	{
		cout << "Id?" << endl;
		int answer = 0;
		cin >> answer;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		target = SIM::findById(answer);
		break;
	}
	case '2':
	{
		cout << "Name?" << endl;
		string name;
		cin >> name;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		target = SIM::findByName(name);
		break;
	}
	default:;
	}
	if (target == NULL)
	{
		cout << "Not found.\n";
		return;
	}
	printStu(target);
	cout << "Modify record? y/n\n";
	{
		cout << "Choose one to proceed:\n";
		while (1)
		{
			cout << "Press 1 to change id.\n";
			cout << "Press 2 to change name.\n";
			cout << "Press 3 to change sex.\n";
			cout << "Press 4 to change building.\n";
			cout << "Press 5 to change room.\n";
			cout << "Press 6 to delete current record.\n";
			cout << "Press any other key to cancel.\n";
			int a = 0;
			cin >> a;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (a <= 0 || a > 6)
				break;
			if (modify(target, a))
				goto complete;
			cout << "Continue to change other attribute? y/n\n";
			if (scask() != 'y')
				break;
		}
	}
	complete:
		cout << "Operation complete." << endl;
	return;
}

void SIM::lookUpRoomates()
{
	using namespace std;
	Stu* p;
	cout << "Which one do you want to search by?\n";
	cout << "Press 1 by id.\n";
	cout << "Press 2 by name.\n";
	cout << "Press 3 by building with room.\n";
	cout << "Press any other key back to main menu.\n";
	switch (scask())
	{
	case '1':
	{

		cout << "Please input room member's id.\n";
		int id = 0;
		cin >> id;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		p = findById(id);
		printRoom(p->building, p->room);
		break;
	}
	case '2':
	{
		cout << "Please input room member's name.\n";
		string name;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		p = findByName(name);
		printRoom(p->building, p->room);
		break;
	}
	case '3':
		cout << "Please input the building of room.\n";
		{
			int building, room;
			do
			{
				cout << "Building:" << endl;
				cin >> building;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (building <= 0)
					invalid();
			} while (building <= 0);
			do
			{
				cout << "Room:" << endl;
				cin >> room;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (room <= 0 || room >= 1000)
					invalid();
			} while (room <= 0 || room >= 1000);
			printRoom(building, room);
			break;
		}
		break;
	}
}

bool SIM::modify(Stu* p,int a)
{
	using namespace std;
	switch (a)
	{
	case 1:
		int newId;
		while (1)
		{
			cout << "Please input new id." << endl;
			cin >> newId;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (((newId > 100000000 || newId < 10000000)) || findById(newId))
			{
				invalid();
				cout << "Canceled modifying\n";
				return false;
			}
			else
				break;
		}
		p->id = newId;
		return true;
	case 2:
		cout << "Please input new name.\n";
		cin >> p->name;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return true;
	case 3:
		char newSex;
		cout << "Please input new sex.(m/f)\n";
		cin >> newSex;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (newSex == 'm' || newSex == 'f')
		{
			p->sex = newSex;
			return true;
		}
		cout << "Canceled modifying\n";
		return false;
	case 4:
		do
		{
			cout << "Please input building." << endl;
			cin >> p->building;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (p->building <= 0)
				invalid();
		} while (p->building <= 0);
		return 1;
	case 5:
		do
		{
			cout << "Please input new room." << endl;
			cin >> p->room;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (p->room <= 0 || p->room >= 1000)
				invalid();
		} while (p->room <= 0 || p->room >= 1000);
	case 6:
		printStu(p);
		cout << "Delete any why? Press y to confirm.\n";
		if (scask() == 'y')
		{
			remove(p);
			return true;
		}
	default:
		return false;
	}
}

bool SIM::create()
{
	using namespace std;
	Stu* p;
	p = (Stu*)malloc(sizeof(Stu));
	for (int a = 1; a < 6; a++)
		if (!modify(p, a))
		{
			cout << "Adding the new student canceled.\n";
			free(p);
			return false;
		}
	while (1)
	{
		printStu(p);
		cout << "Is this right? y/n\nPress y to confirm, any other key to cancel.\n";
		switch (scask())
		{
		case 'y':break;
		case 'Y':break;
		default:
			cout << "The information inputed before will be lost. Proceed anyway? y/n\n";
			char answer = scask();
			if (answer == 'y')
			{
				cout << "Adding the new student canceled.\n";
				free(p);
				return false;
			}
		}
		break;
	}
	push(p);
	cout << "Add the new student successfully!\n";
	return true;
}

//user interaction func
void printHelp()
{
	using namespace std;
	cout << "Press 1 to look up a student or then modify it.\n";
	cout << "Press 2 to check roommates.\n";
	cout << "Press 3 to add a new student.\n";
	cout << "Press 4 to save all changes\n";
	cout << "Any other key to quit.\n";
	cout << "Press h to see this message again.\n";
}

void invalid()
{
	using namespace std;
	cout << "Invalid!\n";
}

char scask()
{
	using namespace std;
	char tmp = '\0';
	cin >> tmp;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (tmp == '\n')
	{
		invalid();
		scask();
	}
	return tmp;
}