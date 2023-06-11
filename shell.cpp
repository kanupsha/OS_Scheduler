#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<iostream>
#include<string>
#include<bits/stdc++.h>
#define MAXPROC 100
 struct PCB{
 int PID;
 int PC;
 int IR0;
 int IR1;
 int  AC;
 int MAR;
 int MBR;
 int Base;
 int burst_time;
 }p[MAXPROC]; /* Maximum number of processes is 100*/


extern int M;
extern int Mem[];
extern bool Flag;
//string f[50];
extern char filename[50];
extern int base;
int count_process=2;
extern void load_prog(char str[50], int base);

void process_init_PCB(int);
void process_set_registers();
void boot_system(int);
//void* shell_command(int);
extern void process_dump_PCB();
extern void process_dump_readyQ();
//extern void* shell_command(void *);
extern void process_init();
extern void process_submit(int);
//extern queue<int> readyQ;
extern void process_execute();
extern void process_dump_readyQ();
extern void process_dump_PCB();
extern void shell_print_registers();
extern void shell_print_memory();
extern void printer_dump_spool();
extern void printer_terminate();


using namespace std;

void *shell_interface(void * arg)
{
  int input;
  while(1)
    {   
    cout<<"What would you like to do"<<endl;
    cout<<"Option 0:Terminate the entire system"<<endl;
    cout<<"Option 1:Submit a new process"<<endl;
    cout<<"Option 2:Dump the values of all registers"<<endl;
    cout<<"Option 3:Dump the content of the entire memory"<<endl;
    cout<<"Option 4:Dump the information of all processes in the ready queue"<<endl;
    cout<<"Option 5:Dump the information of all processes in the list of PCB"<<endl;
    cout<<"Option 6:Dump the PIDs of all the processes with their spool files open"<<endl;
    cout<<"Enter(0-6):";
    cin>>input;
    if(input==0)
      {
       
       Flag=true;
       break;
       // exit(0);
      }
    else if(input==1)
      {
        int cmd=1;
        int t=0;
	//process_init();
	//process_submit(count);
        //count++;
	printf("Submit a new process\n");

	cout<<"Input Program File and Base>";
   
	//   cin.ignore(255,'\n');
	cin.getline(filename,50,' ');

	// cout<<filename;
	cin>>base;
	// cout<<base;
	char * p=filename;
	load_prog(p,base);
	//process_init();
        process_submit(count_process);
        count_process++;

     
      }    
    else if(input==2) 
      {
	shell_print_registers();
      
      }   
    else if(input==3)
      {
	shell_print_memory();

      }
    else if(input==4)
      {
       
	process_dump_readyQ();

      }
    else if(input==5)
      {

	process_dump_PCB();

      }
    else if(input==6)
      {
        
        printer_dump_spool();

      }
    }
    return NULL;
}

void shell_print_registers()
{
  int i;
  printf("\n=============================================\n");
    printf("\n      Register Dump\n");
    printf("\n=============================================\n");
                
  printf("\nPC:%d",p[i].PC);
  printf("\nIR0:%d",p[i].IR0);
  printf("\nIR1:%d",p[i].IR1);
  printf("\nAC:%d",p[i].AC);
  printf("\nMAR:%d",p[i].MAR);
  printf("\nMBR:%d",p[i].MBR);
  printf("\nBase:%d\n",p[i].Base);
}

void shell_print_memory()
{
  printf("\n=============================================\n");
    printf("\n      Memory Dump\n");
    printf("\n=============================================\n");

  printf("\n");
  int i;
  for (i=0; i<M; i++)
    {
      printf("%d ,",Mem[base + i] );   
      
    }
  printf("\n");
}

void* shell_command (void* cmd)
{
  int *command=(int *)cmd;
  int j;
  switch(*command)
    {
    case 1:
      {
      printf("Submit a new process\n");
      
      cout<<"Input Program File and Base>";
      cout.flush();
      //   cin.ignore(255,'\n');
      cin.getline(filename,50,' ');
      
      // cout<<filename;
      cin>>base;
      // cout<<base;
      char * p=filename;     
      load_prog(p,base);
      //   pthread_join(t1,NULL);
      // cout<<"thread1";
      // process_init();
      // process_submit(count);
      //count++;
   
      break;
      }
    case 2:
      printf("\nDumping the values of registers\n");
      shell_print_registers();
      break;
      
    case 3:
      printf("\nDumping the values of memory\n");
      shell_print_memory();
      break;
    case 4:
      printf("\nDumping the information of all processes in the ready queue\n");
      process_dump_readyQ();
      break;
    case 5:
      process_dump_PCB();
      break;
    case 6:
      printf("\nDumping the spooled contents of each process on the printer\n");
      printer_dump_spool();
      break;
        
    case 0:
      exit(0);
      printer_terminate();
      break;

    }

}
