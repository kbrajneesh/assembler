#include<iostream>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<iomanip>
#include<stdio.h>
#include<vector>
#include<ctype.h>
#include<stdlib.h>
#define B_ADDR 2000
#define I_addr 0

using namespace std;
FILE *f=fopen("prog.txt","r");
FILE *fm=fopen("mot.txt","r");
FILE *fs=fopen("symbol.txt","r");
FILE *fb=fopen("base.txt","r");

long int symsize; 
 
struct machine_op_table
{    
	char mnemonic[5];
	char binary[3];
	int length;
	int format;
}m;

struct symbol_table
{    
	char symbol[9];
	int value;
	int length;
	char relocation;
}s;

struct base
{   
	int index; 
	char avail;
	int address;
}b;

int search_symbol(char *sname)
{
	symsize=sizeof(s);
		rewind(fs);
        while(fread(&s,symsize,1,fs)==1)
	   	{    
			if(strcmp(sname,s.symbol)==0)
			{ 
	        	return(s.value);
			}
		}
		return(0);
}

int search_base()
{   
	symsize=sizeof(b);
		rewind(fb);
 		while(fread(&b,symsize,1,fb)==1)
 		{   
			if(b.avail=='Y')
			{   
	        	return(b.index);
			}
		}
		return(0);
}

int search_mot(char *token)
{
	symsize=sizeof(m);
	rewind(fm);
	while(fread(&m,symsize,1,fm)==1)
    {   
		if(strcmp(token,m.mnemonic)==0)
		 { 
		   if(m.format==0)
		   {
		   	return(2);
	       }
	       if(m.format==1)
		   {
		   	return(3);
	       }
	       if(m.format==10)
		   {
		   	return(4);
	       }
	       if(m.format==11)
		   {
		   	return(5);
	       }
	       if(m.format==100)
		   {
		   	return(6);
	       }
		}
	}
	return(0);
}
char* m_op_binary(char *token)
{
	symsize=sizeof(m);
	rewind(fm);
	while(fread(&m,symsize,1,fm)==1)
    {   
		if(strcmp(token,m.mnemonic)==0)
		 { 
		    return(m.binary);
		}
   }
   return(0);
}

int main()
{
	vector<string> a(50);
	char* h,binary_op;
	char ch;
	int i=0,j=0,k=0,add_symbol,index;
	a[0]="\0";
	while((ch = fgetc(f)) != EOF)
	{
		if(ch==' '||ch==','||ch=='\n')
		 {
			 i++;
			 a[i]="\0";
		}
		else
		 a[i]=a[i]+ch;
		
		if(a[i]=="end"||a[i]=="END")
		break;
	}
	j=i;
	for(i=0;i<j;i++)
	{
		if(a[i]=="START")
	     {
	     	char* num_ptr = (char*)a[i+1].c_str();
    	   while(*num_ptr < '0' || *num_ptr > '9')
            ++num_ptr;
           index = atoi(num_ptr); 
	     	i+=1;
		 }
		 else
		 {
		   h=(char*)a[i].c_str();
		   k=search_mot(h);
           if(!(k==0)) 
		   if(k==3)
    	   {
		      char* num_ptr = (char*)a[i+1].c_str();
    	      while(*num_ptr < '0' || *num_ptr > '9')
                ++num_ptr;
              int reg = atoi(num_ptr); 
              char* num_ptr1 = (char*)a[i+2].c_str();
              add_symbol=search_symbol(num_ptr1);
              int bb=search_base();
    	  	  cout<<setw(2)<<h<<" "<<reg<<","<<add_symbol<<"("<<index<<","<<bb<<")"<<endl;
    	  	  i+=2;
		  }
     	}
   }
	fclose(fs);
	fclose(fm);
	fclose(f);
	fclose(fb);
	return 0;
}
