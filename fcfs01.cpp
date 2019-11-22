// fcfs01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

//ȫ�������ڶ����õ��ı������ȶ���
//�������Ľ�����Ϊ100

#define MaxNum 100
//���嵽��ʱ�����飬��������ÿһ�����̵ĵ���ʱ��
int ArrivalTime[MaxNum];
//�������ʱ�����飬��������ÿһ�����̵ķ���ʱ��
//������ⲿ���������
int ServiceTime[MaxNum];
//�������ʱ�����飬��������ÿһ�����̵����ʱ��
int FinishTime[MaxNum];
//�������н��̵���תʱ��
double WholeTime[MaxNum];
//���������û�����
bool IsFinished[MaxNum];
//�������н��̵Ĵ�Ȩ��תʱ��
double WeightWholeTime[MaxNum];
//�ֱ���FCFS�㷨��SJF�㷨�õ��Ľ��̵�ƽ����תʱ��
double AverageWT_FCFS,AverageWT_SJF;
//�ֱ���FCFS�㷨��SJF�㷨�õ��Ľ��̵�ƽ����Ȩ��תʱ��
double AverageWWT_FCFS,AverageWWT_SJF;

//��ʼ������
int Init(int n)
{
	if(n>MaxNum)
	{
		cout<<"����Ľ����������˿ɴ�����"<<endl;
		return 1;
	}
	else
	{
		ArrivalTime[MaxNum-1] = 1000;
		ServiceTime[MaxNum-1] = 1000;
		return 0;
	}
}

//��ȡҪ��������Ľ��̵��������
int GetInputData(int n) 
{
	cout<<"������������̵ĵ���ʱ��ArrivalTime:"<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>ArrivalTime[i];
	}
	cout<<"������������̵ķ���ʱ��ServiceTime:"<<endl;
	for(i=0;i<n;i++)
	{
		cin>>ServiceTime[i];
	}
	return 0;
}

//�ҵ����絽��Ľ��̣��ҵ����絽������㷨������һ����
int GetFirstProcess(int n)
{
	//FirstProcess��ʾ�������絽��ĵڼ�������
	int FirstProcess = 0;
	for(int i=0;i<n;i++)
	{
		if(ArrivalTime[i]<=ArrivalTime[FirstProcess])
		{
			FirstProcess = i;
		}
	}
	return FirstProcess;
}

//FCFS�㷨�ҵ��ϸ�������ɺ���һ���ȵ��Ľ���
int GetNextProcessFCFS(int n,int finishTime)
{
	int nextProcess = MaxNum-1;
	for(int i=0;i<n;i++)
	{
		//��һ��Ҫ���еĽ��̵���ʱ��ҪС���ܽ������ʱ��
		//���������Ҫ��û����ɵĽ���
		if(ArrivalTime[i]<=finishTime&&IsFinished[i]!=true)
		{
			if(ArrivalTime[i]<ArrivalTime[nextProcess])
			{
				nextProcess = i;
			}
		}
	}
	return nextProcess;
}

//SJF�㷨�ҵ��ϸ�������ɺ������ʱ���ڵ���Ľ����У�ServiceTime��С�Ľ���
int GetNextProcessSJF(int n,int finishTime)
{
	int nextProcess = MaxNum-1;
	
	for(int i = 0;i<n;i++)
	{
		if(ArrivalTime[i]<=finishTime&&IsFinished[i]!=true)
		{
			if(ServiceTime[i]<ServiceTime[nextProcess])
			{
				nextProcess =  i;
			}
		}
	}
	return nextProcess;
}

//���
void OutPut(int n)
{
	//������תʱ���ܺ�
	double wholeTime = 0;
	//�����Ȩ��תʱ���ܺ�
	double weightWholeTime = 0;
	for(int i=0;i<n;i++)
	{
		wholeTime = wholeTime+WholeTime[i];
		weightWholeTime = weightWholeTime+WeightWholeTime[i];
	}
	AverageWT_FCFS = wholeTime/n;
	AverageWWT_FCFS = weightWholeTime/n;
	for(int j = 0;j<6;j++)
	{
		switch(j)
		{
			case(0):
				cout<<"                ";
				for(i = 0;i<n;i++)
				{
					cout<<i+1<<"    ";
				}
				cout<<"ƽ��"<<endl;
				break;
			case(1):
				cout<<"����ʱ��"<<"        ";
				for(i = 0;i<n;i++)
				{
					cout<<ArrivalTime[i]<<"    ";
				}
				cout<<endl;
				break;
			case(2):
				cout<<"����ʱ��"<<"        ";
				for(i = 0;i<n;i++)
				{
					cout<<ServiceTime[i]<<"    ";
				}
				cout<<endl;
				break;
			case(3):
				cout<<"���ʱ��"<<"        ";
				for(i = 0;i<n;i++)
				{
					cout<<FinishTime[i]<<"    ";
				}
				cout<<endl;
				break;
			case(4):
				cout<<"��תʱ��"<<"        ";
				for(i = 0;i<n;i++)
				{
					cout<<WholeTime[i]<<"    ";
				}
				cout<<AverageWT_FCFS<<endl;
				break;
			case(5):
				cout<<"��Ȩ��תʱ��"<<"    ";
				for(i = 0;i<n;i++)
				{
					cout<<WeightWholeTime[i]<<"    ";
				}
				cout<<AverageWWT_FCFS<<endl;
				break;
		}
	}
}
		
