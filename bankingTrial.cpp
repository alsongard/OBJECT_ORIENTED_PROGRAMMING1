#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;
class customer
{
    public:
    char  customerName[100];
    int customerId;
    int customerAge;
    int customerAddress;
    int customerPhoneNumber;

    //methods getDetails(), updateDetails()
    void getDetails();
    void updateDetails();
};

void customer::getDetails()
{
    cout<<"Enter customer Id"<<endl;
    cin>>customerId;
    cout<<"Enter customer Name"<<endl;
    cin.ignore();
    cin.getline(customerName, 100);
    cout<<"Enter the customer age"<<endl;
    cin>>customerAge;
    cout<<"enter phoneNumber"<<endl;
    cin>>customerPhoneNumber;
    cout<<"Enter customer Address"<<endl;
    cin>>customerAddress;
    cout<<"user details have been captured, kindly proceed to create account"<<endl;
}
void customer::updateDetails()
{
    cout<<"enter account number \n";
    cin>>customerId;
    cout<<"Enter customer name \n";
    cin.getline(customerName, 100);
    cout<<"Enter the type of account "<<" Saving account or Family Account"<<endl;
}

class accounts : public customer//main inheritance - getDetails();
{
    public:
	int accountNumber;
	int balance;
    char accountType[20];

    //function belonging to the account class
    void openAccount();
	// void closeAccount();
	void updateAccount(int checkNum);  
	void displayDetails();
	int returnAccountNumber() const
	{
		return accountNumber;
	}
};

void accounts::openAccount()
{   
    cout<<"Enter the Account Number\n";
    cin>>accountNumber;
    //myfile<<accountNumber;
    cout<<"Enter the amount you wish to deposit\n";
    cin>>balance;
	cin.ignore();
    cout<<"Enter the type of account for the user \n"<<"Saving account or Family Account"<<endl;
    cin.getline(accountType, 20);
	cout<<"You acccount is successfully created\n";
	cout<<endl<<endl;
}
void accounts::updateAccount(int checkNum)
{
	accounts accountObject;
	//the account number is provided when updateAccount is called
	//check if account exists
	fstream inFile;
	inFile.open("accountDetails.dat", ios::in | ios::out | ios::binary);
	if (!inFile)
	{
		cout<<"No file was found\n";
	}
	//read data from file
	inFile.read(reinterpret_cast<char *>(&accountObject), sizeof(accounts));
	if (accountObject.returnAccountNumber() == checkNum)
	{
		cout<<"Account has been found \n";
		cout<<"Enter the type of account you wish to change to \n Savings Account \n Family Account"<<endl;
		cin>>accountType;
		//how to change data from file
	}
	cout<<"Account Type has been successfully changed\n";
}
void accounts::displayDetails()
{
	cout<<"Account Number : "<<accountNumber<<endl;
	cout<<"Account User Name : "<<customerName<<endl;
	cout<<"Account type : "<<accountType<<endl;
	cout<<"Account Balance : "<<balance<<endl;
	cout<<endl;
	cout<<endl;
}

class transaction : public accounts//inherit attributes and methods from accounts class
{	
    public:
	//declare methods functions
	void makeDeposit(int checkNumber);
	void makeWithdraw(int checkNumber);
	void updateAccount();
	void getTransactionHistory();
};

