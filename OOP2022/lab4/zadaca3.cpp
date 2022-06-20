//
// Created by kbogojoska on 19.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

// вашиот код

class Avtomobil
{
private:
    char color[20];
    char brand[20];
    char model[20];
public:
    Avtomobil(char *color="", char *brand="", char *model="")
    {
        strcpy(this->color,color);
        strcpy(this->brand,brand);
        strcpy(this->model,model);
    }
    Avtomobil& operator=(const Avtomobil &a)
    {
        if(this!=&a)
        {
            strcpy(this->color,a.color);
            strcpy(this->brand,a.brand);
            strcpy(this->model,a.model);
        }
        return *this;
    }
    ~Avtomobil(){}
    friend class ParkingPlac;
};

class ParkingPlac
{
private:
    char address[20];
    char *id;
    int price;
    int earnings;
    Avtomobil *autos;
    int n;
    void copy(const ParkingPlac &pp)
    {
        strcpy(this->address,pp.address);
        this->id=new char[strlen(pp.id)+1];
        strcpy(this->id,pp.id);
        this->price=pp.price;
        this->earnings=pp.earnings;
        this->n=pp.n;
        this->autos=new Avtomobil[n];
        for(int i=0;i<n;i++)
        {
            this->autos[i]=pp.autos[i];
        }
    }
public:
    ParkingPlac(char *address="", char *id="", int price=0)
    {
        strcpy(this->address,address);
        this->id=new char[strlen(id)+1];
        strcpy(this->id,id);
        this->price=price;
        this->earnings=0;
        this->n=0;
        this->autos=new Avtomobil[0];
    }
    ParkingPlac(const ParkingPlac &pp)
    {
        copy(pp);
    }
    ParkingPlac& operator=(const ParkingPlac &pp)
    {
        if(this!=&pp)
        {
            delete [] id;
            delete [] autos;
            copy(pp);
        }
        return *this;
    }
    ~ParkingPlac()
    {
        delete [] id;
        delete [] autos;
    }
    char* getId()
    {
        return id;
    }
    void platiCasovi(int casovi)
    {
        this->earnings+=(casovi*price);
    }
    void pecati()
    {
        if(earnings!=0)
        {
            cout<<id<<" "<<address<<" - "<<earnings<<" denari"<<endl;
        }
        else
        {
            cout<<id<<" "<<address<<endl;
        }
    }
    bool daliIstaAdresa(ParkingPlac p)
    {
        return strcmp(this->address,p.address)==0;
    }
    void parkirajVozilo(Avtomobil novoVozilo)
    {
        Avtomobil *tmp=new Avtomobil[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=autos[i];
        }
        tmp[n++]=novoVozilo;
        delete [] autos;
        autos=tmp;
    }
    void pecatiParkiraniVozila()
    {
        cout<<"Vo parkingot se parkirani slednite vozila:"<<endl;
        for(int i=0;i<n;i++)
        {
            cout<<i+1<<"."<<autos[i].color<<" "<<autos[i].brand<<" "<<autos[i].model<<endl;
        }
    }
};

int main(){

    ParkingPlac p[100];
    int n,m;
    char adresa[50],id[50];
    int brojcasovi,cenacas;
    cin>>n;
    if(n > 0){


        for (int i=0;i<n;i++){
            cin.get();
            cin.getline(adresa,50);
            cin>>id>>cenacas;

            ParkingPlac edna(adresa,id,cenacas);

            p[i]=edna;
        }

        //plakjanje
        cin>>m;
        for (int i=0;i<m;i++){

            cin>>id>>brojcasovi;

            int findId=false;
            for (int j=0;j<m;j++){
                if (strcmp(p[j].getId(),id)==0){
                    p[j].platiCasovi(brojcasovi);
                    findId=true;
                }
            }
            if (!findId)
                cout<<"Ne e platen parking. Greshen ID."<<endl;
        }

        cout<<"========="<<endl;
        ParkingPlac pCentar("Cvetan Dimov","C10",80);
        for (int i=0;i<n;i++)
            if (p[i].daliIstaAdresa(pCentar))
                p[i].pecati();
    }
    else {

        ParkingPlac najdobarPlac("Mars", "1337", 1);
        int brVozila;
        cin >> brVozila;
        for(int i = 0; i < brVozila; ++i){

            char boja[20];
            char brend[20];
            char model[20];

            cin >> boja >> brend >> model;
            Avtomobil novAvtomobil(boja, brend, model);
            najdobarPlac.parkirajVozilo(novAvtomobil);
        }
        if(brVozila != 0)
            najdobarPlac.pecatiParkiraniVozila();

    }
}