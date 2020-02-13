#include <iostream>
#include <string>
using namespace std;

class student{
public:
	string number;
	friend void start(student &p);
	student() :number("111"){
	}
	~student(){
	}
};
void isnumber(student &i)
{
	cout << i.number << endl;
	i.number = "222";
	cout << i.number << endl;
}
int main()
{
	student s;
	isnumber(s);
	return 0;
}

