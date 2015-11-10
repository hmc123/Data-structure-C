#include<iostream>
using namespace std;


//�Ⱥ��Car
class Waiting_Car
{
public:
	int num_car;
	Waiting_Car *next;
};

//�Ⱥ���Car����
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
	
	bool IsWaiting_CarsymEmpty();  //�Ⱥ����Ƿ��ѿգ�
	void Waiting_CarIn(int num_car);  //������ȥ�Ⱥ���
	int  Waiting_CarOut();            //�������Ⱥ���
	
};


//ͣ����ջ
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
	bool IsParkingsymFull();       //ͣ�����Ƿ�������
	void CarIn(int num_newcar, Waiting_Carsym &q);    //��������ͣ����
	void CarOut(int num_newcar, Parkingsym &s, Waiting_Carsym &q);  //������ͣ����
};





bool Parkingsym::IsParkingsymFull()
{
	if (this->top>=this->maxsize-1)
	{
		cout<<"ͣ��������,���복��������Ⱥ���\n";
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
			cout<<"�³�����(�Ⱥ���)"<<this->num_car[this->top]<<"����(ͣ����)\n";
		}
		else                                                //�Ⱥ�������ͣ����δ��ֱ�ӽ���
		{
			this->top++;
			this->num_car[this->top] = num_newcar;
			cout<<"�³���"<<num_newcar<<"ֱ�ӽ���(ͣ����)\n";
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
		cout<<this->num_car[this->top]<<"������ʱ(ͣ����)\n";
		this->top--;
	}
	cout<<"OK!"<<this->num_car[this->top]<<"�ɹ��뿪(ͣ����)��\n";
	this->top--;
	while (s.top>-1)
	{
		this->top++;
		this->num_car[this->top] = s.num_car[s.top];
		cout<<this->num_car[this->top]<<"�ص�(ͣ����)\n";
		s.top--;
	}

	//��ʱͣ�����п�λ�ã��ɽ��Ⱥ�����������
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
	cout<<num_car<<"����Ⱥ���\n";
	
}


int Waiting_Carsym::Waiting_CarOut()
{
	if (!this->IsWaiting_CarsymEmpty())
	{
		Waiting_Car *p;
		p = this->front;
		this->front = p->next;
		delete p;
		cout<<this->front->num_car<<"�뿪�Ⱥ���\n";
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
	cout<<"�����źż����ƺ�:";
	cin>>sign;cin>>carnumber; //�����źż������ĳ��ƺ�
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
		cout<<"�����źż����ƺ�:";
		cin>>sign;cin>>carnumber; 
	}
	
	return 0;
}