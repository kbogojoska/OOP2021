//
// Created by kbogojoska on 19.6.2022.
//

#include<iostream>
#include<cstring>
using namespace std;

class Rabotnik
{
private:
    char name[30];
    char surname[30];
    int salary;
public:
    Rabotnik(char *name="", char *surname="", int salary=0)
    {
        strcpy(this->name,name);
        strcpy(this->surname,surname);
        this->salary=salary;
    }
    int getPlata()
    {
        return salary;
    }
    void pecati()
    {
        cout<<name<<" "<<surname<<" "<<salary<<endl;
    }
    ~Rabotnik(){}
};

class Fabrika
{
private:
    Rabotnik rabotnik[100];
    int numberOfEmployees;
public:
    Fabrika()
    {
        numberOfEmployees=100;
    }
    Fabrika(Rabotnik *rabotnik, int numberOfEmployees)
    {
        this->numberOfEmployees=numberOfEmployees;
        for(int i=0;i<numberOfEmployees;i++)
        {
            this->rabotnik[i]=rabotnik[i];
        }
    }
    void pecatiVraboteni()
    {
        for(int i=0;i<numberOfEmployees;i++)
        {
            rabotnik[i].pecati();
        }
    }
    void pecatiSoPlata(int plata)
    {
        for(int i=0;i<numberOfEmployees;i++)
        {
            if(rabotnik[i].getPlata()>=plata)
            {
                rabotnik[i].pecati();
            }
        }
    }
    ~Fabrika(){}
};

int main()
{
    int n;
    cin>>n;

    Rabotnik r[100];
    for(int i=0;i<n;i++)
    {
        char im[50];
        char p[50];
        int pl;
        cin>>im;
        cin>>p;
        cin>>pl;
        r[i]=Rabotnik(im,p,pl);
    }
    int limit;
    cin>>limit;
    Fabrika f(r, n);
    cout<<"Site vraboteni: "<<endl;
    f.pecatiVraboteni();
    cout<<"Vraboteni so plata povisoka od "<<limit<<" :"<<endl;
    f.pecatiSoPlata(limit);
}