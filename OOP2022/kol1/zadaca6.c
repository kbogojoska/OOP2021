//
// Created by kbogojoska on 19.6.2022.
//

#include<iostream>
#include <cstring>
using namespace std;

struct Voz
{
    char relacija[50];
    int km;
    int brPatnici;
};

struct ZeleznickaStanica
{
    char grad[20];
    Voz vozovi[30];
    int brVozovi;
};

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
{
    char rel[50];
    int kmF;
    for (int i=0;i<n;i++)
    {
        if(!strcmp(zs[i].grad,grad))
        {
            strcpy(rel,zs[i].vozovi[0].relacija);
            kmF=zs[i].vozovi[0].km;
            for(int j=1;j<zs[i].brVozovi;j++)
            {
                if(kmF>=zs[i].vozovi[j].km)
                {
                    kmF=zs[i].vozovi[j].km;
                    strcpy(rel,zs[i].vozovi[j].relacija);
                }
            }

        }
    }
    cout<<"Najkratka relacija: "<<rel<<" ("<<kmF<<" km)"<<endl;
}

int main(){

    int n;
    cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        cin>>zStanica[i].grad;
        cin>>zStanica[i].brVozovi;
        for(int j=0; j<zStanica[i].brVozovi;j++)
        {
            cin>>zStanica[i].vozovi[j].relacija;
            cin>>zStanica[i].vozovi[j].km;
            cin>>zStanica[i].vozovi[j].brPatnici;
        }
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
    }

    char grad[25];
    cin>>grad;

    najkratkaRelacija(zStanica,n,grad);
    return 0;
}