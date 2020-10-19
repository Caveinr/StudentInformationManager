//UTF-8
#include<iostream>
#include<fstream>//for file io
#include<io.h>//for using function access()
#include<cstdlib>
#include<cstring>
#include<stdio.h>//for getchar(),EOF.

//global settings
using namespace std;

typedef struct _Stu //dssds
{
	int id;
	char name[16];//consider there'll be English name
	char sex;//m or f
	int building;
	int room;
	struct _Stu *next;//end address of Stu, store where next Stu start
} Stu;

//user interaction function
void printHelp();//print help information
void invalid();//tell user input invalid
char scask();//ask for sanity checked char
void printStu(Stu *p);//print given Stu informations
void printRoom(Stu *head, int building, int room);//print room members by given Stu

//file r/w function
int savef(Stu *head,Stu *tail);//txt << mem
int modify(Stu *head, Stu *p);//change the record of the given pointer
Stu *findId(Stu *head, int id);//return Stu by id
Stu *findName(Stu *head, char *name);//reture Stu by name

int main()
{
	//TODO using XML instead ot txt
	//TODO:check if cache is up to date.(by using C++17 std::filesystem)
	//Check if si.txt does exist and r/writable
	if( _access("si.txt",02))
	{
		cout <<"'si.txt' appears not exist or permission denied! Please check." <<endl;
		cout << "If it does not exsit, please make a new one where program locate." << endl;
		getchar();//pause
		return 1;
	}
	Stu *head, *tail;
	head = NULL;
	tail = NULL;
	//readf(head,tail);

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
			if (head == NULL)
			{
				head = p;
				tail = p;
				head->next = tail;
			}
			else
			{
				tail->next = p;
				tail = p;
			}
			file >> test;
		}
		file.close();
		tail->next = NULL;
	}
	cout <<"Welcome to Student Information Manager!" <<endl;
	
	//interaction with user
	printHelp();
	while (1)//infinite loop
	{
		cout << "So, what do you want to do?" << endl;
		char answer;
		cin >> answer;
		cin.ignore(1,EOF);
		switch (answer)
		{
			case 'h': printHelp(); break;
			case 'H': printHelp(); break;//in case of ones whose Caps always lock
			case '1': //look up
			{
				cout << "Which way do you want to look up by?" << endl;
				int answer = 0;
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
						int answer;
						cin>>answer;
						cin.ignore(1,EOF);
						target = findId(head, answer);
						break;
					}
					case '2':
					{
						cout << "Name?" << endl;
						char name[16];
						cin >>name;
						cin.ignore(1, EOF);
						target = findName(head, name);
						break;
					}
					default:;
					}
					printStu(target);
					if (target == NULL)
						break;
					cout << "Modify record?y/n"<<endl;
					switch (scask())
					{
						case 'y':;
						case 'Y':
							modify(head,target);
						default:;
					}
					cout << "Operation complete."<<endl;
					break;
				}
				break;
			}
			case '2': //to see roommates
			{
				Stu *p;
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
					cin.ignore(1,EOF);
					p = findId(head, id);
					printRoom(head, p->building, p->room);
					break;
				}
				case '2':
				{	
					cout << "Please input room member's name."<<endl;
					char name[16];
					cin.ignore(1,EOF);
					p = findName(head, name);
					printRoom(head, p->building, p->room);
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
							cin.ignore(1,EOF);
							if (building <= 0)
							invalid();
						} while (building <= 0);
						do
						{
							cout << "Room:" << endl;
							cin >> room;
							cin.ignore(1,EOF);
							if (room <= 0 || room >= 1000)
								invalid();
						} while (room <= 0 || room >= 1000);
						printRoom(head, building, room);
						break;
					}
					break;
				}
			}
			case '3'://add new
			{
				Stu *add;
				add = (Stu *)malloc(sizeof(Stu));
				//get id then sanity check
				int addId;
				while (1)
				{
					cout << "Id?" << endl;
					cin >> addId;
					cin.ignore(1,EOF);
					if (addId > 100000000 || addId < 10000000)
						cout << "Id invalid or already exist." << endl;
					else
						if (findId(head, addId))
							cout << "Already exist!" << endl;
						else
							break;
				}
				add->id = addId;
				//get name but no sanity checking(admit that if input \n it will cause some problem)
				cout << "Name?" << endl;
				cin >> add->name;
				cin.ignore(1,EOF);
				//get sexual then sanity check
				sex:
				cout << "Sex?m/f" << endl;
				add->sex = getchar();
				cin.ignore(1,EOF);
				switch (add->sex)
				{
					case 'f': break;//do like this is to suppurt changing sex manually
					case 'F': break;//in si.txt . if an user whose CapsLK always on
					case 'm': break;//feels like to do like the above, it will also
					case 'M': break;//influence pirnt Stu part. so no auto-lowerscape
					case 'n':
					case 'N':
					case 'y':
					case 'Y': cout << "It'll be denfinately known to him/her." << endl;
					default:
						invalid();
					goto sex;//a little indolently
				}
				//get building and sanity check
				do
				{
					cout << "Which building?" << endl;
					cin >> add->building;
					cin.ignore(1,EOF);
					if (add->building <= 0)
						invalid();
				} while (add->building <= 0);
				//get room and sanity check
				do
				{
					cout << "Which room?" << endl;
					cin >> add->room;
					cin.ignore(1,EOF);
					if (add->room <= 0 || add->room >= 1000)
						invalid();
				} while (add->room <= 0 || add->room >= 1000);
				printStu(add);
				//link to list
				if (head==NULL)
				{
					head = tail = add;
					head->next = tail;
				}
				else
				{
					tail->next = add;
					tail = add;
				}
				tail->next = NULL;
				cout << "Add the new student successed!" << endl;
				break;
			}
			case '4':
				if(savef(head,tail))
					cout<< "Changes saved."<<endl;
				else
					cout<< "Failed to save Changes."<<endl;
				cout<< "Press enter to exit";
				getchar();
				exit(0);
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
	cout << "Press 1 to look up a student." << endl;
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
void printRoom(Stu *head,int building, int room)
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
	char achar = getchar();//get first char
	cin.ignore(1,EOF);
	if (achar == '\n')
	{
		invalid();
		scask();//recursion
		cin.ignore(1,EOF);
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

int savef(Stu *head, Stu *tail)
{
	if(head== NULL)
	{
		cout<< "Nothing to write.Press enter to exit.";
		getchar();
		exit(0);
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
		getchar();
		exit(1);
	}
	//check si.txt
	ofstream file("si.txt");//delete and write file
	if(!file)
		return 1;//file doesn't exist
	cout<<"Checking complete.";
	//start save file
	p= head;
	while (p)
	{
		cout<<"Saving..."<<endl;
		file << '0' << p->id << p->name <<'\t'<< p->sex << p->building <<'\t'<< p->room <<endl;
		p=p->next;
	}
	file << '1';//the end of linked list , used in reading file
		file.close();
	return 1;//complete saving
}
Stu *findId(Stu *head,int id)
{
	Stu *p;
	p = head;
	if (head == NULL)
		return NULL;
	while (p && (p->id != id)) 
	{
		p = p->next;
	}
	return p;
}
Stu *findName(Stu *head,char *name)
{
	Stu *p;
	p = (Stu *)malloc(sizeof(Stu));
	p = head;
	while (p && strcmp(name, p->name))
	{
		p = p->next;
	}
	return p;
}
int modify(Stu *head,Stu *p)
{
	cout << "Choose one to proceed" << endl;
	cout << "Press 1 to change id" << endl;
	cout << "Press 2 to change name" << endl;
	cout << "Press 3 to change sex" << endl;
	cout << "Press 4 to change building" << endl;
	cout << "Press 5 to change room" << endl;
	cout << "Press 6 to delete current record.";
	cout << "Press any other key back to main menu" << endl;
	switch (scask())
	{
	case '1':
		int addId;
		while (1)
		{
			cout << "Please input new id." << endl;
			cin >> addId;
			cin.ignore(1,EOF);
			if (((addId > 100000000 || addId < 10000000)) || findId(head,addId))
				invalid();
			else
				break;
		}
		p->id = addId;
		return 0;
	case '2':
		cout << "Please input new name." << endl;
		cin>> p->name;
		cin.ignore(1,EOF);
		return 0;
	case '3':
	sex:
		cout << "Please input new sex.(m/f)" << endl;
		p->sex = getchar();
		cin.ignore(1,EOF);
		switch (p->sex)
		{
		case 'f': break;//do like this is to suppurt changing sex manually
		case 'F': break;//in si.txt . if an user whose CapsLK always on
		case 'm': break;//feels like to do like the above, it will also
		case 'M': break;//influence pirnt Stu part. so no auto-lowerscape
		case 'n':
		case 'N':
		case 'y':
		case 'Y': cout << "It'll be denfinately known to him/her" << endl;
		default:
			invalid();
			goto sex;//a little indolently
		}
		return 0;
	case '4':
		do
		{
			cout << "Please input building." << endl;
			cin >> p->building;
			cin.ignore(1,EOF);
			if (p->building <= 0)
				invalid();
		} while (p->building <= 0);
		return 0;
	case '5':
		do
		{
			cout << "Please input new room." << endl;
			cin >> p->room;
			cin.ignore(1,EOF);
			if (p->room <= 0 || p->room >= 1000)
				invalid();
		} while (p->room <= 0 || p->room >= 1000);
	case '6':
		printStu(p);
		cout << "Delete any why? Press y to confirm." << endl;
		switch (scask())
		{
		case 'y':;
		case 'Y':
		{
			if (p == head)//if p is head of list
			{
				return 0;
			}
			//if p isn't head of list
			Stu *pre;
			pre = head;
			while (pre->next != p)
			{
				pre = pre->next;
			}
			pre->next = p->next;
			return 0;
		}
		default:;
		}
	default:
		return 0;
	}
	return 0;
}
