#include<iostream>
#include <Windows.h>
#include<stdio.h>
#define t `double 
#include<cmath>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <cstdio>
#include<conio.h>
using namespace std;


class Account{
	
	protected:	
	string Atype;
	string AccountPassword;
	
	public:
		string name;
	Account(){
		AccountPassword = "12345678";
	}
	
	void changeName(){
		fflush(stdin);
		cout<<"Enter the new Name of the Account: ";
		getline(cin,name);
	}
	
	void password(char pwd[], int n){
	int x;
	for(x=0; 1;x++){ // n= size of password
	pwd[x] = getch();

	if(pwd[x] == 8 && x > 0){ // 8 means backspace
	printf("\b \b");
	x -=2;
	}
	// else if(pwd[x] == 8 && x == 0){
	// }
	else if(pwd[x] == 13){
		pwd[x] = '\0';
	break;
	} // 13 meas enter key
	else{
	printf("*");
	}

}
}

	string GetAccountPassword(){
		return(AccountPassword);
	}

	void SetAccountPassword(string s){
		AccountPassword = s;
	}		
};




// Exceptional Checker	
int ExceptionalChecker(int upper_limit, int lower_limit){
	int temp;
	bool flag = true;
	
	while(flag){
	try{
		cin>>temp;
		if(temp>=lower_limit && temp<= upper_limit){
			flag = false;
		}
		else{
			throw 1;
		}
		
		if(cin.fail()){
			flag = true;
		  while (cin.fail())
    		{
        	cin.clear(); // clear input buffer to restore cin to a usable state
        	cin.ignore(INT_MAX, '\n'); // ignore last input
        	throw 2;
   			 }		
		}
		
		
	}
	catch(int tam){
		if( tam == 1){
			cout<<">>Error: Enter a valid choice!\n>> ";
		}
		else if(tam == 2){
        	cout << ">>Error: Non-int type value entered!\n>> ";
		}
		else{
				cout << ">>Unknown Error! \n>> ";
		}
	}
	catch(...){
		cout<<">>Error!\n>> ";
	}
	
}
	
return(temp);
}





class UserAccount: virtual public Account{
	friend class Admin;
	static int Ucount;
	protected: 
	static UserAccount accounts[3];

	public:
		
		UserAccount(){
			if(Ucount == 0){
			this->name = "User";
			}
			else{		
			this->name = "User";				
			}this->Atype = "Guest";
		}
				
		static int GetUcount(int x=0){
			Ucount += x;
			return(Ucount);
		}
		
		static void SetUcount(int x){
			Ucount = x;
		}
		
		void SetType(string type = "Guest"){
			this->Atype = type;
		}
};
int UserAccount::Ucount = 0;
UserAccount UserAccount::accounts[3];


class Admin: virtual public Account{

	public:
		Admin():Account(){
		name = "Admin";
		Atype = "Administrator";
		
		}
		
		string getType(){
			return(Atype);
		}
	
	// Create New Account
		
	void CreateNewAccount(){
		system("cls");
	if( (UserAccount::GetUcount())<3){
		bool flag = true;
		while(flag){
		char temppwd[20];
		char temppwd2[20];
		system("cls");
		cout<<"\n\n\t\t\t\t------------Creating New Account------------\n\n";
		cout<<"\t\t\t\tEnter Account Name:     ";
		fflush(stdin);
		getline(cin, (UserAccount::accounts[UserAccount::GetUcount()].name));
		cout<<"\n\t\t\t\tEnter Account Password: ";
		password(temppwd, 20);
		cout<<"\n\n\t\t\t\tRe-Enter Account Password: ";
		password(temppwd2, 20);
		if(!(strcmp(temppwd ,temppwd2))){
			cout<<"\n\n\t\t\t\tAccount created successfully !";
			getch();
			UserAccount::accounts[UserAccount::GetUcount()].AccountPassword = temppwd;
			flag = false;
		}
		else{
			cout<<"\n\n\t\t\t\t Password doesnot matches ...";
			Sleep(3000);
			flag = true;
		}
	}
		UserAccount::GetUcount(1);			
	}
	else{
		cout<<"Account Limit reached! "<<endl;
	}					
	}
	
	
	//      Delete Function
	
	void DeleteAccount(){
		int temp;
		fflush(stdin);
		cout<<"\nAccount no.>> ";
		temp = ExceptionalChecker(UserAccount::GetUcount(), 1);
		if(UserAccount::GetUcount() >0 && temp<= UserAccount::GetUcount() && temp > 1 ){
			 UserAccount::GetUcount(-1);
			for(int x= temp-2 ; x< UserAccount::GetUcount(); x++){
				UserAccount::accounts[x] = UserAccount::accounts[x+1];				
			}
		}
		else{
			cout<<"cannot perform this illegal action !"<<endl;
		}	
	}
	
	// Show All Account
	
	void ShowallAccounts(){
//		system("cls");
		cout<<"\n\n\n\t\t\t\t---------ACCOUNTS-------------\n\n";
		cout<<"\t\t\t1. "<<name<<"\t\t\t"<<"Administrator"<<endl<<endl;
		for(int x=0; x<UserAccount::GetUcount(); x++){
			cout<<"\t\t\t"<<2+x<<". "<<UserAccount::accounts[x].name<<"\t\t\t";
			cout<<UserAccount::accounts[x].Atype<<endl;
			}
		}

	
	// Change Account Password
	
	void changePassword(){
		char temp[20];
		char tempOld[20];
		int index;
		system("cls");
		cout<<"\t\t----------------------- Change Password -------------------\n";
		ShowallAccounts();
		cout<<">\t\t>> ";
		index = ExceptionalChecker(UserAccount::GetUcount()+1, 1);
		if(index <=UserAccount::GetUcount()+1){
			if(index == 1){
				cout<<"\n\nEnter Old Password: ";
				password(tempOld, 20);
				if(tempOld == this->AccountPassword){
					cout<<"\n\nEnter New Password: ";
					password(tempOld, 20);
					cout<<"\n\nRe-Enter New Password: ";
					password(temp, 20);	
					if(!(strcmp(tempOld, temp))){
						cout<<"Password Changed Successfully !"<<endl;
						this->AccountPassword = temp;
						getch();
					}
					else{
						cout<<"Password change unsuccessful! "<<endl;
						getch();
					}
				
				}
			}
			else{
				char temp3[20];
				cout<<"\n\nEnter Old Password: ";
				password(tempOld, 20);
				if(tempOld == UserAccount::accounts[index-2].AccountPassword){
					cout<<"\n\nEnter New Password: ";
					password(temp3, 20);
					cout<<"\n\nRe-Enter New Password: ";
					password(temp, 20);	
					if(!(strcmp(temp3, temp))){
						cout<<"Password Changed Successfully !"<<endl;
						UserAccount::accounts[index-2].AccountPassword = temp;
						Sleep(3000);
					}
					else{
						cout<<"Password doesn't match ....\nPassword changed unsuccessful! "<<endl;
						cout<<temp3<<endl;
						cout<<temp<<endl;
						getch();
						Sleep(3000);
					}				
				}
				else{
					cout<<"\nIncorrect old Password Entered!"<<endl;
					Sleep(3000);
				}
				
				
			}
			
			
			
			
			
		}
		
		
		
		
	}



