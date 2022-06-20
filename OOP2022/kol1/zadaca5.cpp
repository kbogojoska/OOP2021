//
// Created by kbogojoska on 19.6.2022.
//

#include <iostream>
#include <cstring>
using namespace std;

class Gitara
{
private:
    char serial[25];
    float price;
    int year;
    char type[40];
public:
    Gitara(char *type="", char *serial="", int year=0, float price=0)
    {
        strcpy(this->type,type);
        strcpy(this->serial,serial);
        this->year=year;
        this->price=price;
    }
    ~Gitara(){}
    bool daliIsti(Gitara g)
    {
        return strcmp(this->serial,g.serial)==0;
    }
    void pecati()
    {
        cout<<serial<<" "<<type<<" "<<price<<endl;
    }
    char* getTip()
    {
        return type;
    }
    char* getSeriski()
    {
        return serial;
    }
    int getGodina()
    {
        return year;
    }
    float getNabavna()
    {
        return price;
    }
};

class Magacin
{
private:
    char name[30];
    char location[60];
    Gitara *guitars;
    int n;
    int year;
    void copy(const Magacin &m)
    {
        strcpy(this->name,m.name);
        strcpy(this->location,m.location);
        this->n=m.n;
        this->year=m.year;
        this->guitars=new Gitara[n];
        for(int i=0;i<n;i++)
        {
            guitars[i]=m.guitars[i];
        }
    }
public:
    Magacin(char *name="", char *location="", int year=0)
    {
        strcpy(this->name,name);
        strcpy(this->location,location);
        this->n=0;
        this->year=year;
        this->guitars=new Gitara[0];
    }
    Magacin(const Magacin &m)
    {
        copy(m);
    }
    Magacin& operator=(const Magacin &m)
    {
        if(this!=&m)
        {
            delete [] guitars;
            copy(m);
        }
        return *this;
    }
    ~Magacin()
    {
        delete [] guitars;
    }
    double vrednost()
    {
        double vk=0;
        for(int i=0;i<n;i++)
        {
            vk+=guitars[i].getNabavna();
        }
    }
    void dodadi(Gitara d)
    {
        Gitara *tmp=new Gitara[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=guitars[i];
        }
        tmp[n++]=d;
        delete [] guitars;
        guitars=tmp;
    }
    int count(Gitara p)
    {
        int vk=0;
        for(int i=0;i<n;i++)
        {
            if(guitars[i].daliIsti(p))
            {
                vk++;
            }
        }
        return vk;
    }
    void prodadi(Gitara p)
    {
        int amount=0;
        amount=count(p);
        Gitara *tmp=new Gitara[n-amount];
        int j=0;
        for(int i=0;i<n;i++)
        {
            if(!guitars[i].daliIsti(p))
            {
                tmp[j++]=guitars[i];
            }
        }
        delete [] guitars;
        guitars=tmp;
        n=j;
    }
    void pecati(bool daliNovi)
    {
        cout<<name<<" "<<location<<endl;
        if(daliNovi)
        {
            for(int i=0;i<n;i++)
            {
                if(guitars[i].getGodina()>year)
                {
                    guitars[i].pecati();
                }
            }
        }
        else
        {
            for(int i=0;i<n;i++)
            {
                guitars[i].pecati();
            }
        }
    }
};

int main() {
// se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50],tip[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getTip()<<endl;
        cout<<g.getSeriski()<<endl;
        cout<<g.getGodina()<<endl;
        cout<<g.getNabavna()<<endl;
    }
    else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6)
    {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;
}
