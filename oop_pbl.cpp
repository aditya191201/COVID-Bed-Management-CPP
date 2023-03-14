#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
using namespace std;

static int severeCount=0;
class hospital    //hospital class
{
protected:
    char name[50],area[100];
    int hospital_id,pincode,bed_normal,bed_oxygen,bed_ventilator;
public:
    void get_data();   //member functions
    void put_data();
    int get_pincode()
    {
        return pincode;
    };
    int get_id()
    {
        return hospital_id;
    };
}h;
class labs     //lab class
{
protected:
    char name_lab[50],area_lab[20];
    int pin_lab,lab_id;
public:
    void get_data_lab();
    void put_data_lab();
    int get_id_lab()
    {
        return lab_id;
    };
}l;
void labs::get_data_lab()     //function to input data of lab
{
    cout<<"\nEnter the ID of the lab:\n";
    cin>>lab_id;
    cout<<"\nEnter the name of the lab:\n";
    cin>>name_lab;
    cout<<"\nEnter the area where the lab is present:\n";
    cin>>area_lab;
    cout<<"\nEnter the pincode of the area where the lab is present:\n";
    cin>>pin_lab;

}
void labs::put_data_lab()    //function to display data of lab
{
    cout<<"\n"<<lab_id<<"\t\t"<<pin_lab<<setw(30)<<name_lab<<setw(30)<<area_lab<<"\n";
}

void hospital::get_data()      //function to input data of hospital
{
    cout<<"\nEnter the name of the Hospital:\n";
    cin>>name;
    cout<<"\nEnter hospital ID:\n";
    cin>>hospital_id;
    cout<<"Enter the area in which hospital is located:\n";
    cin>>area;
    cout<<"\nEnter the pin code of the hospital:\n";
    cin>>pincode;
    cout<<"\nEnter the total number of normal beds available in the hospital:\n";
    cin>>bed_normal;
    cout<<"\nEnter the total number of oxygen beds available in the hospital:\n";
    cin>>bed_oxygen;
    cout<<"\nEnter the total number of ICU beds with ventilator available in the hospital:\n";
    cin>>bed_ventilator;
}

void hospital::put_data()    //function to display data of lab
{
    cout<<"\n"<<hospital_id<<"\t"<<pincode<<"\t\t"<<bed_normal<<"\t\t"<<bed_oxygen<<"\t"<<bed_ventilator<<"\t"<<name<<"\n";
}

class file     //file class storing data of hospitals
{
public:
    void add_entry();
    void display_list();
    void Search_hospital();
    void delete_entry();
    void modify();
};

void file::add_entry()     //function to add entry of hospital in the file
{
    char ch='y';
    ofstream fout("hospital.dat",ios::out|ios::app|ios::binary);
    while(ch=='y'||ch=='Y')
    {
        h.get_data();
        fout.write((char*)&h,sizeof(h));
        cout<<"\nDo you want to add more entries? Enter y for yes\n";
        cin>>ch;
    }
    cout<<"\nData Added and Transferred to file!!!";
    fout.close();
}

void file::display_list()    //function to display all the hospitals in the file
{
    ifstream fin("hospital.dat",ios::in|ios::binary);
    cout<<"\nID\tPincode\t      Isolated\t       Oxygen\tICU\tHospital Name\n";
    while(fin.read((char*)&h,sizeof(h)))
    {
        h.put_data();
    }
    fin.close();
}

void file::Search_hospital()    //function to search a hospital from a file
{
    ifstream fin("hospital.dat",ios::in|ios::binary);
    int pincodeuser,i=0;
    char found='n';
    cout<<"\nEnter the pin code of the area where you live:\n";
    cin>>pincodeuser;
    while(fin.read((char*)&h,sizeof(h)))
    {
        if(h.get_pincode()==pincodeuser)    //searching based on pincode of the area where user lives
        {
            cout<<"\nID\tPincode\t      Isolated\t       Oxygen\tICU\tHospital Name\n";
            h.put_data();
            found='y';
        }
        i++;
    }
    if(found=='n')
    {
        cout<<"\nThere is no hospital available in your area. Please find a suitable hospital in the list of hospitals\n";
    }
    fin.close();
}

