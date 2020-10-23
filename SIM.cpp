//UTF-8
#include<iostream>
#include<fstream>//for file io
#include<io.h>//for using function access()
#include<cstdlib>
#include<limits>

//global settings
using namespace std;

typedef struct Stu //dssds
{
	int id;
	char name[16];//consider there'll be English name
	char sex;//m or f
	int building;
	int room;
	struct Stu *next;//end address of Stu, store where next Stu start
} Stu;
Stu *head, *tail;

/**typedef struct bptnode //node of b+tree, will achieve in the next version
{
	bptnode *subf//first subnode
	bptnode *subm//middle subnode
	bptnode *subl//last subnode
}bptnode;**/

//user interaction function
void printHelp();//print help information
void invalid();//tell user input invalid
char scask();//ask for sanity checked char
void printStu(Stu *p);//print given Stu informations
void printRoom(int building, int room);//print room members by given Stu

//file r/w function
int check();//check database is exactly where program locate
int readf();//txt >> mem
int savef();//txt << mem
int modify(Stu *p,int a);//change the record of the given pointer,a means which to get modified
int create(Stu *p);//create Stu (next version will also update b+tree
int link(Stu *p);//link p to list (next version will also update b+tree
Stu *findId(int id);//return Stu by id (next version will support search in b+tree
Stu *findName(char *name);//reture Stu by name (next version will support search in b+tree

