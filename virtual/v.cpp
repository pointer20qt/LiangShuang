#include <iostream>
#include <string>
using namespace std;

class A
{
public:
	virtual void play()
	{
		cout << "A��play" << endl;
	}
	void eat()
	{
		cout << "A��eat" << endl;
	}
	virtual void fun()
	{
		cout << "A��fun" << endl;
	}
};
class B :public A
{
	virtual void fun()
	{
		cout << "b��fun" << endl;
	}
};
int main()
{
	A a;
	B b; //B��̳���A����A�����麯����
		//��˲���ֱ�ӷ��ʣ�Ҫͨ����ָ��ȥ�ҵ���Ӧ�ĺ���ȥ����
	A*  pb = &b;//��ָ�� �����Ƶ22���Ӵ�
	pb->fun();
	return 0;
}