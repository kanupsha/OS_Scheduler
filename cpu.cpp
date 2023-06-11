#include<unistd.h>
#include <stdio.h>
#include<stdlib.h>
#include<iostream>
extern struct PCB{
  int PID;
  int PC;
  int IR0;
  int IR1;
  int  AC;
  int MAR;
  int MBR;
  int Base;
}p[100];

  int opcode;
  int operand;
extern int Mem[];
int i;
extern void mem_read(int);
extern int cpu_mem_address(int,int);
extern void mem_write(int);
extern void* shell_command(void*);
extern void process_exit(int);
extern int temp;
extern void print_print(char buffer[],int pid);

using namespace std;
 void cpu_fetch_instruction(int k) 
  { 
   
    // cout<<"you are in fetch"<<endl;
    // cout<<p[k].PC<<endl;
   
    // PC = Base;
    p[k].MAR=p[k].PC;
    // cout<<p[k].MAR<<endl;
    mem_read(k);
    p[k].IR0=p[k].MBR;
      ++p[k].PC;
    p[k].MAR=p[k].PC;
    mem_read(k);
    p[k].IR1=p[k].MBR;
    ++p[k].PC;
    // printf("%d ",p[k].IR0);
    // printf("%d ",IR1);

    
  }

  void cpu_execute_instruction(int k) 
  {
     opcode =p[k].IR0;
     operand = p[k].IR1;
     // cout<<"you are in execute"<<endl;
     // cout<<"opcode:"<<p[k].IR0<<endl;
     // cout<<"operand:"<<p[k].IR1<<endl;
     
     int time;
     

    switch(opcode)
      {
      case 1:
     p[k].AC = operand;
     temp++;
      break;

      case 2:
	p[k].MBR=cpu_mem_address(operand,k);
      p[k].AC =p[k].MBR;
      // printf("%d",AC);
      //  printf("%s","case2\n");
      temp++;
      break;
     
      case 3:
	p[k].MBR = cpu_mem_address(operand,k);
      p[k].AC = p[k].AC + p[k].MBR;
      // printf("%d",AC);
      //  printf("%s","case3");
      temp++;
      break; 

      case 4:
	p[k].MBR = cpu_mem_address(operand,k);
      p[k].AC = p[k].AC * p[k].MBR;
      // printf("%s","case4");
      temp++;
      break;
     
      case 5:
      p[k].MAR=operand+p[k].Base;
      p[k].MBR=p[k].AC;
      mem_write(k);
      // printf("AC:%d",p[k].AC);
      // printf("%s","case5");
      temp++;
      break;
     
      case 6:
      if (p[k].AC>0){        
        p[k].PC=cpu_mem_address(operand,k);
	// cout<<"JUMP"<<p[k].PC;
	//printf("%s","case6");
        }
      
      temp++;
      break; 
     
      case 7:
      printf("\nAC:%d",p[k].AC);
      char s[50];
      int x;
      x=p[k].AC;
      sprintf(s,"%d",x);

      print_print(s,p[k].PID);
       printf("\n");
       temp++;
      break;
      
      case 8:
      time=operand;
      sleep(time);
      // printf("%s","case8");
      temp++;
      break;

      case 9:
        void *operand;
        shell_command(operand);
	// printf("%s","case9");
	temp++;
      break;
            
      case 0:
	// printf("%s","case0");
	process_exit(p[k].PID);
	 exit(0);
         temp++;
	 break;
      }
  
  }


int cpu_mem_address(int maddr, int k)
{
  int val;
  //  cout<<"maddr"<<maddr<<endl;
  // cout<<"base of k"<<p[k].Base<<endl;
  p[k].MAR =maddr+p[k].Base;
  val=p[k].MAR;
  // cout<<"val"<<val;
  return val;
 
}

void cpu_operation(int k)
{ 
   p[k].PC=p[k].Base;
   opcode=777; 
   printf("you are in cpu\n");
  
  while(opcode!=0)
    {
      // cout<<k<<endl;
      cpu_fetch_instruction(k);
      cpu_execute_instruction(k);
  }
}
