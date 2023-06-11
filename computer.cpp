#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<pthread.h>
#include <queue>

extern int PC;
extern int IR0;
extern int IR1;
extern int  AC;
extern int MAR;
extern int MBR;
extern  int Base;
extern void* shell_interface(void*);
extern void process_init();
extern void process_submit(int);
extern std::queue<int> readyQ;
extern void process_execute();
extern void print_init();
extern void print_init_spool(int);
extern void process_execute();
extern void process_dump_readyQ();
extern void process_dump_PCB();
extern void shell_print_registers();
extern void shell_print_memory();
extern void load_prog(char*,int);
extern void cpu_operation(int);
//extern int M;
extern int Mem[];
//extern int base;
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
}p[100];

bool Flag=false;
int M;
char filename[50];
int base;
int TQ;
int PT;
void process_init_PCB();
void process_set_registers();
void boot_system(int);
//extern void load_prog(char[50],int);
extern void mem_init(int);
extern void cpu_operation();
extern int count_process;
extern void print_init();
extern void print_init_spool(int);
pthread_t t1;

using namespace std;

int main()

{ 
  int input;
  int K;
  FILE* fptr;
 
  fptr = fopen("config.sys", "r");
 
  fscanf(fptr,"%d%d%d",&M,&TQ,&PT); 
  while (!feof (fptr))
    {  
     
      fscanf (fptr, "%d%d%d", &M,&TQ,&PT);      
    }
   
  //  boot_system(M);
  print_init();
  process_init();

  //Clearing ready Queue
  while (!readyQ.empty())
    {
      readyQ.pop();
    }
  //  process_dump_readyQ();

  char s[50]="prog-idle";
  char * ptr=s;
  load_prog(ptr ,0);
   // cout<<"here";
  process_submit(1);
  // cpu_operation(1);
 
  pthread_create(&t1,NULL,&shell_interface,NULL);
  while(!Flag)
    {
      if(readyQ.empty())
        {
	  cout<<"Running idle process here"<<endl;
	  cpu_operation(1);

        }
  
      process_execute();
      

    }
  pthread_join(t1,NULL);
     

  fclose(fptr);  /* close the file */ 

  return(0);
}
void boot_system(int K)

{
  mem_init(K);

}