    //Account Settings 
		
	void Settings(){
		while(1){
			int a, c;
			system("cls");
		cout<<"------------Account Settings-----------------\n\n";
		cout<<"0. Back"<<endl;
		ShowallAccounts();
		cout<<"\n>> ";
		a = ExceptionalChecker(UserAccount::GetUcount()+1, 0);
		if(a>UserAccount::GetUcount()+1){
				cout<<"\nYou cannot perform this illegal Action !"<<endl;
				Sleep(3000);
				continue;
			}
		if(a>4){
			cout<<"Invalid Input !"<<endl;
			continue;
		}
		if(a == 0){
			break;
		}
		if(a > 1){
			cout<<"\n\n1. Change Account name\n0. back\n\n>> ";
			a = ExceptionalChecker(1, 0);
			if(a>1 || a == 0){
				continue;
			}
			if(a ==1){
			UserAccount::accounts[a-2].changeName();
			continue;
			}
			
		}
		if(a == 1){
			cout<<"\n\n1. Change Account name\n2. Change Account Password\n3. Create New Account\n4. Delete Account\n\n>> ";
			c = ExceptionalChecker(4, 1);
			switch(c){
				case 1:
					if(a==1){
						changeName();
					}
					else{
						UserAccount::accounts[a-2].changeName();
					}
					break;
				case 2:
					changePassword();
					break;

				case 3:
					CreateNewAccount();
					break;
				case 4:
					DeleteAccount();
					break;
				default:
					break;					
			}
		}
		
		}
	}
	
		
	// Open Account
	
	bool OpenTheAccount(){
		int index;
		bool Adminflag = false;
		bool flag;
		flag = false;
		while(!(flag)){
			system("cls");
		this->ShowallAccounts();
		cout<<"\n\n\t\t\t>> ";
		index = ExceptionalChecker(UserAccount::GetUcount()+1, 1);
		if(index>UserAccount::GetUcount()+1){
			flag = false;
		}
		else if(index ==1){
		Adminflag = true;	
		char temppwd[20];
		fflush(stdin);
		cout<<"\n\t\t\tEnter Account Password: ";
		password(temppwd, 20);
		if(temppwd ==this->AccountPassword){
			cout<<"\n\n\t\t\t procceed!";
			Sleep(3000);
			flag = true;
		}
		else{
			cout<<"\n\n\t\t\t n0 procceed!"<<endl;
			getch();
			Sleep(3000);
			flag = false;
		}	
		}
		else{
			char temppwd[20];
		fflush(stdin);
		cout<<"\n\t\t\tEnter Account Password: ";
		password(temppwd, 20);
		if(temppwd== UserAccount::accounts[index-2].AccountPassword){
			cout<<"\n\n procceed!";
			flag = true;
			Sleep(3000);
			}
		else{
			cout<<"\n\n No procceed!";
			getch();
			flag = false;			
			}
		
		
		}
	}
		return(Adminflag);

	}

	
	
};

class Folder: public Admin, public UserAccount {
	protected:
	string file_path;
	string type;
	public:
	Folder(){
		name = "Untitled";
		type = "folder";
		file_path = "E:\\project\\2nd semester\\group work\\desktop";
	}
};



class File: public Admin, public UserAccount{
	protected:
	string file_path;
	string type;
	public:
	File(){
		name = "Untitled.txt";
		type = "text";
		file_path = "E:\\project\\2nd semester\\group work\\desktop\\documents";
	}
};


class Applications: public Admin, public UserAccount{
	protected:
	string file_path;
	string type;
	public:
	Applications(){
		name = "Untitled";
		type = "folder";
		file_path = "E:\\project\\2nd semester\\group work\\desktop";
	}
};

//-----------------------------------------------------------------Tic Tac Toe------------------------------------------------------------------------

class TicTacToe: virtual public Applications{
	
	private:
	char a;
	char b;
	int pos[9];
	int player[5];
	int pmoves, lost, won ,tie;
 	int bingo[5];
	int moves;
	
	public:
		
		TicTacToe(){
			pmoves = 0;
			a = 'X';
			b = 'O';
			moves=0;
			for(int x=0; x<9; x++){
			pos[x] = 0;
			player[x] = 0;
			tie =0 ; won =0 ; lost =0;
			}
		}
	
	bingoSetter(){
		int arr[5] = {6, 15, 12, 24, 18};
		for(int x=0; x<4; x++){
			bingo[x] = arr[x];
		}
	}
	
	// searcher is bug free
		
	bool searcher(int num, int arr[], int size){       // compares the number with an array
		bool flag = false;
		for(int x=0; x<size; x++){
		if(num == arr[x]){
			flag = true;
			break;
		}	
		}
		return flag;
	
	
	}
			
	void getInput(){
		int aim;
		cout<<"\n\nEnter the the position to place the mark: ";
		aim = ExceptionalChecker(9, 0);
		for(int x =0; x<9; x++){
			if(aim == pos[x] || aim>9 || aim<1){
				cout<<"~Enter the the position to place the mark: ";
				aim = ExceptionalChecker(9, 0);
				x=0;
			}		
		}
			
			pos[moves] = aim;
			player[pmoves] = aim;
			moves++;			
			pmoves++;
	}


	
	bool available(int temp){
		bool flag = true;
		for(int x=0; x<6; x++){
			if(temp == pos[x] || temp<=0 || temp >=10){
				flag = false;
			}
		}
		return flag;
	}




	int putter(int num,int numm,int nummm, int nummmm, int arr[], int size){		// returns suitable position
			for(int x=0; x<size; x++){
				if(num != bingo[x] && numm != bingo[x] && nummm != bingo[x] && nummmm != bingo[x]){
					break;
				}
				return(bingo[x]);
			}
			
		
		
	}
	
	int whenElse(){
		int x;
		for( x=9; x>1; x--){
			if(pos[x] != x){
				break;
			}
		}
		
		return x;
	}
		
	int stepOne(){
		int middle[4] = {2, 4, 6, 8};
		int corner[4] = {1, 3, 7, 9};
		int centre = 5;
		
		// playing defensive
		if(searcher(pos[moves], corner, 4)){
			pos[moves] = 5;
		}
		else if(searcher(pos[moves], middle, 4)){
			pos[moves] = putter(pos[moves-1]+3, pos[moves-1]-3,pos[moves-1]+1, pos[moves-1]-1, corner, 4);
		}
		else if(pos[moves] == 5){
			pos[moves] = 9;
		}
		else{
			pos[moves] = whenElse();
		}

	}
	
	
	int stepTwo(){

		int y= 0;
		for(int x=0; x<5; x++){		
		if(available(bingo[x] - (pos[0]+pos[2]))){
			y = (bingo[x] - (pos[0]+pos[2]));
			break;
		}
	}
		// else
		if(y == 0){
			y = whenElse();
		}
		return(y);
		}
	
	
	int stepThree(){
		int y =0;
		//playing offensive
		for(int x=0; x< 5 ; x++){
			if(available(bingo[x] -( pos[1]+pos[3]) )){
				y = (bingo[x] -( pos[1]+pos[3]));
				break;
			}
		}
		// playing defensive	
		if(y==0){
			for(int x=0; x<5; x++){
			if(available(bingo[x]-(pos[0]+pos[2]))){
				y = (bingo[x] - (pos[0]+pos[2]) );
				break;
			}
			if(available(bingo[x] - (pos[0]+pos[4]))){
				y = (bingo[x] - (pos[0]+pos[4]));
				break;
			}
			if(available(bingo[x] - (pos[4]+pos[2]))){
				y = (bingo[x] - (pos[4]+pos[2]));
				break;
			}
		}
	}
		// else
		if(y == 0){
			y = whenElse();
		}	
		return(y);
		}



