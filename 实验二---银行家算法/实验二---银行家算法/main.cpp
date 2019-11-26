#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

vector<string> ProcessName;	 // ��������
vector<string> ResourcesName;// ��Դ����
vector<int> TotalResources;  // ��Դ������

vector<int> Available;
vector<int> Work;			
vector<vector<int>> Max;	 
vector<vector<int>> Allocation;
vector<vector<int>> Need;
vector<vector<int>> Request;
vector<string> Finish;

// ϵͳ��Դ���ơ�ϵͳ��Դ���������������������̶���Դ���������
// �����������뵽��Դ������Ϣ��ʼֵ�������ڳ�����ָ���̶�ֵ
void InitDate()
{
	size_t num;
	cout << "������ϵͳ��Դ����" << endl;
	cin >> num;
	cout << "������" << num << "����Դ���Ƽ�����" << endl;

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
	cout << "��������̸���" << endl;
	cin >> num;
	cout << "�����������������������ԴMax" << endl;
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
	// ������һ������, ��1��ʼ
	for (size_t i = 0; i < num; i++)
	{
		string tmp = "P";
		tmp = i + '0';
		ProcessName.push_back(tmp);
	}

	cout << "������������ѷ������Դ��Ϣ" << endl;

	// Alloction ��ʼ��
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

	// Finish ��ʼ��
	Finish.resize(ProcessName.size());
	for (size_t i = 0; i < ProcessName.size(); i++)
	{
		Finish[i] = "false";
	}

	// Need ��ʼ��
	Need.resize(ProcessName.size());
	for (size_t i = 0; i < ProcessName.size(); i++)
	{
		Need[i].resize(ResourcesName.size());
		for (size_t j = 0; j < ResourcesName.size(); j++)
		{
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}
	}

	// Available ��ʼ��
	Available.resize(ResourcesName.size());
	Available = TotalResources;
	for (size_t i = 0; i < ProcessName.size(); i++)
	{
		for (size_t j = 0; j < ResourcesName.size(); j++)
		{	
			Available[j] -= Allocation[i][j];
		}
	}
	// work ��ʼ��
	Work = Available;
}

// �ͷ���Դ, �޸�״̬
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
	cout << endl << "���ڳ�����Դ����: " << endl;
	vector<int> ret; // ���յİ�ȫ����
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
			
			cout << "����Ϊ����" << ProcessName[i] << "������Դ" << endl;
			for (size_t j = 0; j < ResourcesName.size(); j++)
			{
				if (Finish[i] == "false" && Need[i][j] <= Work[j])
				{
					flag[j] = 1;
				}
			}
			// �����������Ƿ���Ի�ȡ��Դ
			for (size_t k = 0; k < ResourcesName.size(); k++)
			{
				if (flag[k] != 1)
				{
					flag2 = 1;
				}
			}
			if (flag2 == 0)
			{
				cout << "����" << ProcessName[i] << "����ɹ�" << endl;
				ReleaseResources(i);
				complateNum++;
				ret.push_back(i);
			}
			else
			{
				cout << "����" << ProcessName[i] << "������Դʧ��" << endl;
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
		cout << "�ް�ȫ����" << endl;
	}
	else
	{
		cout << "һ����ȫ����Ϊ:" << endl;
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