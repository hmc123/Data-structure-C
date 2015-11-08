#include<iostream>
using namespace std;


class node
{
public:
	int data;
	node *next;
};

class linkqueue
{
public:
	linkqueue()
	{
		front = new node;
		front->next = NULL;
		rear = front;
	}

	node *front, *rear;
};


bool IsEmpty(linkqueue *Q)
{
	if (Q->front == Q->rear)
		return true;
	else
		return false;
}

void EnQueue(linkqueue *Q, int e)
{
	node *p = new node;
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
}

int DeQueue(linkqueue *Q)
{
	node *p;
	int k;
	
	if (!IsEmpty(Q))
	{
		p = Q->front;
		k = p->next->data;
		Q->front = p->next;
		delete p;
		return k;  //return the data of the deleted node 
	}
	else
	{
		cout<<"队列已空！";
		return 0;
	}
}

int LenQueue(linkqueue *Q)
{
	int count = 0;
	node *p = Q->front;
	while (p->next != NULL)
	{
		count++;
		p= p->next;
	}
	return count;
}


int main()
{
	linkqueue m;

	cout<<"下面进行进队列操作\n";
	for (int i = 0; i<10; i++)
	{
		EnQueue(&m, i*2);
	}

	cout<<"队列长度为："<<LenQueue(&m)<<endl;

	cout<<"下面做出出队列操作\n";
	while (!IsEmpty(&m))
	{
		
		cout<<DeQueue(&m)<<endl;
	}
	cout<<"队列长度为："<<LenQueue(&m)<<endl;

	return 0;
}