	int stepFour(){
		int y =0;
		//playing offensive
		for(int x=0; x<5; x++){
			if(available(bingo[x] -( pos[1]+pos[3]) )){
				y = (bingo[x] -( pos[1]+pos[3]));
				break;
			}
			if(available(bingo[x] -( pos[1]+pos[5]) )){
				y = (bingo[x] -( pos[1]+pos[5]));
				break;
			}
			if(available(bingo[x] -( pos[5]+pos[3]) )){
				y = (bingo[x] -( pos[5]+pos[3]));
				break;
			}
		}
		// playing defensive	
		if(y==0){
			for(int x=0; x<5; x++){
			if(available(bingo[x]-(pos[0]+pos[2]) )){
				y = (bingo[x] - (pos[0]+pos[2]) );
				break;
			}
			if(available(bingo[x] - (pos[0]+pos[4]))){
				y = (bingo[x] - (pos[0]+pos[4]));
				break;
			}
			if(available(bingo[x] - (pos[4]+pos[2]))){
				y = (bingo[x] - (pos[4]+pos[2]));
				break;
			}
			if(available(bingo[x]-(pos[6]+pos[2]) )){
				y = (bingo[x] - (pos[6]+pos[2]) );
				break;
			}
			if(available(bingo[x] - (pos[6]+pos[4]))){
				y = (bingo[x] - (pos[6]+pos[4]));
				break;
			}
			if(available(bingo[x] - (pos[0]+pos[6]))){
				y = (bingo[x] - (pos[0]+pos[6]));
				break;
			}
		}
	}
		// else
		if(y == 0){
			y = whenElse();
		}
		
		return(y);
		}



	
	
	
	
		
		
		void board(){										// board
			cout<<endl<<endl<<endl;
			cout<<"\t\t\t\t Tic-Tac-Toe Game\n"<<endl<<endl;
			int cnt = 10;
				cout<<"\t\t \t|\t\t \t|\n";
			for (int x=0; x<3; x++){
				for(int y=0; y<3; y++){
					bool flag = false;			
					cnt--;


				for(int p=0; p<9; p++){									// checking positions	
					if(pos[p] == cnt ){
					cout<<"\t\t";
					if(searcher(cnt, this->player, sizeof(pmoves+1))){					// searcher(cnt, this->player, 5)
						cout<<this->a;
					}
					else{
						cout<<this->b;
					}
					
					flag = true;
					break;
					}
					
			}
				
					if(y!=2 && flag==1){
						cout<<"\t|";
					}

				if (flag==1){
					continue;
				}
				
				cout<<"\t\t"<<cnt;
	
					
					if(y!=2){
						cout<<"\t|";
					}
					
				}
				cout<<"\n\t _______________|_______________________|_______________________\n";		
			cout<<"\t\t \t|\t\t \t|\n";
			}
			cout<<"\t\t \t|\t\t \t|";
		}
	
	
	void computer(){		
		if(moves == 1){			// Step 1
			stepOne();
			moves++;
		}		
		
		if(moves == 3){				// Step 2
			pos[moves] = stepTwo();
			moves++;
		}
		
		if(moves == 5){		          	// Step 3
			pos[moves] = stepThree();
			moves++;			
		}
		
		if(moves == 7){		           	// Step 4
			pos[moves] = stepFour();
			moves++;			
		}
	
}
	


int bigToSmallSub(int a, int b, int c){
int ans;
if(a>=b && a>=c){
	ans= a-(b+c);
	return ans;
}
else if(b>=a && b>=c){
	ans= b-(a+c);
	return ans;
}
else if(c>=a && c>=b){
	ans= c-(b+a);
	return ans;
}
}


bool bingoChecker(int n, int num, int number){
int sum = n+num+number;
bool flag = false;
	
	if(sum ==24){
		flag = true;
	}
	else if(sum == 12 && bigToSmallSub(n, num, number) == 2){
		if(n == 1 || num == 1 || number == 1){
			flag = true;
		}
		}	
	else if(sum == 18 && bigToSmallSub(n, num, number) == 0){
		if(n == 3 || num == 3 || number == 3){
			flag = true;
		}
	}
	else if(sum == 6 && bigToSmallSub(n, num, number) == 0){
		flag = true;
	}
		
	else if(sum == 15){
		if(n == 5 || num == 5 || number == 5){
		flag = true;
		
		}
	}
	return(flag);
}


int umpire(){
	bool flag = false;
	int signal=0;
	
	// writing for computer


		
		flag = bingoChecker(pos[1] ,pos[3] ,pos[5]);     // 1 3 5 7
		if(flag){
			signal = 1;
		}
		flag = bingoChecker (pos[1], pos[3], pos[7]); 
		if(flag){
			signal = 1;
		}
		flag =  bingoChecker(pos[1], pos[7], pos[5]); 
		if(flag){
			signal = 1;
		}
		flag = bingoChecker(pos[3], pos[5],pos[7]); 
		if(flag){
			signal = 1;
		}	

		
		flag = bingoChecker( pos[0], pos[2] , pos[4]);
		if(flag){
			signal = 2;
		}
		flag = bingoChecker( pos[0], pos[2] , pos[6]); 		
		if(flag){
			signal = 2;
		}
		flag = bingoChecker( pos[4], pos[6] , pos[0]); 
		if(flag){
			signal = 2;
		}
		flag = bingoChecker( pos[0], pos[2] , pos[6]); 
		if(flag){
			signal = 2;
		}
		flag = bingoChecker( pos[2], pos[4] , pos[6]); 
		if(flag){
			signal = 2;
		}
		flag = bingoChecker(pos[0], pos[2] , pos[8]); 
		if(flag){
			signal = 2;
		}
		flag = bingoChecker(pos[2], pos[4] , pos[8]);     // 1 3 5 7
		if(flag){
			signal = 2;
		}
		flag = bingoChecker(pos[4], pos[6] , pos[8]); 
		if(flag){
			signal = 2;
		}
		flag = bingoChecker(pos[8], pos[4] , pos[0]);     // 1 3 5 7
		if(flag){
			signal = 2;
		}
		flag = bingoChecker(pos[8], pos[0] , pos[6]); 					
		if(flag){
			signal = 2;
		}

	if(signal == 1){
		system("cls");
		this->board();
		cout<<"\nYou lost the game !\n";
		system("pause");
	}
	else if(signal == 2){
		system("cls");
		this->board();
		cout<<"\nYou Won the game !\n";
		system("pause");
	}
	else if(signal == 0 && moves ==9){
		system("cls");
		this->board();
		cout<<"\nIt's a Tie !\n";
		system("pause");
	}
	return(signal);
}




void scoreBoard(int signal){
	char a, b =146;
	if(signal == 0){
		tie++;
	}
	else if(signal == 1){
		lost++;
	}
	else if(signal == 2){
		won++;
	}
	
	cout<<"\n\t\t\t\tScore Board\t\t\t"<<endl;
	cout<<"\t_________________________________________________________";
	cout<<"\n\t|\tTotal Games\t|\tX\t|\tO\t|\n";
	cout<<"\t_________________________________________________________"<<endl;
	cout<<"\t|\t   "<<tie+won+lost<<"   |\t|\t"<<won<<"\t|\t"<<lost<<"\t|"<<endl;
	
	cout<<endl<<b<<" Do you wish to play another game? <y/n>: ";
	cin>>a;
	
	if(a == 'y' || a== 'Y'){
		this->Game();
	}	
	else if(a == 'n' || a== 'N'){
		cout<<" Exiting game...\n";
	}		
}

void Game(){
	
	TicTacToe o;
	bool flag=false; 
	o.bingoSetter();

	system("cls");
	
	for(int x=0; x<5; x++){			
		o.board();
		o.getInput();
		flag = o.umpire();
			if(flag){
				break;
			}
		o.computer();
		flag = o.umpire();	
			if(flag){
				break;
			}	
		system("cls");
}
	system("cls");
	o.board();
	o.scoreBoard(umpire());




	
}		
	
	
};

