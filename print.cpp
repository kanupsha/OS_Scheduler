#include <stdio.h>
#include <iostream>
#include <unistd.h>


extern void printer_init();
extern void printer_init_spool();
extern void printer_end_spool(int);
extern void printer_print();
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

int id=fork();

int pfd1[2];
int pfd2[2];
using namespace std;

void print_init()
{
  char y[10];
  pipe(pfd1);
  // int id = fork();
  if (id==0){
    printer_init();
  }
  read(pfd1[0],&y,sizeof(string));
  
  close(pfd1[0]);

}

void print_init_spool(int process)
{
  pipe(pfd2);
  int id = fork();
  if (id==0){
    printer_init_spool();
  }
  int y=p[process].PID;
  write(pfd2[1],&y,sizeof(int));
  
  close(pfd2[0]);


}

void print_end_spool(int process)
{
  pipe(pfd2);
  // int id = fork();
  if (id==0){
    printer_end_spool(process);
  }
  int y=p[process].PID;
  write(pfd2[1],&y,sizeof(int));

  close(pfd2[1]);


}

void print_print(char buffer[100] , int pid)
{
  pipe(pfd2);
  // int id = fork();
  if (id==0){
    printer_print();
  }
  write(pfd2[1],&pid,sizeof(int));
  write(pfd2[1],&buffer,sizeof(int));

}

void print_terminate()
{

}
