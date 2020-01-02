#pragma once
#define FREE 0 //空闲状态
#define BUSY 1 //已用状态
#define MAX_SPACE 512  

// 节点类型
class ElemType
{
public:
	int size;
	int address;
	int state;
};

typedef struct DListNode
{
	ElemType _data;
	DListNode *_pPre;
	DListNode *_pNext;
}DListNode, *PDLNode;


bool DListInsert();			// 分配空间
bool DListErase(int num);	// 释放空间
void PrintDList();			// 打印结果
bool DListInit();			// 初始化
PDLNode block_first;		//头结点
PDLNode block_last;			//尾结点
