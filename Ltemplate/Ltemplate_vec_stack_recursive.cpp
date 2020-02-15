#include <iostream>
#include <vector>
using namespace std;

//栈stack，先入后出， push,pop,top，size，empty
template<class T> class L_stack{
	std::vector<T> arr;
public:
	void push(T&& obj){
		arr.push_back(obj);
	}
	void pop(){
		arr.pop_back();
	}
	T& top(){
		return arr.back();
	}
	size_t size(){
		return arr.size();
	}
	bool empty(){
		return arr.empty();
	}
};

void Lprint()//递归拆包结束
{
	cout << "禁止套娃" << endl;
}
template<class T, class... args> void Lprint(T f, args... d){
	cout << f << endl;
	Lprint(d...);
}


int main()
{
    L_stack<int> l;
    l.push(1);
    l.push(2);
    l.push(3);
    cout << l.size() << endl;
    cout << l.top() << endl;
    l.pop();
    cout << l.size() << endl;
    Lprint(1,1,1,"4554359");
    return 0;
}




