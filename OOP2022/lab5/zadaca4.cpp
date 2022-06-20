//
// Created by kbogojoska on 20.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class PlDrustvo
{
private:
    char *name;
    int tours;
    int members;

    void copy(const PlDrustvo &p)
    {
        this->name=new char[strlen(p.name)+1];
        strcpy(this->name,p.name);
        this->tours=p.tours;
        this->members=p.members;
    }
public:
    PlDrustvo(char *name="", int tours=0, int members=0)
    {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->tours=tours;
        this->members=members;
    }
    PlDrustvo(const PlDrustvo &p)
    {
        copy(p);
    }
    PlDrustvo& operator=(const PlDrustvo &p)
    {
        if(this!=&p)
        {
            delete [] name;
            copy(p);
        }
        return *this;
    }
    ~PlDrustvo()
    {
        delete [] name;
    }
    bool operator>(const PlDrustvo &p)
    {
        return this->members>p.members;
    }
    bool operator<(const PlDrustvo &p)
    {
        return this->members<p.members;
    }
    PlDrustvo operator+(const PlDrustvo &p)
    {
        PlDrustvo tmp;
        if(*this>p)
        {
            tmp=(*this);
            tmp.members+=p.members;
        }
        else if(*this<p)
        {
            tmp=p;
            tmp.members+=this->members;
        }
        return tmp;
    }
    friend ostream& operator<<(ostream& out, const PlDrustvo &p)
    {
        cout<<"Ime: "<<p.name<<" Turi: "<<p.tours<<" Clenovi: "<<p.members<<endl;
    }
};

void najmnoguClenovi(PlDrustvo *p, int n)
{
    PlDrustvo max=p[0];
    for (int i=1;i<n;i++)
    {
        if(p[i]>max)
        {
            max=p[i];
        }
    }
    cout<<"Najmnogu clenovi ima planinarskoto drustvo: ";
    cout<<max;
}

int main()
{
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0;i<3;i++)
    {
        char ime[100];
        int brTuri;
        int brClenovi;
        cin>>ime;
        cin>>brTuri;
        cin>>brClenovi;
        PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;

    }

    pl = drustva[0] + drustva[1];
    cout<<pl;

    najmnoguClenovi(drustva, 3);

    return 0;
}