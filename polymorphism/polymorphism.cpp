#include <iostream>
#include <string>
using namespace std;

class principal//У��
{
	string name;
public:
	principal(string sname)
	{
		this->name = sname;
	}

	~principal()
	{
		cout << "����ʦ�°���" << endl;
	}
};

class school
{
public:
	std::string schoolName;//ѧУ��
	std::string schoolType;//ѧУ��� Сѧ ���� ��ѧ
	std::string address;//ѧУ��ַ
public:
	principal *master;//У��

	string getSchoolName(){
		return schoolName;
	}
	 
	virtual ~school()
	{
		cout << "����������" << schoolName << " ��У��" << endl;
		delete master;
	}
	school(std::string schoolName, std::string schoolType, std::string address)
	{
		cout << "��ͨ���캯��" << endl;
		this->schoolName = schoolName;
		this->schoolType = schoolType;
		this->address = address;
		master = new principal("����ʦ");
	}

	school(const school& p)
	{
		cout << "�������캯��" << endl;
		master = new principal(*p.master);
	}

	school(school&& other) :schoolName(other.schoolName), schoolType(other.schoolType), address(other.address)
	{
		cout << "�ƶ�����" << endl;
		master = other.master;
		other.master = NULL;
	}
	//��ѧ
	virtual void schoolopens()
	{
		cout << this->schoolName << "��ѧ��" << endl;
	}
	virtual void schoolopens(int i)
	{
		for (int j = 0; j < i; j++)
		{
			cout << this->schoolName << "��ѧ��" << endl;
		}
	}
};


class University :public school
{
public:
	University():school("����ָ��", "�����ѵ", "����"){
		cout << "��ѧ�Ĺ��캯��" << endl;
	}
	virtual void schoolopens(){
		cout << "�ڴ�ѧУ��������" << getSchoolName() << "��ѧ����������Ļ" << endl;
	}
};
//��̬˼�� ��չ����
void printfschool(school* school){
	school->schoolopens();
}
void printfschool(school& school){
	school.schoolopens();
}
int main()
{
	school s("����ָ�����", "�����ѵ", "������");
	printfschool(s);
	University u;
	printfschool(u);
}