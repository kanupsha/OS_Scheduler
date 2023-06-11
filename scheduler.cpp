#include<stdio.h>
#include <queue> 
#include<iostream>

#define  MAXPROC 100
extern int count_process;
extern int Mem[];
extern int TQ;
extern void cpu_operation(int);
extern void print_init_spool(int);
extern void print_print();
int temp=0;
extern struct PCB{
  int PID;
  int PC;
  int IR0;
  int IR1;
  int  AC;
  int MAR;
  int MBR;
  int Base;
  int burst_time;
}p[]; /* Maximum number of processes is 100*/

using namespace std;
queue<int> readyQ;

void process_init_PCBs()
{
  p[100];

}

void process_init_PCB(int i)
{
  // p[i];
  p[i].PID=i;
}

void process_dispose_PCB(int i)
{
  int j;
  for (j = i; j < 100; j++)  
    {  
      p[i] = p[i+1]; // assign arr[i+1] to arr[i]  
    }  
}

void process_init_readyQ()
{
  // queue<int> readyQ;
}

void process_insert_readyQ(int i)
{
  
  readyQ.push(i);
}

int process_fetch_readyQ()
{
 
  // readyQ.pop();
  //  cout<<"fetch"<<readyQ.front();
  return readyQ.front();
  readyQ.pop();
}

void process_dump_readyQ ()
{
  printf("\n=============================================\n");
  printf("\n      ReadyQ Dump\n");
  printf("\n=============================================\n");
  int index=0;
  while (!readyQ.empty()) {
    cout <<"Index"<<index<<"\t"<< readyQ.front()<<endl;
    readyQ.pop();
    index++;
  }
  cout<<'\n'; 

} 

void process_dump_PCB()
{
  printf("\n=============================================\n");
  printf("\n      PCB Dump\n");
  printf("\n=============================================\n");

  for (int i=0 ; i<readyQ.size();i++)
    {
      cout<<"PID:"<<p[i].PID<<"\t";
      cout<<"PC:"<<p[i].PC<<"\t";
      cout<<"IR0:"<<p[i].IR0<<"\t";
      cout<<"IR1:"<<p[i].IR1<<"\t";
      cout<<"AC:"<<p[i].AC<<"\t";
      cout<<"MAR"<<p[i].MAR<<"\t";
      cout<<"MBR"<<p[i].MBR<<"\t";
      cout<<"Base:"<<p[i].Base<<"\t";
      cout<<"\n"; 
    }
}

void process_context_switch(int i,int j)
{

  struct temp{
    int PID;
    int PC;
    int IR0;
    int IR1;
    int  AC;
    int MAR;
    int MBR;
    int Base;
  }t;  

}

void process_init()
{
  
  process_init_PCBs();
  process_init_readyQ();
}

void process_submit(int k)
{
   if(k==1){
     process_init_PCB(k);
     return;
   }
  process_init_PCB(k);
  process_insert_readyQ(k);
  print_init_spool(k);
  // cout<<"Flag";
}

void process_execute()
{
  int i=process_fetch_readyQ();

  int total_number_ins=p[i].burst_time;
   p[i].burst_time=total_number_ins;
   //   cout<<readyQ.front();
  // run idle here
  /*   
     if(readyQ.empty())
     {

       cpu_operation(1);

     }
  */
 
   if(p[i].burst_time < TQ)
   {
    
     cpu_operation(i);
     // readyQ.pop(i);

   }
 else
   {
   while(temp!=TQ) 
     { 
           
       cpu_operation(i);
       
     }
   p[i].burst_time-=TQ;
   process_insert_readyQ(i);
    
   }
}

void process_exit(int i)
{
  process_dispose_PCB(i);
  //  print_print();
}
