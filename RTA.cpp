#include<fstream.h>
#include<string.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<iomanip.h>
#include<ctype.h>
#include<graphics.h>
fstream f, t;


class plate
{    public:
	char city[25];
	int pno;

	void pin()
	{
	    cout<<"\n\tEnter City of plate : ";
	  gets(city);
	  cout<<"\n\tEnter Plate number : ";
	  cin>>pno;
	}
	void pout()
	{
	      cout<<"\n\tPlate info : ";
	  puts(city); cout<<"\t"<<pno;
	}

	void retcity()
	{
	    puts(city);
	    }
};


class licence
{
   public:
	char name[50], nation[50],  reglic[100] ;
	int di, db, de,mi,mb,me, yi, yb ,ye;
	float amount;
	plate p;
	void valid(int d,int m,int y);
	void licin();
	void licout();

	licence()
	{ amount=0.0;
	}
} l;


void licence::licin()
{
    int i, n;
    cout<<"\n\tEnter Name : ";
    gets(name);
    cout<<"\n\tEnter Nationality : ";
    gets(nation);
    p.pin();
    cout<<"\n\tEnter License Registration number : ";
    gets(reglic);
    a:
    cout<<"\n\tEnter Date of Birth :";

    cin>>db>>mb>>yb;
    if(yb>1991)
    {   cout<<endl;
	cout<<"\n\tNot eligible to Drive (yet!)"<<endl;
	goto a;
	 valid(db,mb,yb);
    }

    b:
    cout<<endl;
    cout<<"\n\tEnter Date of Issue : ";

    cin>>di>>mi>>yi;
    if(yi>=2010)

       {        cout<<endl;
		cout<<"\n\tInvalid date!";
		goto b;

       }
	 valid(di,mi,yi);
    c:
    cout<<"\n\tEnter Date Of Expiry : ";

    cin>>de>>me>>ye;

   if(ye<=yi+5)
	{       cout<<endl;
		cout<<"\n\tInvalid date! Should Be Atleast 5 years from Issue";
		goto c;

	}
	valid(de,me,ye);


    }




void licence::licout()
 {
    int i, n;
    cout<<"\n\tName : ";
    puts(name);
    cout<<"\n\tNationality : ";
    puts(nation);
    cout<<"\n\tRegistration Number of License: ";
    puts(reglic);
    cout<<"\n\tDate of Issue : ";
    cout<<di<<"/"<<mi<<"/"<<yi;
    cout<<"\n\tDate of Expiry : ";
    cout<<de<<"/"<<me<<"/"<<ye;
    cout<<"\n\tDate of birth : ";
    cout<<db<<"/"<<mb<<"/"<<yb;
    cout<<"\n\tFines Pending : ";
    cout<<amount;
}

void fines()
{
	    f.open("proj.dat", ios::in| ios::binary );
	    t.open("temp.dat", ios::out|ios::binary);
	int reason;
	f.seekg(0);
	int blackpoint,pnum;
	float amt=0.0;
	cout<<"\n\t\t Enter Plate Number : ";
	cin>>pnum;
	while(f.read((char*)&l,sizeof(l)))
	{
		if(pnum==l.p.pno)
	{
	   // l.p.pout();
	cout<<"\n\t\tOffence : ";
	cout<<"\n\t\t1. Over-speeding";
	cout<<"\n\t\t2. Crossing Red Light";
	cout<<"\n\t\t3. Accidents";
	cout<<"\n\t\t4. Parking issues";
	cout<<"\n\t\t5. Other Reasons";
	    cout<<"\n\t\tEnter Reason of Fine : ";
	cin>>reason;
	switch(reason)
	{
		case 1: blackpoint+=2;
			amt+=200.0;
			break;
		case 2: blackpoint+=3;
			amt+=500.0;
			break;
		case 3: blackpoint+=5;
			amt+=1500.0;
			break;
		case 4: blackpoint+=2;
			amt+=100.0;
			break;
		case 5: blackpoint+=1;
			amt+=200.0;
			break;
	}
	l.amount+=amt;
      //	f.seekp(f.tellg()-sizeof(l));
	t.write((char*)&l,sizeof(l));
       }
	}
	t.close();
	f.close();
	remove("proj.dat");
	rename("temp.dat","proj.dat");
}


void create()
{
	    int i,n;
	f.open("proj.dat",ios::out|ios::binary);
	cout<<"\n\tEnter No details to be entered : ";
	cin>>n;
	for(i=1;i<=n;i++)
	{
		l.licin();
		f.write((char*)&l,sizeof(l));
	}
	f.close();
}

void edit()
{
	    int pum;
	cout<<"\n\tEnter Plate number : ";
	cin>>pum;
	    t.open("temp.dat", ios::out|ios::binary);
	f.open("proj.dat",ios::in|ios::binary);
	f.seekg(0);
	while(f.read((char*)&l,sizeof(l)))
	{
		if(pum==l.p.pno)
		{
			l.licin();
			}
		t.write((char*)&l,sizeof(l));
	}
	t.close();
	f.close();
	remove("proj.dat");
	rename("temp.dat", "proj.dat");
}

