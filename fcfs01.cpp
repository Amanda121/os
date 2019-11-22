// fcfs01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

//全生命周期都会用到的变量，先定义
//定义最大的进程数为100

#define MaxNum 100
//定义到达时间数组，用来保存每一个进程的到达时间
int ArrivalTime[MaxNum];
//定义服务时间数组，用来保存每一个进程的服务时间
//这个是外部输入进来的
int ServiceTime[MaxNum];
//定义完成时间数组，用来保存每一个进程的完成时间
int FinishTime[MaxNum];
//定义所有进程的周转时间
double WholeTime[MaxNum];
//定义进程有没有完成
bool IsFinished[MaxNum];
//定义所有进程的带权周转时间
double WeightWholeTime[MaxNum];
//分别定义FCFS算法和SJF算法得到的进程的平均周转时间
double AverageWT_FCFS,AverageWT_SJF;
//分别定义FCFS算法和SJF算法得到的进程的平均带权周转时间
double AverageWWT_FCFS,AverageWWT_SJF;

//初始化变量
int Init(int n)
{
	if(n>MaxNum)
	{
		cout<<"输入的进程数超出了可处理量"<<endl;
		return 1;
	}
	else
	{
		ArrivalTime[MaxNum-1] = 1000;
		ServiceTime[MaxNum-1] = 1000;
		return 0;
	}
}

//获取要进行运算的进程的相关数据
int GetInputData(int n) 
{
	cout<<"请依次输入进程的到达时间ArrivalTime:"<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>ArrivalTime[i];
	}
	cout<<"请依次输入进程的服务时间ServiceTime:"<<endl;
	for(i=0;i<n;i++)
	{
		cin>>ServiceTime[i];
	}
	return 0;
}

//找到最早到达的进程，找到最早到达进程算法两者是一样的
int GetFirstProcess(int n)
{
	//FirstProcess表示的是最早到达的第几个进程
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

//FCFS算法找到上个进程完成后，下一个先到的进程
int GetNextProcessFCFS(int n,int finishTime)
{
	int nextProcess = MaxNum-1;
	for(int i=0;i<n;i++)
	{
		//下一个要进行的进程到达时间要小于总进程完成时间
		//且这个进程要是没有完成的进程
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

//SJF算法找到上个进程完成后，在完成时间内到达的进程中，ServiceTime最小的进程
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

//输出
void OutPut(int n)
{
	//计算周转时间总和
	double wholeTime = 0;
	//计算带权周转时间总和
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
				cout<<"平均"<<endl;
				break;
			case(1):
				cout<<"到达时间"<<"        ";
				for(i = 0;i<n;i++)
				{
					cout<<ArrivalTime[i]<<"    ";
				}
				cout<<endl;
				break;
			case(2):
				cout<<"服务时间"<<"        ";
				for(i = 0;i<n;i++)
				{
					cout<<ServiceTime[i]<<"    ";
				}
				cout<<endl;
				break;
			case(3):
				cout<<"完成时间"<<"        ";
				for(i = 0;i<n;i++)
				{
					cout<<FinishTime[i]<<"    ";
				}
				cout<<endl;
				break;
			case(4):
				cout<<"周转时间"<<"        ";
				for(i = 0;i<n;i++)
				{
					cout<<WholeTime[i]<<"    ";
				}
				cout<<AverageWT_FCFS<<endl;
				break;
			case(5):
				cout<<"带权周转时间"<<"    ";
				for(i = 0;i<n;i++)
				{
					cout<<WeightWholeTime[i]<<"    ";
				}
				cout<<AverageWWT_FCFS<<endl;
				break;
		}
	}
}
		
//FCFS算法
int FCFS(int n)
{
	int flag = Init(n);
	if(flag == 1)
	{
		return 1;
	}
	GetInputData(n);
	int firstProcess = GetFirstProcess(n);
	//定义总进程结束时间，也是上一个进程结束的时间
	//用于计算下一个进程的结束时间
	int finishTime = ArrivalTime[firstProcess];
	FinishTime[firstProcess] = finishTime+ServiceTime[firstProcess];
	IsFinished[firstProcess] = true;
	finishTime = FinishTime[firstProcess];
	//周转时间=结束时间-到达时间
	WholeTime[firstProcess] = FinishTime[firstProcess]-ArrivalTime[firstProcess];
	//带权周转时间=周转时间/服务时间
	WeightWholeTime[firstProcess] = WholeTime[firstProcess]/ServiceTime[firstProcess];
	
	//正在计算的进程的结束时间就是整个进程的总的结束的时间
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

//SJF算法
int SJF(int n)
{
	int flag = Init(n);
	if(flag == 1)
	{
		//初始化发生了错误
		return 1;
	}
	GetInputData(n);
	int firstProcess = GetFirstProcess(n);
	//总进程的时间
	int finish = 0;
	FinishTime[firstProcess] = ArrivalTime[firstProcess]+ServiceTime[firstProcess];
	finish = FinishTime[firstProcess];
	IsFinished[firstProcess] = true;

	//周转时间
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
	cout<<"请输入要运算的进程数:"<<endl;
	int n;
	cin>>n;
	cout<<"请选择要进行的算法:"<<endl;
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