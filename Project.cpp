#include <stdio.h>
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h>
#include <string.h>
#include <time.h>

using namespace std;

class Person
{
    char Name[50],Gender[10];
    int Age,Date,Month,Year;
    char City[50],Country[50],State[50],blood_g[5];
public:
    void PersonInfo()
    {
        cout<<"Enter Name :";
        cin.clear();
        cin.ignore();
        cin.getline(Name,50);
        cout<<"Enter Gender :";
        cin>>Gender;
        cout<<"Enter Age :";
        cin>>Age;
        cout<<"Enter Address :";
        cin>>Country;
        cout<<"Enter Blood group:";
        cin>>blood_g;
    }

    void Display_info()
    {
        cout<<"Name: "<<Name<<endl;
        cout<<"Gender: "<<Gender<<endl;
        cout<<"Age: "<<Age<<endl;
        cout<<"Address: "<<this->Country<<endl;
        cout<<"Blood Group:"<<blood_g<<endl;
    }
};

class Staff:public Person
           {
           int salary;
           char time_from[30],time_to[30];

    public:

          void staff_info()
          {
              PersonInfo();
              cout<<"Enter salary:";cin>>salary;
              cout<<"Enter Duty time:"; cout<<"From:";cin>>time_from;cout<<"To:";cin>>time_to;
          }

           void show_staff()
           {
                cout<<"\nSalary: "<<salary;
                cout<<"\nDuty Time: "<<time_from<<"--"<<time_to<<endl;
                Display_info();
           }
};


class patient: public Person
{
int reg_no;
char occupation[30];
char date_admit[30];
char date_discharge[30];
int bill,total;

public:
char medicine[100];
void patient_bill();
void getdata();
void showdata();
int retidno();
void modify_medicine(int n);
    void write_patient();
    void display_all();
    void display_p(int n);
    void modify_patient(int n);
    void delete_patient(int n);
};


void patient::patient_bill()
{
    system("CLS");
cout << "********************************************************************************";
cout << "\n\n\t\t\t\tPatient Fee Charge\n\n ";
cout << "*******************************************************************************";

cout << "\nHospital Care Charges                      :\t  50";
cout << "\nHospital Maintaince Charges                :\t  50";
cout << "\nPatient Individual  Charges                :\t " << bill;
total = 50 + 50 + bill;
cout << "\nTotal Fee Charge                           :\t"  << total<<"\n";
cout << "********************************************************************************";
}

void patient::getdata()
{
PersonInfo();
cout<<"\nEnter The registration number of the patient: ";
cin>>reg_no;
cout<<"\nEnter The phone number of the patient: ";
cin>>occupation;
cout<<"\nEnter The bill of the patient:";
cin>>bill;
cout<<"\nEnter The date admitted(dd/mm/yyyy):";
cin>>date_admit;
patient_bill();
strncpy(medicine, "null", sizeof(medicine) - 1);
    medicine[sizeof(medicine) - 1] = 0;
}

void patient::showdata()
{
cout<<"\nRegistration number of patient: "<<reg_no<<"\n";
Display_info();
cout<<"\nNumber : "<<occupation;
cout<<"\nAdmit date : "<<date_admit;
cout<<"\nBill :"<<total;
cout<<"\nPrescribed Medicine: "<<medicine;

}

int  patient::retidno()
{
return reg_no;
}