void licence::valid(int dd,int mm,int yy)
{

	if(mm==1||mm==3||mm==5||mm==7||mm==8||mm==10||mm==12)
	 {
		if(dd<=31 && dd>0)
			cout<<"\n\tValid date"<<endl;
		else
			cout<<"\n\tInvalid date"<<endl;
	}

	else if( mm==4||mm==6||mm==9||mm==11)
	{
		if(dd>0 && dd<=30)
			cout<<"\n\tValid date "<<endl;
		else
			cout<<"\n\tInvalid date"<<endl;

	}
	else if(mm==2)
	{
		if((yy%100==0)&&(yy%400==0)||(!(yy%100==0))&&(yy%4==0))
		  if (dd>0 && dd<=29)
			cout<<"\n\tValid date"<<endl;
		else
			cout<<"\n\tInvalid date"<<endl;
		else
		  if(dd>0 && dd<=28)
			cout<<"\n\tValid date"<<endl;
		else
			cout<<"\n\tInvalid date"<<endl;
	}
	else
			cout<<"\n\tInvalid date "<<endl;
}

void check()
{
	    int pnum1;
	cout<<"\n\tEnter Plate no : ";
	cin>>pnum1;
	f.open("proj.dat",ios::in|ios::binary);
	f.seekg(0);
	while(f.read((char*)&l,sizeof(l)))
	{
		if(pnum1==l.p.pno)
		{
		l.licout();
		}
	}
	f.close();
}

void payment()
{
	    char a, b, key;
	int crdt,amt,bal;
	int pnum2;
	cout<<"\n\tEnter Plate no : ";
	cin>>pnum2;
	f.open("proj.dat",ios::in|ios::binary);
	t.open("temp.dat", ios::out|ios::binary);
	f.seekg(0);
	while(f.read((char*)&l,sizeof(l)))
	{
		if(pnum2==l.p.pno)
		{
		l.licout();
	    cout<<"\n\tWould you like to clear your outstanding amount? (y/n)";
	cin>>a;
	if(a=='y'||a=='Y')
	{
	     cout<<"\n\tPlease enter last four numbers of your credit card number : ";
	     cin>>crdt;
	cout<<"\n\tEnter Amount you wish to pay : ";
	cin>>amt;
	cout<<"\n\tYou have choosen to pay Dhs. "<<amt<<"\n";
	cout<<"\n\tYour transaction is being processed";
	bal=l.amount;
	bal-=amt;
	l.amount=bal;
	t.write((char*)&l,sizeof(l));
	cout<<"\n\tYour outstanding balance is : Dhs "<<bal;
	}
	if(a!='y'||a!='Y')
	t.write((char*)&l,sizeof(l));
	t.close();
	f.close();
	remove("proj.dat");
	rename("temp.dat", "proj.dat");


	}
	}

}


void adminmenu()
{
	    int ch1;
	clrscr();
	char pswrd[20], check[10]="password";
	cout<<"\n\n\t\t\tPASS-CODE:";
	gets(pswrd);
	if(strcmp(pswrd,check)!=0)
	exit(0);
	else
	{
			clrscr();
		cout<<"\n\t\tADMIN MENU"<<endl;
		cout<<"\n\t\t1. New License"<<endl;
		cout<<"\n\t\t2. Edit Existing License"<<endl;
		cout<<"\n\t\t3. Fines Management"<<endl;
		cout<<"\n\t\t4. Back";
			cout<<"\n\t\tEnter Choice : ";
		cin>>ch1;
		switch(ch1)
		{
			case 1: create();
					break;
			case 2: edit();
					break;
			case 3: fines();
					break;
			case 4: exit(0);
		}
	}
}



void usermenu()
{
	    int ch2;
	clrscr();
	cout<<"\n\t\tUSER MENU"<<endl;
	cout<<"\n\t\t1. Show License Details";
	cout<<"\n\t\t2. Fine Enquiry";
	    cout<<"\n\t\tEnter Choice : ";
	cin>>ch2;
	switch(ch2)
	{
			case 1:	check();
				break;
		case 2:	payment();
				break;

	}
}

void mainmenu()
{
	    int ch3;
	clrscr();
	cout<<"\n\t\t ---MAIN MENU----"<<endl;
	cout<<"\n\t\t1. Administrator Menu";
	cout<<"\n\t\t2. Public Menu";
	cout<<"\n\t\t3. Exit";
	    cout<<"\n\t\tEnter Choice : ";
	cin>>ch3;
	switch(ch3)
	{
		case 1: adminmenu();
				break;
		case 2: usermenu();
				break;
		case 3: break;
	}
}


void main()
{
	    clrscr();
	
	char ans;
	char A;
	    cout<<" \n\n\n\n\n\n\n\n\t\t\t***** Abu Dhabi Police HQ *****";
	cout<<" \n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout<<" \n\t\t\t   Traffic Control Department";
	cout<<"\n\n\n\t\t\t\t Press any Key";
	getch();

	clrscr();
	do
	{
	mainmenu();
	cout<<"\n\tAre you sure you want to quit the program?? (y/n) ";
	cin>>A;
	}while(A=='n'||A=='N');
	cout<<"\n\t\tThank you for visting Abu Dhabi Police HQ.";
	getch();
}





