#include<iostream.h>
#include<fstream.h>
#include<stdlib.h>
#include<iomanip.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dir.h>
#include<dos.h>

const char* fileName="Employee.txt";

class Employee{
private:
int EmpID;
char EmpName[50],Post[50],Department[10];
float Salary;
public:
void ReadData();
int GetID();
void DisplayRecord();
char* GetDepartment();
};
void Employee::ReadData()
{
cout<<"Employee ID:";
cin>>EmpID;
cout<<"Employee Name:";
cin>>EmpName;
cout<<"Employee's Post:";
cin>>Post;
cout<<"Employee's Department:";
cin>>Department;
cout<<"Salary:";
cin>>Salary;
}
void Employee::DisplayRecord()
{
cout<<endl<<"___________________________________________________________";
cout<<endl<<setw(5)<<EmpID<<setw(15)<<EmpName<<setw(15)<<Post<<setw(15)<<Department<<setw(8)<<Salary;
}
int Employee::GetID()
{
return EmpID;
}
char* Employee::GetDepartment()
{
return Department;
}



class attendenceout;
class idinfo
{
protected:
    char  depcode[7],dayno[6];
    int no,year,month;
    int day;
public:
    void id(void){cout<<depcode<<no;}
    void dayset(void);
};

void idinfo::dayset(void)
	{
	  struct date a;
	  getdate(&a);
	  year=a.da_year;
	  month=a.da_mon;
	  day=a.da_day;
	  cout<<day<<"."<<month<<"."<<year<<endl;
	}

class attendencein:virtual public idinfo
	{
	  char filename[15];
	  char folnam[15] ;
	  int tot, flag[120];
	  public:
	  void input(void);
	  void attend(void);
	  void folder(void);
	  void file(void);
	  void crefilename(int);
	  void sinfile(int pa);
	} ;

void attendencein::folder(void)
	{
	strcpy(folnam,depcode);
	mkdir(folnam);
	strcat(folnam,"\\");
	  }

void attendencein::input(void)
	{
	cout<<endl<<"ATTENDENCE SHEET"<<endl;
	cout<<"\n Enter Department code:(should be number): ";
	cin>>depcode ;
	cout<<"\n Input day number : ";
	cin>>dayno;
	cout<<"\n Total Employee   : ";
	cin>>tot ;
	attend();
	file();
	   }
void attendencein::crefilename(int i)
	 {
	  if(i==1)
	    {
	     strcpy(filename,depcode);
	    }
	else  if(i==0)
	    {
	 strcat(filename,dayno);
	 strcat(filename,".txt");
	    }

	 }

void attendencein::file(void)
{
     dayset();
     fstream k;
     crefilename(0);
     k.open(filename,ios::out);
     k<<"\tATTENDENCE SHEET\n\t----------------\n\n";
     k<<"\ndate"<<day<<"\\"<<month<<"\\"<<year<<endl ;
     k<<"\nDepartment Code : ";
     k<<depcode;
     k<<"\nEMPLOYEE ID : ";
     k<<dayno;
     k<<"\n\nEMPLOYEE ID#\t\t\tATTENDENCE\n";
     int i=1;
     while(i<=(no-1))
     {
	k.fill(48);
	k<<"\n"<<depcode<<setw(3)<<i<<"\t\t\t";
	if(flag[i]==0)
	    k<<"absent";
	else
	    k<<"present";
	i++;
    }
    k.close();
}


void attendencein::attend(void)
 {
    dayset();
    no=1;
    int t=tot;
    char a[4];
    strcpy(a,depcode);
    cout<<"\n(*if absent press 'TAB' and if present press any key if postponed operation press ""ESC"")\n";
    getch();
    clrscr();
    folder();
    cout<<"date"<<day<<"\\"<<month<<"\\"<<year<<endl ;
    cout<<"\nEMPLOYEE ID#\t\tATTENDENCE\n";
    while(no<=t)
     {
       cout.fill(48);
       cout<<"\n"<<a<<setw(3)<<no<<"\t\t";
       char c=getch();
	   if(c==9)
	 {
	  flag[no]=0;

	textcolor(1);
	cprintf("absent");
	  sinfile(0);
	  }
      else  if(c==27)
	  {
	  for(;no<=t;no++)
	      {
	       flag[no]=1;
	       sinfile(1);
	      }
	   break;
	  }
      else  if(c!=9)
	   {
	    flag[no]=1;
	    textcolor(6);
	    cprintf("present");
	    textcolor(7);
	    sinfile(1);
	    }
	no++;
	if(no==125)
	break;
	}
	}
