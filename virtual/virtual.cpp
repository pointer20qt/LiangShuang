#include <iostream>
#include <string>
//纯虚函数，用来定义接口，只定义了型，没有内容
//只要有纯虚数，就是虚基类
class A{//纯虚函数
public:
	virtual void run() = 0;
};

class Base :public A
{
public:
	void run(){
		std::cout << "开始执行" __FUNCTION__ << std::endl;
	}
};

int main()
{
	Base b;
	b.run();
	return 0;
}