int main()
{
	//TODO using XML instead ot txt
	//TODO:check if cache is up to date.(by using C++17 std::filesystem)
	//Check if si.txt does exist and r/writable
	if(check())
		return 1;
	//initialize global pointer head and tail
	head = NULL;
	tail = NULL;
	//load linked list(and create b+tree, next version
	readf();

	//interaction with user
	cout <<"Welcome to Student Information Manager!" <<endl;
	printHelp();
	while (1)//infinite loop
	{
		cout << "So, what do you want to do?" << endl;
		switch (scask())
		{
			case 'h': printHelp(); break;
			case 'H': printHelp(); break;//in case of ones whose Caps always lock
			case '1': //look up
			{
				cout << "Which way do you want to look up by?" << endl;
				while (1)
				{
					cout << "Press 1 by id." << endl;
					cout << "Press 2 by name." << endl;
					cout << "Press any other key to go back to the main menu." << endl;
					
					Stu *target;
					target = NULL;
					switch (scask())
					{
					case '1':
					{
						cout << "Id?" << endl;
						int answer=0;
						cin>>answer;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						target = findId(answer);
						break;
					}
					case '2':
					{
						cout << "Name?" << endl;
						char name[16];
						cin >>name;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						target = findName(name);
						break;
					}
					default:;
					}
					if (target == NULL)
					{ 
						cout << "Not found." << endl;
						break;
					}
					printStu(target);
					cout << "Modify record?y/n"<<endl;
					switch (scask())
					{
					case 'y':;
					case 'Y':
						cout << "Choose one to proceed" << endl;
						char answer;
						while (1)
						{							
							cout << "Press 1 to change id" << endl;
							cout << "Press 2 to change name" << endl;
							cout << "Press 3 to change sex" << endl;
							cout << "Press 4 to change building" << endl;
							cout << "Press 5 to change room" << endl;
							cout << "Press 6 to delete current record."<<endl;
							cout << "Press any other key to cancel." << endl;
							int a = 0;
							cin >> a;
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							if (a <= 0 || a > 6)
								break;
							if (modify(target, a)==2)
								goto complete;
							cout << "Continue to change other attribute?y/n"<<endl;
							answer = scask();
							if (answer != 'y' || answer != 'Y')
								break;
						} 
					default:
					free(target);
					}
					complete:
					cout << "Operation complete."<<endl;
					break;
				}
				break;
			}
			case '2': //to see roommates
			{
				Stu *p;
				p = (Stu*)malloc(sizeof(Stu));
				cout << "Which one do you want to search by?" << endl;
				cout << "Press 1 by id." << endl;
				cout << "Press 2 by name." << endl;
				cout << "Press 3 by building with room." << endl;
				cout << "Press any other key back to main menu."<<endl;
				switch (scask())
				{
				case '1':
				{
					
					cout << "Please input room member's id."<<endl;
					int id = 0;
					cin >> id;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					p = findId(id);
					printRoom(p->building, p->room);
					free(p);
					break;
				}
				case '2':
				{	
					cout << "Please input room member's name."<<endl;
					char name[16];
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					p = findName(name);
					printRoom(p->building, p->room);
					free(p);
					break;
				}
				case '3':
					cout << "Please input the building of room." << endl;
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
				free(p);
			}
			case '3'://add new
			{
				Stu *add;
				add = (Stu*)malloc(sizeof(Stu));
				if(create(add)==2)
					free(add);//add cancele. so memory allocated should be freed
				break;
			}
			case '4':
			{
				if(savef())
					cout<< "Changes saved."<<endl;
				else
					cout<< "Failed to save Changes."<<endl;
				cout<< "Press enter to exit";
				cin.get();
				exit(0);
			}
			default:
			{	
				cout << "Quit the application?y/n" << endl;
				char answer = scask();
					if (answer == 'Y' || answer == 'y')
				return 0;//end the application
			}
		}
	}
}

//user interaction function
void printHelp()
{
	cout << "Press 1 to look up a student or then modify it." << endl;
	cout << "Press 2 to check roommates." << endl;
	cout << "Press 3 to add a new student." << endl;
	cout<< "Press 4 to save all changes"<<endl;
	cout << "Any other key to quit." << endl;
	cout << "Press h to see this message again." << endl;
}
void invalid()
{
	cout << "Invalid!Please input again." << endl;
}
void printStu(Stu *p)
{
	if (p)
		cout << "Id:" << p->id << "\tName:" << p->name << "\tSex:" << p->sex << "\tBuilding:" << p->building << "\tRoom:" << p->room << endl;
	else
		cout << "Fully matched student not found!" << endl;
	return;
}
void printRoom(int building, int room)
{
	Stu *p;
	p = head;
	while (p)
	{
		if ((p->building == building) && (p->room == room))
			printStu(p);
		p = p->next;
	}
}
char scask()
{
	char achar = '\0';
	cin >> achar;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (achar == '\n')
	{
		invalid();
		scask();//recursion
	}
	return achar;
}


//file r/w function
/**TODO
bool isUpdate(string a,)
{
	fs::path p = fs::current_path() / "";
};
**/
int check()
{
	if (_access("si.txt", 02))
	{
		cout << "'si.txt' appears not exist or permission denied! Please check." << endl;
		cout << "If it does not exsit, please make a new one where program locate." << endl;
		cout << "Press enter to exit." << endl;
		cin.get();//pause
		return 1;
	}
	return 0;
}
int readf()
{
	Stu *p;
	ifstream file("si.txt");
	char test;
	file >> test;
	while (test == '0')
	{
		p = (Stu *)malloc(sizeof(Stu));
		file >> p->id;
		file >> p->name;
		file >> p->sex;
		file >> p->building;
		file >> p->room;
		link(p);
		file >> test;
	}
	file.close();
	tail->next = NULL;
	return 1;
}
int savef()
{
	if(head== NULL)
	{
		cout<< "Nothing to write.Press enter to exit.";
		return 1;
	}
	Stu *p;
	p = head;
	while (p->next)
	{
		p = p->next;
	}
	if (p != tail)
	{
		cout << "Data Integrity check failed! Saving canceled." << endl;
		cin.get();
		return 2;
	}
	//check si.txt
	ofstream file("si.txt");//delete and write file
	if(!file)
		return 1;//file doesn't exist
	cout<<"Checking complete.";
	//start save file
	p= head;
	cout<<"Saving..."<<endl;
	while (p)
	{
		file << '0' << p->id << p->name <<'\t'<< p->sex << p->building <<'\t'<< p->room <<endl;
		p=p->next;
	}
	file << '1';
		file.close();
	return 1;//complete saving
}
Stu *findId(int id)
{
	Stu *p;
	if (head == NULL)
		return NULL;
	p = head;
	while (p && (p->id != id)) 
	{
		p = p->next;
	}
	return p;
}
Stu *findName( char *name)
{
	Stu *p;
	p = head;
	while (p && strcmp(name, p->name))
	{
		p = p->next;
	}
	return p;
}
int modify(Stu *p, int a)
{
	switch (a)
	{
	case 1:
		int addId;
		while (1)
		{
			cout << "Please input new id." << endl;
			cin >> addId;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			p = NULL;
			if (((addId > 100000000 || addId < 10000000)) || findId(addId))
				invalid();
			else
				break;
		}
		p->id = addId;
		return 1;
	case 2:
		cout << "Please input new name." << endl;
		cin>> p->name;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return 1;
	case 3:
		sex:
		cout << "Please input new sex.(m/f)" << endl;
		cin >> p->sex;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (p->sex)
		{
		case 'f': break;//do like this is to suppurt changing sex manually
		case 'F': break;//in si.txt . if an user whose CapsLK always on
		case 'm': break;//feels like to do like the above, it will also
		case 'M': break;//influence pirnt Stu part. so no auto-lowerscape
		case 'n'://changing manually may no longer support in the next version
		case 'N':
		case 'y':
		case 'Y': cout << "It'll be denfinately known to him/her" << endl;
		default:
			invalid();
			goto sex;//a little indolently
		}
		return 1;
	case 4:
		do
		{
			cout << "Please input building." << endl;
			cin >> p->building;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (p->building <= 0)
				invalid();
		} 
		while (p->building <= 0);
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
		cout << "Delete any why? Press y to confirm." << endl;
		switch (scask())
		{
		case 'y':
		case 'Y':
		{
			if (p == head)//if p is head of list
			{ 
				head = head->next;
				free(p);
				return 2;
			}
			//if p isn't head of list
			//I have to admit that what write below is very stupid
			Stu *pre;
			pre = head;
			while (pre->next != p)
			{
				pre = pre->next;
			}
			pre->next = p->next;
			free(p);
			return 2;
		}
		default:;
		}
	default:
		return 0;
	}
}
int create(Stu *p)
{
	for (int a = 1; a < 6; a++)
		modify(p, a);
	while(1)
	{ 
		printStu(p);
		cout << "Is this right?"<<endl<< "Press y to confirm, any other key to cancel."<<endl;
		switch (scask())
		{
		case 'y':break;
		case 'Y':break;
		default:
			cout << "Your information input before will lost. Abandon anyway?y/n" << endl;
			char answer = scask();
			if (answer == 'y' || answer == 'Y')
			{ 
				cout << "Add the new student canceled." << endl;
				return 2;
			}
		}
		break;
	}
	link(p);
	cout << "Add the new student successfully!" << endl;
	return 1;
}
int link(Stu *p)
{
	if (head == NULL)
	{
		head = tail = p;
		head->next = tail;
	}
	else
	{
		tail->next = p;
		tail = p;
	}
	tail->next = NULL;
	return 1;
}
