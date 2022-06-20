//
// Created by kbogojoska on 20.6.2022.
//

#include<iostream>
#include<cstring>
using namespace std;

// vasiot kod za klasite ovde

class StockRecord
{
private:
    char id[12];
    char name[50];
    double bought;
    double current;
    int n;
public:
    StockRecord(char *id="", char *name="", double bought=0, int n=0, double current=0)
    {
        strcpy(this->id,id);
        strcpy(this->name,name);
        this->bought=bought;
        this->n=n;
        this->current=current;
    }
    double value()
    {
        return current*n;
    }
    double profit () const
    {
        return n*(current-bought);
    }
    void setNewPrice(double c)
    {
        this->current=c;
    }
    friend ostream& operator<<(ostream& out, const StockRecord &sr)
    {
        out<<sr.name<<" "<<sr.n<<" "<<sr.bought<<" "<<sr.current<<" "<<sr.profit()<<endl;
        return out;
    }
    friend class Client;
};

class Client
{
private:
    char nameSur[60];
    int id;
    StockRecord *rcds;
    int n;

    void copy(const Client &c)
    {
        strcpy(this->nameSur,c.nameSur);
        this->id=c.id;
        this->n=c.n;
        this->rcds=new StockRecord[n];
        for(int i = 0; i < n; ++i)
        {
            this->rcds[i]=c.rcds[i];
        }
    }
public:
    Client(char *nameSur="", int id=0)
    {
        strcpy(this->nameSur,nameSur);
        this->id=id;
        this->rcds=new StockRecord[0];
        this->n=0;
    }
    Client(const Client &c)
    {
        copy(c);
    }
    Client& operator=(const Client &c)
    {
        if(this!=&c)
        {
            delete [] rcds;
            copy(c);
        }
        return *this;
    }
    ~Client()
    {
        delete [] rcds;
    }
    double totalValue() const
    {
        double vk=0;
        for(int i = 0; i < n; ++i)
        {
            vk+=rcds[i].value();
        }
        return vk;
    }
    Client& operator+=(const StockRecord &s)
    {
        StockRecord *tmp=new StockRecord[n+1];
        for(int i = 0; i < n; ++i)
        {
            tmp[i]=rcds[i];
        }
        tmp[n++]=s;
        delete [] rcds;
        rcds=tmp;
    }
    friend ostream& operator<<(ostream& out, const Client &c)
    {
        out<<c.id<<" "<<c.totalValue()<<endl;
        for(int i = 0; i < c.n; ++i)
        {
            cout<<c.rcds[i];
        }
        return out;
    }
};

// ne menuvaj vo main-ot

int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}