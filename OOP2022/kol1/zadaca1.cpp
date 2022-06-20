//
// Created by kbogojoska on 19.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

enum tip
{
    pop, rap, rok
};

class Pesna
{
private:
    char *name;
    int minutes;
    tip type;
    void copy(const Pesna &p)
    {
        this->name=new char[strlen(p.name)+1];
        strcpy(this->name,p.name);
        this->minutes=p.minutes;
        this->type=p.type;
    }
public:
    Pesna(char *name="", int minutes=0, tip type=pop)
    {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->minutes=minutes;
        this->type=type;
    }
    Pesna(const Pesna &p)
    {
        copy(p);
    }
    Pesna& operator=(const Pesna &p)
    {
        if(this!=&p)
        {
            delete [] name;
            copy(p);
        }
        return *this;
    }
    ~Pesna()
    {
        delete [] name;
    }
    void pecati()
    {
        cout<<"\""<<name<<"\"-"<<minutes<<"min"<<endl;
    }
    friend class CD;
};

class CD
{
private:
    Pesna songs[10];
    int n;
    int minutes;
public:
    CD(int minutes=0)
    {
        this->n=0;
        this->minutes=minutes;
        songs[0];
    }
    ~CD(){}
    void dodadiPesna (Pesna p)
    {
        if(n<10)
        {
            int vk=0;
            for(int i=0;i<n;i++)
            {
                vk+=songs[i].minutes;
            }
            if(vk+p.minutes<minutes)
            {
                songs[n++]=p;
            }
        }
    }
    Pesna& getPesna(int m)
    {
        for(int i=0;i<n;i++)
        {
            if(m==i)
            {
                return songs[i];
            }
        }
    }
    int getBroj()
    {
        return n;
    }
    void pecatiPesniPoTip(tip t)
    {
        for(int i=0;i<n;i++)
        {
            if(songs[i].type==t)
            {
                songs[i].pecati();
            }
        }
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    }
    else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}