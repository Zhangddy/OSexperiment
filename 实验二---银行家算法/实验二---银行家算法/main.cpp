#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

vector<string> ProcessName;	 // 进程名称
vector<string> ResourcesName;// 资源名称
vector<int> TotalResources;  // 资源总数量

vector<int> Available;
vector<int> Work;			
vector<vector<int>> Max;	 
vector<vector<int>> Allocation;
vector<vector<int>> Need;
vector<vector<int>> Request;
vector<string> Finish;

// 系统资源名称、系统资源数量、进程数量、各进程对资源的最大需求、
// 各进程已申请到资源数等信息初始值不可以在程序中指定固定值
void InitDate()
{
	size_t num;
	cout << "请输入系统资源个数" << endl;
	cin >> num;
	cout << "请输入" << num << "个资源名称及数量" << endl;

	for (size_t i = 0; i < num; i++)
	{
		cout << i << ":";
		string stmp;
		int itmp;
		cin >> stmp >> itmp;
		ResourcesName.push_back(stmp);
		TotalResources.push_back(itmp);
	}

	cout << endl;
	cout << "请输入进程个数" << endl;
	cin >> num;
	cout << "请输入各个进程所需的最大资源Max" << endl;
	Max.resize(num);
	for (size_t i = 0; i < num; i++)
	{
		cout << i << ":";
		
		for (size_t j = 0; j < ResourcesName.size(); j++)
		{
			int itmp;
			cin >> itmp;
			Max[i].push_back(itmp);
		}
	}
	// 给进程一个名字, 从1开始
	for (size_t i = 0; i < num; i++)
	{
		string tmp = "P";
		tmp = i + '0';
		ProcessName.push_back(tmp);
	}

	cout << "请输入各进程已分配的资源信息" << endl;

	// Alloction 初始化
	Allocation.resize(ProcessName.size());
	for (size_t i = 0; i < ProcessName.size(); i++)
	{
		Allocation[i].resize(ResourcesName.size());
		cout << i  << ":";

		for (size_t j = 0; j < ResourcesName.size(); j++)
		{
			int itmp;
			cin >> itmp;
			Allocation[i][j] = itmp;
		}
	}

	// Finish 初始化
	Finish.resize(ProcessName.size());
	for (size_t i = 0; i < ProcessName.size(); i++)
	{
		Finish[i] = "false";
	}

	// Need 初始化
	Need.resize(ProcessName.size());
	for (size_t i = 0; i < ProcessName.size(); i++)
	{
		Need[i].resize(ResourcesName.size());
		for (size_t j = 0; j < ResourcesName.size(); j++)
		{
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}
	}

	// Available 初始化
	Available.resize(ResourcesName.size());
	Available = TotalResources;
	for (size_t i = 0; i < ProcessName.size(); i++)
	{
		for (size_t j = 0; j < ResourcesName.size(); j++)
		{	
			Available[j] -= Allocation[i][j];
		}
	}
	// work 初始化
	Work = Available;
}

// 释放资源, 修改状态
void ReleaseResources(int processIndex)
{
	Finish[processIndex] = "true";
	for (size_t i = 0; i < ResourcesName.size(); i++)
	{
		Work[i] += Allocation[processIndex][i];
	}
}

void SafetyCheck()
{
	
	int complateNum = 0;
	cout << endl << "正在尝试资源分配: " << endl;
	vector<int> ret; // 最终的安全队列
	int num;
	for (num = 0; num < ProcessName.size(); ++num)
	{
		for (size_t i = 0; i < ProcessName.size(); i++)
		{
			if (Finish[i] == "true")
			{
				continue;
			}
			int flag2 = 0;
			vector<int> flag;
			flag.resize(ResourcesName.size());
			
			cout << "尝试为进程" << ProcessName[i] << "分配资源" << endl;
			for (size_t j = 0; j < ResourcesName.size(); j++)
			{
				if (Finish[i] == "false" && Need[i][j] <= Work[j])
				{
					flag[j] = 1;
				}
			}
			// 检测这个进程是否可以获取资源
			for (size_t k = 0; k < ResourcesName.size(); k++)
			{
				if (flag[k] != 1)
				{
					flag2 = 1;
				}
			}
			if (flag2 == 0)
			{
				cout << "进程" << ProcessName[i] << "分配成功" << endl;
				ReleaseResources(i);
				complateNum++;
				ret.push_back(i);
			}
			else
			{
				cout << "进程" << ProcessName[i] << "分配资源失败" << endl;
			}
		}
		if (complateNum == ProcessName.size())
		{
			break;
		}
	}
	cout << endl;
	if (num == ProcessName.size())
	{
		cout << "无安全序列" << endl;
	}
	else
	{
		cout << "一个安全序列为:" << endl;
		for (size_t i = 0; i < ret.size(); i++)
		{
			cout << ret[i] << " ";
		}
		cout << endl;
	}

}

int main()
{
	system("color f0");
	InitDate();
	SafetyCheck();
	system("pause");
	return 0;
}