#include<iostream>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include<stdio.h>

using namespace std;

FILE *ft;
FILE *fp=fopen("literal.txt","r+");

struct literal_table
{   
	int number; 
	char literal[9];
	char address[5];
};
int main()
{
	
	struct literal_table s;
	int ch,i=0,t;
	long int symsize; 
	symsize=sizeof(s);
	do
	{
	cout<<"\n------ LITERAL  TABLE ------ ";
	cout<<"\n###### MENU ########"<<endl ;
	cout<<"1.display"<<endl;
	cout<<"2.insert"<<endl;
	cout<<"3.delete"<<endl;
	cout<<"Enter your choice(enter other no to exit):";
	cin>>ch;
	switch(ch)
	{
		case 1:	cout<<"\n   number    literal    address"<<endl;
		        rewind(fp);
		        while(fread(&s,symsize,1,fp)==1)
			     cout<<"      "<<s.number<<"       "<<s.literal<<"        "<<std::right<<std::setfill('0')<<setw(4)<<s.address<<endl;
			    break;
		case 2:	i=0;
				rewind(fp);
				while(fread(&s,symsize,1,fp)==1)
				i++; 
			s.number=i+1;
			cout<<"Enter literal name:";
			cin>>s.literal;
			cout<<"Enter address:";
			cin>>s.address;
			fseek(fp,0,SEEK_END);
			fwrite(&s,symsize,1,fp);
			break;
		case 3:  cout<<"Enter literal number to delete:";
			cin>>t;
			rewind(fp);
			ft=fopen("temp.txt","w+");
		    while(fread(&s,symsize,1,fp)==1)
		    {   
		      if(s.number!=t)
				fwrite(&s,symsize,1,ft);
			}
			fclose(fp);
			fclose(ft);
			remove("literal.txt");
			rename("temp.txt","literal.txt");
			fp=fopen("literal.txt","r+");
			 break;
		 default: cout<<"wrong choice";
			  fclose(fp);
			  exit(0);
	   }
	  }while(1);
	  fclose(fp);
}
