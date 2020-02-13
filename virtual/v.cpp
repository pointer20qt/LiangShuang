#include <iostream>
#include <string>
using namespace std;

class A
{
public:
	virtual void play()
	{
		cout << "A的play" << endl;
	}
	void eat()
	{
		cout << "A的eat" << endl;
	}
	virtual void fun()
	{
		cout << "A的fun" << endl;
	}
};
class B :public A
{
	virtual void fun()
	{
		cout << "b的fun" << endl;
	}
};
int main()
{
	A a;
	B b; //B类继承自A，而A中有虚函数，
		//因此不能直接访问，要通过虚指针去找到对应的函数去调用
	A*  pb = &b;//虚指针 详见视频22分钟处
	pb->fun();
	return 0;
}