void calculator_functionality();

class Calculator{
	public:
		Calculator(){
		}
		~Calculator(){
		}
};
template<class T=double>
class Basic_Calculations:public Calculator{
protected:
	T a,b;
public:
	Basic_Calculations(){
		cout<<"Enter First Number: \n";
		a = ExceptionalChecker(INT_MAX, INT_MIN);
		cout<<"Enter Second Number:\n";
		b = ExceptionalChecker(INT_MAX, INT_MIN);
	}
	virtual double Operation(){
	}
	virtual void display_data(){
	}
	~Basic_Calculations(){}
};
	class Addition:public Basic_Calculations<double>{
	public:
		void display_data(){
			cout<<Operation()<<endl;
		}
		double Operation(){
			//Basic_Calculations::get_data();
			return(a+b);
		}
		
};
	class Subtraction:public Basic_Calculations<>{
	public:
		void display_data(){
			cout<<Operation()<<endl;
		}
		double Operation(){
			//Basic_Calculations::get_data();
			return(a-b);
		}
		
};
	class Multiplication:public Basic_Calculations<>{
	public:
		void display_data(){
			cout<<Operation()<<endl;
		}
		double Operation(){
			//Basic_Calculations::get_data();
			return(a*b);
		}
		
};
	class Division:public Basic_Calculations<>{
	public:
		void display_data(){
			cout<<Operation()<<endl;
		}
		double Operation(){
		try{
			if(b=0){throw(b);
			}
			else return(a/b);
		}
			catch(int no){
				cout<<"Denominator is equal to zero"<<endl;
			}
		}
		
};
class Extended_Calculations:public Calculator{
	private:
	protected:
		double a,b;
	public:
		Extended_Calculations(double a , double b):a(a),b(b){}
	virtual double Operation()=0;
	virtual void display_data()=0;	

};
   class Power : public Extended_Calculations{
   	public:
   		Power(int x,int y):Extended_Calculations(x,y){
		   } 			
	
   		double Operation(){
   			return pow(a,b);
		   }
		void display_data(){
			cout<<Operation()<<endl;
		}
   }; 
   class Root: public Extended_Calculations{
   	public:
   		Root(int x,int y):Extended_Calculations(x,y){
		   } 		
   		double Operation(){
   			return pow(a,1.0/b);
		   }
		void display_data(){
			cout<<Operation()<<endl;
		}
   
   }; 

   
template<class T=double>
class TrigonometricFunctions:public Calculator{
	protected:
		T x,deg,a;
	public:
 TrigonometricFunctions(){
 		cout<<"Enter The Angle in Degree's"<<endl;
		cin>>deg;
 	x=deg*M_PI/180;
	 a=deg;
	 }		
	};
		class Sine : public TrigonometricFunctions<double>{
 public:
 	Sine(){
	 }
 	void sine(){
 		
		cout<<"sin("<<x<<") ="<<sin(x)<<endl;
}
};
class Cosine:public TrigonometricFunctions<>{
	public:
		void cosine(){
		cout<<"cos("<<x<<") ="<<cos(x)<<endl;
}
};
class Tangent:public TrigonometricFunctions<>{
	public:
		void tangent(){
			try{
			if(fmod((x/M_PI_2),2)){
			throw(a);
			}
			else{
				cout<<"tan("<<x<<") ="<<tan(x)<<endl;
			}}
			catch(int a){
			cout<<"Donot Enter odd Multiples of pi/2  For tan Function"<<endl;
			}
		
}
};
class Asine:public TrigonometricFunctions<>{
	public:
		void asine(){
		try{
			if(a<-1||a>1){
			throw(a);
			}
			else{
				cout<<"asine("<<x<<") ="<<asin(x)<<endl;
			}}
			catch(int a){
			cout<<"Enter Only No. Between -1 and 1 For Asine Function"<<endl;
			}
		}	
		
};
class Acosine:public TrigonometricFunctions<>{
	public:
		void acosine(){
		cout<<"acos("<<x<<") ="<<acos(x)<<endl;
}
};
class Atangent:public TrigonometricFunctions<>{
	public:
		void atangent(){
		cout<<"atan("<<x<<") ="<<atan(x)<<endl;
}
};
class Logrithm_baseE: public TrigonometricFunctions<>{
//	private:
//		int a;
	public:
//	Logrithm(){
//		a=x*180/M_PI;
//	} 
	void LoG(){
			try{
			if(a>0){
				cout<<"log("<<a<<") ="<<log(a)<<endl;
			}
			else {
				throw(a);
			}
		}
		catch(int num){
			cout<<"You Can Only Enter No. Greater than 0 in log."<<endl;
		}
		}
};
class Logrithm_base10: public TrigonometricFunctions<>{
//	private:
//		int a;
	public:
//	Logrithm(){
//		a=x*180/M_PI;
//	} 
	void LoG(){
		try{
			if(a>0){
				cout<<"log("<<a<<") ="<<log10(a)<<endl;
			}
			else {
				throw(a);
			}
		}
		catch(int num){
			cout<<"You Can Only Enter No. Greater than 0 in log."<<endl;
		}
			
		}
};

class Algebraic_equations:public Calculator{
	public:
	Algebraic_equations(){}
	~Algebraic_equations(){}
};
class linear:public Algebraic_equations{
	
	private:
		double coff, constant;
		
	public:
		linear(){
		}
		
		linear(double c,double con):coff(c),constant(con){
		}
		
