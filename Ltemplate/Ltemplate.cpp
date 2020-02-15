#include <iostream>
#include <vector>

using namespace std;

template <class T> void Swap(T &a, T &b)//模板函数交换
{
	T temp = a;
	a = b;
	b = temp;
	cout << "使用的模板函数" << endl;
}
void Swap(int &a, int &b)//int交换
{
	int temp = a;
	a = b;
	b = temp;
	cout << "int交换" << endl;
}

class vec
{
	int value;
	char *p;
public:
	vec(int v){
		p = new char[100];//申请空间存数据
		value = v;
		cout << "无参构造" << endl;
	}
	vec(const vec &tem)
	{
		p = new char[100];
		value = tem.value;
		cout << "调用了拷贝构造函数" << endl;
	}
	~vec()
	{
		cout << "析构函数 delete p" << endl;
		delete p;
	}
	vec& operator=(const vec&tem)//重载操作符 My_swap函数中的等号是进行浅拷贝 二次析构出错
	{
		delete p;
		p = new char[100];
		value = tem.value;
		return *this;
	}
};
void My_swap(vec &a, vec &b)
{
	vec temp(a);
	a = b;
	b = temp;
}

int main()
{
	int x1 = 1,x2 = 2;
	//模板类的隐式推导
	Swap(x1, x2);
	//模板类的显式推导
	Swap<int>(x1, x2);
	//模板类的强制模板
	Swap<>(x1, x2);
	cout << "x1: " << x1 <<" x2: "<< x2 << endl;
	//模板函数类中应用
	vec A(100);
	vec B(200);
	My_swap(A, B);
	cout << "程序结束" << endl;
	return 0;
}