#include <iostream>
#include <string>
using namespace std;

class principal//校长
{
	string name;
public:
	principal(string sname)
	{
		this->name = sname;
	}

	~principal()
	{
		cout << "杨老师下班了" << endl;
	}
};

class school
{
public:
	std::string schoolName;//学校名
	std::string schoolType;//学校类别： 小学 高中 大学
	std::string address;//学校地址
public:
	principal *master;//校长

	string getSchoolName(){
		return schoolName;
	}
	 
	virtual ~school()
	{
		cout << "析构函数：" << schoolName << " 闭校了" << endl;
		delete master;
	}
	school(std::string schoolName, std::string schoolType, std::string address)
	{
		cout << "普通构造函数" << endl;
		this->schoolName = schoolName;
		this->schoolType = schoolType;
		this->address = address;
		master = new principal("杨老师");
	}

	school(const school& p)
	{
		cout << "拷贝构造函数" << endl;
		master = new principal(*p.master);
	}

	school(school&& other) :schoolName(other.schoolName), schoolType(other.schoolType), address(other.address)
	{
		cout << "移动构造" << endl;
		master = other.master;
		other.master = NULL;
	}
	//开学
	virtual void schoolopens()
	{
		cout << this->schoolName << "开学了" << endl;
	}
	virtual void schoolopens(int i)
	{
		for (int j = 0; j < i; j++)
		{
			cout << this->schoolName << "开学了" << endl;
		}
	}
};


class University :public school
{
public:
	University():school("大庆指针", "软件培训", "大庆"){
		cout << "大学的构造函数" << endl;
	}
	virtual void schoolopens(){
		cout << "在大学校长带领下" << getSchoolName() << "开学典礼完美落幕" << endl;
	}
};
//多态思想 扩展程序
void printfschool(school* school){
	school->schoolopens();
}
void printfschool(school& school){
	school.schoolopens();
}
int main()
{
	school s("大庆指针分针", "软件培训", "黑龙江");
	printfschool(s);
	University u;
	printfschool(u);
}