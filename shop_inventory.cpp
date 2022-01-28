

#include <iostream>
#include <fstream>
#include<string>
using namespace std;
int ID;
class Order{
public:
	int order_id;
	string customer_name;
	string card_number;
	int cvv;
};

class Product
{
public:
     int id;
     string name;
     int price;
     int stock_item;
     string company_name;
        
};



void addproduct() {
    Product p;
    cout << "\n\tEnter Product name : ";
    cin.get();
    getline(cin, p.name);
    cout << "\n\tEnter Product price : ";
    cin >> p.price;
    cout << "\n\tEnter stock item : ";
    cin >> p.stock_item;
    cout << "\n\tEnter Company name : ";
    cin >> p.company_name;
    ID++;

    ofstream write;
    write.open("inventory.txt", ios::app);
    write << "\n" << ID;
    write << "\n" << p.name ;
    write << "\n" << p.price ;

    write << "\n" << p.stock_item ;
    write << "\n" << p.company_name;
    write.close();
    write.open("id.txt");
    write << ID;
    write.close();
    cout << "\n\tData save to file";
}

void print(Product p) {
    cout << "\n\t---Product Data---";
    cout << "\n\tID is : " << p.id;
    cout << "\n\tProduct Name is : " << p.name;
    cout << "\n\tPrice is : " << p.price;
    cout << "\n\tStock Item is : " << p.stock_item;
    cout << "\n\tCompany Name is : " << p.company_name;

}

int get_stock_item(int id)
{
    Product p;
    ifstream read;
    read.open("inventory.txt");
    while (!read.eof()) {
        read >> p.id;
        read.ignore();
        getline(read, p.name);
        read >> p.price;
        read >> p.stock_item;
        read >> p.company_name;
        if (p.id == id) {
            return p.stock_item;
        }
    }
}



void readData() {
    Product p;
    ifstream read;
    read.open("inventory.txt");
    while (!read.eof()) {
        read >> p.id;
        read.ignore();
        getline(read, p.name);
        read >> p.price;
        read >> p.stock_item;
        read >> p.company_name;
        print(p);
    }
    read.close();
}

int searchData() {
    int id;
    cout << "\n\tEnter product id want to search : ";
    cin >> id;
    Product p;
    ifstream read;
    read.open("inventory.txt");
    while (!read.eof()) {
        read >> p.id;
        read.ignore();
        getline(read, p.name);
        read >> p.price;
        read >> p.stock_item;
        read >> p.company_name;
        if (p.id == id) {
            print(p);
            return id;
        }
    }
}

void searchDatabyname() {
    string name;
    cout << "\n\tEnter product name want to search : ";
    cin.get();
    getline(cin, name);
    Product p;
    ifstream read;
    read.open("inventory.txt");
    while (!read.eof()) {
        read >> p.id;
        read.ignore();
        getline(read, p.name);
        read >> p.price;
        read >> p.stock_item;
        read >> p.company_name;
        if (p.name == name) {
            print(p);
        }
    }
}


void buy_product()
{
    int id = searchData();
    cout << "\n\tYou want to buy product (y/n) : ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
	Order od;
	int item_count=get_stock_item(id);
	if(item_count>0)
	{
    cout << "\n\tEnter name on card : ";
    cin.get();
    getline(cin, od.customer_name);
    cout << "\n\tEnter card number : ";
    cin >> od.card_number;
    cout << "\n\tEnter card cvv : ";
    cin >> od.cvv;
    
    ofstream write;
    write.open("orders.txt", ios::app);
    write << "\n" << id;
    write << "\n" << od.customer_name ;
    write << "\n" << od.card_number;
    write << "\n" << od.cvv;
    write.close();

    Product p;
    ofstream tempFile;
    tempFile.open("temp.txt");
    ifstream read;
    read.open("inventory.txt");
    while (!read.eof()) {
            read >> p.id;
            read.ignore();
            getline(read, p.name);
            read >> p.price;
            read >> p.stock_item;
            read >> p.company_name;
            if (p.id != id) {
                tempFile << "\n" << p.id;
                tempFile << "\n" << p.name;
                tempFile << "\n" << p.price;
                tempFile << "\n" << p.stock_item;
                tempFile << "\n" << p.company_name;
            }
            else {
                tempFile << "\n" << p.id;
                tempFile << "\n" << p.name;
                tempFile << "\n" << p.price;
                tempFile << "\n" << int(p.stock_item-1);
                tempFile << "\n" << p.company_name;
            }
        }
        read.close();
        tempFile.close();
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        cout << "\n\tData updated successfuly";
	cout << "\n\tOrder Placed successfully";
  }
    
    
else{
	cout<<"\n\tItem out of stock :(";
	cout<<"\n\t Cannot Place Order";
}
}
	
}


