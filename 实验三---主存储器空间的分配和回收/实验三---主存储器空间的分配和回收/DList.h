#pragma once
#define FREE 0 //����״̬
#define BUSY 1 //����״̬
#define MAX_SPACE 512  

// �ڵ�����
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


bool DListInsert();			// ����ռ�
bool DListErase(int num);	// �ͷſռ�
void PrintDList();			// ��ӡ���
bool DListInit();			// ��ʼ��
PDLNode block_first;		//ͷ���
PDLNode block_last;			//β���
