#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define HEAD_POS 100 
// �����ͷ����

// ���ݵ����㷨
void DiskSch(int num)
{
	vector<int> v;

	// �������num������
	for (size_t i = 0; i < num; i++)
	{
		int n = rand() % 200 + 1;
		v.push_back(n);
	}
	cout << "�Զ�������������" << endl;
	cout << "---------------------------" << endl;
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}

	// �����ɴ�С����
	sort(v.begin(), v.end(), greater<int>());

	// �ҵ������ͷ����ҷ�����ȷ�Ĵŵ�
	cout << "������ɵĴŵ�����:" << endl;
	cout << "---------------------------" << endl;
	int HeadPos = v.size() - 1;
	for (size_t i = 0; i < v.size() - 1; i++)
	{
		if (v[i] < HEAD_POS)
		{
			HeadPos = i - 1;
			break;
		}
	}

	int flag = -1;
	int tmpIndex = HeadPos + 1;
	int lastPos = HEAD_POS;
	int sum = 0;

	// ��ʼ���е��ݵ���
	cout << "��һ�������ʵĴŵ���" << "  " << "�ƶ����� " << endl;
	for (size_t i = 0; i < v.size(); i++)
	{
		// ��ӡ��һ�����ʵĴŵ��ź��ƶ�����
		cout << v[HeadPos] << "\t\t\t" << abs(lastPos - v[HeadPos]) << endl;

		// ��¼���˶�����
		sum += abs(lastPos - v[HeadPos]);
		lastPos = v[HeadPos];
		
		// ���Ĵ�ͷ�˶�����
		HeadPos = HeadPos + flag;
		if (HeadPos == -1)
		{
			HeadPos = tmpIndex;
			flag *= -1;
		}
	}

	// ���ƽ�����ȳ���
	double aSum = sum * 1.0 / num;
	cout << "ƽ��Ѱ������: " << aSum << endl;
}

int main()
{
	srand((unsigned int)time(0));
	int input;
	system("color f0");
	cout << "������������ɵĴŵ��������и���:" << endl;
	cin >> input;
	if (input > 0)
	{
		DiskSch(input);
	}

	return 0;
}
