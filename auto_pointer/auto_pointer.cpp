// 任务：用模板类实现自己的auto智能指针及各功能
// operator=() reset() get() release(),operator*() operator->()等
#include <iostream>
#include <memory>

using namespace std;

int toolnum = 0;

template <class T>
class L_autoPtr{
    T* obj = nullptr;//本地会存有一个指针 先nullptr
public:
    L_autoPtr(T* ptr):obj(ptr){//构造函数 赋值一个指针

    }
/*     L_autoPtr(T* ptr){//构造函数 赋值一个指针
        obj = ptr;
    }
*/
    L_autoPtr() = default;//无参构造
    L_autoPtr(L_autoPtr<T>& ptr){//不标准的复制构造（转移内部指针控制权）
        //delete obj;//删除原来的指针，因为本函数是构造，一开始并没有
        obj = ptr.obj;
        ptr.obj = nullptr;
    }
 /*
    L_autoPtr& operator=(L_autoPtr<T>& ptr){//不标准的复制赋值（转移内部指针控制权）
        delete obj;
        obj = ptr.obj;
        ptr.obj = nullptr;
        return *this;//将现有指针返回
    }
 */
    L_autoPtr& operator=(L_autoPtr<T>& ptr)/*:obj(ptr.release)非构造函数不能初始化参数列表*/
    {//不标准的复制赋值优化
        obj = ptr.release();
        return *this;//将现有指针返回
    }

    void reset(T* newptr = nullptr){//重置
        delete obj; //删除原来的指针
        obj = newptr; //赋为新的指针
    }
    T* release(){//释放控制权，返回指针/*2020.2.16.sunday 武汉肺炎限制出行 我也想回指针*/
        auto tem = obj;
        obj = nullptr;//释放指针
        return tem; //传出外界，爱干嘛干嘛
    }
    T* operator*(){//模拟指针的访问方法
        return *obj;
    }
    T* operator->(){//模拟指针箭头的访问方法
        return obj;
        // 箭头是特别的一个方法,写法固定,
        // 最特别的运算符,相当于auto = (ptr->),不好实现,编译器特别优化
    }
    T* get(){//获得指针指向的指针
        return obj;
    }
    ~L_autoPtr(){//释放空间
        delete obj;
    }
};

class tool{//工具len,好惨一类
public:
    int value = 0;
	tool(){
        toolnum ++;
		cout << "tool构造了" << toolnum <<endl;
	}
	tool(int t){
		cout << "单参数构造了,参数是t"<<t << endl;
	}
	tool(const tool&){
		cout << "tool拷贝构造了" << endl;
	}
	tool(tool&&){
		cout << "tool移动构造了" << endl;
	}
	~tool(){
		cout << "tool析构了" << toolnum << endl;
	}
	tool& operator = (tool&&){
		cout << "tool移动赋值了" << endl;
		return *this;
	}
	tool& operator = (const tool&){
		cout << "tool拷贝赋值了" << endl;
		return *this;
	}
};

int main ()
{
    tool* p = new tool;
    delete p;

    auto_ptr<tool> ptr1(new tool);
    auto_ptr<tool> ptr2(ptr1);
    auto_ptr<tool> ptr3;

    L_autoPtr<tool> ptr4(new tool);
    L_autoPtr<tool> ptr5(ptr4);
    L_autoPtr<tool> ptr6;
    ptr6 = ptr5;

    return 0;
}