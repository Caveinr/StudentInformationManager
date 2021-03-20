#pragma once
//UTF-8
#include<string>
using std::string;

class SIM
{
private:
	struct Stu
	{
		int id;
		string name;
		char sex;//m or f
		int building;
		int room;
		struct Stu* next;//end address of Stu, store where next Stu start
	};
	Stu* head, * tail;

	//link list func
	bool savedb();//txt << mem
	bool push(Stu*);//link p to list
	bool remove(Stu*);//remove given Stu*
	Stu* findById(int);//return Stu by id
	Stu* findByName(string);//reture Stu by name
public:
	//special member func
	SIM();//txt >> mem
	~SIM();//destruct entire list

	//output func
	void printStu(Stu*);//print given Stu informations
	void printRoom(int, int);//print roomates by given Stu

	//interaction func
	void lookUp();
	void lookUpRoomates();
	bool modify(Stu*, int);
	bool create();
	bool save() { return savedb(); }
};

//interaction func
void printHelp();//print help information
void invalid();//tell user input invalid
char scask();//ask for a sanity checked char