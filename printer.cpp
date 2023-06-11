#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
extern int  pfd1[2];
extern int pfd2[2];
using namespace std;
int spool_open[50];
int counter=0;
void printer_init()
{
  char x[10]="ACK";
  ofstream fp;
  fp.open("printer.out");
  
  write(pfd1[1],&x,sizeof(string));
  close(pfd1[1]); 
  fp.close();

}

void printer_init_spool()
{
  int x;
  ofstream fp;
  read(pfd2[0],&x,sizeof(string));
  char s[10];
  sprintf(s,"%d",x);
  //  s[5]=s+".out"; 
  fp.open(s);
  spool_open[counter]=x;
  counter++;
  close(pfd2[0]);
  fp.close();

}
void printer_end_spool(int k)
{
  int x;
  read(pfd2[0],&x,sizeof(int));
  ifstream f1;
  ofstream f2;
  string str;
  char s[10];
  sprintf(s,"%d",k);
  f1.open(s);
  f2.open("printer.out");
    while(!f1.eof())
      {
	getline(f1,str);
	f2<<str<<endl;
      }
  f1.close();
  f2.close();
  close(pfd2[0]);

}
void printer_dump_spool()
{

  int i;
  printf("\n=============================================\n");
  printf("\n      printer Dump\n");
  printf("\n=============================================\n");

  for (int i=0;i<counter;i++)
    {
      cout<<"Index:"<<i<<spool_open[i]<<endl;
    }

}
void printer_print()
{
  int x;
  char y[100];
  ofstream fp;
  read(pfd2[0],&x,sizeof(int));
  read(pfd2[0],&y,sizeof(int));
  char s[10];
  sprintf(s,"%d",x);
  fp.open(s);
  fp<<y;
  close(pfd2[0]);
  fp.close();

}

void printer_terminate()
{

  for(int i=0; i<counter;i++)
    {
      char s[10];
      sprintf(s,"%d",spool_open[i]);
	      remove(s);

    }
}

void printer_main()
{

  printer_init();
}