//FCFS�㷨
int FCFS(int n)
{
	int flag = Init(n);
	if(flag == 1)
	{
		return 1;
	}
	GetInputData(n);
	int firstProcess = GetFirstProcess(n);
	//�����ܽ��̽���ʱ�䣬Ҳ����һ�����̽�����ʱ��
	//���ڼ�����һ�����̵Ľ���ʱ��
	int finishTime = ArrivalTime[firstProcess];
	FinishTime[firstProcess] = finishTime+ServiceTime[firstProcess];
	IsFinished[firstProcess] = true;
	finishTime = FinishTime[firstProcess];
	//��תʱ��=����ʱ��-����ʱ��
	WholeTime[firstProcess] = FinishTime[firstProcess]-ArrivalTime[firstProcess];
	//��Ȩ��תʱ��=��תʱ��/����ʱ��
	WeightWholeTime[firstProcess] = WholeTime[firstProcess]/ServiceTime[firstProcess];
	
	//���ڼ���Ľ��̵Ľ���ʱ������������̵��ܵĽ�����ʱ��
	int nextProcess = GetNextProcessFCFS(n,FinishTime[firstProcess]);
	while(nextProcess!=MaxNum-1)
	{
		FinishTime[nextProcess] = finishTime + ServiceTime[nextProcess];
		finishTime = FinishTime[nextProcess];
		IsFinished[nextProcess] = true;
		WholeTime[nextProcess] = FinishTime[nextProcess]-ArrivalTime[nextProcess];
		WeightWholeTime[nextProcess] = WholeTime[nextProcess]/ServiceTime[nextProcess];
		
		nextProcess = GetNextProcessFCFS(n,FinishTime[nextProcess]);
	}
	OutPut(n);
	return 0;
}

//SJF�㷨
int SJF(int n)
{
	int flag = Init(n);
	if(flag == 1)
	{
		//��ʼ�������˴���
		return 1;
	}
	GetInputData(n);
	int firstProcess = GetFirstProcess(n);
	//�ܽ��̵�ʱ��
	int finish = 0;
	FinishTime[firstProcess] = ArrivalTime[firstProcess]+ServiceTime[firstProcess];
	finish = FinishTime[firstProcess];
	IsFinished[firstProcess] = true;

	//��תʱ��
 	WholeTime[firstProcess] = FinishTime[firstProcess]-ArrivalTime[firstProcess];
 	WeightWholeTime[firstProcess] = WholeTime[firstProcess]/ServiceTime[firstProcess];
	
	int nextProcess = GetNextProcessSJF(n,finish);
	cout<<nextProcess<<endl;
	while(nextProcess!=MaxNum-1)
	{
		IsFinished[nextProcess] = true;
		FinishTime[nextProcess] = finish+ServiceTime[nextProcess];
		finish = FinishTime[nextProcess];
		WholeTime[nextProcess] = FinishTime[nextProcess]-ArrivalTime[nextProcess];
		WeightWholeTime[nextProcess] = WholeTime[nextProcess]/ServiceTime[nextProcess];
		nextProcess = GetNextProcessSJF(n,finish);
	}
	OutPut(n);
	return 0;
}

int main(int argc, char* argv[])
{
	cout<<"������Ҫ����Ľ�����:"<<endl;
	int n;
	cin>>n;
	cout<<"��ѡ��Ҫ���е��㷨:"<<endl;
	cout<<"1:FCFS;  2:SJF;"<<endl;
	int choose;
	cin>>choose;
	if(choose==1)
	{
		FCFS(n);
	}
	else
	{
		SJF(n);
	}
	return 0;
}