void file::delete_entry()      //function to delete an entry of a hospital
{
    int id;
    char found='n';
    fstream fio("hospital.dat",ios::in|ios::out|ios::binary|ios::app);
    ofstream fout("temp.dat",ios::out|ios::binary|ios::app);
    ofstream out("trash.dat",ios::out|ios::binary|ios::app);
    cout<<"Enter the Id of the hospital whose details are to be deleted:\n";
    cin>>id;
    while(fio.read((char*)&h,sizeof(h)))
    {
        if(h.get_id()==id)
        {
            out.write((char*)&h,sizeof(h));
            found='y';
            cout<<"\nRecord Deleted!!!\n";
        }
        else
        {
            fout.write((char*)&h,sizeof(h));
        }
    }
    if(found=='n')
    {
        cout<<"\nHospital with ID "<<id<<" is not in the file!!!\n";
    }
    fio.close();
    fout.close();
    remove("hospital.dat");
    rename("temp.dat","hospital.dat");
}
int covid_check()   //function to check the symptoms the patient who is covid positive is feeling
{
	int ch, count=0;
	severeCount=0;
    cout<<"\nPlease answer the questions correctly!!\nENTER 1 FOR YES. 0 FOR NO\n";
    cout<<"1.Do you have dry cough?\n";
	cin>>ch;
	if(ch==1)
		count++;
	cout<<"2.Do you have sore throat?\n";
	cin>>ch;
	if(ch==1)
		count++;
	cout<<"3.Do you have fever?\n";
	cin>>ch;
	if(ch==1)
		count++;
	cout<<"\nSEVERE SYMPTOMS:\n";
	cout<<"4.Are you experiencing shortness of breath?\n";
	cin>>ch;
	if(ch==1)
	{
		count++;
		severeCount++;
	}
	cout<<"5.Are you experiencing lack of sense of taste and smell?\n";
	cin>>ch;
	if(ch==1)
	{
		count++;
		severeCount++;
	}
	return count;
}
int non_covid_check()     //function to ask patients the symptoms they are having who are yet to take a covid test
{
	int ch, count=0;
	severeCount=0;
    cout<<"\nENTER 1 FOR YES. 0 FOR NO\n";
    cout<<"1.Dry cough\n";
	cin>>ch;
	if(ch==1)
    {
        count++;
    }
	cout<<"2.Sore throat\n";
	cin>>ch;
	if(ch==1)
    {
        count++;
    }
	cout<<"3.Fever\n";
	cin>>ch;
	if(ch==1)
	{
        count++;
    }
	cout<<"\nDo you have any of the following Severe Symptoms?\n 1. Difficulty in  breathing 2. Lack of sense of taste and smell\n";
	cin>>ch;
	if(ch==1)
	{
		count++;
	}
	return count;
}
void file::modify()     //function to modify the details of the hospital
{
    fstream fio("hospital.dat",ios::in|ios::out|ios::binary);
    int id;
    char found='n';
    fio.seekg(0);
    cout<<"\nEnter the ID of the hospital whose record is to be modified:\n";
    cin>>id;
    while(fio)
    {
        int location=fio.tellg();
        fio.read((char*)&h,sizeof(h));
        if(h.get_id()==id)
        {
            h.get_data();
            found='y';
            fio.seekg(location);
            fio.write((char*)&h,sizeof(h));
            cout<<"\nRecord of hospital with ID "<<id<<" is updated!!!";
        }
    }
    if(found=='n')
    {
        cout<<"\nThe hospital with ID. "<<id<<" is not in the file!!!\n";
    }
    fio.close();
}
class file1    //file 1 class for lab file
{
public:
    void add_entry_lab();
    void display_list_lab();
    void delete_entry_lab();
    void modify_entry_lab();
};
void file1::add_entry_lab()    //function to add entry of lab in the file
{
    char ch='y';
    ofstream fout("lab.dat",ios::out|ios::app|ios::binary);
    while(ch=='y'||ch=='Y')
    {
        l.get_data_lab();
        fout.write((char*)&l,sizeof(l));
        cout<<"\nDo you want to add more entries? Enter y for yes\n";
        cin>>ch;
    }
    cout<<"\nData Added and Transferred to file!!!";
    fout.close();
}
void file1::display_list_lab()   //function to display entry of lab from the file
{
    ifstream fin("lab.dat",ios::in|ios::binary);
    cout<<"\nID\t\tPincode\t\t         Lab Name\t   \t\t    Area\n";
    while(fin.read((char*)&l,sizeof(l)))
    {
        l.put_data_lab();
    }
    fin.close();
}
void file1::delete_entry_lab()    //function to delete entry of lab from the file
{
    int id;
    char found='n';
    fstream fio("lab.dat",ios::in|ios::out|ios::binary|ios::app);
    ofstream fout("temp1.dat",ios::out|ios::binary|ios::app);
    ofstream out("trash1.dat",ios::out|ios::binary|ios::app);
    cout<<"Enter the Id of the lab whose details are to be deleted:\n";
    cin>>id;
    while(fio.read((char*)&l,sizeof(l)))
    {
        if(l.get_id_lab()==id)
        {
            out.write((char*)&l,sizeof(l));
            found='y';
            cout<<"\nRecord Deleted!!!\n";
        }
        else
        {
            fout.write((char*)&l,sizeof(l));
        }
    }
    if(found=='n')
    {
        cout<<"\nLab with ID "<<id<<" is not in the file!!!\n";
    }
    fio.close();
    fout.close();
    remove("lab.dat");
    rename("temp1.dat","lab.dat");
}
void file1::modify_entry_lab()    //function to modify entry of lab
{
    fstream fio("lab.dat",ios::in|ios::out|ios::binary);
    int id;
    char found='n';
    fio.seekg(0);
    cout<<"\nEnter the ID of the lab whose record is to be modified:\n";
    cin>>id;
    while(fio)
    {
        int location=fio.tellg();
        fio.read((char*)&l,sizeof(l));
        if(l.get_id_lab()==id)
        {
            l.get_data_lab();
            found='y';
            fio.seekg(location);
            fio.write((char*)&l,sizeof(l));
            cout<<"\nRecord of lab with ID "<<id<<" is updated!!!";
        }
    }
    if(found=='n')
    {
        cout<<"\nThe lab with ID. "<<id<<" is not in the file!!!\n";
    }
    fio.close();
}
void home_quarantine()      //function used to display home quarantine packages to the users
{
    int package;
    cout<<"Available COVID 19 Packages are as follows: \nEnter:\n";
    cout<<"1. Sahayadri Hospital Pune.\n2. Jehangir Hospital Pune\n3. View Both\n";
    cout<<"Choose the package number for more details. \n";
    cin>>package;
    switch(package)
    {
    case 1:
        cout<<"Premium Care Package @ Rs. 16,000 (for 17 days): Package includes:\n1. 1st Consultation with Physician @Hospital followed by Online Follow-up Consultation\n";
        cout<<"2. Essential Home Care Kit (Vitals Monitoring Devices - Thermometer, BP Monitor, Sp02 Probe, Home Disinfectants, etc.)\n";
        cout<<"3. Detailed Guidelines on Self-Monitoring, Isolation & Personal Hygiene\n4. Diet Consultation (Online)\n";
        cout<<"5. Vital Monitoring by a Dedicated Nursing Care Manager throughout the quarantine period (via tele-review)\n";
        cout<<"6. Online psychological counseling\n7. Home Sanitisation service at end of quarantine period\n8. Repeat COVID testing on Day 15 (by home collection)";
        break;
    case 2:
        cout<<"COVID-19 Home Care Isolation Basic Package offered by the hospital at Rs. 10000 for 17 Days!!!\nThis includes: \n1. 2 hours of video consultation daily\n";
        cout<<"2. Pharmacy kit\n3. Medical kit for 17 days\n4. Investigation kit on the first day, and the investigation on the seventh day";
        break;
    case 3:
        cout<<"*****Sahayadri Hospital*****\n";
        cout<<"Premium Care Package @ Rs. 16,000 (for 17 days): Package includes:\n1. 1st Consultation with Physician @Hospital followed by Online Follow-up Consultation\n";
        cout<<"2. Essential Home Care Kit (Vitals Monitoring Devices - Thermometer, BP Monitor, Sp02 Probe, Home Disinfectants, etc.)\n";
        cout<<"3. Detailed Guidelines on Self-Monitoring, Isolation & Personal Hygiene\n4. Diet Consultation (Online)\n";
        cout<<"5. Vital Monitoring by a Dedicated Nursing Care Manager throughout the quarantine period (via tele-review)\n";
        cout<<"6. Online psychological counseling\n7. Home Sanitisation service at end of quarantine period\n8. Repeat COVID testing on Day 15 (by home collection)";
        cout<<"\n\n*****Jehangir Hospital*****\n";
        cout<<"COVID-19 Home Care Isolation Basic Package offered by the hospital at Rs. 10000 for 17 Days!!!\nThis includes: \n1. 2 hours of video consultation daily\n";
        cout<<"2. Pharmacy kit\n3. Medical kit for 17 days\n4. Investigation kit on the first day, and the investigation on the seventh day\n";
        break;
    default:
        cout<<"Wrong Choice\n";
    }
}
int main()
{
    int c,ch,choice,admin,choice1=1,choice2=1,count,test,home,l;
    file f;
    file1 e;
    do
    {
        cout<<"\t\t\t\t\t**********WELCOME**********\n\n";
        cout<<"\nAre you an Administrator of this program? If yes enter your secret password. If you are a patient enter 1\n";
        cin>>admin;
        if(admin==191201||admin==260301||admin==250701||admin==300801)    //checking if the user is administrator or not
        {
            if(admin==191201)
            {
                cout<<"Welcome Aditya!!!\n";
            }
            else if(admin==260301)
            {
                cout<<"Welcome Shreya!!!\n";
            }
            else if(admin==250701)
            {
                cout<<"Welcome Parantak!!!\n";
            }
            else if(admin==300801)
            {
                cout<<"Welcome Tanvi!!!\n";
            }
            do
            {   //menu for administrator
                cout<<"Enter\n1. Add Hospital Record\n2. Display Hospital Record\n3. Search for a Record\n4. Delete Hospital Record\n";
                cout<<"5. Modify Hospital Record\n6. Add Lab Record\n7. Display Lab Record\n8. Delete Lab Record\n9. Modify Lab Record\n";
                cout<<"Enter your choice\n";
                cin>>choice;
                switch(choice)
                {
                case 1:
                    system("CLS");
                    cout<<"\nADD Record of Hospital!\n";
                    f.add_entry();
                    break;
                case 2:
                    system("CLS");
                    cout<<"\nDisplay Total list of Hospital\n";
                    f.display_list();
                    break;
                case 3:
                    system("CLS");
                    cout<<"\nSearch Hospital\n";
                    f.Search_hospital();
                    break;
                case 4:
                    system("CLS");
                    cout<<"\nDelete Record Of Hospital\n";
                    f.delete_entry();
                    break;
                case 5:
                    system("CLS");
                    cout<<"\nModify Record of the Hospital\n";
                    f.modify();
                    break;
                case 6:
                    system("CLS");
                    cout<<"\nADD Record of Lab!\n";
                    e.add_entry_lab();
                    break;
                case 7:
                    system("CLS");
                    cout<<"\nDisplay Total list of Labs\n";
                    e.display_list_lab();
                    break;
                case 8:
                    system("CLS");
                    cout<<"\nDelete Record Of Lab\n";
                    e.delete_entry_lab();
                    break;
                case 9:
                    system("CLS");
                    cout<<"\nModify Record of the Lab\n";
                    e.modify_entry_lab();
                    break;
                default:
                    system("CLS");
                    cout<<"\nWrong Choice!!\n";
                }
                cout<<"\nDo you want to continue?(Admin) If Yes Press 1, If No press 0\n";
                cin>>choice1;
            }while(choice1==1);
        }
        else if(admin==1)
        {
            do
            {   //menu for patient
                system("CLS");
                cout<<"\nWelcome to COVID 19 Bed Management System----PUNE DIVISION\n";
                cout<<"\nHave you gone through COVID-19 Test? Press:\n1: If you are diagnosed as Positive\n2. If you are yet to take a COVID Test.\n";
                cin>>test;
                if(test==1)
                {
                    cout<<"Now we would be asking you some questions please answer them correctly.\n";
                    count=covid_check();   //calling this function to find out the symptoms user is facing
                    if(count>=3)   //this means he is having more than 3 symptoms
                    {
                        cout<<"You have enough symptoms to get yourself admitted\n";
                        cout<<"Enter:\n";
                        cout<<"1. Search for hospital\n2. Display all the hospitals\n";
                        cout<<"Enter your choice\n";
                        cin>>choice;
                        switch(choice)
                        {
                        case 1:
                            system("CLS");
                            cout<<"\nSearch Hospital\n";
                            f.Search_hospital();
                            break;
                        case 2:
                            system("CLS");
                            cout<<"\nList of all Hospitals\n";
                            f.display_list();
                            break;
                        }
                    }
                    else if(count<3 && severeCount>0)    //having less than 3 symptoms but having a severe symptoms
                    {
                        cout<<"Severe symptom present, you should get admitted immediately\n";
                        cout<<"Enter:\n";
                        cout<<"1. Search for hospital\n2. Display all the hospitals\n";
                        cout<<"Enter your choice\n";
                        cin>>choice;
                        switch(choice)
                        {
                        case 1:
                            system("CLS");
                            cout<<"\nSearch Hospital\n";
                            f.Search_hospital();
                            break;
                        case 2:
                            system("CLS");
                            cout<<"\nList of all Hospitals\n";
                            f.display_list();
                            break;
                        }
                    }
                    else if(count<3 && severeCount==0)    //less than 3 symptoms so home quarantine would be recommended
                    {
                        cout<<"Mild symptoms, home quarantine recommended\n\n";
                        cout<<"Would you like to check various home quarantine kits offered by hospitals? If yes Enter 1\n\n";
                        cout<<"If you still want to search or view the hospitals, Enter 2\n";
                        cin>>home;
                        if(home==1)
                        {
                            home_quarantine();
                        }
                        else if(home==2)
                        {
                            cout<<"Enter:\n";
                            cout<<"1. Search for hospital\n2. Display all the hospitals\n";
                            cout<<"Enter your choice\n";
                            cin>>choice;
                            switch(choice)
                            {
                            case 1:
                                system("CLS");
                                cout<<"\nSearch Hospital\n";
                                f.Search_hospital();
                                break;
                            case 2:
                                system("CLS");
                                cout<<"\nList of all Hospitals\n";
                                f.display_list();
                                break;
                            }
                        }
                    }
                }
                else if(test==2)     //loop for patient who has not taken a covid test
                {
                    cout<<"Now we would be asking you some questions please answer them correctly.\n";
                    count=non_covid_check();
                    if(count>=3)    //this means he is having more than 3 symptoms so testing is required
                    {
                        cout<<"You have enough symptoms to go through a covid test\n";
                        cout<<"To view all the available labs Enter 1\n";
                        cin>>l;
                        if(l==1)
                        {
                            system("CLS");
                            cout<<"\nDisplay Total list of Labs\n";
                            e.display_list_lab();
                        }
                    }
                    else if(count<3)    ////this means he is having less than 3 symptoms still taking a test is advised
                    {
                        cout<<"You are in Low Risk. Still for caution consult a doctor.\n";
                        cout<<"Do you still want to view the labs? Enter 1\n";
                        cin>>l;
                        if(l==1)
                        {
                            system("CLS");
                            cout<<"\nDisplay Total list of Labs\n";
                            e.display_list_lab();
                        }
                    }
                }
                cout<<"\nDo you want to continue?(Patient) If Yes Press 1, If No press 0\n";
                cin>>choice2;
            }while(choice2==1);
        }
        else
        {
            cout<<"\nIf you are administrator you have entered the wrong password. If you are a patient Enter 1 again\n";
        }
        cout<<"\nDo you want to continue? If YES Enter 1, If NO enter 0\n";
        cin>>ch;
    }while(ch==1);
}
