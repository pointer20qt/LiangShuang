#include "try_catch.h"
#include <iostream>
#include <vector>

using namespace std;

//int main()
//{
//	vector<int> arr{ 1, 2, 3, 4, 5, 6 };
//	try
//	{
//		for (int i = 0; i < 6; i++)
//		{
//			cout << arr.at(i) << endl;
//		}
//		throw out_of_range("越界异常");
//		cout << "打印结束" << endl;
//	}
//	catch (out_of_range &e)
//	{
//		cout << "数组越界异常" << endl;
//	}
//	catch (...)
//	{
//		cout << "程序发生异常" << endl;
//	}
//
//	cout << "程序最后一句" << endl;
//
//}