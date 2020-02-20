#include<iostream>
#include<math.h>
#include<time.h>
using namespace std;
//传入0到100的整数，概率性判断成功,成功返回true
bool probability(int n){
	int p = rand() % 100;
	if (p <n){
		return true;
	}
	else{
		return false;
	}
}
//传入0到1的浮点数来判断概率
//怎么通过rand生成[0,20)的数rand()%20
//怎么通过rand生成[0,a)的数rand()%a
//怎么通过rand生成[5,20)的数rand()%(20-5)+5
//怎么通过rand生成[a,b)的数rand()%(b-a)+a
//怎么生成一个0~1的随机小数double
//怎么生成a~b的随机小数
//传入0到1的double，概率性判断成功，成功返回ture。
bool probability(double n){
	double p = ((double)rand()) / RAND_MAX;
	if (p <n){
		return true;
	}
	else{
		return false;
	}
}

int main(){
	//初始化随机种子
	//根据线性取余，生成 复杂函数
	//time(0)从1970到现在的秒数
	srand(time(0));
	//获得随机数，0~RAND_MAX
	int t = 0, f = 0;
	for (int i = 0; i < 100; i++)
	{
		if (probability(0.05)){
			cout << "暴击" << endl;
			t++;
		}
		else
		{
			f++;
		}
	}
	cout << t << "和" << f << endl;
}