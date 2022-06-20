//
// Created by kbogojoska on 20.6.2022.
//

// vashiot kod ovde
#include<iostream>
#include<cstring>

using namespace std;

class Ucesnik
{
private:
    char *name;
    bool pol;
    int age;

    void copy(const Ucesnik &u)
    {
        this->name=new char[strlen(u.name)+1];
        strcpy(this->name,u.name);
        this->pol=u.pol;
        this->age=u.age;
    }
public:
    Ucesnik(char *name="", bool pol=false, int age=0)
    {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->pol=pol;
        this->age=age;
    }
    Ucesnik(const Ucesnik &u)
    {
        copy(u);
    }
    Ucesnik& operator=(const Ucesnik &u)
    {
        if(this!=&u)
        {
            delete [] name;
            copy(u);
        }
        return *this;
    }
    ~Ucesnik()
    {
        delete [] name;
    }
    bool operator>(const Ucesnik &u)
    {
        return this->age>u.age;
    }
    friend ostream& operator<<(ostream& out, const Ucesnik &u)
    {
        out<<u.name<<endl;
        if(u.pol)
        {
            out<<"mashki"<<endl;
        }
        else
        {
            out<<"zhenski"<<endl;
        }
        out<<u.age<<endl;
    }
    friend class Maraton;
};

class Maraton
{
private:
    char location[100];
    Ucesnik *participants;
    int n;

    void copy(const Maraton &m)
    {
        strcpy(this->location,m.location);
        this->n=m.n;
        this->participants=new Ucesnik[n];
        for(int i = 0; i < n; ++i)
        {
            participants[i]=m.participants[i];
        }
    }
public:
    Maraton(char *location="")
    {
        strcpy(this->location,location);
        this->n=0;
        this->participants=new Ucesnik[0];
    }
    Maraton(const Maraton &m)
    {
        copy(m);
    }
    Maraton& operator=(const Maraton &m)
    {
        if(this!=&m)
        {
            delete [] participants;
            copy(m);
        }
        return *this;
    }
    ~Maraton()
    {
        delete [] participants;
    }
    Maraton& operator+=(const Ucesnik &u)
    {
        Ucesnik *tmp=new Ucesnik[n+1];
        for(int i = 0; i < n; ++i)
        {
            tmp[i]=participants[i];
        }
        tmp[n++]=u;
        delete [] participants;
        participants=tmp;
    }
    int allAge()
    {
        int vk=0;
        for(int i = 0; i < n; ++i)
        {
            vk+=participants[i].age;
        }
        return vk;
    }
    double prosecnoVozrast()
    {
        return (double)allAge()/n;
    }
    void pecatiPomladi(Ucesnik &u)
    {
        for(int i = 0; i < n; ++i)
        {
            if(participants[i].age<u.age)
            {
                cout<<participants[i];
            }
        }
    }
};

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }

    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}