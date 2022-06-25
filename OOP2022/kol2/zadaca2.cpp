//
// Created by kbogojoska on 25.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class Vozac
{
protected:
    char name[100];
    int age;
    int races;
    bool isVeteran;
public:
    Vozac(const char* name="", int age=0, int races=0, bool isVeteran=false)
    {
        strcpy(this->name,name);
        this->age=age;
        this->races=races;
        this->isVeteran=isVeteran;
    }
    friend ostream& operator<<(ostream &out, const Vozac &v)
    {
        out<<v.name<<endl;
        out<<v.age<<endl;
        out<<v.races<<endl;
        if(v.isVeteran)
        {
            out<<"VETERAN"<<endl;
        }
        return out;
    }
    bool operator==(Vozac &v)
    {
        return earn()==v.earn();
    }
    virtual double earn() = 0;
    virtual double danok() = 0;
};

class Avtomobilist : public Vozac
{
private:
    double autoPrice;
public:
    Avtomobilist(const char* name="", int age=0, int races=0, bool isVeteran=false, double autoPrice=0.0) : Vozac(name,age,races,isVeteran)
    {
        this->autoPrice=autoPrice;
    }
    double earn()
    {
        return autoPrice/5.0;
    }
    double danok()
    {
        if(races>10)
        {
            return earn()*0.15;
        }
        else
        {
            return earn()*0.1;
        }
    }
};

class Motociklist : public Vozac
{
private:
    int power;
public:
    Motociklist(const char* name="", int age=0, int races=0, bool isVeteran=false, int power=0) : Vozac(name,age,races,isVeteran)
    {
        this->power=power;
    }
    double earn()
    {
        return power*20.0;
    }
    double danok()
    {
        if(isVeteran)
        {
            return earn()*0.25;
        }
        else
        {
            return earn()*0.2;
        }
    }
};

int soIstaZarabotuvachka(Vozac **drivers, int n, Vozac *v)
{
    int count=0;
    for(int i=0;i<n;i++)
    {
        if(*drivers[i]==*v)
        {
            count++;
        }
    }
    return count;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}