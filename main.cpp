/*DS PROJECT
"PHONE DIRECTORY"

Group Members:
Muhammad Anus  
Saad-ur-Rrehman 

Section: B
*/
#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include<io.h>
using namespace std;
void gotoxy(short x, short y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int main();
class Member
{
public:
	string name;
	string sim_name;
	long long int sim_no;
	string cnic;
	float balance;
	string email;
	char gender;
	long long int last_call;
	int seconds;
	Member *left;
	Member *right;
	Member *next;
	void dec_balance(long long int,int);
};
class Queuery
{
	Member *front;
	Member *rear;
	public:
		Queuery()
		{
			front=rear=NULL;
		}
		void Enqueue(string a,string b,char c)
		{
		    Member *newnode=new Member;
			newnode->next=NULL; 
			newnode->name =a ;
			newnode->cnic =b;
			newnode->gender =c;
			if((front&&rear)==NULL)
			{
				front=rear=newnode;
			}
			else
			{
				rear->next=newnode;
				rear=newnode;
			}				
        }
        void Dequeue()
        {
        	if(front->next==NULL)
        	{
        		front=NULL;
        		rear=NULL;
			}
			else
			{
				Member *temp=front;
				front=front->next;
        		delete temp;	
			}
		}
		void appointment()
		{
			string msg="SORRY LIMIT OF MEMBERS EXCEED...YOU SHOULD WAIT A WHILE FOR APPOINTMENT :";
			string a,b,name,sim_name,cnic,email,chk;
			int bal,flag=0,count=0;
			long long int mob_no;
			char gen;
			ifstream in;
			in.open("appointment.txt",ios::app);
			while(!in.eof())
			{
				getline(in,chk);
				count++;	
			}
			count--;
			in.close();
			if(count<10)
			{
				gotoxy(45, 15);
				cout<<"Enter Name: ";
				cin>>a;
				gotoxy(45, 17);
				cout<<"enter cnic: ";
				cin>>b;
				ifstream fin;
				ofstream fout;
				fout.open("appointment.txt",ios::app);
				fin.open("file.txt",ios::app);
				while(!fin.eof())
				{
					fin >> name >> sim_name >> mob_no >> cnic >> bal >> gen;getline(fin,email);	
					if(a==name && b==cnic )
					{
						Enqueue(name,cnic,gen);
						flag=1;
						fout<<name<<"\t"<<cnic<<"\t"<<gen<<endl;
						gotoxy(45, 20);
						cout<<"You are registered for appointment..\n";
						break;
					}
				}
				if(flag==0)
				{
					gotoxy(45, 20);
					cout<<"Sorry You are not our member..";
				}
				fin.close();
				
			}
			else
			{
			
				gotoxy(42,15);
				int a=0;
				system("color 0a");
				while(msg[a]!='\0')
				{
					cout<<msg[a];
					if(msg[a]!=' ' && msg[a]!='\0')
					{
						Beep(950,100);
					}
					Sleep(00);
					a++;
				}	
			}
			int c;
			gotoxy(45, 24);
			cout<<"Press 1 for take appointment, press 2 for go on mainmenu :";
			cin>>c;
			if(c==1)
			{
				system("cls");
				appointment();
			}
			else if(c==2)
			{
				system("cls");
				main();
			}
			
			
	}
		int isempty()
		{
			if(front==NULL)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		
        void delete_appointment()
        {
        	int flag=0;
        	string name,cnic;
        	char gen;
        	ifstream fin;
        	Queuery obj;
        	fin.open("appointment.txt",ios::app);
        	while(fin>>name>>cnic>>gen)
        	{
        		obj.Enqueue(name,cnic,gen);
			}
        	fin.close();
        	obj.Dequeue();
        	obj.display_file();
		}
		void display_file()
		{
			Member *temp=front;
			ofstream fout;
			fout.open("temp.txt");
        	while(temp!=NULL)
        	{
        		fout<<temp->name<<"\t"<<temp->cnic<<"\t"<<temp->gender<<endl;
        		temp=temp->next;
			}
			fout.close();
			remove("appointment.txt");
			rename("temp.txt","appointment.txt");
		}
        int display_console()
        {
        	string name,cnic;
        	char gen;
        	int flag=1;
        	ifstream fin;
        	fin.open("appointment.txt",ios::app);
        	cout<<"NAME\t\tCNIC\t\t\tGENDER\n\n";
			while(fin>>name>>cnic>>gen)
        	{
        		flag=0;
        		cout<<name<<"\t\t"<<cnic<<"\t\t"<<gen<<endl;
			}	
			fin.close();
			return flag;
		}
		void complete_appointment()
		{
			system("cls");
			int flag;
			flag=display_console();
			int choice;
			cout<<"\n\n\n\n\n\t\t\t\t\tPress 1 for HAVE YOUR QUERY HAS BEEN RESOLVED\n\n";
			cout<<"\t\t\t\t\tPress 2 for GO TO MAINMENU\n\n";
			cout<<"\t\t\t\t\t";
			cin>>choice;
			system("cls");
			switch(choice)
			{
				case 1:
					{
						
						if(flag==1)
						{
							
							cout<<"\n\n\n\n\n\n\t\t\t\t\t\tNO Member in a queue..";
							cout<<"\n\n\n\n\t\t\t\t\tpress any key for go to mainmenu..";
							getch();
							system("cls");
							main();
						}
						else
						{
							delete_appointment();
					    	complete_appointment();	
						}
								
					}
					break;
				case 2:
				    main();
					break;
				default:
				cout<<"\n\n\t\t\tPlease Enter a valid Number...";
				cout<<"press any key for continue..";
				getch();
				system("cls");
				complete_appointment();
			}
		}
};
class package
{
	public:
	string s_name;
	string type;
	int mbs;
	int sms;
	int call_min;
	string code;
	int charges;
	package *left;
	package *right;
};
void Member::dec_balance(long long int num,int charges )
	 {
	 	string name,sim_name,all;
		long long int mob_no;
		int bal;
	 	ofstream e;
	 	e.open("new.txt",ios::out);
	 	ifstream fin;
	 	fin.open("file.txt",ios::in);
	 	while(!fin.eof())
	 	{
	 		fin >> name >> sim_name >> mob_no>>cnic>>bal; getline(fin,all);
	 		
	 		if(mob_no==num)
	 		{
	 			bal=bal-charges;
	 			e<<name<<"\t"<<sim_name<<"\t"<<mob_no<<"\t"<<cnic<<"\t"<<bal<<"\t"<<all<<endl;
			}
	 		else
	 		{
	 			e<<name<<"\t"<<sim_name<<"\t"<<mob_no<<"\t"<<cnic<<"\t"<<bal<<"\t"<<all<<endl;
	 		}
	 		
		}
	 	fin.close();
	 	e.close();
	 	remove("file.txt");
		rename("new.txt","file.txt");
	 }

class BST : protected Member
{
public:
	Member *root;
	package *root1;
	BST()
	{
		root = NULL;
		root1=NULL;
	}

	void add_data()
	{
		int flag;
		ofstream file;
		file.open("file.txt", ios::app);
		//gotoxy(45,18);
		cout << "\n\n\t\t\tENTER YOUR NAME (UPPER CASE) :";
		fflush(stdin);
		getline(cin, name);
		
		cout << "\n\n\t\t\tENTER YOU SIM NAME :(UPPER-CASE)";
		cin >> sim_name;
		while (1)
		{
			try
			{

				if (sim_name == "JAZZ")
				{
					fflush(stdin);
					cout << "\n\n\t\t\tENTER YOUR JAZZ SIM NO (0300#######):";
					cin >> sim_no;
					if(sim_no >= 3000000000 && sim_no <= 3099999999)
					{
						break;
					}
					else
					{
						throw -1;
					}
				}
				else if (sim_name == "UFONE")
				{
					fflush(stdin);
					cout << "\n\n\t\t\tENTER YOUR UFONE SIM NO (0330#######):";
					cin >> sim_no;
					if (sim_no >= 3300000000 && sim_no <= 3399999999)
					{
						break;
					}
					else
					{
						throw -1;
					}
				}
				else if (sim_name == "ZONG")
				{
					fflush(stdin);
					cout << "\n\n\t\t\tENTER YOUR ZONG SIM NO (0310#######):";
					cin >> sim_no;
					if (sim_no >= 3100000000 && sim_no <= 3199999999)
					{
						break;
					}
					else
					{
						throw -1;
					}
				}
				else if (sim_name == "TELENOR")
				{
					fflush(stdin);
					cout << "\n\n\t\t\tENTER YOUR TELENOR SIM NO (0340#######):";
					cin >> sim_no;
					if (sim_no >= 3400000000 && sim_no <= 3499999999)
					{
						break;
					}
					else
					{
						throw -1;
					}
				}
			}
			catch (...)
			{
				cout << "\n\n\t\t\tPLEASE ENTER IN CORRECT BAR CODE\n";
			}
		}
		while (1)
		{
			try
			{
				cout << "\n\n\t\t\tENTER YOUR CNIC NO :(#####-#######-#)";
				cin >> cnic;
				if (cnic[5] == '-' && cnic[13] == '-')
				{
					break;
				}
				else
				{
					throw -1;
				}
			}
			catch (...)
			{
				cout << "\n\n\t\t\tPLEASE ENTER DATA IN CORRECT FORMAT I.E(#####-#######-#)\n";
			}
		}
		cout << "\n\n\t\t\tENTER YOUR BALANCE IN THE SIM";
		cin >> balance;
		fflush(stdin);
		cout << "\n\n\t\t\tENTER YOUR EMAIL :";
		cin >> email;
		cout << "\n\n\t\t\tENTER YOUR GENDER (F/M)";
		cin >> gender;
		file << name << "\t" << sim_name << "\t" << sim_no << "\t" << cnic << "\t" << balance << "\t" << gender << "\t" << email << endl;
		//	cout<<name<<" "<<sim_name<<" "<<sim_no<<" "<<cnic<<" "<<balance<<" "<<email<<" "<<gender;
		int c;
		cout<<"\n\n\n\n\t\t\t\tPress 1 for add another data, Press 2 for mainmenu : ";
		cin>>c;
		system("cls");
		if(c==1)
		{
			fflush(stdin);
			add_data();
		}
		else if(c==2)
		main();
	}

	void createnode(string a, string b, long long int c, string d, float e, char f, string i)
	{
		Member *newnode = new Member;
		newnode->name = a;
		newnode->sim_name = b;
		newnode->sim_no = c;
		newnode->cnic = d;
		newnode->balance = e;
		newnode->gender = f;
		newnode->email = i;
		newnode->right = NULL;
		newnode->left = NULL;
		insertnode(root, newnode);
	}

	Member *insertnode(Member *&root, Member *&newnode)
	{
		if (root == NULL)
		{
			root = newnode;
		}
		else if (newnode->sim_no < root->sim_no)
		{
			insertnode(root->left, newnode);
		}
		else if (newnode->sim_no > root->sim_no)
		{
			insertnode(root->right, newnode);
		}
	}
	void createnode1(string a, string b, long long int c, string d, float e, char f, string i)
	{
		Member *newnode = new Member;
		newnode->name = a;
		newnode->sim_name = b;
		newnode->sim_no = c;
		newnode->cnic = d;
		newnode->balance = e;
		newnode->gender = f;
		newnode->email = i;
		newnode->right = NULL;
		newnode->left = NULL;
		insertnode1(root, newnode);
	}

	Member *insertnode1(Member *&root, Member *&newnode)
	{
		if (root == NULL)
		{
			root = newnode;
		}
		else if (newnode->name < root->name)
		{
			insertnode1(root->left, newnode);
		}
		else if (newnode->name > root->name)
		{
			insertnode1(root->right, newnode);
		}
	}
	
	void Display()
	{
		Member *temp;
		temp = root;
		cout << "\nNAME\t\t\tSIM NAME\tSIM NUMBER\t\tCNIC\t\t\tBALANCE\t\tGENDER\t\t\tEMAIL\n";
		printinorder(temp);
		int c;
		cout<<"\n\n\n\n\t\t\t\tPress 1 for add another data, Press 2 for mainmenu : ";
		cin>>c;
		system("cls");
		if(c==1)
		{
			fflush(stdin);
			show_data();
		}
		else if(c==2)
		main();
	}
	void printinorder(Member *temp)
	{
		if (temp == NULL)
		{
			return;
		}
		else
		{
			printinorder(temp->left);
			cout << temp->name << "\t\t\t" << temp->sim_name << "\t\t" << temp->sim_no << "\t\t" << temp->cnic << "\t\t" << temp->balance << "\t\t" << temp->gender << "\t" << temp->email << endl;
			printinorder(temp->right);
		}
	}
	void search_by_cnic()
	{
		string name, sim_name, cnic, email;
		long long int mob_no;
		char gen;
		float bal;
		int i;
		string n;
		int flag = 0;
		gotoxy(37,12);
		cout << "ENTER CNIC NUMBER YOU WANT TO SEARCH (#####-#######-#):";
		cin >> n;
		ifstream fin;
		fin.open("file.txt");
		while (!fin.eof())
		{
			fin >> name >> sim_name >> mob_no >> cnic >> bal >> gen;
			getline(fin, email);

			if (n == cnic)
			{
				flag = 1;
				//system("color 0a");
				cout << "\n\n\n\t\t\t\t\t-----------SEARCHING THE DATA-------------\n\n";
				char a = 177, b = 219;
				cout << a;
				cout << "\t\t\t\t";
				cout << a;
				for (int i = 0; i <= 40; i++)
				{
					cout << a;
				}
				cout << "\r";
				cout << "\t\t\t\t";
				for (int i = 0; i <= 40; i++)
				{
					cout << b;
					Sleep(100);
				}
				system("cls");
				cout << "\nNAME\t\tSIM NAME\tSIM NUMBER\tCNIC\t\t\tBALANCE\t\tGENDER\t\tEMAIL\n";
				cout << name << "\t\t" << sim_name << "\t\t" << mob_no << "\t" << cnic << "\t\t" << bal << "\t\t" << gen << "\t" << email << endl;
				break;
			}
		}
		if (flag != 1)
		{
			cout << "SORRY!! CNIC NUMBER NOT FOUND";
		}
		fin.close();
		int c;
		cout<<"\n\n\n\n\t\t\t\tPress 1 for another search, Press 2 for mainmenu : ";
		cin>>c;
		system("cls");
		if(c==1)
		{
			fflush(stdin);
			search();
		}
		else if(c==2)
		main();
	}
	void search_by_sim_no()
	{
		long long int n;int flag=0;
		sort_by_num();
		Member*temp=root;
		gotoxy(45,13);
		cout<<"ENTER SIM NUMBER YOU WANT TO SEARCH :";
        cin>>n;
		while(temp!=NULL)
		{
			if(n==temp->sim_no)
			{
				flag = 1;
				//system("color 0a");
				cout << "\n\n\n\t\t\t\t\t-----------SEARCHING THE DATA-------------\n\n";
				char a = 177, b = 219;
				cout << a;
				cout << "\t\t\t\t";
				cout << a;
				for (int i = 0; i < 40; i++)
				{
				cout << a;
			    }
				cout << "\r";
				cout << "\t\t\t\t";
				for (int i = 0; i <= 40; i++)
				{
					cout << b;
					Sleep(100);
				}
				system("cls");
				cout << "\nNAME\t\tSIM NAME\tSIM NUMBER\tCNIC\t\t\tBALANCE\t\tGENDER\t\tEMAIL\n";
				cout << temp->name<<"\t\t"<<temp->sim_name<<"\t\t"<<temp->sim_no<<"\t"<<temp->cnic<<"\t\t"<<temp->balance<<"\t\t"<<temp->gender<<"\t"<<temp->email<<endl;
				break;
			}
			if(n<temp->sim_no)
			{
				temp=temp->left;
			}
			else if(n>temp->sim_no)
			{
				temp=temp->right;
		}
		
		}
		if(flag!=1)
		{
			cout<<"SORRY!! SIM NUMBER NOT FOUND";
		}
		
		int c;
		cout<<"\n\n\n\n\t\t\t\tPress 1 for another search, Press 2 for mainmenu : ";
		cin>>c;
		system("cls");
		if(c==1)
		{
			fflush(stdin);
			search();
		}
		else if(c==2)
		main();
		
}
	void delete_data()
	{
		long long int num;
		sort_by_num();
		gotoxy(45,13);
		cout<<"enter mobile number: ";
		cin>>num;
		if(deletion(root,num)==1)
		{
			gotoxy(45,16);
			cout<<"data successfully deleted..";
			ofstream fout;
			fout.open("temp.txt");
			printpreorder(root,fout);
			fout.close();
			remove("file.txt");
			rename("temp.txt","file.txt");			
		}
		else
		{
			gotoxy(45,16);
			cout<<"data not found...";	
		}
		
		int c;
		gotoxy(45,23);
		cout<<"Press 1 for delete more data, Press 2 for mainmenu : ";
		cin>>c;
		system("cls");
		if(c==1)
		delete_data();
		else if(c==2)
		main();
		
	}
	
	void printpreorder(Member* temp,ofstream &fout)
	{
		if(temp==NULL)
		{
			return;
		}
		else
		{
			fout << temp->name<<"\t"<<temp->sim_name<<"\t"<<temp->sim_no<<"\t"<<temp->cnic<<"\t"<<temp->balance<<"\t"<<temp->gender<<"\t"<<temp->email<<endl;
			printpreorder(temp->left,fout);
			printpreorder(temp->right,fout);
			
		}
	}
	Member* findmin(Member* temp)
	{
		while(temp->left != NULL) temp = temp->left;
		return temp;
	}
	int deletion(Member*& root,long long int data)
	{
		if(root==NULL)
			{
				return 0;
			}
		else if(data < root->sim_no)
			{
				deletion(root->left,data);
			}
			else if(data > root->sim_no)
			{
				deletion(root->right,data);		
			}
			else
			{
					if(root->left==NULL && root->right==NULL)
					{
						delete root;
						root=NULL;
					}
					
						else if(root->left==NULL)
						{
							Member *temp;
							temp=root;
							root=root->right;
							delete temp;
						}
						else if(root->right==NULL)
						{
							Member *temp;
							temp=root;
							root=root->left;
							delete temp;
						}
						else
						{
							Member *temp=findmin(root->right);
							root->name=temp->name;
							root->sim_name=temp->sim_name;
							root->sim_no=temp->sim_no;
							root->cnic=temp->cnic;
							root->balance=temp->balance;
							root->gender=temp->gender;
							root->email=temp->email;
							deletion(root->right,temp->sim_no);
						}
						return 1;
				}
			}
	
	void search()
	{
		int opt;
		gotoxy(45,11);
		cout << "1.SEARCH BY CNIC\n";
		gotoxy(45,13);
		cout << "2.SEARCH BY SIM NUMBER\n";
		gotoxy(45,15);
		cout << "ENTER YOUR CHOICE :";
		cin >> opt;
		system("cls");
		switch (opt)
		{
		case 1:
			search_by_cnic();
			break;

		case 2:
			search_by_sim_no();
			break;
		default:
		cout<<"\n\n\t\t\tPlease Enter a valid Number...";
		cout<<"press any key for continue..";
		getch();
		system("cls");
		search();	
		}
	}
	void sort_by_num()
	{
		string name, sim_name, cnic, email;
		long long int mob_no;
		char gen;
		float bal;
		ifstream fin;
		fin.open("file.txt");
		while (!fin.eof())
		{
			fin >> name >> sim_name >> mob_no >> cnic >> bal >> gen;
			getline(fin, email);
			//cout<<name<<"\t"<<sim_name<<"\t"<<mob_no<<"\t"<<cnic<<"\t"<<bal<<"\t"<<gen<<"\t"<<last_call<<"\t"<<sec<<"\t"<<email<<endl;
			//j++;
			createnode(name, sim_name, mob_no, cnic, bal, gen, email);
		}
		fin.close();		
	}
	void sort_by_name()
	{
		string name, sim_name, cnic, email;
		long long int mob_no;
		char gen;
		float bal;
		ifstream fin;
		fin.open("file.txt");
		while (!fin.eof())
		{
			fin >> name >> sim_name >> mob_no >> cnic >> bal >> gen;
			getline(fin, email);
			createnode1(name, sim_name, mob_no, cnic, bal, gen, email);
		}
		fin.close();
	}
	void show_data()
	{
		int opt;
		gotoxy(45, 11);
		cout << "1. SORT BY NAME";
		gotoxy(45, 13);
		cout << "2.SORT BY MOB NUMBER";
		gotoxy(45, 21);
		cout << "enter your choice: ";
		cin >> opt;
		system("cls");
		
		switch (opt)
		{
		case 1:
			sort_by_name();
			Display();
			break;
		case 2:
			sort_by_num();
			Display();
			break;
			
		default:
		cout<<"\n\n\t\t\tPlease Enter a valid Number...";
		cout<<"press any key for continue..";
		getch();
		system("cls");
		show_data();		
		}
	}
	
	void call_history()
	{
		 string name,sim_name,date,time;
		 long long int sim_no,last_call;
		 long long int n;
		 int seconds;
		 int flag=0;
         ifstream fin;
		 fin.open("History.txt");
		 gotoxy(37,13);
		 cout<<"ENTER THE MOBILE NUMBER TO EXTRACT HISTORY: ";
		 cin>>n;
		 while(!fin.eof())
		 {
			fin>>name>>sim_name>>sim_no>>last_call>>seconds;
			getline(fin,date);
			 if(n==sim_no)
			 {
			 	flag=1;
			 	system("cls");
				cout<<"\n\n\n\nNAME\tSIM NAME\tSIM NUMBER\tLAST CALL\t SECONDS\t DATE\t\tTIME\n\n";
				cout<<name<<"\t"<<sim_name<<"\t\t"<<sim_no<<"\t"<<last_call<<"\t"<<seconds<<"\t"<<date<<endl;
				break;
			 }
		 }
		 if(flag!=1)
		 {
		 	gotoxy(45,17);
			 cout<<"\nSORRY THERE IS NO SUCH HISTORY RELATED TO GIVEN NUMBER !!";
		 }
		 int c;
		gotoxy(45,23);
		cout<<"Press 1 for search more history, Press 2 for mainmenu : ";
		cin>>c;
		system("cls");
		if(c==1)
		call_history();
		else if(c==2)
		main();
		 
		 
	}
	void createnode2(string a, string b,int c,int d,int e, string f, int g,string sim)
	{
		package *newnode = new package;
		newnode->s_name = a;
		newnode->type = b;
		newnode->mbs = c;
		newnode->call_min = d;
		newnode->sms = e;
		newnode->code = f;
		newnode->charges = g;
		newnode->right = NULL;
		newnode->left = NULL;
		insertnode2(root1, newnode,sim);
	}

	Member *insertnode2(package *&root1, package *&newnode,string sim)
	{
		if(newnode->s_name==sim)
		{
			if (root1 == NULL)
			{
				root1 = newnode;
			}
			else if ((newnode->charges < root1->charges))
			{
				insertnode2(root1->left, newnode,sim);
			}
			else if ((newnode->charges > root1->charges))
			{
				insertnode2(root1->right, newnode,sim);
			}
		}
		
	}
	void display_package(package *temp)
	{
		if (temp == NULL)
		{
			return;
		}
		else
		{
			display_package(temp->left);
			cout << temp->s_name << "\t" << temp->type << "\t" << temp->mbs << "\t" << temp->call_min << "\t" << temp->sms << "\t" << temp->code << "\t" << temp->charges << endl;
			display_package(temp->right);
		}
	}
	

	void show_all_packages()
	{
		ifstream fin;
		int opt;
		string a,b,f;
		int c,d,e,g;
		fin.open("package.txt",ios::app);
		gotoxy(45, 9);
		cout<<"1.JAZZ";
		gotoxy(45, 11);
		cout<<"2.ZONG";
		gotoxy(45, 13);
		cout<<"3.UFONE";
		gotoxy(45, 15);
		cout<<"4.TELENOR";
		gotoxy(45,17);
		cout<<"enter your choice: ";
		cin>>opt;
		system("cls");
		switch(opt)
		{
			case 1:
				while(!fin.eof())
				{
					fin>>a>>b>>c>>d>>e>>f>>g;
					createnode2(a,b,c,d,e,f,g,"JAZZ");
				}
				break;
			case 2:
				while(!fin.eof())
				{
					fin>>a>>b>>c>>d>>e>>f>>g;
					createnode2(a,b,c,d,e,f,g,"ZONG");
				}
				break;
			case 3:
				while(!fin.eof())
				{
					fin>>a>>b>>c>>d>>e>>f>>g;
					createnode2(a,b,c,d,e,f,g,"UFONE");
				}
				break;
			case 4:
				while(!fin.eof())
				{
					fin>>a>>b>>c>>d>>e>>f>>g;
					createnode2(a,b,c,d,e,f,g,"TELENOR");
				}
				break;
			default:
			cout<<"\n\n\t\t\tPlease Enter a valid Number...";
			cout<<"press any key for continue..";
			getch();
			system("cls");
			show_all_packages();
				
		}
		display_package(root1);
		root1=NULL;
		fin.close();
		int n;
		cout<<"\n\n\n\n\t\t\t\tPress 1 for show more packages, Press 2 for mainmenu : ";
		cin>>n;
		system("cls");
		if(n==1)
		{
		fflush(stdin);
		show_all_packages();
		}
	
		else if(n==2)
		main();
	}
	
	void package_registration(BST &obj)
	{
		long long int num;string code;
		gotoxy(45,13);
		cout<<"enter mobile number: ";
		cin>>num;
		gotoxy(45,15);
		cout<<"enter package code: ";
		cin>>code;
		ifstream fin,pin;
		fin.open("file.txt",ios::app);
		pin.open("package.txt",ios::app);
		ofstream fout;
		fout.open("res_pack.txt",ios::app);
		int flag=0,flag1=0;
		string name,sim_name,all;
		long long int mob_no;
		string cnic;int bal;
		while(!fin.eof())
		{
			fin >> name >> sim_name >> mob_no>>cnic>>bal; getline(fin,all);
			if(mob_no==num)
			{
				flag=1;
				break;
			}
		}
		string a,b,f;
		int c,d,e,g;
		while(!pin.eof())
		{
			
			pin>>a>>b>>c>>d>>e>>f>>g;
			if(code==f)
			{
				flag1=1;
				break;
			}
		}
		if(flag==1 && flag1==1)
		{
			if(sim_name==a)
			{
				if(bal>=g)
				{
					fout<<sim_name<<"\t"<<mob_no<<"\t"<<b<<"\t"<<code<<"\t"<<c<<"\t"<<d<<"\t"<<e<<"\n";	
					fin.close();
					cout<<"package successfully registered...";
					obj.dec_balance(mob_no,g);
					
				}	
				else
				cout<<"your balance is less";
			}
			else
			cout<<"please enter valid code...";
			
		}
		else
		cout<<"data not found..";

		pin.close();
		fout.close();
		
		cout<<"\n\n\n\n\t\t\t\tPress 1 for another registration, Press 2 for mainmenu : ";
		cin>>c;
		system("cls");
		if(c==1)
		package_registration(obj);
		else if(c==2)
		main();
	}
	
	void search_reg_packages()
	{
		string s_name,code,pac_type;
		long long int num,a;
		int mbs,sms,call;
		ifstream fin;
		gotoxy(45,13);
		cout<<"Enter Mobile.no: ";
		cin>>a;
		fin.open("res_pack.txt",ios::app);
	
		cout<<"\n\n\nSIM\tMOBILE.NO\tTYPE\tCODE\tMBS\tSMS\tCALL_MINS\n";
		while(!fin.eof())
		{
			fin>>s_name>>num>>pac_type>>code>>mbs>>call>>sms;
			if(a==num)
			{
				cout<<s_name<<"\t"<<num<<"\t"<<pac_type<<"\t"<<code<<"\t"<<mbs<<"\t"<<call<<"\t"<<sms<<endl;
				break;
			}
		}
		fin.close();
		int c;
		cout<<"\n\n\n\n\t\t\t\tPress 1 for another registration, Press 2 for mainmenu : ";
		cin>>c;
		system("cls");
		if(c==1)
		search_reg_packages();
		else if(c==2)
		main();
	}
	void show_reg_packages()
	{
		string s_name,code,pac_type;
		long long int num;
		int mbs,sms,call;
		ifstream fin;
		fin.open("res_pack.txt", ios::app);
		cout<<"\nSIM\tMOBILE.NO\tTYPE\tCODE\tMBS\tSMS\tCALL_MINS\n\n";
		while(fin>>s_name>>num>>pac_type>>code>>mbs>>call>>sms)
		{
			cout<<s_name<<"\t"<<num<<"\t"<<pac_type<<"\t"<<code<<"\t"<<mbs<<"\t"<<call<<"\t"<<sms<<endl;
		}
		fin.close();
		int c;
		cout<<"\n\n\n\n\t\t\t\tPress 1 for delete more serach, Press 2 for mainmenu : ";
		cin>>c;
		system("cls");
		if(c==1)
		show_reg_packages();
		else if(c==2)
		main();
	}
	
	void show_registered_package()
	{
		int opt;
		gotoxy(45,13);
		cout<<"1.Search";
		gotoxy(45,15);
		cout<<"2.Show all";
		gotoxy(45,17);
		cout<<"enter you choice: ";
		cin>>opt;
		system("cls");
		switch(opt)
		{
			case 1:
				search_reg_packages();
				break;
			case 2:
			 	show_reg_packages();
				 break;	
		}	
	}
	void search_feedback()
	{
	    int flag=0;
		long long int n;
		cout<<"ENTER MOBILE NO :";
		cin>>n;
		string name;
		long long int mob;
		string b;
		string review;
		ifstream fin;
		fin.open("Reviews.txt");
		while(!fin.eof())
		{
			fin>>name>>mob;
			getline(fin,review);
	if(mob==n)
	{
		
	ifstream fin1,fin2;int k=0;
	string a;	
	int size;
	int size1;
	fin1.open("Keywords.txt");
	size=0;
	size=review.length();
	char text[size];
	strcpy(text,review.c_str());
	while(getline(fin1,b))
	{
	size1=b.length();
	char key[size1];
	strcpy(key,b.c_str());	
	if(strstr(text,key))
	{
	    flag=1;
		break;	
	}
	else if(!strstr(text,key)) 
	{
		flag=-1;
	}
	else{
	}
	}
	break;
	fin1.close();
}

}
if(flag==1)	
	{
		
		cout<<"THIS CUSTOMER HAS GIVEN POSITIVE REVIEWS\n";
		cout<<"CUSTOMER'S NAME ="<<name<<endl;
		cout<<"CUSTOMER'S FEEDBACK ="<<review<<endl;
	}
	else if(flag==-1)
	{
		cout<<"THIS CUSTOMER HAS GIVEN NEGATIVE REVIEWS"<<endl;
		cout<<"CUSTOMER'S NAME ="<<name<<endl;
		cout<<"CUSTOMER'S FEEDBACK ="<<review<<endl;
	}     
	int c;
	cout<<"\n\n\n\n\t\t\t\tPress 1 for search another feedback, Press 2 for mainmenu : ";
	cin>>c;
	system("cls");
	if(c==1)
	search_feedback();
	else if(c==2)
	main();
		

		
fin.close();
}	

};


int main()
{
	int opt;
	BST b1;
	Queuery q1;
	
	string msg="---------------PHONE DIRECTORY-----------";
	
	int a=0;
	gotoxy(45,06);
	while(msg[a]!='\0')
	{
		
		cout<<msg[a];
		Beep(850,100);
		Sleep(00);
		a++;
	}
	gotoxy(45, 9);
	cout << "1. ADD DATA";
	gotoxy(45, 11);
	cout << "2. SHOW DATA"; 
	gotoxy(45, 13);
	cout << "3. SEARCH DATA "; 
	gotoxy(45, 15);
	cout << "4. SHOW PACKAGES' DETAILS"; 
	gotoxy(45, 17);
	cout << "5. PACKAGE REGISTERATION";
	gotoxy(45, 19);
	cout<<"6.SHOW REGISTERED PACKAGE";
	gotoxy(45,21);
	cout << "7. CALL HISTORY"; 
	gotoxy(45, 23);
	cout << "8. DELETE RECORD"; 
	gotoxy(45, 25);
	cout << "9. APPOINTMENT FOR QUERY";
	gotoxy(45, 27);
	cout << "10. CUSTOMERS WHICH ARE ALREADY IN QUEUE";
	gotoxy(45, 29);
	cout<<"11. DETECT CUSTOMER'S FEEDBACK";
	gotoxy(45, 31);
	cout << "12. EXIT";
	gotoxy(45, 33);
	cout << "ENTER YOUR CHOICE:";
	cin >> opt;
	system("cls");
	switch (opt)
	{
	case 1:
		b1.add_data();
		break;
	case 2:
		b1.show_data();
		break;
	case 3:
		b1.search();
		break;
	case 4:                                                             
		b1.show_all_packages();
		break;
	case 5:
		b1.package_registration(b1);	
		break;	
	case 6:
		b1.show_registered_package();
	 	break;	
	case 7:
		b1.call_history();
		break;	
	case 8:
		b1.delete_data();
		break;
	case 9:
		q1.appointment();
		break;	
	case 10:
	    q1.complete_appointment();
		break;
	case 11:
	     b1.search_feedback();
	     break;
	default:
	{
		cout<<"\n\n\t\t\tPlease Enter a valid Number...";
		cout<<"press any key for continue..";
		getch();
		system("cls");
		main();
	}			
	}
}
