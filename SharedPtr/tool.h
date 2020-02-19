#include <iostream>
#include <memory>

using namespace std;


namespace liang{
    //unique_ptr
    template <class T>
    class L_uniquePtr{
        T* obj = nullptr;//本地会存有一个指针 先nullptr
    public:
        L_uniquePtr(T* ptr):obj(ptr){//构造函数 赋值一个指针

        }
    /*     L_uniquePtr(T* ptr){//构造函数 赋值一个指针
            obj = ptr;
        }
    */
        L_uniquePtr() = default;//无参构造
        L_uniquePtr(const T&) = delete;//
        L_uniquePtr(L_uniquePtr<T>&& ptr) {//移动构造
            //delete obj;//删除原来的指针，因为本函数是构造，一开始并没有
            obj = ptr.obj;
            ptr.obj = nullptr;
        }
    /*
        L_uniquePtr& operator=(L_uniquePtr<T>& ptr){//不标准的复制赋值（转移内部指针控制权）
            delete obj;
            obj = ptr.obj;
            ptr.obj = nullptr;
            return *this;//将现有指针返回
        }
    */
        L_uniquePtr& operator=(const L_uniquePtr<T>&) = delete;//禁止拷贝赋值
        L_uniquePtr& operator=(L_uniquePtr<T>&& ptr)/*:obj(ptr.release)非构造函数不能初始化参数列表*/
        {//移动复制赋值
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
        ~L_uniquePtr(){//释放空间
            delete obj;
        }
    };

	//资源计数类
	template<class T>
	class Ref{
		//当前资源计数
		int r_count=0;
		//当前弱引用指针计数
		int w_count=0;
		T* object=nullptr;
	public:
		Ref(T* target):object(target){ //构造函数，一旦放入，计数器加一
			++r_count;
		}
        //内联函数，省一丢丢性能
		inline void increase(){
			r_count++;
		}
		inline void reduce(){ //如果计数值为空，则没有指针指向 析构
			r_count--;
			if (r_count == 0){
				delete object; //析构记住的爱啥啥类
				delete this; //析构本引用计数类
				if(w_count == 0){//当r_count减少到0，如果w_count也为0
					delete this;//删除本引用计数器
				}
			}
		}
		inline void reduce_w(){
			w_count--;
			//为什么要判断条件要加上r_count==0
			//如果r不为0，说明还有指向
			if (w_count == 0&&r_count==0){
				delete this;
			}
		}

		//获得指向的爱啥啥对象
		T* get(){
			return object;
		}
        //记了多少次
		int getCount(){
			return r_count;
		}
    };
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
	template<class T> class LweakPtr;//声明一下
    template<class T> class LSharedPtr{ //模板类
		friend class LweakPtr<T>;//LweakPtr为LSharePtr的友元函数
	    Ref<T>* ref=nullptr; //有一个Ref类爱指向啥指向啥
	public:
		LSharedPtr() = default;//无参构造
		~LSharedPtr(){//析构时，计数器不为零，要将计数类减一，计数器为零，有计数器delete object&this
			if (ref){
				ref->reduce();
			}
		}
		LSharedPtr(Ref<T>* newRef){
			ref = newRef;
			if (ref){
				ref->increase();
			}
		}
		LSharedPtr(T* newP){ //指针指向构造
			ref = new Ref<T>(newP);
		}
		LSharedPtr(const LSharedPtr& other){ //拷贝构造
			ref = other.ref;
			if (ref){ //指同一个地方，计数器加一
				ref->increase();
			}
		}
		LSharedPtr(LSharedPtr&& other){ //移动构造
			swap(ref,other.ref);
		}
		LSharedPtr& operator=(const LSharedPtr& other){//拷贝复制
			if (ref){
				ref->reduce();
			}
			ref = other.ref;
			if (ref){
				ref->increase();
			}
			return *this;
		}
		LSharedPtr& operator=(LSharedPtr&& other){//移动赋值
			if (ref){
				ref->reduce();
			}
			ref = other.ref;
			other.ref = nullptr; //原本的掏空了，给赋予的对象
			return *this;
		}
		void swap(LSharedPtr& other){
			swap(ref,other.ref);
		}
		void reset(T* target=nullptr){//重置，如果传进来的为空指针，就置为空
			if (ref){//要指向一块新的空间，所以原来的计数器要减一
				ref->reduce();
			}
			if (target != nullptr){//如果不为空
				ref = new Ref<T>(target);//给传来的新空间，Ref在构造时自己会加一
			}
			else{
				ref = nullptr;
			}
		}
		T& operator*(){//模拟指针的访问方法
			if (ref){
				return *ref->get();//（ref->get()）获得计数器指向的爱啥啥对象
			}
			else{
				return *(T*)nullptr;
			}
		}
		T* operator->(){//模拟指针箭头的访问方法
			if (ref){
				return ref->get();
			}
			else{
				return (T*)nullptr;
			}
		}
		T* get(){//获得裸指针
			if (ref){
				return ref->get();//获得计数器指向的爱啥啥对象
			}
			else{
				return (T*)nullptr;
			}
		}
		int use_count(){//获得引用计数
			if (ref){
				return ref->getCount();
			}
			else{
				return 0;
			}
		}
		bool unique(){//判断当前是否唯一
			if (ref){
				return ref->getCount() == 1;
			}
			else{
				return false;
			}
		}
		//判断当前智能指针是否和对象关联
		operator bool(){
			return ref != nullptr;
		}
	};


	//weak_ptr实现
	template<class T>
	class LweakPtr{
		Ref<T>* ref = nullptr;
	public:
		LweakPtr() = default;
		LweakPtr(LSharedPtr<T>& other):ref(other.ref){
			cout << "使用shread_构造一个weak的拷贝赋 值运算符" << endl;
			if (ref){
				ref->increase_w();
			}
		}
		LweakPtr(const LweakPtr<T>& other) :ref(other.ref){
			if (ref){
				ref->increase_w();
			}
		}
		LweakPtr(LweakPtr<T>&& other){
			swap(ref,other.ref);
		}
		LweakPtr<T>& operator = (const LweakPtr<T>& other){
			cout << "调用了weak的拷贝赋值运算符" << endl;
			if (ref){
				ref->reduce_w();
			}
			ref = other.ref;
			if (ref){
				ref->increase_w();
			}
			return *this;
		}
		LweakPtr<T>&  operator=(LweakPtr<T>&& other){
			cout << "调用了weak的移动赋值运算符" << endl;
			if (ref){
				ref->reduce_w();
			}
			ref = other.ref;
			other.ref = nullptr;
			return *this;
		}
		int use_count(){
			if (ref){
				return ref->getCount();
			}
			else{
				return 0;
			}
		}
		bool expired(){
			if (ref){
				return ref->getCount() > 0;
			}
			else{
				return false;
			}
		}
		LSharedPtr<T> lock(){
			LSharedPtr<T> tem(ref);
			return tem;
		}

		void LSwap(LweakPtr<T>& other){
			swap(ref,other.ref);
		}
		void reset(){
			ref->reduce_w();
			ref = nullptr;
		}
	};
	template<class T,class ...args>
	LSharedPtr<T>
	make_Lshared(args... a){
		//将ref对象和T对象在一起创建。
		//创建一次ref对象，在new T对象
		LSharedPtr<T> t(new T(a...));
		return t;
	}
};




class tool{//工具len,好惨一类
public:
    int value = 0;
	tool(){
		cout << "tool构造了" <<endl;
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
		cout << "tool析构了" << endl;
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
