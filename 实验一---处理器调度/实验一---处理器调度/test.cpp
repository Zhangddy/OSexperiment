#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <functional>
#include <ctime>

using namespace std;
// ����һ��ģ����̵��ȵ��㷨
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
	// ��ʼ������
	for (int i = 1; i <= size; ++i)
	{
		mpp[i - 1].pName = "P";
		mpp[i - 1].pName += i + '0';
	}
	
	// ��ʼ�����ȼ�
	for (int i = 0; i < size; ++i)
	{
		int randomNum = rand() % 5 + 1;
		mpp[i].priority = randomNum;
	}

	// ��ʼ������ʱ��
	for (int i = 0; i < size; ++i)
	{
		int randomNum = rand() % 5 + 1;
		mpp[i].runTime = randomNum;
	}

	// ��ʼ��״̬
	// do nothing

}

void ProcessorScheduling(multiset<MyPCB, myCompare>& multiSetList)
{
	cout << "���ڽ��н��̵���, ԭ����Ϊ:" << endl;
	for (auto& i : multiSetList)
	{
		cout << i.pName << " ";
	}
	cout << endl;
	while (multiSetList.size() > 0)
	{
		multiset<MyPCB, myCompare>::iterator it = multiSetList.begin();
		cout << it->pName << "��������" << endl;
		MyPCB tmp = *it;
		multiSetList.erase(it);
		tmp.runTime--;
		tmp.priority--;
		if (tmp.runTime == 0)
		{
			cout << tmp.pName << "���������!" << endl;
			tmp.status = 'E';
		}
		if (tmp.status == 'R')
		{
			multiSetList.insert(tmp);
		}
		cout << "���к���";
		for (auto& i : multiSetList)
		{
			cout << i.pName << " ";
		}
		cout << endl;
	}

	cout << "���̵������!" << endl;
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