		void get_ans(){
			
			if(constant >=0 )
			
			cout << "x = " << (-constant/coff);
			
			else if (constant <0)
				cout << "x = " << (constant/coff);
		}
		
		
};

class quadratic:public Algebraic_equations{
	
	private:
		double p,q,r;

		
	public:
		quadratic(){
		}
		
		quadratic(double p , double q , double r):p(p),q(q),r(r){
		}
		
		void roots(){
			
			double det = (q*q) - (4*p*r);
			
			if(det == 0 || det > 0){
				
				double x1 = (-q + sqrt(det))/2*(p);
				double x2 = (-q - sqrt(det))/2*(p);
				
				cout << "\nx1 = " << x1 << endl;
				cout << "x2 = " << x2 << endl;
			}
			
			else if (det < 0){
				
				double real_part1 = (-q)/(2*p);
				double imagin_part1 = sqrt(-1*det)/(2*p);
				double real_part2 = (-q)/(2*p);
				double imagin_part2 = sqrt(-1*det)/(2*p);
				
				cout << "x1 = " << real_part1 << " + " << imagin_part1 << "i" <<endl;
				cout << "x2 = " << real_part2 << " - " << imagin_part2 << "i" <<endl;
				
			}
		}
		
//		void get_roots(){
//			
//			
//		}
};
	
//The multiplication of A and B (A*B) is defined only if the number of columns of A is the same as the number of
//rows of B.
//If A is of the size m * n and B is of the size n * t, then A * B = [cik] is of the size m*t

//Cik = ai1b1k + ai2b2k + ... + cinbnk


class Matrix:public Calculator, public Account{
	
	static int counter;
	int rows, column;
	double arr[100][100];
	public:
				Matrix(int row,int column){
//		cout<<"Matrix "<<++counter<<" Created! \n";
		this->rows = row;
		this->column = column;
		}
	public:
	void Setvalues(){
//		cout<<rows<<column;
		for(int x=0; x<rows; x++){
			for(int y=0; y<column; y++){
				cout<<"Enter the Matrix arr["<<x<<"]["<<y<<"] element: ";
				cin>>arr[x][y];
			}
		}
	}
	Matrix operator+(Matrix temp){
		Matrix M1(this->rows,this->column);
		
		if(rows != temp.rows || column != temp.column){
			cout<<"Matrix Cannot be added, becouce size is not same!";		
			for(int x=0; x<rows; x++){
				for(int y=0; y<column; y++){
					M1.arr[x][y] = 0;
				}
				return M1;	
		}
	}
		else{
			for(int x=0; x<rows; x++){
				for(int y=0; y<column; y++){
					M1.arr[x][y] = this->arr[x][y] + temp.arr[x][y];
				}
			}
				return M1;
		}
	}
	Matrix operator-(Matrix temp){
		Matrix M1(this->rows,this->column);
		
		if(rows != temp.rows || column != temp.column){
			cout<<"Matrix Cannot be subtracted, becouce size is not same!\n\n";
		
			for(int x=0; x<rows; x++){
				for(int y=0; y<column; y++){
					M1.arr[x][y] = 0;
				}
				return M1;
		}
	}
		else{
			for(int x=0; x<rows; x++){
				for(int y=0; y<column; y++){
					M1.arr[x][y] = this->arr[x][y] - temp.arr[x][y];
				}
			}
				return M1;
		}
	}	
	Matrix operator*(Matrix temp){
		Matrix M1(this->rows, temp.column);
		
		if(column != temp.rows){
			cout<<"Matrix cannot be Multiplicated! becouse number of columns of A \n isn't equal to number of rows of B\n\n";		
			
			for(int x=0; x<rows; x++){
				for(int y=0; y<column; y++){
					M1.arr[x][y] = 0;
				}
				return M1;
			}
		}
		else{
			for(int x=0; x<rows; x++){
				for(int y=0; y<column; y++){
					M1.arr[x][y] = this->arr[x][y] * temp.arr[y][x];
				}
			}
		}
		return M1;
	}
	
	friend ostream& operator<<(ostream& out, Matrix& M);
	}; 
int Matrix:: counter=0;
	ostream& operator<<(ostream& out, Matrix& M){
		for(int x=0; x<M.rows; x++){
			cout<<"\n";
			for(int y=0; y<M.column; y++){
				cout<<"\t"<<M.arr[x][y];
			}
		}
	cout<<"\n";
	}
	

