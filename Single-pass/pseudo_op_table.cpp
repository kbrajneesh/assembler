#include<iostream>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include<stdio.h>

using namespace std;

struct pseudo_op_table
{
	char pseudo[9];
	char address[9];
};
int main()
{

	struct pseudo_op_table s;
	int ch,k,i=0,flag=0,t;
	char ss[9];
	FILE *fp,*ft;
	long int symsize;
	fp=fopen("pot.txt","r+");
	if(fp==NULL)
	{
		fp=fopen("pot.txt","w+");
		if(fp==NULL)
		{
		cout<<"cannot open file";
		exit(0);
		}
	}
	symsize=sizeof(s);
	do
	{

	cout<<"\n------ PSEUDO OP TABLE ------ ";
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
		case 1:	cout<<"\n   pseudo op     address  "<<endl;
		        rewind(fp);
		        while(fread(&s,symsize,1,fp)==1)
			     cout<<"    "<<std::left<<std::setfill(' ')<<setw(5)<<s.pseudo<<"        "<<s.address<<endl;
			    break;
		case 2:  cout<<"Enter pseudo op to search:";
				 cin>>ss;
				 rewind(fp);
		        while(fread(&s,symsize,1,fp)==1)
		    	{
		    	if(strcmp(ss,s.pseudo)==0)
				{
				cout<<"\n   pseudo op     address  "<<endl;
			     cout<<"    "<<std::left<<std::setfill(' ')<<setw(5)<<s.pseudo<<"        "<<s.address<<endl;
				 flag=1;
				break;
				}
			 }
			 if(flag==0)
			 cout<<"Pseudo op not found";
			 flag=0;
			 break;
		case 3: cout<<"Enter pseudo op name:";
			cin>>s.pseudo;
			cout<<"Enter address:";
			cin>>s.address;
			fseek(fp,0,SEEK_END);
			fwrite(&s,symsize,1,fp);
			i++;
			break;
		case 4: cout<<"Enter pseudo op to modify:";
			cin>>ss;
			rewind(fp);
		      while(fread(&s,symsize,1,fp)==1)
		    	{
				if(strcmp(ss,s.pseudo)==0)
				{
				cout<<"------old values------";
				cout<<"\n   pseudo op     address  "<<endl;
			     cout<<"    "<<std::left<<std::setfill(' ')<<setw(5)<<s.pseudo<<"        "<<s.address<<endl;
				 cout<<"------new values------\n";
				cout<<"Enter psudo op name:";
				cin>>s.pseudo;
				cout<<"Enter address:";
				cin>>s.address;
				fseek(fp,-symsize,SEEK_CUR);
				fwrite(&s,symsize,1,fp);
				flag=1;
				break;
				}
			 }
			 if(flag==0)
			 cout<<"Pseudo op not found";
			 flag=0;
			 break;
		case 5:  cout<<"Enter pseudo op to delete:";
			cin>>ss;
			rewind(fp);
			ft=fopen("temp.txt","w+");
		    while(fread(&s,symsize,1,fp)==1)
		    {
		      if(strcmp(ss,s.pseudo)!=0)
				fwrite(&s,symsize,1,ft);
			}
			fclose(fp);
			fclose(ft);
			remove("pot.txt");
			rename("temp.txt","pot.txt");
			fp=fopen("pot.txt","r+");
			 break;
		 default: cout<<"wrong choice";
			  fclose(fp);
			  exit(0);
	   }
	  }while(1);
	  fclose(fp);
}
