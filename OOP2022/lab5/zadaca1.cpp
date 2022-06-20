//
// Created by kbogojoska on 20.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class Automobile
{
private:
    char *brand;
    int *registration;
    int maxSpeed;

    void copy(const Automobile &a)
    {
        this->brand=new char[strlen(a.brand)+1];
        strcpy(this->brand,a.brand);
        this->registration=new int[5];
        for(int i=0;i<5;i++)
        {
            this->registration[i]=a.registration[i];
        }
        this->maxSpeed=a.maxSpeed;
    }
public:
    Automobile(char *brand="", int *registration=0, int maxSpeed=0)
    {
        this->brand=new char[strlen(brand)+1];
        strcpy(this->brand,brand);
        this->registration=new int[5];
        if(registration!=0)
        {
            for(int i=0;i<5;i++)
            {
                this->registration[i]=registration[i];
            }
        }
        this->maxSpeed=maxSpeed;
    }
    Automobile(const Automobile &a)
    {
        copy(a);
    }
    Automobile& operator=(const Automobile &a)
    {
        if(this!=&a)
        {
            delete [] brand;
            delete [] registration;
            copy(a);
        }
        return *this;
    }
    ~Automobile()
    {
        delete [] brand;
        delete [] registration;
    }
    bool operator==(const Automobile &a)
    {
        for(int i=0;i<5;i++)
        {
            if(this->registration[i]!=a.registration[i])
            {
                return false;
            }
        }
        return true;
    }
    friend ostream& operator<<(ostream &out, const Automobile &a)
    {
        out<<"Marka\t"<<a.brand<<"\tRegistracija[ ";
        for(int i=0;i<5;i++)
        {
            out<<a.registration[i]<<" ";
        }
        out<<"]"<<endl;
        return out;
    }
    friend class RentACar;
};

class RentACar
{
private:
    char name[100];
    Automobile *autos;
    int n;
public:
    RentACar(char *name="")
    {
        strcpy(this->name,name);
        this->n=0;
        this->autos=new Automobile[0];
    }
    RentACar()
    {
        delete [] autos;
    }
    RentACar& operator+=(const Automobile &a)
    {
        Automobile *tmp=new Automobile[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=autos[i];
        }delete [] autos;
        tmp[n++]=a;

        autos=tmp;

        return *this;
    }
    RentACar& operator-=(const Automobile &a)
    {
        Automobile *tmp=new Automobile[n-1];
        int j=0;
        for(int i=0;i<n;i++)
        {
            if(!(autos[i]==a))
            {
                tmp[j++]=autos[i];
            }
        }
        delete [] autos;
        autos=tmp;
        n=j;

        return *this;
    }
    void pecatiNadBrzina(int max)
    {
        cout<<name<<endl;
        for(int i=0;i<n;i++)
        {
            if(autos[i].maxSpeed>max)
            {
                cout<<autos[i];
            }
        }
    }
};

int main()
{
    RentACar agencija("FINKI-Car");
    int n;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        char marka[100];
        int regisracija[5];
        int maximumBrzina;

        cin>>marka;

        for (int i=0;i<5;i++)
            cin>>regisracija[i];

        cin>>maximumBrzina;

        Automobile nov=Automobile(marka,regisracija,maximumBrzina);

        //dodavanje na avtomobil
        agencija+=nov;

    }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin>>marka;
    for (int i=0;i<5;i++)
        cin>>regisracija[i];
    cin>>maximumBrzina;

    Automobile greshka=Automobile(marka,regisracija,maximumBrzina);

    //brishenje na avtomobil
    agencija-=greshka;

    agencija.pecatiNadBrzina(150);

    return 0;
}