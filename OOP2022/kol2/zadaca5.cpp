//
// Created by kbogojoska on 25.6.2022.
//

#include<iostream>
#include<cstring>
int MAX=50;

using namespace std;

enum typeC
{
    standard, loyal, vip
};

class UserExistsException
{
public:
    void message()
    {
        cout<<"The user already exists in the list!"<<endl;
    }
};

class Customer
{
private:
    char name[50];
    char email[50];
    typeC type;
    static int startDiscount;
    static const int additionalDiscount =20;
    int products;
public:
    Customer(const char *name="", const char *email="", typeC type=standard, int products=0)
    {
        strcpy(this->name,name);
        strcpy(this->email,email);
        this->type=type;
        this->products=products;
    }
    friend ostream& operator<<(ostream& out, Customer &a)
    {
        out<<a.name<<endl;
        out<<a.email<<endl;
        out<<a.products<<endl;
        switch(a.type)
        {
            case 0:
                out<<"standard 0"<<endl;
                break;
            case 1:
                out<<"loyal "<<Customer::startDiscount<<endl;
                break;
            case 2:
                out<<"vip "<<Customer::startDiscount+Customer::additionalDiscount<<endl;
                break;
        }
        return out;
    }
    char* getEmail()
    {
        return email;
    }
    typeC getType()
    {
        return type;
    }
    int getProducts()
    {
        return products;
    }
    void setDiscount1(int n)
    {
        startDiscount=n;
    }
    void setType(typeC t)
    {
        type=t;
    }
};

int Customer::startDiscount=10;

class FINKI_bookstore
{
private:
    Customer *customers;
    int n;
public:
    FINKI_bookstore()
    {
        n=0;
        customers=new Customer[0];
    }
    FINKI_bookstore(const FINKI_bookstore &fb)
    {
        n=fb.n;
        customers=new Customer[n];
        for(int i=0;i<n;i++)
        {
            customers[i]=fb.customers[i];
        }
    }
    FINKI_bookstore& operator=(const FINKI_bookstore &fb)
    {
        if(this!=&fb)
        {
            delete [] customers;
            n=fb.n;
            customers=new Customer[n];
            for(int i=0;i<n;i++)
            {
                customers[i]=fb.customers[i];
            }
        }
        return *this;
    }
    ~FINKI_bookstore()
    {
        delete [] customers;
    }
    bool notFound(Customer &c)
    {
        for(int i=0;i<n;i++)
        {
            if(strcmp(customers[i].getEmail(),c.getEmail())==0)
            {
                return false;
            }
        }
        return true;
    }
    FINKI_bookstore& operator+=(Customer &c)
    {
        if(!notFound(c))
        {
            throw UserExistsException();
        }
        else
        {
            Customer *tmp=new Customer[n+1];
            for(int i=0;i<n;i++)
            {
                tmp[i]=customers[i];
            }
            tmp[n++]=c;
            delete [] customers;
            customers=tmp;
            return *this;
        }
    }
    void setCustomers(Customer *c, int a)
    {
        delete [] customers;
        customers=new Customer[a];
        for(int i=0;i<a;i++)
        {
            customers[i]=c[i];
        }
        n=a;
    }
    friend ostream& operator<<(ostream& out, const FINKI_bookstore &a)
    {
        for(int i=0;i<a.n;i++)
        {
            out<<a.customers[i];
        }
        return out;
    }
    void update()
    {
        for(int i=0;i<n;i++)
        {
            if(customers[i].getType()==0&&customers[i].getProducts()>5)
            {
                customers[i].setType((typeC)1);
            }
            else if(customers[i].getType()==1&&customers[i].getProducts()>10)
            {
                customers[i].setType((typeC)2);
            }
        }
    }
};



int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try
        {
            fc+=c;
        }
        catch(UserExistsException e)
        {
            e.message();
        }
        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer cu(name, email, (typeC) tC, numProducts);
        try
        {
            fc+=cu;
        }
        catch(UserExistsException e)
        {
            e.message();
        }
        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
