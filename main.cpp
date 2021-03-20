//UTF-8
#include<iostream>
#include"SIM.h"

int main()
{
	using namespace std;
	SIM db;
	printHelp();
	while (1)
	{
		cout << "So, what do you want to do?\n";
		switch (scask())
		{
		case 'h':
			printHelp();
			break;
		case '1'://look up
			db.lookUp();
		case '2'://see roomates
			db.lookUpRoomates();
		case '3'://add new
			db.create();
		case '4'://save
			db.save();
		default://quit
		{
			cout << "Quit? y/n\n";
			char answer = scask();
			if (answer == 'Y')
				return 0;//exit
		}
		}
	}
}