void calculator_functionality()
{
	int choice;
	double a=0,b=0,c=0;
	char C;
	bool situation=true;
	while(situation){
	system("cls");
	cout<<"Welcome to Calculator"<<endl;
	cout<<"Select The Options of your liking :"<<endl<<"1. Arithmetic Calulations"<<endl<<"2. Extended Arithmetic Calulations"<<endl<<"3. Trigonometric Functions"<<endl<<"4. Algebric Equations"<<endl<<"5. Matrices Calculations"<<endl;
	choice = ExceptionalChecker(5, -1);
	switch(choice){
	case 1:{
		bool sit=true;
		while(sit){	
		cout<<"Welcome to Arithmetic Calculations"<<endl<<"Enter The Operation of your choice:"<<endl<<"1 for Addition"<<endl<<"2 for Subtraction"<<endl<<"3 for Multiplication"<<endl<<"4 for Division"<<endl;
		choice = ExceptionalChecker(4, 0);
		Basic_Calculations<>B1();
		switch(choice){
			case 1:{
				Addition A1;
				A1.Operation();
				A1.display_data();
				break;
			}
			case 2:{
				Subtraction S;
				S.Operation();
				S.display_data();
				break;
			}
			case 3:{
				Multiplication M;
				M.Operation();
				M.display_data();
				break;
			}
			case 4:{
				Division D;
				D.Operation();
				D.display_data();
				break;
			}
			default:
		cout<<"Chose the right Number on the list"<<endl;
		
	}break;}		
		
	cout<<"If you Want to Perform More Operations on the Arithmetic Calculator press 'y'";
	cin>>C;
	if(C!='y')
	{
		sit=false;
	}
	break;}
	case 2:{
		bool sit2=true;
		while(sit2){
		cout<<"Welcome to Extended Arithmetic Calculations"<<endl<<"1 for power(any type)"<<endl<<"2 for root(any type)"<<endl;
		 choice = ExceptionalChecker(INT_MAX, INT_MIN);
		 switch(choice){
		 	case 1:{
		 		cout<<"Welcome to Power \n Enter The number: ";
		 		a = ExceptionalChecker(99000, -99000);
		 		cout<<"It's Power: ";
		 		b = ExceptionalChecker(99000, -99000);
		 		Power P(a,b);
				P.Operation();
				P.display_data();		
				break;
			 }
			 case 2:{
			 	cout<<"Welcome to Roots \n Enter The Number then it's Root with a space b\\w them:";
		 		cin>>a>>b;
		 		Root R(a,b);
				R.Operation();
				R.display_data();		
				break;
			 }
			 
			 default:
		cout<<"Chose the right Number on the list"<<endl;
		break;
		}
	cout<<"If you Want to Perform More Operations on the Extended Arithmetic Calculations press 'y'"<<endl;
	cin>>C;
	if(C!='y')
	{
		sit2=false;
	}	}
	}
	break; 	
	case 3:{
		bool sit3=true;
		while(sit3){
		cout<<"Welcome To Trigonometric Section:"<<endl<<"Press:"<<endl<<"1 For Sine"<<endl<<"2 for Cosine"<<endl<<"3 for Tangent"<<endl<<"4 for Sine Inverse"<<endl<<"5 for CosineInverse"<<endl<<"6 for Tangent Inverse"<<endl;
		cout<<"7 for Log(Base 10)"<<endl<<"8 for log(Base e)"<<endl;
		choice = ExceptionalChecker(10, 0);

		TrigonometricFunctions<> Tig();
		switch(choice){
			case 1:{
				Sine s1;
				s1.sine();
				break;
			} 
			case 2:{
				Cosine cs1;
				cs1.cosine();
				break;
			}
			case 3:{
				Tangent Ta1;
				Ta1.tangent();
				break;
			}
			case 4:{
				Asine asi;
				asi.asine();
				break;
			}
			case 5:{
				Acosine acs;
				acs.acosine();
				break;
			}
			case 6:{
				Atangent ata;
				ata.atangent();
				break;
			}
			case 7:{
				Logrithm_base10 lo;
				lo.LoG();		
				break;
			}
			case 8:{
				Logrithm_baseE le;
				le.LoG();
				break;
			}
			default:
		cout<<"Chose the right Number on the list"<<endl;
	}	
			
	cout<<"If you Want to Perform More Operations on the Trigonometric Section press 'y'"<<endl;
	cin>>C;
	if(C!='y')
	{
		sit3=false;
	}	}		}
		break;
	case 4:{
		bool sit4=true;
		while(sit4){
		cout<<"Welcome to Algebraic Equations";
		Algebraic_equations ae;
		cout<<"Welcome To Algebraic Equations:"<<endl<<"Press:"<<endl<<"1 For Linear"<<endl<<"2 for Quadratic"<<endl;
		choice = ExceptionalChecker(99000, -99000);
		switch(choice){
			case 1:{
				cout<<"Enter Values A and B:"<<endl<<"(Ax + B)"<<endl;
				cin>>a>>b;
				linear lin1(a,b);
				lin1.get_ans();
				break;
			}
			case 2:{
					int x,y,z;
				cout<<"Enter Values A , B and C:"<<endl<<"(Ax^2 + Bx + C)"<<endl;
				cin>>x>>y>>z;
				try{
					if(x==0){throw (x);
					}
					else{
				quadratic quadd1(x,y,z);
				quadd1.roots();
					}
				}
				catch(int a)
				{
					cout<<"If A in Quadratic equation is Equal to zero than"<<endl<<"Equation is no Longer Quadratic it become linear."<<endl;
				
				}
				break;
			}
		}
	cout<<"If you Want to Perform More Operations on the Algebric Equations press 'y'"<<endl;
	cin>>C;
	if(C!='y')
	{
		sit4=false;
	}
	}
		break;
	}
	case 5:{
		bool sit5=true;
		while(sit5){
		cout<<"Welcome to Matrix Sections:"<<endl;
		cout<<"Enter No. Of Rows and Columns respectively with space b/w them:\n"<<endl;
		a = ExceptionalChecker(INT_MAX, INT_MIN);
		b = ExceptionalChecker(INT_MAX, INT_MIN);
		Matrix M1(a,b), M2(a,b), M3(a, b), M4(a, b), M5(a, b);
			M1.Setvalues();
	cout<<"\n------Matrix 1----------"<<endl;
	cout<<M1;
	M2.Setvalues();
	cout<<"\n------Matrix 2----------"<<endl;
	cout<<M2<<endl;
	cout<<"Enter The choice You want To Perform:"<<endl<<"1 for Matrix addition"<<endl<<"2 for matrix Subtraction"<<endl<<"3 for Matrix Multiplication"<<endl;
	choice = ExceptionalChecker(99000, -99000);;
	switch(choice){
		case 1:{
			M3 = M2+M1;
	cout<<"M3 = (Matrix 1 + Matrix 2)\n";
	cout<<M3<<endl;
			break;
		}
		case 2:{
	cout<<"M5 = M4 - M2\n";
	M5 = M4-M2;
	cout<<M5;
			break;
		}
		case 3:{
		cout<<endl<<"M4 = (Matrix 1 X Matrix 2)\n";
	M4 = M2*M1;
	cout<<M4<<endl;		
			break;
		}
}
	cout<<"If you Want to Perform More Operations on the Trigonometric Section press 'y'"<<endl;
	cin>>C;
	if(C!='y')
	{
		sit5=false;
	}}break;}
	default:
		cout<<"Chose the right Number on the list"<<endl;
break;
}
	cout<<"If you Want to Perform More Operations on the Calculator press 'y'";
	cin.ignore();
	char C;
	cin>>C;
	if(C!='y')
	{
		situation=false;
	}
}


}

//-----------------------------------------------------security-------------------------------------------------------------

class security_profile{
protected:
	string opass,animal,usename;
public:
	security_profile(){opass="ZAk101";animal="cat";usename="Zeeshan";}
void set_opass(string opass){
	this->opass=opass;
} 
string get_opass(){
	return(opass);
}
 
string get_usename(){
	return(usename);
}
void verification(){
	cout<<"Enter your favourite animal"<<endl;
	cin>>animal;
}
};
class Username:public security_profile{
	private:
		
		string eusename;
	public:
		bool verification(){
	cout<<"Enter Your UserName:"<<endl;
	cin>>eusename;
	if(eusename == usename){return (true);
	}
	else{
		return(false);
	}
}};
class password:public security_profile{
	private:
		
		string epass;
	public:
		bool verification(){
	cout<<"Enter Your PassWord:"<<endl;
	cin>>epass;
	if(epass==opass){return (true);
	}
	else{
		return(false);
	}
}};
//This class Will gain info about the questions when the user creates an account and set two step verification
class two_step_verification:public security_profile{
	private:
		string check;
public:
	bool verification(){
		cout<<"Enter Your Favourite animal"<<endl;
		cin>>check;
		if(check==animal){
			return true;
		}
		else 
		return false;
	}
};

