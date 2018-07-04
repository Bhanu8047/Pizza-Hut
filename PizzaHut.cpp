#include<iostream>
#include<string.h>
#include<fstream>
#include<conio.h>
#include<stdlib.h>
using namespace std;
// Declare file pointers
fstream fin;
void firstPizza();

class Pizza
{
public:

    int id;
    char name[50];
    int price;

    void show();
    void input();
};


void Pizza :: show()
{
	cout<<"Id:"<<id<<endl;
	cout<<"Name:"<<name<<endl;
	cout<<"Price:"<<price<<endl<<endl;
}

void Pizza :: input()
{
	cout<<"Id:";cin>>id;
	cout<<"Name:";cin.ignore();cin.getline(name ,50);
	cout<<"Price:";cin>>price;
}

void checkPizza()
{
    ifstream fin;
 fin.open("Pizza.dat", ios::in|ios::binary);
if(!fin){cout<<"\t\t\tFile not Found.\n\t\t\tTo create file [Press Enter]";getch();firstPizza();}
else{
        Pizza obj;
    bool flag=false;
    fin.read((char*)&obj, sizeof(obj));
    while(!fin.eof())
    {
        if(obj.id==1){flag=true;break;}
        else{flag=false;}
        fin.read((char*)&obj ,sizeof(obj));
    }
    if(!flag)
    {
        cout<<"Pizza menu not available";
        getch();
        firstPizza();
    }
    else{
    cout<<"Pizza Menu Available";
    }
    getch();
}

}


void firstPizza()
{
    ofstream fout;
	fout.open("Pizza.dat", ios::app|ios::binary);
	if(!fout){cout<<"File creation Failed";}
    else
    {
        Pizza obj;
        system("cls");
        cout<<"First Pizza Id:1\n";
        obj.id=1;
        cout<<"Enter name:";
        cin.ignore();
        cin.getline(obj.name ,50);
        cout<<"Enter Price:";
        cin>>obj.price;

        fout.write((char*)&obj, sizeof(obj));
        fout.close();
        system("cls");
        cout<<"\n\t\t\t\t\t\tPizza Successfully Added!";getch();
    }
}

class managePizza :public Pizza  //A class to Manage pizza details.
{
public:

    void pizzaMenu();

    void addPizza();

    void deletePizza();

    void searchPizza();

    void modifyPizza();

};

void managePizza :: addPizza()  //Add new Pizza
{   system("cls");

        ofstream fout;
        fout.open("Pizza.dat",ios::app|ios::binary);
        if(!fout){cout<<"File not found!";}
        else{

        Pizza temp;
        cout<<"Enter id:";
        cin>>temp.id;
        cout<<"Enter name:";
        cin.ignore();
        cin.getline(temp.name ,50);
        cout<<"Enter Price:";
        cin>>temp.price;

            fout.write((char*)&temp, sizeof(temp));
            fout.close();
            system("cls");
            cout<<"\n\t\t\t\t\t\tPizza Successfully Added!";getch();

                }
}




void managePizza :: deletePizza()  //delete Pizza
{
    int n;
	cout<<"Enter id that should be Deleted :";
	cin>>n;
	Pizza obj;
	ofstream fout;
	fout.open("new.dat",ios::out|ios::binary);
	fin.open("Pizza.dat",ios::in| ios::binary);
	if(!fin)
	{
		cout<<"File not Found";
		exit(0);
	}
	else
	{
		fin.read((char*)&obj, sizeof(obj));
		while(!fin.eof())
		{
			if(n == obj.id)
			{
				fout.write((char*)&obj, sizeof(obj));
			}
			else
			{
				 cout<<"Press Any Key....For Search"<<endl;
				 getch();
			}
			fin.read((char*)&obj, sizeof(obj));
		}
	}
	fout.close();
	fin.close();
	remove("Pizza.dat");
	rename("new.dat", "Pizza.dat");
}

void managePizza :: pizzaMenu()  // Pizza Menu
{
    ifstream fin;
    fin.open("Pizza.dat", ios::in|ios::binary);
    Pizza obj;
    fin.read((char*)&obj, sizeof(obj));
        while(!fin.eof())
        {
            obj.show();
            fin.read((char*)&obj, sizeof(obj));
        }
        getch();
        fin.close();
    }