void attendencein::sinfile(int pa)
{
    fstream x;
    char nam[10],name[20],*tmp;
    itoa(no,nam,10);
    strcpy(name,depcode);
    strcat(name,nam);
    tmp=new char[strlen(folnam)+strlen(name)+4];
    strcpy(tmp,folnam);
    strcat(strcat(tmp,name),".txt");
    x.open(tmp,ios::app);
    x<<pa;
    x.close();
    delete [] tmp;
}

class attendenceout:virtual attendencein,virtual idinfo
	    { int no;
	      public:
	      char filename[12];
	      int outputfile(void);
	      int outstfile(void);
	      void output(void);
	      void getdata(void);
	      void getidno(void){cout<<"\n\ninput the EMPLOYEE ID#(exp 1 or 12)";
			cin>>no;  }
	      void attendencedata(void);
	      void employeedata(void);
	  };
void attendenceout::getdata(void)
	       {
	       clrscr();
	       cout<<"\n Enter the batch code and department code: \n\n";
	       cout<<"\n DEPARTMENTAL CODE     : ";
	       cin>>depcode;
	       cout<<"\n Attendence day number : ";
	       cin>>dayno;
	       }
int attendenceout::outputfile(void)
	{int i=0;
	 char p;
	 fstream u;
	 strcat(filename,dayno);
	 strcat(filename,".txt");
	 u.open(filename,ios::in);
	 if(!u)
	   {
	    cout<<"file error"<<filename;
	    return 0;
	   }
	 clrscr();
	 cout<<"\n\nTHE EMPLOYEE PARTICIPATION SHEET IS BELOW :\n\n\n" ;
	 while(u)
	     {  if(i==660)
	       {
	     i=0;
	     getch();
	     clrscr();
	    }
	    delay(50);
	      u.get(p);
	      cout<<p;
	      i++;
	     }
	  u.close();
	 getch();
	  return 0;
		}

void attendenceout::output(void)
	    {while(1)
	      {
	     cout<<"\nENTER UR OPTION\n";
	     cout<<"TO SHOW DAILY ATTENDENCE DATA(press enter)\nTO SHOW EMPLOYEE DATA(press space)\nTO back press ESC\n";
	     char i;
	     i=getch();
	     if(i==13)
	    attendencedata();
	    else if(i==32)
	     employeedata();
	     else if(i==27)
	      break;
	      }
	    }
void attendenceout::attendencedata(void)
	       {
		getdata();
		outputfile();
	       }

void attendenceout::employeedata(void)
	    {
	     getdata();
	     getidno();
	     outstfile();
	    }
int attendenceout::outstfile(void)
	   {
	    crefilename(1);
	    ifstream st;
	int ab=0,cl=0,pre=0;
	char nam[10],name[20],file[20],ch;
	itoa(no,nam,10);
	strcpy(file,depcode);
	strcat(file,"\\");
	strcpy(name,depcode);
	strcat(name,nam);
	strcat(file,name);
	strcat(file,".txt") ;
	st.open(file);
	while(st)
	{st.get(ch);
	 if(ch==48)
	   ab++;
	 if(ch==49)
	   pre++;
	 }
	st.close();
	cl=ab+pre;
	float per=(pre*100/cl) ;

	cout<<"\nEMPLOYEE data\n\n" ;
	cout<<"TOTAL DAYS :";
	delay(150) ;
	cout<<cl<<"\n";
	cout<<"PRESENT  :";
	delay(150);
	cout<<pre<<"\n";
	cout<<"ABSENT   :";
	delay(150);
	cout<<ab<<"\n";
	cout<<"TOTAL ATTENDENCE PERCENTAGE:";
	delay(250);
	cout<<per<<endl;
	return 0;
	}


