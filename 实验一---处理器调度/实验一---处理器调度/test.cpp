#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <functional>
#include <ctime>

using namespace std;
// 这是一个模拟进程调度的算法
class MyPCB
{
public:
	string pName;
	size_t runTime;
	int priority;
	char status = 'R';
};

class myCompare
{
public:
	bool operator()(const MyPCB& mp1, const MyPCB& mp2)
	{
		return (mp1.priority > mp2.priority) || 
			   (mp1.priority == mp2.priority) && (mp1.pName < mp2.pName);
	}
};

void InitPCB(MyPCB* mpp, int size)
{
	// 初始化名称
	for (int i = 1; i <= size; ++i)
	{
		mpp[i - 1].pName = "P";
		mpp[i - 1].pName += i + '0';
	}
	
	// 初始化优先级
	for (int i = 0; i < size; ++i)
	{
		int randomNum = rand() % 5 + 1;
		mpp[i].priority = randomNum;
	}

	// 初始化运行时间
	for (int i = 0; i < size; ++i)
	{
		int randomNum = rand() % 5 + 1;
		mpp[i].runTime = randomNum;
	}

	// 初始化状态
	// do nothing

}

void ProcessorScheduling(multiset<MyPCB, myCompare>& multiSetList)
{
	cout << "正在进行进程调度, 原队列为:" << endl;
	for (auto& i : multiSetList)
	{
		cout << i.pName << " ";
	}
	cout << endl;
	while (multiSetList.size() > 0)
	{
		multiset<MyPCB, myCompare>::iterator it = multiSetList.begin();
		cout << it->pName << "正在运行" << endl;
		MyPCB tmp = *it;
		multiSetList.erase(it);
		tmp.runTime--;
		tmp.priority--;
		if (tmp.runTime == 0)
		{
			cout << tmp.pName << "已运行完毕!" << endl;
			tmp.status = 'E';
		}
		if (tmp.status == 'R')
		{
			multiSetList.insert(tmp);
		}
		cout << "运行后结果";
		for (auto& i : multiSetList)
		{
			cout << i.pName << " ";
		}
		cout << endl;
	}

	cout << "进程调度完毕!" << endl;
}

int main()
{
	srand((unsigned int)time(0));
	MyPCB* mpp = new MyPCB[5];

	InitPCB(mpp, 5);
	multiset<MyPCB, myCompare> multiSetList(mpp, mpp + 5);

	ProcessorScheduling(multiSetList);

	delete[] mpp;
	system("pause");
	return 0;
}