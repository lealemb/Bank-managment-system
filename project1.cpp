#include <iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
using namespace std;

struct account
{
	int acno;
	char name[50];
	int deposit;
	char type;
};

	void write_account();
	void display_all();
	void display_sp(int);
	void modify_account(int);
	void delete_account(int);
	void deposit_withdraw(int, int);
	void intro();
	
	account ac;

int main(int argc, char** argv)
 {
	
	system("color 3E");
	char ch;
	int num;
	intro();
	system("cls");
	do
	{
		
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t1. NEW ACCOUNT";
		cout<<"\n\n\t2. DEPOSIT AMOUNT";
		cout<<"\n\n\t3. WITHDRAW AMOUNT";
		cout<<"\n\n\t4. BALANCE ENQUIRY";
		cout<<"\n\n\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t6. CLOSE AN ACCOUNT";
		cout<<"\n\n\t7. MODIFY AN ACCOUNT";
		cout<<"\n\n\t8. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) :" ;
		cin>>ch;
		
		 switch(ch)
		  {
		case '1':
		  	write_account();
		  	break;
		case '2':
		  	cout<<"\n\n\tEnter The account No. :"; cin>>num;
		  	deposit_withdraw(num, 1);
		  	break;
		case '3':
		  	cout<<"\n\n\tEnter The account No. :"; cin>>num;
		  	deposit_withdraw(num, 2);
		  	break;
		case '4':
		  	cout<<"\n\n\tEnter The account No. :"; cin>>num;
		  	display_sp(num);
		  	break;
		case '5':
		 	display_all();
		  	break;
		case '6':
		  	cout<<"\n\n\tEnter The account NO. :"; cin>>num;
		  	delete_account(num);
		  	break;
		case '7':
		  	cout<<"\n\n\tEnter The account NO. :"; cin>>num;
		  	modify_account(num);
		  	break;
		case '8':
			cout<<"\n\n\tThanks for using bank managment system";
			break;
			 default :cout<<"\a\a\a\a\a\a\a";
		  }
		 cin.ignore();
		 cin.get();
		 
	}while(ch!='8');
	return 0;
}


