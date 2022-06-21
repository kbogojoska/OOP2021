//
// Created by kbogojoska on 21.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class Nedviznina
{
protected:
    char *address;
    int area;
    int price;

    void copy(const Nedviznina &n)
    {
        this->address=new char[strlen(n.address)+1];
        strcpy(this->address,n.address);
        this->area=n.area;
        this->price=n.price;
    }
public:
    Nedviznina(char *address="", int area=0, int price=0)
    {
        this->address=new char[strlen(address)+1];
        strcpy(this->address,address);
        this->area=area;
        this->price=price;
    }
    Nedviznina(const Nedviznina &n)
    {
        copy(n);
    }
    Nedviznina& operator=(const Nedviznina &n)
    {
        if(this!=&n)
        {
            delete [] address;
            copy(n);
        }
        return *this;
    }
    ~Nedviznina()
    {
        delete [] address;
    }
    void pecati()
    {
        cout<<address<<", Kvadratura: "<<area<<", Cena po Kvadrat: "<<price<<endl;
    }
    char *getAdresa()
    {
        return address;
    }
    int cena()
    {
        return area*price;
    }
    double danokNaImot()
    {
        return cena()*0.05;
    }
    friend istream& operator>>(istream& in, Nedviznina &n)
    {
        in>>n.address;
        in>>n.area;
        in>>n.price;
        return in;
    }
};

class Vila : public Nedviznina
{
private:
    int luxury;
public:
    Vila(char *address="", int area=0, int price=0, int luxury=0) : Nedviznina(address,area,price)
    {
        this->luxury=luxury;
    }
    friend istream& operator>>(istream& in, Vila &v)
    {
        in>>v.address;
        in>>v.area;
        in>>v.price;
        in>>v.luxury;
        return in;
    }
    ~Vila(){}
    double danokNaImot()
    {
        return Nedviznina::danokNaImot()+cena()*(luxury/100.0);
    }
    void pecati()
    {
        cout<<address<<", Kvadratura: "<<area<<", Cena po Kvadrat: "<<price<<", Danok na luksuz: "<<luxury<<endl;
    }
};
int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}