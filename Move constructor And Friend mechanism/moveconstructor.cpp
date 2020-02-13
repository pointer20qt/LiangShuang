#include<iostream>
#include<vector>
#include<string>
using namespace std;

class moveconstructor
{
public:
	std::string Name;
	std::string Type;
	std::string address;
	moveconstructor *member;
	moveconstructor(moveconstructor&& c)
	{
		member = c.member;
		c.member = NULL;
		cout << "ÒÆ¶¯¿½±´" << endl;
	}
	moveconstructor(std::string Name, std::string Type, std::string address){
		this->Name = Name;
		this->address = address;
		this->Type = Type;
	}



};

//int main()
//{
//	moveconstructor s1("tom", "reacher", "school");
//	moveconstructor s2(move(s1));
//}