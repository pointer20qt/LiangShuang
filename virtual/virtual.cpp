#include <iostream>
#include <string>
//���麯������������ӿڣ�ֻ�������ͣ�û������
//ֻҪ�д����������������
class A{//���麯��
public:
	virtual void run() = 0;
};

class Base :public A
{
public:
	void run(){
		std::cout << "��ʼִ��" __FUNCTION__ << std::endl;
	}
};

int main()
{
	Base b;
	b.run();
	return 0;
}