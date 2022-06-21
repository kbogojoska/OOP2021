//
// Created by kbogojoska on 21.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class Ekipa
{
protected:
    char name[15];
    int loss;
    int win;
public:
    Ekipa(char *name="", int win=0, int loss=0)
    {
        strcpy(this->name,name);
        this->win=win;
        this->loss=loss;
    }
    ~Ekipa(){}
    void pecati()
    {
        cout<<"Ime: "<<name<<" Pobedi: "<<win<<" Porazi: "<<loss;
    }
};

class FudbalskaEkipa : public Ekipa
{
private:
    int red;
    int yellow;
    int draw;
public:
    FudbalskaEkipa(char *name="", int win=0, int loss=0, int red=0, int yellow=0, int draw=0) : Ekipa(name,win,loss)
    {
        strcpy(this->name,name);
        this->win=win;
        this->loss=loss;
        this->draw=draw;
    }
    ~FudbalskaEkipa(){}
    int pts()
    {
        return win*3+draw;
    }
    void pecati()
    {
        Ekipa::pecati();
        cout<<" Nereseni: "<<draw<<" Poeni: "<<pts()<<endl;
    }
};

int main(){
    char ime[15];
    int pob,por,ck,zk,ner;
    cin>>ime>>pob>>por>>ck>>zk>>ner;
    FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
    f1.pecati();
    return 0;
}