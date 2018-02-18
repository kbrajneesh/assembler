#include<iostream>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include<stdio.h>

using namespace std;

struct machine_op_table
{    
	char mnemonic[5];
	char binary[3];
	int length;
	int format;
};
int main()
{
	
	struct machine_op_table s;
	int ch,k,i=0,flag=0,t;
	char ss[9];
	FILE *fp,*ft;
	long int symsize; 
	fp=fopen("mot.txt","r+");
	if(fp==NULL)
	{
		fp=fopen("mot.txt","w+");
		if(fp==NULL)
		{
		cout<<"cannot open file";
		exit(0);
		}
	}
	symsize=sizeof(s);
	do
	{
	
	cout<<"\n------ MACHINE OP  TABLE ------ ";
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
		case 1:	cout<<"\n   mnemonic    binary    length    format    reserved"<<endl;
		        rewind(fp);
		        while(fread(&s,symsize,1,fp)==1)
			     cout<<"    "<<std::left<<std::setfill(' ')<<setw(4)<<s.mnemonic<<"        "<<setw(2)<<s.binary<<"         "<<std::right<<std::setfill('0')<<setw(2)<<s.length<<"       "<<setw(3)<<s.format<<endl;
			    break;
		case 2:  cout<<"Enter mnemonic op to search:";
				 cin>>ss;
				 rewind(fp);
		        while(fread(&s,symsize,1,fp)==1)
		    	{   
		    	if(strcmp(ss,s.mnemonic)==0)
				{
				cout<<"\n   mnemonic    binary    length    format    reserved"<<endl;
			     cout<<"    "<<std::left<<std::setfill(' ')<<setw(4)<<s.mnemonic<<"        "<<s.binary<<"         "<<std::right<<std::setfill('0')<<setw(2)<<s.length<<"       "<<setw(3)<<s.format<<endl;
				flag=1;
				break;
				}
			 }
			 if(flag==0)
			 cout<<"mnemonic op not found";
			 flag=0;
			 break;
		case 3: cout<<"Enter mnemonic op name:";
			cin>>s.mnemonic;
			cout<<"Enter binary op:";
			cin>>s.binary;
			cout<<"Enter length:";
			cin>>s.length;
			cout<<"Enter format:";
			cin>>s.format;
			fseek(fp,0,SEEK_END);
			fwrite(&s,symsize,1,fp);
			i++;
			break;
		case 4: cout<<"Enter machine op to modify:";
			cin>>ss;
			rewind(fp);
		      while(fread(&s,symsize,1,fp)==1)
		    	{    
				if(strcmp(ss,s.mnemonic)==0)
				{
				cout<<"------old values------";
				cout<<"\n   mnemonic    binary    length    format    reserved"<<endl;
			     cout<<"    "<<std::left<<std::setfill(' ')<<setw(4)<<s.mnemonic<<"        "<<s.binary<<"         "<<std::right<<std::setfill('0')<<setw(2)<<s.length<<"       "<<setw(3)<<s.format<<endl;
				cout<<"------new values------\n";
				cout<<"Enter mnemonic op name:";
			cin>>s.mnemonic;
			cout<<"Enter binary op:";
			cin>>s.binary;
			cout<<"Enter length:";
			cin>>s.length;
			cout<<"Enter format:";
			cin>>s.format;
				fseek(fp,-symsize,SEEK_CUR);
				fwrite(&s,symsize,1,fp);
				flag=1;
				break;
				}
			 }
			 if(flag==0)
			 cout<<"mnemonic op not found";
			 flag=0;
			 break;
		case 5:  cout<<"Enter machine op to delete:";
			cin>>ss;
			rewind(fp);
			ft=fopen("temp.txt","w+");
		    while(fread(&s,symsize,1,fp)==1)
		    {   
		      if(strcmp(ss,s.mnemonic)!=0)
				fwrite(&s,symsize,1,ft);
			}
			fclose(fp);
			fclose(ft);
			remove("mot.txt");
			rename("temp.txt","mot.txt");
			fp=fopen("mot.txt","r+");
			 break;
		 default: cout<<"wrong choice";
			  fclose(fp);
			  exit(0);
	   }
	  }while(1);
	  fclose(fp);
}
