#include<iostream>
using namespace std;


//等候的Car
class Waiting_Car
{
public:
	int num_car;
	Waiting_Car *next;
};

//等候区Car队列
class Waiting_Carsym
{
public:
	Waiting_Carsym()
	{
		front = new Waiting_Car;
		front->next = NULL;
		rear = front;
	}
	Waiting_Car *front, *rear;
	
	bool IsWaiting_CarsymEmpty();  //等候区是否已空？
	void Waiting_CarIn(int num_car);  //车辆进去等候区
	int  Waiting_CarOut();            //车辆出等候区
	
};


//停车场栈
class Parkingsym  
{
public:
	Parkingsym(int maxsize)
	{
		this->maxsize = maxsize;
		num_car = new int[maxsize];
		top = -1;
	}
	int *num_car;
	int top, maxsize;
	bool IsParkingsymFull();       //停车场是否已满？
	void CarIn(int num_newcar, Waiting_Carsym &q);    //车辆进入停车场
	void CarOut(int num_newcar, Parkingsym &s, Waiting_Carsym &q);  //车辆出停车场
};





bool Parkingsym::IsParkingsymFull()
{
	if (this->top>=this->maxsize-1)
	{
		cout<<"停车场已满,新入车辆将进入等候区\n";
		return true;
	}
	else
		return false;
}


void Parkingsym::CarIn(int num_newcar, Waiting_Carsym &q)
{
	if (!this->IsParkingsymFull())   
	{
		if (!q.IsWaiting_CarsymEmpty())                 
		{
			this->top++;
			this->num_car[this->top] = q.Waiting_CarOut();
			cout<<"新车辆由(等候区)"<<this->num_car[this->top]<<"进入(停车场)\n";
		}
		else                                                //等候区空且停车场未满直接进入
		{
			this->top++;
			this->num_car[this->top] = num_newcar;
			cout<<"新车辆"<<num_newcar<<"直接进入(停车场)\n";
		}
	}
	else
	{
		q.Waiting_CarIn(num_newcar);
	}
		
}

void Parkingsym::CarOut(int num_wantoutcar, Parkingsym &s, Waiting_Carsym &q)
{
	while ((!s.IsParkingsymFull()) && (this->num_car[this->top] != num_wantoutcar) && this->top >-1)
	{
		s.top++;
		s.num_car[s.top] = this->num_car[this->top];
		cout<<this->num_car[this->top]<<"进入临时(停车场)\n";
		this->top--;
	}
	cout<<"OK!"<<this->num_car[this->top]<<"成功离开(停车场)！\n";
	this->top--;
	while (s.top>-1)
	{
		this->top++;
		this->num_car[this->top] = s.num_car[s.top];
		cout<<this->num_car[this->top]<<"回到(停车场)\n";
		s.top--;
	}

	//此时停车场有空位置，可将等候区车辆进入
	while (!this->IsParkingsymFull())
	{
		if (!q.IsWaiting_CarsymEmpty())
			this->CarIn(q.Waiting_CarOut(), q);
	}
}



bool Waiting_Carsym::IsWaiting_CarsymEmpty()
{
	if (this->front == this->rear)
		return true;
	else
		return false;
}

void Waiting_Carsym::Waiting_CarIn(int num_car)
{
	Waiting_Car *p = new Waiting_Car;
	p->num_car = num_car;
	p->next = NULL;
	this->rear->next = p;
	this->rear = p;
	cout<<num_car<<"进入等候区\n";
	
}


int Waiting_Carsym::Waiting_CarOut()
{
	if (!this->IsWaiting_CarsymEmpty())
	{
		Waiting_Car *p;
		p = this->front;
		this->front = p->next;
		delete p;
		cout<<this->front->num_car<<"离开等候区\n";
		return this->front->num_car;
	}
	else
		return 0;
}


int main()
{
	Parkingsym s1(3), s2(3);
	Waiting_Carsym Q;
	char sign;
	int carnumber=0;
	cout<<"输入信号及车牌号:";
	cin>>sign;cin>>carnumber; //输入信号及操作的车牌号
	while (sign != '@')
	{
		switch (sign)
		{
			case 'A':
			case 'a':
				s1.CarIn(carnumber, Q);
				break;
			case 'D':
			case 'd':
				s1.CarOut(carnumber, s2, Q);
				break;
		}
		cout<<"输入信号及车牌号:";
		cin>>sign;cin>>carnumber; 
	}
	
	return 0;
}