void main()
{


Employee emp,e;
char option,ch,Dept[50];
int ID,isFound;
system("cls");
fstream file;
file.open(fileName,ios::ate|ios::in|ios::out|ios::binary);
cout<<""<<endl;
textcolor(964);cprintf("                     WELCOME TO EMPLOYEE MANAGEMENT SYSTEM");
cout<<""<<endl<<endl;
char* pass="sandeep";
char* input;
cout<<"Please enter the password to acess the system:";
cin>>input;
cout<<""<<endl;
if (strcmp(pass,input)==0){
textattr(9);
textcolor(693);cprintf("                              Welcome Sir!!!");
cout<<endl<<"		      Entered right password..... :)"<<endl<<endl;
system("pause");
goto ax;
}
else{
cout<<endl<<endl<<"                        :( Wrong password entered.... \n            Please reopen the program and re-enter the password..."<<endl<<endl;
system("pause");
exit(0);}

ax:
int sel;
system("cls");
cout<<endl<<endl<<"                             *****Select Option*****"<<endl;
cout<<"           1.Keep Employee Record"<<endl;
cout<<"           2.Employee Attendence Record"<<endl;
cin>>sel;
if (sel==1)
goto sel;
else
goto les;
sel:
{
do
{

system("cls");
textcolor(694); cprintf("                         Employee Management System");
cout<<endl<<"              _______________________________________________"<<endl;
cout<<endl<<"              |            ********Menu********             |";
cout<<endl<<"              | Enter your option                           |  ";
cout<<endl<<"              | 1 => Add a new record                       |";
cout<<endl<<"              | 2 => Search record from employee id         |";
cout<<endl<<"              | 3 => List Employee of particular department |";
cout<<endl<<"              | 4 => Display all employee                   |";
cout<<endl<<"              | 5 => Update record of an employee           |";
cout<<endl<<"              | 6 => Delete record of particular employee   |";
cout<<endl<<"              | 7 => Exit from the program                  |"<<endl;
cout<<"              |            ********************             |"<<endl;
cout<<"              _______________________________________________"<<endl;
cin>>option;


switch(option)
{
case '1':
{
emp.ReadData();
file.seekg(0,ios::beg);
isFound=0;
file.read((char*)&e,sizeof(e));
while(!file.eof())
{
if(e.GetID()==emp.GetID())
{
cout<<"This ID already exists..Try for another ID";
isFound=1;
break;
}
file.read((char*)&e,sizeof(e));
}
if(isFound==1)
break;
file.clear();
file.seekp(0,ios::end);
file.write((char*)&emp, sizeof(emp));
cout<<endl<<"New record has been added successfully";
break;
}
case '2':
{
isFound=0;
cout<<endl<<"Enter ID of an employee to be searched:";
cin>>ID;
file.seekg(0,ios::beg);
file.read((char*)&e,sizeof(e));
while(!file.eof())
{
if(e.GetID()==ID)
{
cout<<endl<<"The record found...."<<endl;
cout<<endl<<setw(5)<<"ID"<<setw(15)<<"Name"<<setw(15)<<"Post"<<setw(15)<<"Department"<<setw(8)<<"Salary";
e.DisplayRecord();
isFound=1;
break;
}
file.read((char*)&e,sizeof(e));
}
file.clear();
if(isFound==0)
cout<<endl<<"Data not found for employee ID#"<<ID;
break;
}
case '3':
{
isFound=0;
cout<<"Enter department name to list employee within it:";
cin>>Dept;
file.seekg(0,ios::beg);
file.read((char*)&e,sizeof(e));
while(!file.eof())
{
if(strcmp(e.GetDepartment(),Dept)==0)
{
cout<<endl<<"The record found for this department"<<endl;
cout<<endl<<setw(5)<<"ID"<<setw(15)<<"Name"<<setw(15)<<"Post"<<setw(15)<<"Department"<<setw(8)<<"Salary";
e.DisplayRecord();
isFound=1;
break;
}
file.read((char*)&e,sizeof(e));
}
file.clear();
if(isFound==0)
cout<<endl<<"Data not found for department"<<Dept;
break;
}
case '4':
{
     int counter=0;
cout<<endl<<"Record for employee";
file.clear();
file.seekg(0,ios::beg);
file.read((char*)&e,sizeof(e));
while(!file.eof())
{
counter++;
if(counter==1)
{
cout<<endl<<setw(5)<<"ID"<<setw(15)<<"Name"<<setw(15)<<"Post"<<setw(15)<<"Department"<<setw(8)<<"Salary";
}
e.DisplayRecord();
file.read((char*)&e,sizeof(e));
}
cout<<endl<<counter<<"records found.....";
file.clear();
break;
}
int location;

case '5':
{
     int idFound;
     int recordNo=0;
cout<<endl<<"File is being modified.";
cout<<endl<<"Enter employee ID to be updated:";
cin>>ID;
isFound=0;
file.seekg(0,ios::beg);
file.read((char*)&e,sizeof(e));
while(!file.eof())
{
recordNo++;
if(e.GetID()==ID)
{
cout<<"The old record of employee having ID"<<ID<< "is:";
e.DisplayRecord();
isFound=1;
break;
}
file.read((char*)&e,sizeof(e));
}
if(idFound==0)
{
cout<<endl<<"Data not found for employee ID#"<<ID;
break;
}
file.clear();
location=(recordNo-1)*sizeof(e);
file.seekp(location,ios::beg);
cout<<endl<<"Enter new record for employee having ID"<<ID;
e.ReadData();
file.write((char*)&e, sizeof(e));
break;
}
case '6':
{
int recordNo=0;
cout<<endl<<"Enter employment ID to be deleted:";
cin>>ID;
isFound=0;
file.seekg(0,ios::beg);
file.read((char*)&e,sizeof(e));
while(!file.eof())
{
recordNo++;
if(e.GetID()==ID)
{
cout<<" The old record of employee having ID "<<ID<< " is: ";
e.DisplayRecord();
cout<<"\n"<<"Record ID#"<<ID<<" is successfully deleted.....";
isFound=1;
break;
}
file.read((char*)&e,sizeof(e));
}
char tempFile[]="temp.txt";
fstream temp(tempFile,ios::out|ios::binary);
if(isFound==0)
{
cout<<endl<<"Data not found for employee ID#"<<ID;
break;
}

else
{
file.clear();
file.seekg(0,ios::beg);
file.read((char*)&e,sizeof(e));
while(!file.eof())
{
if(e.GetID()!=ID)
temp.write((char*)&e,sizeof(e));
file.read((char*)&e,sizeof(e));
}
file.close();
temp.close();
temp.open(tempFile,ios::in|ios::binary);
file.open(fileName,ios::out|ios::binary);
temp.read((char*)&e,sizeof(e));
while(!temp.eof())
{
file.write((char*)&e,sizeof(e));
temp.read((char*)&e,sizeof(e));
}
}
temp.close();
file.close();
remove(tempFile);
file.open(fileName,ios::ate|ios::in|ios::out|ios::binary);
break;
}
case '7':
{
cout<<"Exiting the program";
delay(2000);
cout<<"......."<<endl;
system("pause");
system("cls");
cout<<endl<<"                              EMS closed!";
cout<<endl<<"\nHave a GOOD DAY Sir.....!!!"<<endl<<endl<<endl;
textcolor(10);cprintf("           Project Members:    Sandeep Maharjan(75/BCT/2070)");
cout<<endl;
textcolor(11);cprintf("                               Sanjeev Shrestha(77/BCT/2070)");
cout<<endl;
textcolor(12);cprintf("                               Saujan Rajbhandari(75/BCT/2070)");
cout<<endl;
system("pause");
exit(0);
break;
}
default:

	  cout<<"Invalid Options";
}
cout<<"\nDo you want to continue.....?y/n       ";
cin>>ch;
}while(ch!='n');
cout<<"Closing System";
delay(2000);
cout<<"......."<<endl;
system("pause");
system("cls");
cout<<endl<<"                                EMS closed!! \n";
cout<<endl<<"\nHAVE A GOOD DAY SIR.....!!!"<<endl<<endl<<endl;

textcolor(10);cprintf("           Project Members:    Sandeep Maharjan(75/BCT/2070)");
cout<<endl;
textcolor(11);cprintf("                               Sanjeev Shrestha(77/BCT/2070)");
cout<<endl;
textcolor(12);cprintf("                               Saujan Rajbhandari(75/BCT/2070)");
cout<<endl;
system("pause");
exit(0);
}


les:
{

    idinfo d;
    d.dayset();
    attendencein a;
    char options;
    int i=0;
    clrscr();
    while(1)
	 {
	  clrscr();
	 flushall();

	  d.dayset();
	  textcolor(698);
	  cprintf("\n                     Welcome in Attendence Record of EMPLOYEE");
	  cout<<endl;
	  textcolor(15);
	  cprintf("press ESC......QUIT");
	  cout<<endl<<endl;
	  cprintf("1. INPUT");
	  cout<<endl;
	  cprintf("2. OUTPUT\n\n\n");
	  options=getch();
	  clrscr();
	  if(options==49)
	   {
	 a.input();
	 i=1;
	}
	else if(options==50)
	{
	 attendenceout b;
	 b.output();
	}
	else if(options==27)
	{
	 if(i==1)
	 textcolor(1);
	 cout<<"\n"<<endl;

	  cprintf("            THANK YOU FOR Keeping Employee ATTENDENCE Record");

cout<<endl<<endl<<endl<<endl<<endl<<"Closing EMS attendence record";
delay(2000);
cout<<"......."<<endl;
system("pause");
system("cls");
cout<<endl<<"                                EMS closed!! \n";
cout<<endl<<"\nHAVE A GOOD DAY SIR.....!!!"<<endl;

textcolor(10);cprintf("           Project Members:    Sandeep Maharjan(75/BCT/2070)");
cout<<endl;
textcolor(11);cprintf("                               Sanjeev Shrestha(77/BCT/2070)");
cout<<endl;
textcolor(12);cprintf("                               Saujan Rajbhandari(75/BCT/2070)");
cout<<endl;
system("pause");

	 break;
	}
     }
     getch();
}
}