void updateData() {
    int id = searchData();
    cout << "\n\tYou want to update record (y/n) : ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        Product newData;
        cout << "\n\tEnter product name : ";
        cin.get();
        getline(cin, newData.name);
        cout << "\n\tEnter product price : ";
        cin >> newData.price;
        cout << "\n\tEnter product stock item : ";
        cin >> newData.stock_item;
        cout << "\n\tEnter product company name : ";
        cin >> newData.company_name;
        Product p;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("inventory.txt");
        while (!read.eof()) {
            read >> p.id;
            read.ignore();
            getline(read, p.name);
            read >> p.price;
            read >> p.stock_item;
            read >> p.company_name;
            if (p.id != id) {
                tempFile << "\n" << p.id;
                tempFile << "\n" << p.name;
                tempFile << "\n" << p.price;
                tempFile << "\n" << p.stock_item;
                tempFile << "\n" << p.company_name;
            }
            else {
                tempFile << "\n" << p.id;
                tempFile << "\n" << newData.name;
                tempFile << "\n" << newData.price;
                tempFile << "\n" << newData.stock_item;
                tempFile << "\n" << newData.company_name;
            }
        }
        read.close();
        tempFile.close();
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        cout << "\n\tData updated successfuly";
    }
    else {
        cout << "\n\tRecord not deleted";
    }
}

void deletedata() {
    int id = searchData();
    cout << "\n\tYou want to delete record (y/n) : ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        Product p;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("inventory.txt");
        while (!read.eof()) {
            read >> p.id;
            read.ignore();
            getline(read, p.name);
            read >> p.price;
            read >> p.stock_item;
            read >> p.company_name;
            if (p.id != id) {
                tempFile << "\n" << p.id;
                tempFile << "\n" << p.name;
                tempFile << "\n" << p.price;
                tempFile << "\n" << p.stock_item;
                tempFile << "\n" << p.company_name;
            }
        }
        read.close();
        tempFile.close();
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        cout << "\n\tData deleted successfuly";
    }
    else {
        cout << "\n\tRecord not deleted";
    }
}

int main()
{
    ifstream read;
    int type_of_user;
    int shopkeeper_selection;
    read.open("inventory.txt");
    if (!read.fail()) {
        read >> ID;
    }
    else {
        ID = 0;
    }
    read.close();

    while (true) {
	cout<<"\n#### Welocome To Rishikesh Super Market####\n";
        cout<<"\nPlease Select the type of user.\n1. Press 1 if you are a shopkeeper\n2. Press 2 if you are a customer\n";
	cin>>type_of_user;
	switch(type_of_user){
	    case 1:
	        cout<<"User is a Shopkeeper. Displaying menu for a shopkeeper\n";
		cout<<"############shopkeeper's Menu############\n";
	    cout<<"1. Press 1 to Add Product\n2. Press 2 to Remove Product \n3. Press 3 to List all Products \n4. Press 4 to Search a Product by Name \n5. Press 5 to Edit a Product \n6. Press 6 to exit shopkeeper's menu\n";
	     cin>>shopkeeper_selection;
	    switch(shopkeeper_selection){
		case 1:
	            addproduct();
		    break;
	        case 2:
	            deletedata();
		    break;
	        case 3:
	            readData();
		    break;
	       case 4:
	            searchDatabyname();
		    break;
	       case 5:
	            updateData();
		    break;
	       case 6:
	            cout<<"Exiting Shopkeeper's Menu\n";
	            break;
	       default:
	            break;
	    }
		break;
	   case 2:
	       cout<<"User is a Customer. Displaying menu for a Customer\n";
	       cout<<"############Customer's Menu############\n";
	    cout<<"1. Press 1 to List Product\n2. Press 2 to Search a Product By Id \n3. Press 3 to Buy a Product \n4. Press 4 to exit Customer's menu\n";
	    cin>>shopkeeper_selection;
	    switch(shopkeeper_selection){
	        case 1:
	            readData();
		    break;
	        case 2:
	            searchData();
		    break;
	        case 3:
	            buy_product();
		    break;
		case 4:
		    break;
	   default:
	        cout<<"Please select a valid option\n";
	        break;
	}
	break;
	
	

   

}
}
return 0;
}




