#include<stdio.h>


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
extern int M;
extern int MAR;
extern int MBR;
int Mem[255];


void mem_init(int x)
{
  x=M;
  int i;
  
  for (i=0; i<M; i++)
    Mem[i]=0;
}
int mem_read(int i)
{
  
 p[i].MBR=Mem[p[i].MAR];
}

void mem_write(int i)
{
  
  Mem[p[i].MAR]=p[i].MBR;
}


