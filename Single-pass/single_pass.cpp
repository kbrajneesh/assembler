#include<iostream>
#include<string.h>
#include<iomanip>
#include<vector>
#include<ctype.h>
#include<stdlib.h>
#define B_ADDR 0100

using namespace std;
FILE *f=fopen("prog.txt","r");
FILE *fm=fopen("mot.txt","r+");
FILE *fp=fopen("pot.txt","r+");
FILE *fs=fopen("symbol.txt","w+");
FILE *fl=fopen("literal.txt","w+");
FILE *fb=fopen("base.txt","w+");
FILE *ft=fopen("tii.txt","w+");
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
	int address;
}l;
struct base
{   
	int index; 
	char avail;
	int address;
}b;
struct tii
{
	int address;
	char symbol[9];
}t;
void insert_tii(char *sname,int add)
{
	symsize=sizeof(t);
		strcpy(t.symbol,sname);
		t.address=add;
		fseek(ft,0,SEEK_END);
		fwrite(&t,symsize,1,ft);
}
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
int search_symbol(char *sname)
{
	symsize=sizeof(s);
		rewind(fs);
        while(fread(&s,symsize,1,fs)==1)
			if(strcmp(sname,s.symbol)==0)
	        	if(s.value==0)
					return(1);
				else
	        		return(s.value);
		return(0);
}
void insert_literal(char *lit,int a=0)
{
		symsize=sizeof(l);
	        int i=0;
			rewind(fl);
 			while(fread(&l,symsize,1,fl)==1)
			i++; 
			l.number=i+1;
			strcpy(l.literal,lit);
			l.address=a;
			fseek(fl,0,SEEK_END);
			fwrite(&l,symsize,1,fl);
}
void insert_base(int n)
{
	symsize=sizeof(b);
		for(int i=0;i<16;i++)
		{
			if(i==n)
			{
				b.avail='Y';
				b.address=B_ADDR;
			}
			else
			{
				b.avail='N';
				b.address=0;
			}
			b.index=i;
			fseek(fb,0,SEEK_END);
			fwrite(&b,symsize,1,fb);
		}
}
int search_mot(char *token)
{
	symsize=sizeof(m);
	rewind(fm);
	while(fread(&m,symsize,1,fm)==1)
		if(strcmp(token,m.mnemonic)==0)
		 { 
		   if(m.format==0)
		   		return(2);
	       if(m.format==1)
		   		return(3);
	       if(m.format==10)
		   		return(4);
	       if(m.format==11)
		   		return(5);
	       if(m.format==100)
		   		return(6);
		}
	return(0);
}
int search_pot(char *token)
{
	symsize=sizeof(p);
	rewind(fp);
	while(fread(&p,symsize,1,fp)==1)
		if(strcmp(token,p.pseudo)==0)
		   return(1);
	return(0);
}
int search_base()
{   
	symsize=sizeof(b);
		rewind(fb);
 		while(fread(&b,symsize,1,fb)==1)
			if(b.avail=='Y')
	        	return(b.index);
		return(0);
}
void show()
{
	cout<<"\n\n------ PROGRAM ------\n";
	char ch;
	rewind(f);
	while((ch = fgetc(f)) != EOF)
		printf("%c",ch);
	cout<<"\n\n------ SYMBOL TABLE ------\n";
	long int symsize; 
	symsize=sizeof(s);
	cout<<"\n   symbol    value    length    relocation"<<endl;
	rewind(fs);
	while(fread(&s,symsize,1,fs)==1)
	    cout<<"   "<<std::left<<std::setfill(' ')<<setw(9)<<s.symbol<<"  "<<std::right<<std::setfill('0')<<setw(4)<<hex<<s.value<<"      "<<setw(2)<<dec<<s.length<<"         "<<s.relocation<<endl;
	cout<<"\n\n------ LITERAL TABLE ------\n";
	symsize=sizeof(l);
	cout<<"\n   number    literal    address"<<endl;
	rewind(fl);
	while(fread(&l,symsize,1,fl)==1)
	    cout<<"      "<<l.number<<"       "<<l.literal<<"        "<<std::right<<std::setfill('0')<<setw(4)<<hex<<l.address<<endl;
	cout<<"\n\n------ BASE TABLE ------\n";
	symsize=sizeof(b);
	cout<<"\n   index    availability    address"<<endl;
	rewind(fb);
	while(fread(&b,symsize,1,fb)==1)
	    cout<<"    "<<setw(2)<<dec<<b.index<<"           "<<b.avail<<"           "<<setw(6)<<hex<<b.address<<endl;
	cout<<"\n\n------ TABLE OF INCOMPLETE INSTRUCTIONS ------\n";
	symsize=sizeof(t);
	cout<<"\n  address      symbol"<<endl;
	rewind(ft);
	while(fread(&t,symsize,1,ft)==1)
	    cout<<"    "<<setw(2)<<dec<<t.address<<"         "<<t.symbol<<endl;
}
int main()
{
	vector<string> a(50);
	char* h;
	char ch;
	int i=0,j=0,addr=0,k=0,x,len=0,index=0,add_symbol;
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
		k=search_mot(h);
      if(!(k==0&&!search_symbol(h)&&!search_pot(h)))
    	 { 
		   if(k==2)
    	  {
    	  	i+=2;
    	  	continue;
		  }
		  if(k==3)
    	  { 
		  	char *ch_ptr = (char*)a[i+2].c_str();
    	  	if(!(search_symbol(ch_ptr)))
	     	  insert_tii(ch_ptr,addr);
		  	addr+=4;
    	  	i+=1;
    	  	continue;
		  }
		 if(a[i]=="START")
    	 {  
    	   if(i>0)
    	    len=1;
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
           insert_literal(ch_ptr,addr);
           ch_ptr = (char*)a[i-1].c_str();
           modify_symbol(ch_ptr,addr-4,len);
	       i+=2;
	     }
	     if(a[i]=="DS")
	     {
	     	len=4;
	       char *ch_ptr = (char*)a[i-1].c_str();
	       addr+=4;
           modify_symbol(ch_ptr,addr-4,len);
	     	i+=2;
		 }
		 if(a[i]=="USING")
	     {
	     	char* num_ptr = (char*)a[i+2].c_str();
    	   while(*num_ptr < '0' || *num_ptr > '9')
            ++num_ptr;
           int bindex = atoi(num_ptr); 
	     	insert_base(bindex);
	     	i+=2;
		 }
	    }
	    else
	     insert_symbol(h);
	}
	show();
	cout<<"\n\n::::: Assembly Code :::::\n\n";
	int bb=search_base();
	for(i=0;i<j;i++)
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
              char* ch_ptr = (char*)a[i+2].c_str();
              add_symbol=search_symbol(ch_ptr);
              
    	  	  cout<<std::right<<std::setfill(' ')<<setw(2)<<dec<<h<<" "<<reg<<","<<add_symbol<<"("<<index<<","<<bb<<")"<<endl;
    	  	  i+=2;
		   }
   }
	fclose(fs);
	fclose(fm);
	fclose(fl);
	fclose(fp);
	fclose(f);
	fclose(fb);
	return 0;
}