void managePizza :: searchPizza()   //Function to search pizza
{
	int n;
	cout<<"Enter Id to search:";
	cin>>n;
	Pizza obj;
	fin.open("Pizza.dat",ios::in| ios::binary);
	if(!fin)
	{
		cout<<"File not Found";
		exit(0);
	}
	else
	{
	    bool flag = false;
		fin.read((char*)&obj, sizeof(obj));
		while(!fin.eof())
		{
			if(obj.id == n)
			{
				obj.show();
				getch();
				flag = true;
				break;
			}
			else
			{
				 flag=false;
			}
			fin.read((char*)&obj, sizeof(obj));
		}
		if(!flag){system("cls");cout<<"\n\t\t\t[No record found !]";getch();}
	}
	fin.close();
}

void managePizza :: modifyPizza()		//Function to Modify Pizza Details
{
	int n;
	cout<<"Enter Id to modify:";
	cin>>n;
	Pizza obj;
	bool flag = false;
	fin.open("Pizza.dat",ios::in| ios::out|ios::binary);
	if(!fin)
	{
		cout<<"File not Found";
		exit(0);
	}
	else
	{
		fin.read((char*)&obj, sizeof(obj));
		while(!fin.eof())
		{
			if(obj.id == n)
			{
				fin.seekg(0,ios::cur);
				cout<<"Enter New Record.."<<endl;
				obj.input();
				fin.seekp(fin.tellg() - sizeof(obj));
				fin.write((char*)&obj, sizeof(obj));
				flag=true;
				break;
			}
			else
			{
				 flag=false;
			}
			fin.read((char*)&obj, sizeof(obj));
		}if(!flag){cout<<"\n\t\t\t[No record found !]";getch();}
	}
	system("cls");
	cout<<"\t\t\t\t\t\t\t\nSuccesfully Modified!";
	getch();

	fin.close();
}


//
//
//Order Function and Classes

class Order : public managePizza
{
public:

    int noOfPerson;
    int orderNo;
    int pizzaId[];
    int Total;

public:

    void orderPizza();

    void generateBill();

    //For input and display;
    void show1();
    void input1();
};

void Order :: show1()
{
    cout<<"\nOrder No."<<orderNo<<endl;
    cout<<"\nNo of Persons:"<<noOfPerson<<endl;
}

void Order :: input1()
{
    cout<<"\nOrder No.";cin>>orderNo;
    cout<<"\nNo of Persons:";cin>>noOfPerson;
    pizzaId[noOfPerson];

}

void choosePizza() // Choosing pizza
{   system("cls");
    ofstream fout;
    Order cust;
    Pizza obj;
    cust.Total=0;
    fout.open("Order.dat", ios::app|ios::binary);
    if(!fout){system("cls");cout<<"\t\t\t\t\t\tError";getch(); exit(0);}
    cout<<"\t\t\t\tEnter Details";
    cust.input1();
    fin.open("Pizza.dat", ios::in|ios::binary);
    if(!fin){system("cls");cout<<"\t\t\t\t\t\tError";getch(); exit(0);}
        for(int i=0;i<cust.noOfPerson;i++)
        {
        cout<<"Enter pizza Id "<<i+1<<":";cin>>cust.pizzaId[i];
        fin.read((char*)&obj, sizeof(obj));
        while(!fin.eof())
        {
            if(cust.pizzaId[i] == obj.id)
            {
                cust.Total+=obj.price;
                fout.write((char*)&cust, sizeof(cust));
                //cust.Total+=obj.price;
            }
            fin.read((char*)&obj, sizeof(obj));
        }
        //fin.seekg(0,ios::beg);
        }//fout.write((char*)&cust, sizeof(cust));
    fin.close();
    fout.close();
    getch();
}

