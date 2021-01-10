#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//Creating Vehicle Class
class vehicle
{
    int  year;
    int id;
    char OwnerName[50];
    char model[50];
    char type[50];
public:
    void add_vehicle();	//Function to add a Vehicle to the Garage
    void show_vehicle() const;	//Function to display a Vehicle
    void modify();	//Function to Update a Users Vehicle
    void report() const; //Function to display Vehicle in a tabular method
    int retid() const;	//Function to return userID
};

void vehicle::add_vehicle()
{
    cout<<"\n User ID :";
    cin>>id;
    cout<<"\nEnter Owner Name :";
    cin.ignore();
    cin.getline(OwnerName,50);
    cout<<"\nEnter Make and Model of Car : ";
    cin.ignore();
    cin.getline(model,50);
    cout<<"\nEnter Type of Vehicle: ";
    cin.ignore();
    cin.getline(type,50);
    cout<<"\nEnter Year of Vehicle: ";
    cin>>year;
    cout<<"\n\nVehicle Added!";
}

void vehicle::show_vehicle() const
{
    cout<<"\n User ID :"<<id;
    cout<<"\nOwner : "<<OwnerName;
    cout<<"\nCar Model : "<<model;
    cout<<model;
    cout<<"\nType of Vehicle : "<<type;
    cout<<"\nYear : "<<year;

}


void vehicle::modify()
{
    cout<<"\nOwner: "<<OwnerName;
    cout<<"\nModify Owner Vehicle (Make/Model) : ";
    cin>>model;
//    cin.getline(model,50);
    cout<<"\nVehicle Type : ";
    cin>>type;
//    cin.ignore();
//    cin.getline(type,50);
    cout<<"\nYear : ";
    cin>>year;
}

int vehicle::retid() const
{
    return id;
}
void vehicle::report() const
{
    cout<<id<<"\t"<<OwnerName<<"\t "<<model<<"\t"<<type<<"\t"<<year<<endl;
}

void write_account();	//Function to write object record in binary file
void display_veh(int);	//function to display vehicle details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details



int main()
{
    char ch;
    int num;
    cout<<"Welcome to the Garage Management System (GMS)";
    do
    {
        cout<<"\n\n\n\tGarage Management System";
        cout<<"\n\n\t1. New Driver";
        cout<<"\n\n\t2. View Driver";
        cout<<"\n\n\t3. All Drivers";
        cout<<"\n\n\t4. Remove Driver";
        cout<<"\n\n\t5. Modify Driver";
        cout<<"\n\n\t6. Exit the System";
        cout<<"\n\n\tSelect Your Option (1-6): ";
        cin>>ch;
        switch(ch)
        {
            case '1':
                write_account();
                break;
            case '2':
                cout<<"\n\n\tEnter the User's ID: "; cin>>num;
                display_veh(num);
                break;
            case '3':
                display_all();
                break;
            case '4':
                cout<<"\n\n\tEnter the User's ID: "; cin>>num;
                delete_account(num);
                break;
            case '5':
                cout<<"\n\n\tEnter the User's ID: "; cin>>num;
                modify_account(num);
                break;
            case '6':
                cout<<"\n\n\tThanks for using the garage management system!";
                break;
            default :cout<<"\a";
        }
        cin.ignore();
        cin.get();
    }while(ch!='6');
    return 0;
}

void write_account()
{
    vehicle veh;
    ofstream outFile;
    outFile.open("garage.dat",ios::binary|ios::app);
    veh.add_vehicle();
    outFile.write(reinterpret_cast<char *> (&veh), sizeof(vehicle));
    outFile.close();
}

void display_veh(int n)
{
    vehicle veh;
    bool flag=false;
    ifstream inFile;
    inFile.open("garage.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\nVEHICLE DETAILS\n";

    while(inFile.read(reinterpret_cast<char *> (&veh), sizeof(vehicle)))
    {
        if(veh.retid()==n)
        {
            veh.show_vehicle();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\nAccount number does not exist";
}

void modify_account(int n)
{
    bool found=false;
    vehicle veh;
    fstream File;
    File.open("garage.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open!\n Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&veh), sizeof(vehicle));
        if(veh.retid()==n)
        {
            veh.show_vehicle();
            cout<<"\n\nEnter New Details of Vehicle"<<endl;
            veh.modify();
            int pos=(-1)*static_cast<int>(sizeof(vehicle));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&veh), sizeof(vehicle));
            cout<<"\n\n\t User's Vehicle Updated";
            found=true;
        }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Vehicle Not Found ";
}

void delete_account(int n)
{
    vehicle veh;
    ifstream inFile;
    ofstream outFile;
    inFile.open("garage.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open!\n Press any Key...";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&veh), sizeof(vehicle)))
    {
        if(veh.retid()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&veh), sizeof(vehicle));
        }
    }
    inFile.close();
    outFile.close();
    remove("garage.dat");
    rename("Temp.dat","garage.dat");
    cout<<"\n\n\tRecord Deleted ..";
}

void display_all()
{
    vehicle veh;
    ifstream inFile;
    inFile.open("garage.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open!\n Press any Key...";
        return;
    }
    cout<<"\n\n\t\t Vehicles In Garage\n\n";
    cout<<"=========================================================================\n";
    cout<<"User    Id    Driver    Make/Model    Type    Year\n";
    cout<<"=========================================================================\n";
    while(inFile.read(reinterpret_cast<char *> (&veh), sizeof(vehicle)))
    {
        veh.report();
    }
    inFile.close();
}
