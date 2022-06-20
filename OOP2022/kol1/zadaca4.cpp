//
// Created by kbogojoska on 20.6.2022.
//

#include<iostream>
#include<cstring>
using namespace std;

class Patnik{
private:
    char name[100];
    int clasa;
    bool bicycle;
public:
    Patnik(char *name="", int clasa=0, bool bicycle=false)
    {
        strcpy(this->name,name);
        this->clasa=clasa;
        this->bicycle=bicycle;
    }
    ~Patnik(){}
    friend ostream& operator<<(ostream &out, const Patnik &p)
    {
        out<<p.name<<endl;
        out<<p.clasa<<endl;
        out<<p.bicycle<<endl;
        return out;
    }
    friend class Voz;
};

class Voz{
private:
    char destination[100];
    Patnik *passenger;
    int n;
    int maxBicycles;

    void copy(const Voz &v)
    {
        strcpy(this->destination,v.destination);
        this->maxBicycles=v.maxBicycles;
        this->n=v.n;
        this->passenger=new Patnik[n];
        for (int i = 0; i < n; i++)
        {
            passenger[i]=v.passenger[i];
        }
    }
public:
    Voz(char *destination="", int maxBicycles=0)
    {
        strcpy(this->destination,destination);
        this->maxBicycles=maxBicycles;
        this->n=0;
        this->passenger=new Patnik[0];
    }
    Voz(const Voz &v)
    {
        copy(v);
    }
    Voz& operator=(const Voz &v)
    {
        if(this!=&v)
        {
            delete [] passenger;
            copy(v);
        }
        return *this;
    }
    ~Voz()
    {
        delete [] passenger;
    }
    friend ostream& operator<<(ostream &out, const Voz &v)
    {
        out<<v.destination<<endl;
        for (int i = 0; i < v.n; i++)
        {
            out<<v.passenger[i]<<endl;
        }
        return out;
    }
    int count()
    {
        int vk=0;
        for (int i = 0; i < n; i++)
        {
            if(passenger[i].bicycle)
            {
                vk++;
            }
        }
        return vk;
    }
    Voz& operator+=(const Patnik &p)
    {
        if(p.bicycle && maxBicycles || !p.bicycle)
        {
            Patnik *tmp=new Patnik[n+1];
            for (int i = 0; i < n; i++)
            {
                tmp[i]=passenger[i];
            }
            tmp[n++]=p;
            delete [] passenger;
            passenger=tmp;
        }
        return *this;
    }
    void patniciNemaMesto()
    {
        int first=0, second=0;
        for (int i = 0; i < n; i++)
        {
            if(passenger[i].bicycle)
            {
                if(passenger[i].clasa==1)
                {
                    first++;
                }
                else if(passenger[i].clasa==2)
                {
                    second++;
                }
            }
        }
        if(first<=maxBicycles)
        {
            cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: 0"<<endl;
            if(first+second<=maxBicycles)
            {
                cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: 0"<<endl;
            }
            else if(first+second>maxBicycles)
            {
                cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<first+second-maxBicycles<<endl;
            }
        }
        else if(first>maxBicycles)
        {
            cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: "<<first-maxBicycles<<endl;
            cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<second<<endl;
        }
    }
};


int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
