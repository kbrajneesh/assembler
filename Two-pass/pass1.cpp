#include<iostream>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<iomanip>
#include<stdio.h>
#include<vector>
#include<ctype.h>
#include<stdlib.h>

using namespace std;
FILE *f=fopen("prog.txt","r");
FILE *fm=fopen("mot.txt","r+");
FILE *fp=fopen("pot.txt","r+");
FILE *fs=fopen("symbol.txt","w+");
FILE *fl=fopen("literal.txt","w+");

long int symsize; 

struct pseudo_op_table
{    
	char pseudo[9];
	char address[9];
}p;

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
struct literal_table
{   
	int number; 
	char literal[9];
	char address[5];
}l;

void insert_symbol(char *sname,int value=0,int length=0,char r='r')
{
	symsize=sizeof(s);
		strcpy(s.symbol,sname);
		s.value=value;
		s.length=length;
		s.relocation=r;
		fseek(fs,0,SEEK_END);
		fwrite(&s,symsize,1,fs);
}
void modify_symbol(char *sname,int value=0,int length=0,char r='r')
{ 
	symsize=sizeof(s);
		rewind(fs);
        while(fread(&s,symsize,1,fs)==1)
	   	{    
			if(strcmp(sname,s.symbol)==0)
			{   
	        	s.value=value;
				s.length=length;
				s.relocation=r;
				fseek(fs,-symsize,SEEK_CUR);
				fwrite(&s,symsize,1,fs);
				break;
			}
		}
}
int search_symbol(char *sname)
{
	symsize=sizeof(s);
		rewind(fs);
        while(fread(&s,symsize,1,fs)==1)
	   	{    
			if(strcmp(sname,s.symbol)==0)
			{
	        	return(1);
			}
		}
		return(0);
}
void insert_literal(char *lit,char *a="0")
{
		symsize=sizeof(l);
	        int i=0;
			rewind(fl);
 			while(fread(&l,symsize,1,fl)==1)
			i++; 
			l.number=i+1;
			strcpy(l.literal,lit);
			strcpy(l.address,a);
			fseek(fl,0,SEEK_END);
			fwrite(&l,symsize,1,fl);
}
int searchtable(char *token)
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
	symsize=sizeof(p);
	rewind(fp);
	while(fread(&p,symsize,1,fp)==1)
    {   
		if(strcmp(token,p.pseudo)==0)
		{ 
		   return(1);
		}
	}
	return(0);
}
void show()
{
	cout<<"\n\n------ SYMBOL TABLE ------\n";
	long int symsize; 
	symsize=sizeof(s);
	cout<<"\n   symbol    value    length    relocation"<<endl;
	rewind(fs);
	while(fread(&s,symsize,1,fs)==1)
	    cout<<"   "<<std::left<<std::setfill(' ')<<setw(8)<<s.symbol<<"  "<<std::right<<std::setfill('0')<<setw(4)<<std::hex<<s.value<<"      "<<setw(2)<<s.length<<"         "<<s.relocation<<endl;
	cout<<"\n\n------ LITERAL TABLE ------\n";
	symsize=sizeof(l);
	cout<<"\n   number    literal    address"<<endl;
	rewind(fl);
	while(fread(&l,symsize,1,fl)==1)
	    cout<<"      "<<l.number<<"       "<<l.literal<<"        "<<std::right<<std::setfill('0')<<setw(4)<<l.address<<endl;
	cout<<"\n\n------ MACHINE OP TABLE (PREDEFINED)------\n";
	cout<<"\n   mnemonic    binary    length    format    reserved"<<endl;
		symsize=sizeof(m);
	rewind(fm);
     while(fread(&m,symsize,1,fm)==1)
	     cout<<"    "<<std::left<<std::setfill(' ')<<setw(4)<<m.mnemonic<<"        "<<setw(2)<<m.binary<<"         "<<std::right<<std::setfill('0')<<setw(2)<<m.length<<"       "<<setw(3)<<m.format<<endl;
	cout<<"\n\n------ PSEUDO OP TABLE (PREDEFINED) ------\n";
	cout<<"\n   pseudo op     address  "<<endl;
	symsize=sizeof(p);
	rewind(fp);
	while(fread(&p,symsize,1,fp)==1)
	 cout<<"    "<<std::left<<std::setfill(' ')<<setw(5)<<p.pseudo<<"        "<<p.address<<endl;
}
int main()
{
	vector<string> a(50);
	char* h;
	char ch;
	int i=0,j=0,addr=0,k=0,x,len=0;
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
		h=(char*)a[i].c_str();
		k=searchtable(h);
      if(!(k==0&&!search_symbol(h)))
    	 { 
		   if(k==2)
    	  {
    	  	i+=2;
    	  	continue;
		  }
		  if(k==3)
    	  { addr+=4;
    	  	i+=1;
    	  	continue;
		  }
		 if(a[i]=="START")
    	 {  
    	   if(i>0)
    	    len=1;
    	  /* char* num_ptr = (char*)a[i+1].c_str();
    	   while(*num_ptr < '0' || *num_ptr > '9')
            ++num_ptr;
           addr = atoi(num_ptr); */
           char *ch_ptr = (char*)a[i-1].c_str();
           modify_symbol(ch_ptr,addr,len);
	       i+=1;
	       continue;
	     }
	     if(a[i]=="DC")
    	 { 
		    
    	   char *ch_ptr = (char*)a[i+1].c_str();
    	   if(ch_ptr[0]=='F')
    	   {
			 len=4;
			 addr+=4;
		   }
    	   ch_ptr[0]='=';
           insert_literal(ch_ptr);
           ch_ptr = (char*)a[i-1].c_str();
           modify_symbol(ch_ptr,addr-4,len);
	       i+=1;
	       continue;
	     }
	     if(a[i]=="DS")
	     {
	     	len=4;
	       char *ch_ptr = (char*)a[i-1].c_str();
	       addr+=4;
           modify_symbol(ch_ptr,addr-4,len);
	     	i+=1;
		 }
		 if(a[i]=="USING")
	     {
	     	i+=2;
		 }
	     
	    }
	    else
	    {
	     insert_symbol(h);
       }
	}
	show();
	fclose(fs);
	fclose(fm);
	fclose(fl);
	fclose(fp);
	fclose(f);
	return 0;
}
