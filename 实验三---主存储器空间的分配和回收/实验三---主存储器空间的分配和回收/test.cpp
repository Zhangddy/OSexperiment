#include "DList.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// ��ʼ������
bool DListInit()
{
	block_first = (PDLNode)malloc(sizeof(DListNode));
	block_last = (PDLNode)malloc(sizeof(DListNode));
	block_first->_pPre = NULL;
	block_first->_pNext = block_last;
	block_last->_pPre = block_first;
	block_last->_pNext = NULL;
	block_last->_data.address = 0;
	block_last->_data.size = MAX_SPACE;
	block_last->_data.state = FREE;
	return true;
}

// �����½ڵ�
bool BuyDListNode(int needSpace)
{
	int ch; //��¼��Сʣ��ռ�
	PDLNode temp = (PDLNode)malloc(sizeof(DListNode));
	temp->_data.size = needSpace;
	temp->_data.state = BUSY;
	DListNode *p = block_first->_pNext;
	DListNode *q = NULL; //��¼��Ѳ���λ��

	// ���������Ӧ�㷨
	// ��һ����С�ҿռ��㹻�ķ���
	// ��ʼ����С�ռ�����λ��
	while (p)
	{
		if (p->_data.state == FREE && (p->_data.size >= needSpace))
		{
			if (q == NULL)
			{
				q = p;
				ch = p->_data.size - needSpace;
			}
			else if (q->_data.size > p->_data.size)
			{
				q = p;
				ch = p->_data.size - needSpace;
			}
		}
		p = p->_pNext;
	}

	// û�ҵ��򷵻�
	if (q == NULL)
		return false;
	else if (q->_data.size == needSpace)
	{
		q->_data.state = BUSY;
		return true;
	}
	// �ҵ���, ����ռ�
	else
	{
		temp->_pPre = q->_pPre;
		temp->_pNext = q;
		temp->_data.address = q->_data.address;
		q->_pPre->_pNext = temp;
		q->_pPre = temp;
		q->_data.address += needSpace;
		q->_data.size = ch;
		return true;
	}
	return true;
}

//����ڵ�
bool DListInsert()
{
	int needSpace;
	cout << "��������Ҫ����Ŀռ��С(��λ:kb)��" << endl;
	cin >> needSpace;
	if (needSpace < 0 || needSpace == 0)
	{
		cout << "������������, ���������룡" << endl;
		return false;
	}

	if (BuyDListNode(needSpace) == true) cout << "����ɹ���" << endl;
	else cout << "�ڴ治�㣬����ʧ�ܣ�" << endl;
	return true;
}


// ɾ���ڵ�
bool DListErase(int num)
{
	DListNode *p = block_first;
	for (int i = 0; i <= num; i++)
		if (p != NULL)
			p = p->_pNext;
		else
			return false;


	p->_data.state = FREE;

	//��ǰ���п��з���
	if (p->_pPre != block_first && p->_pPre->_data.state == FREE)
	{
		p->_pPre->_data.size += p->_data.size;
		p->_pPre->_pNext = p->_pNext;
		p->_pNext->_pPre = p->_pPre;
		p = p->_pPre;
	}

	// �������п��з���
	if (p->_pNext != block_last && p->_pNext->_data.state == FREE)
	{
		p->_data.size += p->_pNext->_data.size;
		p->_pNext->_pNext->_pPre = p;
		p->_pNext = p->_pNext->_pNext;
	}
	if (p->_pNext == block_last && p->_pNext->_data.state == FREE)
	{
		p->_data.size += p->_pNext->_data.size;
		p->_pNext = NULL;
	}

	return true;
}

// ��ӡ������
void PrintDList()
{
	int flag = 0;
	cout << "------------------------------------------------\n";
	DListNode *p = block_first->_pNext;
	cout << "������\t|��ʼ��ַ|������С\t|״̬\n";
	while (p)
	{
		cout << "  " << flag++ << "\t";
		cout << "|  " << p->_data.address << "\t ";
		cout << "|  " << p->_data.size << "kb\t";
		if (p->_data.state == FREE) 
			cout << "|����\n";
		else cout << "|�ѷ���\n";
		p = p->_pNext;
	}
	cout << "------------------------------------------------\n";
}

void test()//���Ժ���
{
	DListInit(); // ��ʼ������
	int flag; 

	while (1)
	{
		PrintDList();
		cout << "��ѡ�����Ĳ���";
		cout << "\n1: �����ڴ�\n2: �����ڴ�\n";

		cin >> flag;
		if (flag == 1)
		{
			DListInsert();
		}
		else if (flag == 2)
		{
			int num;
			cout << "������Ҫ�ͷŷ����ţ�" << endl;
			cin >> num;
			bool res = DListErase(num);
			if (res == false)
			{
				cout << "�ͷſռ�ʧ��!" << endl;
			}
			else
			{
				cout << "�ͷſռ�ɹ�!" << endl;
			}
		}
		else 
		{
			cout << "������������������" << endl;
			continue;
		}
	}
}

int main()
{
	system("color f0");
	test();
	return 0;
}