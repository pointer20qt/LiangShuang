//任务1：unique_ptr练习实现
//任务2：shared_ptr实现，weak_ptr实现

#include <iostream>
#include "tool.h"

using namespace std;


int main ()
{
    tool* p = new tool;
    delete p;

    auto_ptr<tool> ptr1(new tool);
    auto_ptr<tool> ptr2(ptr1);
    auto_ptr<tool> ptr3;

    liang::L_uniquePtr<tool> ptr4(new tool);
    //liang::L_uniquePtr<tool> ptr5(ptr4);没有拷贝构造 拷贝赋值
    //liang::L_uniquePtr<tool> ptr6;
    //ptr6 = ptr5;


	//shared智能指针需要的方法
	/*
	无参构造，传递指针构造，拷贝构造，移动构造，拷贝赋值，移动赋值,交换，析构函数
	reset(T*)替换对象。 reset() 销毁对象
	operator*() operator->()
	get()获得裸指针
	use_count() 获得引用计数
	unique() 判断当前是否唯一  use_count()==1
	operator bool() 是否关联对象
	*/
    liang::LSharedPtr<tool> ptr7(new tool);
    cout << ptr7.use_count() << endl;
    liang::LSharedPtr<tool> ptr8(ptr7);
    liang::LSharedPtr<tool> ptr9;
    ptr9 = ptr8;


    return 0;
}
