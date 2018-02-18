#include<iostream>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include<stdio.h>

using namespace std;

struct symbol_table
{    
	char symbol[9];
	int value;
	int length;
	char relocation;
};
int main()
{
	
	struct symbol_table s;
	int ch,k,i=0,flag=0,t;
	char ss[9];
	FILE *fp,*ft;
	long int symsize; 
	fp=fopen("symbol.txt","r+");
	if(fp==NULL)
	{
		fp=fopen("symbol.txt","w+");
		if(fp==NULL)
		{
		cout<<"cannot open file";
		exit(0);
		}
	}
	symsize=sizeof(s);
	do
	{
	
	cout<<"\n------ SYMBOL  TABLE ------ ";
	cout<<"\n###### MENU ########"<<endl ;
	cout<<"1.display"<<endl;
	cout<<"2.search"<<endl;
	cout<<"3.insert"<<endl;
	cout<<"4.modify"<<endl;
	cout<<"5.delete"<<endl;
	cout<<"Enter your choice(enter other no to exit):";
	cin>>ch;
	switch(ch)
	{
		case 1:	cout<<"\n   symbol    value    length    relocation"<<endl;
		        rewind(fp);
		        while(fread(&s,symsize,1,fp)==1)
			     cout<<"   "<<std::left<<std::setfill(' ')<<setw(8)<<s.symbol<<"  "<<std::right<<std::setfill('0')<<setw(4)<<s.value<<"      "<<setw(2)<<s.length<<"         "<<s.relocation<<endl;
			    break;
		case 2:  cout<<"Enter symbol to search:";
				 cin>>ss;
				 rewind(fp);
		        while(fread(&s,symsize,1,fp)==1)
		    	{   
		    	if(strcmp(ss,s.symbol)==0)
				{
				cout<<"\n   symbol    value    length    relocation"<<endl;
				cout<<"   "<<std::left<<std::setfill(' ')<<setw(8)<<s.symbol<<"  "<<std::right<<std::setfill('0')<<setw(4)<<s.value<<"      "<<setw(2)<<s.length<<"         "<<s.relocation<<endl;
				flag=1;
				break;
				}
			 }
			 if(flag==0)
			 cout<<"Symbol not found";
			 flag=0;
			 break;
		case 3: cout<<"Enter symbol name:";
			cin>>s.symbol;
			cout<<"Enter value:";
			cin>>s.value;
			cout<<"Enter length:";
			cin>>s.length;
			cout<<"Enter relocation:";
			cin>>s.relocation;
			fseek(fp,0,SEEK_END);
			fwrite(&s,symsize,1,fp);
			break;
		case 4: cout<<"Enter symbol to modify:";
			cin>>ss;
			rewind(fp);
		      while(fread(&s,symsize,1,fp)==1)
		    	{    
				if(strcmp(ss,s.symbol)==0)
				{
				cout<<"------old values------";
				cout<<"\n   symbol    value    length    relocation"<<endl;
				cout<<"   "<<std::left<<std::setfill(' ')<<setw(8)<<s.symbol<<"  "<<std::right<<std::setfill('0')<<setw(4)<<s.value<<"      "<<setw(2)<<s.length<<"         "<<s.relocation<<endl;
				cout<<"------new values------\n";
				cout<<"Enter symbol name:";
				cin>>s.symbol;
				cout<<"Enter value:";
				cin>>s.value;
				cout<<"Enter length:";
				cin>>s.length;
				cout<<"Enter relocation:";
				cin>>s.relocation;
				fseek(fp,-symsize,SEEK_CUR);
				fwrite(&s,symsize,1,fp);
				flag=1;
				break;
				}
			 }
			 if(flag==0)
			 cout<<"Symbol not found";
			 flag=0;
			 break;
		case 5:  cout<<"Enter symbol to delete:";
			cin>>ss;
			rewind(fp);
			ft=fopen("temp.txt","w+");
		    while(fread(&s,symsize,1,fp)==1)
		    {   
		      if(strcmp(ss,s.symbol)!=0)
				fwrite(&s,symsize,1,ft);
			}
			fclose(fp);
			fclose(ft);
			remove("symbol.txt");
			rename("temp.txt","symbol.txt");
			fp=fopen("symbol.txt","r+");
			 break;
		 default: cout<<"wrong choice";
			  fclose(fp);
			  exit(0);
	   }
	  }while(1);
	  fclose(fp);
}