void transaction::makeDeposit(int checkNumber)
{
    transaction transactionObject;
    int amount;
    cout<<"Enter the account number of the user  : \n";
    cin>>checkNumber;
    //check if account number exitst - read file and compare
    fstream inFile;
    inFile.open("accountDetails.dat", ios::in |  ios::out | ios::binary);
	fstream outFile;
	outFile.open("accountDetails.dat", ios::out | ios::binary);
    //check existance of file
    if (!inFile)
    {
        cout<<"Error !! No file was currently found, try again later\n";
    }
    inFile.read(reinterpret_cast<char *>(&transactionObject), sizeof(accounts));
    {
        if (transactionObject.returnAccountNumber() == checkNumber)
        {
            cout<<"accountFound and proceed to withdraw \n";
            cout<<"Enter the amount you wish to deposit \n";
            cin>>amount;
            transactionObject.balance = transactionObject.balance + amount;
            cout<<transactionObject.balance<<endl;
            int pos = (-1)*static_cast <int>(sizeof(accounts));
            inFile.write(reinterpret_cast<char *> (&transactionObject), sizeof(accounts));
            cout<<"Records updated successfully \n";
        }
 
    }
}
void transaction::makeWithdraw(int checkNumber)
{
    transaction transactionObject;
    int amount, realNumber;
    //check whether account exist
    //read data from file for comparisons
    fstream inFile;
    inFile.open("accountDetails.dat", ios::in | ios::out | ios::binary);
    //check for file existance 
    if (!inFile)
    {
        cout<<"Error!! the file does not exist\n";
    }
    inFile.read(reinterpret_cast<char *>(&transactionObject), sizeof(accounts));
    if (transactionObject.returnAccountNumber() == checkNumber)
    {
        cout<<"Account found, proceed to withdraw\n";
        cout<<"Enter the amount you wish to withdraw \n";
        cin>>amount;
        //how to withdraw access balance and subtract from amount 
        if(amount < transactionObject.balance)
        {
            cout<<"Current account balance : "<<transactionObject.balance<<endl;
			transactionObject.balance =  transactionObject.balance - amount;
			cout<<"You have successfully withdrawn :"<<amount<<endl;
			cout<<"Your balance is : "<<transactionObject.balance<<endl;
        }
		else
		{
			cout<<"Insufficient Funds, kindly try a lower amount\n"; 
		} 

    }
    
}
void writeAccount();
void closeAccount(int);
void displayAccountDetails(int);
int main()
{

    transaction transactionObject;
	accounts accountObject;
    int choice;
    //PREVENT READ CHARACTERS
	while (choice != 7)
	{
		cout<<"WELCOME TO CRYPTO BANKING SYSTEM"<<endl;
		cout<<"TO GET STARTED, CHOOSE ONE OF THE OPTIONS BELOW"<<endl;
		cout<<"=================MAIN MENU=================="<<endl;
		cout<<"1: CREATE ACCOUNT"<<endl;
		cout<<"2: UPDATE ACCOUNT"<<endl;
		cout<<"3: DISPLAY ACCOUNT"<<endl;
		cout<<"4: WITHDRAW MONEY"<<endl;
		cout<<"5: DEPOSIT MONEY"<<endl;
		cout<<"6: CLOSE ACCOUNT"<<endl;
		cout<<"7: Exit"<<endl;
		cout<<endl;

		cout<<"Choose the options from the above list\n";
		cin>>choice;

			
		int accountNum;
		switch (choice)
		{
			case 1:
				system("clear");
				writeAccount();//create account
				break;
			case 2:
				system("clear");
				cout<<"Enter account number\n";
				cin>>accountNum;
				accountObject.updateAccount(accountNum);//update account details
				break;
			case 3:
				system("clear");
				cout<<"Enter your account number\n";
				cin>>accountNum;
				displayAccountDetails(accountNum);//display user details
				break;
				
			case 4:
				system("clear");
				cout<<"Enter accout number\n";
				cin>>accountNum;
				transactionObject.makeWithdraw(accountNum);//withdraw function
				break;
				
			case 5:
				system("clear");
				cout<<"Enter account Number\n";
				cin>>accountNum;
				transactionObject.makeDeposit(accountNum);//deposit function
				break;
			
			case 6:
				system("clear");
				cout<<"Enter account number\n";
				cin>>accountNum;
				closeAccount(accountNum);//close account
				break;
		}
	}
	cout<<"Thank you for using Crypto Bank. We hope to see you soon\n";
	return (0);
}

void writeAccount()
{
	accounts accountObject;
	fstream outFile;
	outFile.open("accountDetails.dat", ios::app | ios::binary);
	accountObject.getDetails();
	accountObject.openAccount();
	outFile.write(reinterpret_cast<char *>(&accountObject), sizeof(accounts));
	outFile.close();
}
void closeAccount(int num)
{
	// 	int accountNumber; int balance char accountType[20];
	accounts accountsObject;
	
	fstream inFile;
	fstream outFile;
	inFile.open("accountDetails.dat", ios::in | ios::binary);
	if(!inFile)
	{
		cout<<"the file does not exist !!! Check another time\n";
	}
	
	//create a temp file for storing data without the user specified
	outFile.open("temp.dat",ios::out | ios::binary);

	//inFile.seekg(0, ios::beg);

	while(inFile.read(reinterpret_cast<char *>(&accountsObject), sizeof(accounts)))
	{
		if(accountsObject.returnAccountNumber()!= num)
		{
			outFile.write((char *)(&accountsObject), sizeof(accounts));
		}
	}
	inFile.close();
	outFile.close();
	remove("accountDetails.dat");
	rename("temp.dat", "accountDetails.dat");
	cout<<"Account has been succesfully removed\n";
	cout<<endl;
}
void displayAccountDetails(int num)
{
	accounts accountsObject;
	bool condition = false;

	fstream inFile;
	inFile.open("accountDetails.dat", ios::in | ios::binary);
	
	if(!inFile)
	{
		cout<<"Error :: the file does not exist!! \n";
	}
	cout<<"BANK ACCOUNT DETAILS FOR : \n";	
	while(inFile.read(reinterpret_cast<char *>(&accountsObject), sizeof(accounts)))
	{
		if (accountsObject.returnAccountNumber() == num)
		{
			accountsObject.displayDetails();
			condition = true;
		}
	}
	inFile.close();
	if (condition = false)
	{
		cout<<"The account number does not exist\n";
	}
}
