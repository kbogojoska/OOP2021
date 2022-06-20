//
// Created by kbogojoska on 20.6.2022.
//

#include <iostream>
#include <cstring>
using namespace std;

class IceCream
{
private:
    char *name;
    char ingredients[100];
    double price;
    int discount;

    void copy(const IceCream &ic)
    {
        this->name=new char[strlen(ic.name)+1];
        strcpy(this->name,ic.name);
        strcpy(this->ingredients,ic.ingredients);
        this->price=ic.price;
        this->discount=ic.discount;
    }
public:
    IceCream(char *name="", char *ingredients="", int price=0)
    {
        this->name=new char[strlen(name)+4];
        strcpy(this->name,name);
        strcpy(this->ingredients,ingredients);
        this->price=price;
        discount=0;
    }
    IceCream(const IceCream &ic)
    {
        copy(ic);
    }
    IceCream& operator=(const IceCream &ic)
    {
        if(this!=&ic)
        {
            delete [] name;
            copy(ic);
        }
        return *this;
    }
    ~IceCream()
    {
        delete [] name;
    }
    friend ostream& operator<<(ostream& out, const IceCream &ic)
    {
        out<<ic.name<<": "<<ic.ingredients<<" "<<ic.price<<" ";
        if(ic.discount>0)
        {
            out<<"("<<ic.price-ic.price*(ic.discount/100.0)<<")";
        }
        return out;
    }
    IceCream& operator++()
    {
        discount+=5;
        return *this;
    }
    IceCream operator+(const IceCream &ic)
    {
        IceCream tmp(*this);
        delete [] tmp.name;
        tmp.name=new char[strlen(this->name)+strlen(ic.name)+1];
        strcpy(tmp.name,this->name);
        strcat(tmp.name," + ");
        strcat(tmp.name, ic.name);
        tmp.price+=10;
        return tmp;
    }
    void setDiscount(int discount)
    {
        if(discount>=0&&discount<=100)
        {
            this->discount=discount;
        }
    }
    void setName(char* name)
    {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
    }
};

class IceCreamShop
{
private:
    char name[50];
    IceCream *icecreams;
    int n;

    void copy(const IceCreamShop &ics)
    {
        strcpy(this->name,ics.name);
        this->n=ics.n;
        this->icecreams=new IceCream[n];
        for(int i = 0; i < n; ++i) {
            this->icecreams[i]=ics.icecreams[i];
        }
    }
public:
    IceCreamShop(char *name="")
    {
        strcpy(this->name,name);
        this->n=0;
        this->icecreams=new IceCream[0];

    }
    IceCreamShop(const IceCreamShop &ics)
    {
        copy(ics);
    }
    IceCreamShop& operator=(const IceCreamShop &ics)
    {
        if(this!=&ics)
        {
            delete [] icecreams;
            copy(ics);
        }
        return *this;
    }
    ~IceCreamShop()
    {
        delete [] icecreams;
    }
    IceCreamShop& operator +=(const IceCream &ic)
    {
        IceCream *tmp=new IceCream[n+1];
        for(int i = 0; i < n; ++i) {
            tmp[i]=icecreams[i];
        }
        tmp[n++]=ic;
        delete [] icecreams;
        icecreams=tmp;
    }
    friend ostream& operator<<(ostream& out, const IceCreamShop &ics)
    {
        out<<ics.name<<endl;
        for(int i = 0; i < ics.n; ++i) {
            out<<ics.icecreams[i]<<endl;
        }
        return out;
    }
};

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    }
    else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        //cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    }
    else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    }
    else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}