void cart()// display cart
{
    ifstream fil;
    system("cls");
    int orderno;
    cout<<"Enter Orderno:";
    cin>>orderno;
    Order cust;
    Pizza obj;
    fil.open("Pizza.dat",ios::in|ios::binary);
    if(!fil){system("cls");cout<<"\t\t\t\t\t\tError";getch(); exit(0);}
    fin.open("Order.dat", ios::in|ios::binary);

    if(!fin){system("cls");cout<<"\t\t\t\t\t\tError";getch(); exit(0);}
    else
    {
        fin.read((char*)&cust, sizeof(cust));
        cout<<"Order Details\n";
        while(!fin.eof())
        {
            if(orderno==cust.orderNo)
            {
                fil.read((char*)&obj, sizeof(obj));
                cust.show1();
 for(int i=0;i<cust.noOfPerson;i++){
                while(!fil.eof())
                {

                    if(cust.pizzaId[i]==obj.id)
                    {
                        obj.show();
                    }
                    fil.read((char*)&obj, sizeof(obj));
                 }
 }
            }
            fin.read((char*)&cust, sizeof(cust));
        }
    }
    fin.close();
    fil.close();
    getch();
}
//main Orders functions
void Order :: orderPizza() // For selecting pizza
{
    int opt;
    while(1)
    {
        system("cls");
        cout<<"\n[\t\t\t1.Choose pizza.\t\t\t]";
        cout<<"\n[\t\t\t2.Display My Cart.\t\t]";
        cout<<"\n[\t\t\t3.Previous menu.\t\t]";
        cout<<"\n[\t\t\tEnter option:\t\t\t]";
        cin>>opt;
        switch(opt)
        {
            case 1:{choosePizza();break;}
            case 2:{cart();break;}
            case 3:{return;}
            default:{cout<<"Wrong choice!";}
        }
    }
}

void Order :: generateBill() // For Order and billing
{
    system("cls");
    ifstream fil;
    system("cls");
    int orderno;
    cout<<"Enter Orderno:";
    cin>>orderno;
    Order cust;
    //Pizza obj;
    fil.open("order.dat",ios::in|ios::binary);
    if(!fil){system("cls");cout<<"\t\t\t\tBad file error!";getch();exit(0);}
    fil.read((char*)&cust, sizeof(cust));
    while(!fil.eof())
    {

        if(orderno == cust.orderNo)
        {
            cout<<"\nOrderno:"<<cust.orderNo;
            cout<<"\nTotal:"<<cust.Total;
        }
        fil.read((char*)&cust, sizeof(cust));
    }
    fil.close();
    getch();
}




/* Main Functions*/
void order()
{
    Order custs;
    fin.open("Order.dat", ios::app|ios::binary);
    if(!fin){cout<<"File creation error";getch();exit(0);}
    fin.close();
    int opt;
    while(1)
    {
        system("cls");
        cout<<"1.Choose Pizza.\n";
        cout<<"2.Order Pizza.\n";
        cout<<"3.Return to previous menu.\n";
        cout<<"Enter Option:";
        cin>>opt;
        switch(opt)
        {
            case 1:{custs.orderPizza();break;}
            case 2:{custs.generateBill();break;}
            case 3:{return;}
            default:{cout<<"Wrong choice";}
        }
    }
    fin.close();
}

void Manage()
{

    int opt;
    managePizza shop;
    while(1)
    {
        system("cls");
        cout<<"1.Add Pizza.\n";
        cout<<"2.Delete Pizza.\n";
        cout<<"3.Search Pizza.\n";
        cout<<"4.Modify Pizza.\n";
        cout<<"5.Display Pizza.\n";
        cout<<"6.Previous Menu.\n";
        cin>>opt;
        switch(opt)
        {
            case 1:{shop.addPizza();break;}
            case 2:{shop.deletePizza();break;}
            case 3:{shop.searchPizza();break;}
            case 4:{shop.modifyPizza();break;}
            case 5:{shop.pizzaMenu();break;}
            case 6:{return;}
            default:{cout<<"Wrong choice";}
        }
    }
}


main()
{
    checkPizza();
    int opt;
    while(1)
    {
        system("cls");
        cout<<"1.Manage Pizza.\n";
        cout<<"2.Order Pizza.\n";
        cout<<"3.Exit.\n";
        cout<<"Enter Option:";
        cin>>opt;
        switch(opt)
        {
            case 1:{Manage();break;}
            case 2:{order();break;}
            case 3:{exit(0);}
            default:{cout<<"Wrong choice";}
        }
    }

    return 0;
}