void SecurityDetails(){
		string pas1,pas2;
	security_profile s1;
	bool result,sit=true;
	Username u1;
	password p1;
	result=u1.verification();
	if(result==true){
		cout<<"User Name is correct!!!"<<endl<<"Moving TO Password..."<<endl;
	}
	else{
		cout<<"Wrong UserName Please Try Again	Try:1"<<endl;
		result = u1.verification();
		if(result==true)
		{
		cout<<"User Name is correct!!!"<<endl<<"Moving TO Password..."<<endl;
		}
		else{
		cout<<"Wrong Username			Try:2"<<endl;
		two_step_verification v0;
		cout<<"!!!Inorder to change UserName you have to give verification Test!!!"<<endl;	
		result = v0.verification();
	if(result==true){
	cout<<"Your Username is: "<<s1.get_usename()<<endl;
	result = u1.verification();
		if(result==true)
		{
		cout<<"User Name is correct!!!"<<endl<<"Moving TO Password..."<<endl;
	}
	else{cout<<"Verification Failed Try Again Later"<<endl;	
	goto end;
		}}}}
	//Password 	
	result = p1.verification();
	if(result==true){
		cout<<"Login Succesfull";
	}
	else{
		cout<<"Wrong Pasword Please Try Again	Try:1"<<endl;
		result = p1.verification();
		if(result==true)
		{
		cout<<"Login Succesfull";
		}
		else{
		cout<<"Wrong Pasword Please			Try:2"<<endl;
		cout<<"!!!Inorder to change password you have to give verification Test!!!"<<endl;
		two_step_verification v1;	
		result = v1.verification();
	if(result==true){
		cout<<"Continuing to Password Reset"<<endl<<"Enter New Password:"<<endl;
		cin>>pas1;
		cout<<"Confirm Password:"<<endl;
		cin>>pas2;
		if(pas1==pas2){
			s1.set_opass(pas1);
			cout<<"Password Changed Succesfully..."<<endl;
		}
	}
	else{cout<<"Verification Failed Try Again Later"<<endl;
	}
		}
	}
	end:;

}

//-------------------------------------------------Note pad---------------------------------------------------------------
class TextPad: virtual public Applications{
	protected:
	friend class UserInterface;
	public:
	static string fileNames[100];
	static int n;	
	public:
		
		TextPad(){
			n=0;
		}
		
		void intro(){
			
			cout<<"		===================================== NOTE PAD =====================================\n\n";
		}

		void Blank_doc() {
		
			
			char name[20],path[100],Name[20];
			string text;
			
			strcpy(path,".\\desktop\\documents\\");
			
			cout << "\nEnter File name: ";
			fflush(stdin);
			cin.get(name,20);
			
		
			ofstream n1("Names.txt",ios::app);

				n1 <<name<< "\n";
			
			n1.close();
			
			strcat(path,name);
			
//			cout << path;

			fstream f1(path,ios::out);
			
		

				fflush(stdin);
				getline(cin,text);

				f1 << text;
			
			
			f1.close();
			
			

		}

		void Open_doc(int num) {

			string text,txt;
			char Name[20];
			char path[100];
			char ch; 
			
			int i;
			strcpy(path, ".\\desktop\\documents\\");
			ifstream f4;
			
			f4.open("Names.txt");
			
			if(f4.is_open()){
				
			while (i!=num){
					
					f4.get(Name,20);
					getline(f4, text);
					i++;	
			}
			
		}
			f4.close();
			strcat(path,Name);
			
			fstream f;
			
			f.open(path,ios::in);
			
			if(f.is_open()){
				
			while (!f.eof()){
					
					getline(f,text);
						
			}
			cout << text;
			
			cout << "\n\n Want to edit document(Y / N): ";
			cin >> ch;
			
			if(ch == 'Y'){
				
				system("cls");
				
				cout<<"		===================================== NOTE PAD =====================================\n\n";
				
				fstream f;
			
			f.open(path,ios::in);
			
			while (!f.eof()){
					
				getline(f,text);
						
			}
			cout << text;
			
			f.close();
			
			f.open(path,ios::app);
			
			fflush(stdin);
			getline(cin,txt);
			
			f << txt;
			
			f.close();
		}
		
			else{
			
				f.close();
			}
			
			}
			
			else{
				
				cout << "File not exists....." << endl;
			}
			
			f.close();


		}
	
	
	void get_names(){
		
		string Name;
		
			ifstream f3;
			f3.open("Names.txt");
			
			if(f3.is_open()){
				
				while(!f3.eof()){
					
					fflush(stdin);
					getline(f3,Name);
					fileNames[n]= Name;
					n++;
				}
			}
			f3.close();
	}

		void delete_doc(int num){

			int status,i;
			string text;
			char Name[20],path[] = ".\\desktop\\documents\\";

//			cout << "\nEnter File number: ";
//			cin >> num;
			
			ifstream f4;
			
			f4.open("Names.txt");
			
			if(f4.is_open()){
//			i=0;	
			while (i!=num){
					i++;
					f4.get(Name,20);
					getline(f4, text);	
			}
//			cout << text;
		}
			f4.close();
			
			strcat(path,Name);

			status = remove(path);
			if(status==0)
				cout<<"\nFile Deleted Successfully!";
			else
				cout<<"\nError Occurred!";


		
	}
		
		void rename_file(int num){
			int i=0,j=0;
			char old_n[20], new_n[20];
			char path_o[] = ".\\desktop\\documents\\";
			char path_n[] = ".\\desktop\\documents\\";
			
//			strcpy(path_o,path);
//			strcpy(path_n,path);
			
			ifstream f4;
			
			f4.open("Names.txt");
			
			if(f4.is_open()){
				
			while (i!=num){
					
					f4.get(old_n,20);
					i++;	
			}
//			cout << text;
		}
			f4.close();
			
			cout << "Enter new name of file: ";
			fflush(stdin);
			cin.get(new_n,20);
			
			ofstream n1("Names.txt",ios::out);
			
			if(j!=i)
				n1 <<new_n;
				
			j++;
			
			n1.close();
			
			strcat(path_o,old_n);
			strcat(path_n,new_n);
	
			if (rename(path_o,path_n) != 0)
				perror("Error!");
			
			else
				cout << "File renamed successfully";
		
		
	}
		void use_class(){
			TextPad T1;
			int choice;
	
			char ch='Y';
	
			while (ch!='N' || ch!='n'){
		
			T1.intro();

			cout << "\n\n(1) Blank document\n(2) Exit\n\nEnter choice: ";
			choice = ExceptionalChecker(2, 1);

			switch(choice) {

				case 1:
					system("cls");
					T1.intro();
					T1.Blank_doc();
					break;

//			case 2:
//				system("cls");
//				T1.intro();
//				T1.Open_doc();
//				break;
//
//			case 3:
//				system("cls");
//				T1.intro();
//				T1.delete_doc();
//				break;
//
//			case 4:
//				T1.rename_file();
//				break;
				
			case 2:
				break;
	}
	
			if(choice==2)
			break;
			
		if(choice!=5){
			
			cout << "\n\n Back to menu(Y / N): ";
			cin >> ch;
			
		}
	
			system("cls");
	
}
		}
	
		void func(){
			int num,choice;
			TextPad T1;
			
			cout << "\nEnter File number: ";
			num = ExceptionalChecker(5, 1);
			
			cout << "\n\n(1) Open document\n(2) Delete document\n(3) rename document \n(4) Exit\n\nEnter choice: ";
			choice = ExceptionalChecker(4, 1);
			
			switch(choice){
				
			case 1:
				system("cls");
				T1.intro();
				T1.Open_doc(num);
				break;

			case 2:
				system("cls");
				T1.intro();
				T1.delete_doc(num);
				break;

			case 3:
				T1.rename_file(num);
				break;
				
			case 4:
				break;
			}
		}
	

};
string TextPad::fileNames[100];
int TextPad::n = 0;


//-------------------------------------------------UserInterface---------------------------------------------------------------

class UserInterface: virtual public TextPad{
	
