#include <iostream>
using namespace std;




class node
{
public:

	node(int maxsize)
	{
		
		this->maxsize = maxsize;
		data = new int[maxsize];
		front = rear = 0;
	}
	int *data;
	int front, rear, maxsize;

	~node()
	{
		delete data;
	}
};


bool IsEmpty(node *Q)
{
	if (Q->front==Q->rear)
	{	
		cout<<"队列已空！\n";
		return true;
	}
	else
		return false;
}

bool IsFull(node *Q)
{
	if ((Q->rear+1)%Q->maxsize==Q->front)
	{	
		cout<<"队列已满！\n";
		return true;
	}
	else
		return false;
}

void ClearQuene(node *Q)
{
	Q->front=Q->rear=0;
}

bool EnQuene(node *Q, int e)
{
	if (!IsFull(Q))
	{
		Q->rear = (Q->rear+1)%Q->maxsize;
		Q->data[Q->rear] = e;
		return true;
	}
	else
		return false;
}

int DeQuene(node *Q)
{
	if (!IsEmpty(Q))
	{
		Q->front = (Q->front+1)%Q->maxsize;
		return Q->data[Q->front];
	}
}

int LenQuene(node *Q)
{
	return (Q->rear-Q->front+Q->maxsize)%Q->maxsize;
}

int main()
{
	node p(7);
	int i=0;
	while(!IsFull(&p))
	{
		EnQuene(&p, i*2);
		cout<<i;
		i++;
	}
	cout<<LenQuene(&p)<<endl;
	while(!IsEmpty(&p))
	{
		cout<<DeQuene(&p);
	}
	return 0;
}