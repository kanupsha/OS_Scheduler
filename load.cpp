#include<stdio.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include <errno.h>
#include <bits/stdc++.h>
extern int Mem[255];
extern int M;
extern int count_process;
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
}p[]; 
using namespace std;
int arr[100];
void load_prog(char *fname, int base)
{
  // FILE *fp;
  ifstream infile;
  char str[50];
  if(strcmp(fname,"prog-idle"))
    { fname=fname+1;}
  strcpy(str,fname);
  // cout<<str;  
  // fp= fopen(str,"r");
  //  cout<<newstr;
  // cout<<str<<" "<<base<<endl;
  infile.open(str);
  int i=0;
  int num;
  cout<<str;  
  while(infile>>num)
    {

      if(infile.eof()){    
      cout<<"eof"<<endl;
      }
      // cout<<num<<endl;     
      arr[i]=num;
      //  cout<<arr[i]<<endl;  
      i++;
    }
  int total_length=0;
  total_length=sizeof(arr)/sizeof(arr[0]);
  cout<<total_length;
  p[count_process].burst_time=arr[0];
  p[count_process].Base=base;
  //  cout<<p[count_process].burst_time;
    for (int j=0;j<total_length;j++)
    {
      Mem[base+j]=arr[j+2];
      //  printf ("%d\n",Mem[base+j]);

       }
  // fclose(fp);
  infile.close();  
 
  
}

void load_finish(FILE *f)
{

  f = fopen("fname", "w");
  fclose(f);

}