	public:
char flagger(string m){
	if(m == "text"){
		return('T');
	}
	else if(m == "folder"){
		return('F');
	}
	else if(m == "application"){
		return(145);
	}
	
	else{
		return('?');
	}
}





string spaceLinePutter(string a, string b){
	int ss;
	string line;
	int m = a.length();
	ss = 23-(m-4);
	string temp = " ";
	for(int x=0; x<ss; x++){
		temp += " ";
	}
	line = a + temp + b;
	return(line);
}






void tablee(int icon, string arr[], string type[]){	
	string test[icon];
	for(int x=0; x<icon; x++){
		test[x] = arr[x];
	}
	
	
	
//	system("cls");
	int h;
if(icon%2 != 0){
	h = icon-1;
}
else{
	h = icon;
}

for(int x=0; x< h; x++){
	cout<<"  "<<(x+1)<<". __ \t\t      "<<(x+2)<<". __ "<<endl;
	cout<<"    |"<<flagger(type[x])<<" |\t\t\t|"<<flagger(type[x])<<" |"<<endl;
	cout<<"    |__|"<<"\t\t\t|__|"<<endl;
	cout<<"  "<<spaceLinePutter(test[x], test[x+1])<<endl<<endl;
	x++;	
}
if((icon%2) != 0){
	cout<<"  "<<icon<<". __"<<endl;
	cout<<"    |"<<flagger(type[icon-1])<<" |"<<endl;
	cout<<"    |__|"<<endl;
	cout<<"  "<<test[icon-1]<<endl;
}
	
}



void Desktop(bool aa_flag){
	system("cls");
	int count;
	cout<<"\nDesktop-------------\n\n";
	if( (aa_flag) ){ // true
			string arr[] = {"Calculator", "Tic-Tac-Toe", "Notepad", "Documents", "Settings", "Log-off", "Shut Down", "Recycle bin"};
			string arr2[] = {"application", "application", "application", "folder", "folder", "option","option","folder"};
			count = 8;
				tablee(count, arr, arr2);	
	}
	else{
			string arr[] = {"Calculator", "Tic-Tac-Toe", "Notepad", "Documents", "Shut Down", "Log-off", "Recycle bin"};
			string arr2[] = {"application", "application", "application", "folder", "option","option","folder"};
			count = 7;
	tablee(count, arr, arr2);	
	}		
	
}

void Documents(){
	system("cls");
	cout<<"\nDocuments-------------\n\n";
	string arr2[n-1];
	for(int x=0; x< (n-1); x++){
		arr2[x] = "text";
	}
//	int cnt = 5;
	tablee(n-1, fileNames, arr2);		
}


void OperatingSystemIntro(int n = 20){
cout<<"\n\t\t\t\t\t ZAK OPERATING SYSTEM   \n";
cout<<"\t\t\t\t      \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n\n";

int x,  y, k;
char tood = 209;
for(x = 1; x <= n; x++)
{
for(y = 1; y <= n; y++)
{
if(y <= x)			//209
cout<<tood;	//y
//else
cout << "  ";
}
for(y = n; y >= 1; y--)
{
if(y <= x)
cout<<tood;	//y
//else
cout << "  ";
}
cout << "\n";
}
	cout<<"\n\n";
	system("pause");
}


void Shutdown(){
	system("cls");
	OperatingSystemIntro();
	cout<<"Shutting Down ...";
	getch();
	system("cls");
	exit(0);
}

};






//-------------------------------------------------OS_User--------------------------------------------------------------

class OS_User: public TicTacToe, public UserInterface, virtual public TextPad{	

		void Initialization(){    // GetUcount, Account.txt
			ifstream f, f1;
			int temp;
			string m;
			char anma[30], ch;
			
			f.open("Account_Data.bin", ios::in | ios::binary);
//			f1.open("Myfiles.bin", ios::in | ios::binary);
//			this->fileNames;
//			while(!f1.eof){
//				
//			}
			f>>temp;
			UserAccount::SetUcount(temp);
			f.getline(anma, 30, '|');       // name
			name = anma;
			f.getline(anma, 30, '|');       // type
			Atype = anma;
			f.getline(anma, 30, '|');         //password
			m = anma;
			this->AccountPassword = anma;
			getline(f,m);
			for(int x=0; x<GetUcount(); x++){                          // reading Account Names from file
				f.getline(anma, 30, '|');				
				UserAccount::accounts[x].name = anma;		// name
				f.getline(anma, 30, '|');
				UserAccount::accounts[x].SetType(anma);				// type				
				f.getline(anma, 30, '|');
				m = anma;
				UserAccount::accounts[x].SetAccountPassword(m);
				getline(f, m);
			}
			
			f.close();	
		}


	
		void OS_Data_Saving(){    // GetUcount, Account.txt
			ofstream f;
			int temp;
			string m;
			char anma[30];
			
			f.open("Account_Data.bin", ios::out | ios::binary);
			f<<GetUcount()<<" "<<this->name<<'|'<<this->Atype<<'|'<<this->AccountPassword<<'|'<<endl;
			for(int x=0; x<GetUcount(); x++){                          // reading Account Names from file
				f<<UserAccount::accounts[x].name<<'|'<<"Guest"<<'|'<<UserAccount::accounts[x].GetAccountPassword()<<'|'<<endl;
			}
			
			f.close();	
		}




	public:
		
		
		
		
		
		
		
		void OperatingSystem(){
			Initialization();
		int choice = 5;	
//		obj.Desktop();    // desktop
	bool flag = true;
	bool Adminsflag;
	while(flag){
	choice = 0;
	this->
	OperatingSystemIntro();
	Adminsflag = OpenTheAccount();
		while(choice != 6){	
		Desktop(Adminsflag);
		cout<<"\n\n>> ";
		choice = ExceptionalChecker(10, 0);;
		if(Adminsflag == true){
					
		switch(choice){
			case 1:
				calculator_functionality();
				system("cls");
				break;
			case 2:
				Game();
				system("cls");
				break;
			case 3:
				use_class();
				system("cls");
				break;
			case 4:
				get_names();
				Documents();
				func();
				system("cls");
				break;
			case 5:
				Settings();
				break;			
			case 6:
				system("cls");
				continue;
			case 7:
				OS_Data_Saving();
				Shutdown();
				break;			
			default:
				break;
		}
		}
		else{
						
		switch(choice){
			case 1:
				calculator_functionality();
				system("cls");
				break;
			case 2:
				Game();
				system("cls");
				break;
			case 3:
				use_class();
				system("cls");	//	string arr[] = {"Calculator", "Tic-Tac-Toe", "Notepad", "Documents", "Log-off", "Shut Down", "Recycle bin"};

				break;
			case 4:
				get_names();
				Documents();
				func();
				system("cls");
				break;
			case 5:
				Shutdown();
				break;	
			case 6:
				system("cls");
				continue;
			default:
				break;
		}
		}
		system("cls");
		
		}
}		



		}

};

 
//			string arr[] = {"Calculator", "Tic-Tac-Toe", "Notepad", "Documents", "Shut Down", "Log-off", "Recycle bin"};


int main(){
	
	OS_User  user;
	user.OperatingSystem();
}
