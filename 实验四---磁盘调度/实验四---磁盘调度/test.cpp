#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define HEAD_POS 100 
// 定义磁头向外

// 电梯调度算法
void DiskSch(int num)
{
	vector<int> v;

	// 随机产生num个请求
	for (size_t i = 0; i < num; i++)
	{
		int n = rand() % 200 + 1;
		v.push_back(n);
	}
	cout << "自动生成序列如下" << endl;
	cout << "---------------------------" << endl;
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}

	// 进行由大到小排序
	sort(v.begin(), v.end(), greater<int>());

	// 找到距离磁头最近且方向正确的磁道
	cout << "随机生成的磁道申请:" << endl;
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

	// 开始进行电梯调度
	cout << "下一个被访问的磁道号" << "  " << "移动距离 " << endl;
	for (size_t i = 0; i < v.size(); i++)
	{
		// 打印下一个访问的磁道号和移动距离
		cout << v[HeadPos] << "\t\t\t" << abs(lastPos - v[HeadPos]) << endl;

		// 记录总运动距离
		sum += abs(lastPos - v[HeadPos]);
		lastPos = v[HeadPos];
		
		// 更改磁头运动方向
		HeadPos = HeadPos + flag;
		if (HeadPos == -1)
		{
			HeadPos = tmpIndex;
			flag *= -1;
		}
	}

	// 算出平均调度长度
	double aSum = sum * 1.0 / num;
	cout << "平均寻道长度: " << aSum << endl;
}

int main()
{
	srand((unsigned int)time(0));
	int input;
	system("color f0");
	cout << "请输入随机生成的磁道请求序列个数:" << endl;
	cin >> input;
	if (input > 0)
	{
		DiskSch(input);
	}

	return 0;
}
