#include "DList.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// 初始化链表
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

// 生成新节点
bool BuyDListNode(int needSpace)
{
	int ch; //记录最小剩余空间
	PDLNode temp = (PDLNode)malloc(sizeof(DListNode));
	temp->_data.size = needSpace;
	temp->_data.state = BUSY;
	DListNode *p = block_first->_pNext;
	DListNode *q = NULL; //记录最佳插入位置

	// 采用最佳适应算法
	// 找一个最小且空间足够的分区
	// 初始化最小空间和最佳位置
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

	// 没找到则返回
	if (q == NULL)
		return false;
	else if (q->_data.size == needSpace)
	{
		q->_data.state = BUSY;
		return true;
	}
	// 找到后, 分配空间
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

//插入节点
bool DListInsert()
{
	int needSpace;
	cout << "请输入需要分配的空间大小(单位:kb)：" << endl;
	cin >> needSpace;
	if (needSpace < 0 || needSpace == 0)
	{
		cout << "您的输入有误, 请重新输入！" << endl;
		return false;
	}

	if (BuyDListNode(needSpace) == true) cout << "分配成功！" << endl;
	else cout << "内存不足，分配失败！" << endl;
	return true;
}


// 删除节点
bool DListErase(int num)
{
	DListNode *p = block_first;
	for (int i = 0; i <= num; i++)
		if (p != NULL)
			p = p->_pNext;
		else
			return false;


	p->_data.state = FREE;

	//若前面有空闲分区
	if (p->_pPre != block_first && p->_pPre->_data.state == FREE)
	{
		p->_pPre->_data.size += p->_data.size;
		p->_pPre->_pNext = p->_pNext;
		p->_pNext->_pPre = p->_pPre;
		p = p->_pPre;
	}

	// 若后面有空闲分区
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

// 打印分配结果
void PrintDList()
{
	int flag = 0;
	cout << "------------------------------------------------\n";
	DListNode *p = block_first->_pNext;
	cout << "分区号\t|起始地址|分区大小\t|状态\n";
	while (p)
	{
		cout << "  " << flag++ << "\t";
		cout << "|  " << p->_data.address << "\t ";
		cout << "|  " << p->_data.size << "kb\t";
		if (p->_data.state == FREE) 
			cout << "|空闲\n";
		else cout << "|已分配\n";
		p = p->_pNext;
	}
	cout << "------------------------------------------------\n";
}

void test()//测试函数
{
	DListInit(); // 初始化链表
	int flag; 

	while (1)
	{
		PrintDList();
		cout << "请选择您的操作";
		cout << "\n1: 分配内存\n2: 回收内存\n";

		cin >> flag;
		if (flag == 1)
		{
			DListInsert();
		}
		else if (flag == 2)
		{
			int num;
			cout << "请输入要释放分区号：" << endl;
			cin >> num;
			bool res = DListErase(num);
			if (res == false)
			{
				cout << "释放空间失败!" << endl;
			}
			else
			{
				cout << "释放空间成功!" << endl;
			}
		}
		else 
		{
			cout << "输入有误！请重新输入" << endl;
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