//***********************************************************************
//                          function to wrtie a file
//***********************************************************************



	void write_account()
	{
		account ac;
		ofstream outFile;
		outFile.open("accounted1.dat",ios::binary|ios::app);
		cout<<"\nEnter account No. :";
		cin>>ac.acno;
		cout<<"\nEnter The name of The account Holder :";
		cin.ignore();
		cin.getline(ac.name, 50);
		cout<<"\nEnter Type of The accountn(c/s) :";
		cin>>ac.type;
		ac.type=toupper(ac.type);
		cout<<"\nEnter The Initial amount(>=500 for saving and >=1000 for current ) :";
		cin>>ac.deposit;
		cout<<"\n\n\nAccount Created..\n";
		cout<<"\tpress ant key to get started !!";
		outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		outFile.close();
	}
	
	//*********************************************************
	//          function to read specific record drom file
	//**********************************************************
	
	void display_sp(int n)
	{
		account ac;
		bool flag=false;
		ifstream inFile;
		inFile.open("account.dat", ios::binary);
		if(!inFile)
		{
			cout<<"File could not be open ! press any key..";
			return;
		}
	cout<<"\nBALANCE DETAILS\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))	
	{
		if(ac.acno==n)
		{
			cout<<"\nAccount No. :"<<ac.acno;
			cout<<"\nAccount Holder Name :";
			cout<<ac.name;
			cout<<"\nType of Account :"<<ac.type;
			cout<<"\n Balance amount :"<<ac.deposit;
			flag=true;
			cout<<"\tpress any key to get started!!";
			}
		}
		inFile.close();
		if(flag=false)
			cout<<"\n\nAccount number does not exist";
			cout<<"\tpress any key to get started !!";
			}
			
			
		//*******************************************************
		//               function to modify record of file
		//*******************************************************
		
		void modify_account(int n)
		{
			bool found=false;
			account ac;
			fstream File;
			File.open("accounted1.dat", ios::binary|ios::in|ios::out);
			if(!File)
			{
				cout<<"File could not be open !! press any key ...";
				return;
			}
		while(!File.eof() && found==false)
		{
			File.read(reinterpret_cast<char *> (&ac), sizeof(account));
			 if(ac.acno==n)
			 {
			 	cout<<"\nAccount No. :"<<ac.acno;
			 	cout<<"\nAccount Holder Name :";
			 	cout<<ac.name;
			 	cout<<"\nType of Account :"<<ac.type;
			 	cout<<"\nBalance amount :"<<ac.deposit<<endl<<endl;
			 	
			 	cout<<"\n\nEnter The new Details of account"<<endl;
			 	cout<<"\nAccount No. :"<<ac.acno;
			 	cout<<"\nModify Account Holder Name :";
			 	cin.ignore();
			 	cin.getline(ac.name, 50);
			 	cout<<"\nModify Type of Account :";
			 	cin>>ac.type;
			 	ac.type=toupper(ac.type);
			 	cout<<"\nModify Balance Amount :";
			 	cin>>ac.deposit;
			 	int pos=(-1)*static_cast<int>(sizeof(account));
			 	File.seekp(pos, ios::cur);
				 File.write(reinterpret_cast<char *> (&ac), sizeof(account));
				 cout<<"\n\n\t Recored Updated !!!";
				  found==true;
				  cout<<"\tpress any key to get started !!" ;
			}
		}
		File.close();
		if(found==false)
		cout<<"\n\n  Record  NOt Found ";
		}
		
		void delete_account (int n)
		{
			account ac;
			ifstream inFile;
			ofstream outFile;
			inFile.open("accounted1.dat", ios::binary);
			if(!inFile)
			{
				cout<<"File could not be open !! press any key ...";
				return;
			}
			outFile.open("Temped1.dat", ios::binary);
			inFile.seekg(0, ios::beg);
			while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
		{
			if(ac.acno!=n)
			{
			 	outFile.write(reinterpret_cast <char *> (&ac), sizeof(account));
			}
		}
		inFile.close();
		outFile.close();
		remove("accounted1.dat");
		rename("Temped1.dat", "accounted1.dat");
		cout<<"\n\n\tRecord Deleted ..";
		cout<<"\tpress any key to get started !!";
		}
		
		void display_all()
		{
			account ac;
			ifstream inFile;
			inFile.open("accounted1.dat", ios::binary);
			if(!inFile)
			{
				cout<<"File could not open !! press any key ...";
				return;
			}
			cout<<"\n\n\tACCOUNT HOLDER LIST\n\n";
			cout<<"================================================\n";
			cout<<"A/c no.         NAME             type  Balance\n";
			cout<<"==================================================\n";
			while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
			{
				cout<<ac.acno<<setw(10)<<" "<<ac.name<<setw(10)<<" "<<ac.type<<setw(6)<<ac.deposit<<endl;
				}
		inFile.close();
		}
		
		void deposit_withdraw(int n, int option)
		{
			int amt;
			bool found=false;
			account ac;
			fstream File;
			File.open("accounted1.dat", ios::binary|ios::in|ios::out);
			if(!File)
			{
				cout<<"File could not be open !! press any key..";
				return;
			}
			while(!File.eof() && found==false)
			{
		File.read(reinterpret_cast <char *> (&ac), sizeof(account) );
		if(ac.acno==n)
		{
			cout<<"\nAccount No. :"<<ac.acno;
			cout<<"\nAccount Holder Name :";
			cout<<ac.name;
			cout<<"\nType of Account :"<<ac.type;
			cout<<"\nBalance amount : "<<ac.deposit<<endl<<endl;
			
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSIT AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.deposit+=amt;
			}
			if (option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.deposit-amt;
				if((bal<500 && ac.type=='S') || (bal<100 && ac.type=='C'))
				 	cout<<"Insufficience balance";
				 	else
				 	ac.deposit-=amt;
				 	}
				 	int pos=(-1)*static_cast<int>(sizeof(ac));
				 	File.seekp(pos, ios::cur);
				 	File.write(reinterpret_cast<char *> (&ac), sizeof(account));
				 	cout<<"\n\n\t Record Updated";
				 	found=true;
				 	}		
			}
			File.close();
			if(found==false)
			cout<<"\n\n Record Not Found";
			
		}
		
		
		void intro()
		{
			cout<<"******************************************************\n";
			cout<<"\n*\n*\n*\tThis is from Addis Ababa University\t\t\n*";
			cout<<"\tplease, Follow me on Githube to get more projects      \n";
			cout<<"\tStay tunned with me!!";
			cout<<"\n*\n*****************************************************\n";
			cout<<endl;
			cout<<"\tpress any key to get started !!";
			cin.get();
			
			
		}
