#include "deep_copy.h"
#include <iostream>

using namespace std;

struct node
{
	int value;
	struct node* pre;
	struct node* next;
};

class principal
{
	string name;
public:
	principal(string sname)
	{
		this->name = sname;
	}

	~principal()
	{
		cout << "杨老师下班了" << endl;
	}
};

class school
{
public:
	std::string schoolName;
	std::string schoolType;
	std::string address;
	principal *master;

	~school()
	{
		delete master;
	}
	school(std::string schoolName, std::string schoolType, std::string address)
	{
		this->schoolName = schoolName;
		this->schoolType = schoolType;
		this->address = address;
		master = new principal("杨老师");
	}

	school(const school& p)
	{
		master = new principal(*p.master);
	}
	
	
};
void run()
{
	school s("大庆指针", "就业培训机构", "大庆");
	school s2("东北石油大学", "大学", "大庆");
}


int main()
{
	run();
	cout << "下一句代码" << endl;
}