void patient::modify_medicine(int n)
{
bool found=false;
patient p;
fstream File;
File.open("patient.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
    while(!File.eof() && found==false)
{

File.read(reinterpret_cast<char *> (&p), sizeof(patient));
if(p.retidno()==n)
{
p.showdata();
cout<<"\n\nPlease Enter The Medicine of patient"<<endl;
                cin>>p.medicine;
    int pos=(-1)*static_cast<int>(sizeof(p));
    File.seekp(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&p), sizeof(patient));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
File.close();
if(found==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}


void patient::write_patient()  // writing into file
{
patient p;
ofstream outFile;
outFile.open("patient.dat",ios::binary|ios::app);
p.getdata();
outFile.write(reinterpret_cast<char *> (&p), sizeof(patient));
outFile.close();
    cout<<"\n\nPatient record Has Been Created ";
cin.ignore();
cin.get();
}

void patient::display_all()
{
patient p;
ifstream inFile;
inFile.open("patient.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
while(inFile.read(reinterpret_cast<char *> (&p), sizeof(patient)))
{
p.showdata();
cout<<"\n\n=======================================================================================\n";
}
inFile.close();
cin.ignore();
cin.get();
}

void patient::display_p(int n)
{
patient p;
ifstream inFile;
inFile.open("patient.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
bool flag=false;
while(inFile.read(reinterpret_cast<char *> (&p), sizeof(patient)))
{
if(p.retidno()==n)
{
  p.showdata();
flag=true;
}
}
inFile.close();
if(flag==false)
cout<<"\n\nrecord not exist";
cin.ignore();
cin.get();
}


void patient:: modify_patient(int n)
{
bool found=false;
patient p;
fstream File;
File.open("patient.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
    while(!File.eof() && found==false)
{

File.read(reinterpret_cast<char *> (&p), sizeof(patient));
if(p.retidno()==n)
{
p.showdata();
cout<<"\n\nPlease Enter The New Details of patient"<<endl;
                p.getdata();
    int pos=(-1)*static_cast<int>(sizeof(p));
    File.seekp(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&p), sizeof(patient));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
File.close();
if(found==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}


void patient:: delete_patient(int n)
{
patient p;
ifstream inFile;
inFile.open("patient.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
ofstream outFile;
outFile.open("Temp.dat",ios::out);
inFile.seekg(0,ios::beg);
while(inFile.read(reinterpret_cast<char *> (&p), sizeof(patient)))
{
if(p.retidno()!=n)
{
outFile.write(reinterpret_cast<char *> (&p), sizeof(patient));
}
}
outFile.close();
inFile.close();
remove("patient.dat");
rename("Temp.dat","patient.dat");
cout<<"\n\n\tRecord Deleted ..";
cin.ignore();
cin.get();
}


class Doctor: public Staff
{
    int DocID;
    patient p;
    char Spz[500];

public:
     bool CheckRegNo(int n)
      {

      bool found=false;
 Doctor d;
 fstream File;
 File.open("Doctor.dat",ios::binary|ios::in);
 if(!File)
 {
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
 }
    while(!File.eof() && found==false)
        {

File.read(reinterpret_cast<char *> (&d), sizeof(Doctor));
if(d.DocID==n)
{
    found=true;
}
        }
        File.close();
        return found;
        cin.ignore();
        cin.get();


      }


    void DoctorInfo()
    {
        staff_info();
        id:
        cout<<"Enter Doctor ID(1200-1299):";
        int m;
        cin>>m;
        if(CheckRegNo(m)==false)
        {
            DocID=m;
        }
        else
        {
            cout<<"ID already taken\n";
            goto id;
        }


        cout<<"Enter Doctor Specialize :";
        cin>>Spz;
        system("pause");
    }

    void show_doctor()
    {
        cout<<"Doctor ID: "<<DocID;
        show_staff();

        cout<<"\nDoctor Specialize: "<<Spz;
    }

    int  retDid()
   {
return DocID;
   }

    void Prescribe_Medicine()
    {
        int n;
        cout<<"\n\n\tEnter Reg Number Of patient : "; cin>>n;
        p.modify_medicine(n);
    }


    void write_doctor()
   {
Doctor d;
ofstream outFile;
outFile.open("Doctor.dat",ios::binary|ios::app);
d.DoctorInfo();
outFile.write(reinterpret_cast<char *> (&d), sizeof(Doctor));

    cout<<"\n\nDoctor record Has Been Created ";
outFile.close();
cin.ignore();
   }


   void display_all_Doctor()
{
Doctor d;
ifstream inFile;
inFile.open("Doctor.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
while(inFile.read(reinterpret_cast<char *> (&d), sizeof(Doctor)))
{
d.show_doctor();
cout<<"\n\n=======================================================================================\n";
}
inFile.close();
cin.ignore();
cin.get();
}


void display_d(int n)
{
Doctor d;
ifstream inFile;
inFile.open("Doctor.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
bool flag=false;
while(inFile.read(reinterpret_cast<char *> (&d), sizeof(Doctor)))
{
if(d.DocID==n)
{
  d.show_doctor();
flag=true;
}
}
inFile.close();
if(flag==false)
cout<<"\n\nrecord not exist";
cin.ignore();
cin.get();
}

void modify_doctor(int n)
{
bool found=false;
Doctor d;
fstream File;
File.open("Doctor.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
    while(!File.eof() && found==false)
{

File.read(reinterpret_cast<char *> (&d), sizeof(Doctor));
if(d.DocID==n)
{
   d.show_doctor();
   cout<<"\n\nPlease Enter The New Details:"<<endl;
                d.DoctorInfo();
    int pos=(-1)*static_cast<int>(sizeof(d));
    File.seekp(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&d), sizeof(Doctor));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
File.close();
if(found==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}


void Doctor_choice()

{
    Doctor d;
    char ch;

    do
{
int n;
system("cls");

        cout<<"\n\n\t01. Prescribe Medicine for patient ";
cout<<"\n\n\t02. Search DOCTOR ";
cout<<"\n\n\t03. DOCTOR Menu";
cout<<"\n\n\t04. To exit.....";
        cout<<"\n\n\tPlease Select your Option (1-4) ";
        cin>>ch;

switch(ch)
{
case '1': Prescribe_Medicine();
     break;
case '2':
         cout<<"Enter Doctor ID :";cin>>n;
                      display_d(n);
                      break;

                       case '3': d.Doctor_menu();
                       break;
default :cout<<"\b";
}
    }while(ch!='4');

}



   void Doctor_menu()
{
    char ch;

do
{
int n;
system("cls");

cout<<"\n\n\t01. INSERT DOCTOR DATA";
cout<<"\n\n\t02. Search DOCTOR ";
cout<<"\n\n\t03. ALL DOCTOR ";
cout<<"\n\n\t04. MODIFY DOCTOR DATA";
cout<<"\n\n\t05. TO EXIT............";
cout<<"\n\n\tPlease Select Your Option (1-5) ";
cin>>ch;
        system("cls");
switch(ch)
{
case '1': write_doctor();
     break;
case '2':
         cout<<"Enter Doctor ID :";cin>>n;
                      display_d(n);
                      break;

case '3':

        display_all_Doctor();
    break;
case '4':
        cout<<"Enter Doctor ID :";cin>>n;
        modify_doctor(n);
        break;
}
    }while(ch!='5');

}

};

class Receptionist:public Staff
{
    patient p;
    int RecID;

public:



void entry_Patient()
{
char ch;
int num;
do{
system("cls");
cout<<"\n\n\n\tENTRY MENU";
cout<<"\n\n\t1.CREATE PATIENT RECORD";
cout<<"\n\n\t2.DISPLAY ALL PATIENTS RECORDS";
cout<<"\n\n\t3.SEARCH PATIENT RECORD ";
cout<<"\n\n\t4.MODIFY PATIENT RECORD";
cout<<"\n\n\t5.DELETE PATIENT RECORD";
cout<<"\n\n\t6.TO EXIT";
cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
cin>>ch;
system("cls");

switch(ch)
{
case '1': p.write_patient();break;
case '2': p.display_all(); break;
case '3': cout<<"\n\n\tPlease Enter The reg  number "; cin>>num;
   p.display_p(num);break;
case '4': cout<<"\n\n\tPlease Enter The reg number "; cin>>num;
   p.modify_patient(num);break;
case '5': cout<<"\n\n\tPlease Enter The reg number "; cin>>num;
   p.delete_patient(num);break;

}
}while(ch!='6');
}
};

int main()
{
    string passed ="";
    Receptionist r;
    Doctor d;
    int ch;
    char cha;
    do{
    cout<<"\t\t\n\n\n";
    printf("\n\n\n\n\n\n\n\t\t\t\t#########################################");
	printf("\n\t\t\t\t#\t\t WELCOME TO\t\t#");
	printf("\n\t\t\t\t#          HOSPITAL Management SYSTEM   #");
	printf("\n\t\t\t\t#########################################");
	printf("\n\n\n\n\n Please choose from the option below......\n\n");
    cout<<"\t\t1.Receptionist\n";
    cout<<"\t\t2.Doctor\n";
    cout<<"\t\t3.Exit From The SYSTEM\n";
    cin>>ch;
    switch(ch){

        case 1:
                 login2:
                 cout<<"Enter Receptionist password: ";
                 cha = _getch();
                 while(cha != 13){//character 13 is enter
                  passed.push_back(ch);
                cout << '*';
                cha = _getch();
                }
                 if((passed == "reception")==0)
                 {
                   r.entry_Patient();
                 }
                 else
                 {
                    cout<<"WRONG PASSWORD!!!\n";
                    goto login2;
                 }
                break;
        case 2:

                 login3:
                 cout<<"Enter Doctor password: ";
                 cha = _getch();
                 while(cha != 13){
                  passed.push_back(ch);
                cout << '*';
                cha = _getch();
                }

                 if((passed == "doctor")==0)
                 {
                   d.Doctor_choice();
                 }
                 else
                 {
                    cout<<"WRONG PASSWORD!!!\n";
                    goto login3;
                 }
                 break;
            }
    }while(ch!=3);
}

