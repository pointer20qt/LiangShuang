#include<iostream>
#include<string>
#include<initializer_list>
#define NDEBUG
#include<assert.h>

using namespace std;

class vec{
	int* obj;
public:
	vec(initializer_list<int> arr){
		obj = new int[arr.size()];
		for (int i = 0; i < arr.size(); i++){
			obj[i] = *(arr.begin() + i);
		}
	}
	int& operator[](unsigned int index){//使用引用重载运算符，可以实现更改
		assert(0); //加个断言
		return obj[index];
	}
};

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	vec v({ 1, 2, 3, 4, 5, 6, 7 });
	arr[2];
	cout << v[2] << endl;
	v[2] = 6;
	cout << v[2] << endl;
	return 0;
}
//git测试