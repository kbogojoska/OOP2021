//
// Created by kbogojoska on 19.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

enum Tip
{
    LINUX, UNIX, WINDOWS
};

class OperativenSistem
{
private:
    char *name;
    float version;
    Tip type;
    float size;
    void copy(const OperativenSistem &os)
    {
        this->name=new char[strlen(os.name)+1];
        strcpy(this->name,os.name);
        this->version=os.version;
        this->type=os.type;
        this->size=os.size;
    }
public:
    OperativenSistem(char *name="", float version=0.0, Tip type=LINUX, float size=0.0)
    {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->version=version;
        this->type=type;
        this->size=size;
    }
    OperativenSistem(const OperativenSistem &os)
    {
        copy(os);
    }
    OperativenSistem& operator=(const OperativenSistem &os)
    {
        if(this!=&os)
        {
            delete [] name;
            copy(os);
        }
        return *this;
    }
    ~OperativenSistem()
    {
        delete [] name;
    }
    void pecati()
    {
        cout<<"Ime: "<<name<<" Verzija: "<<version<<" Tip: "<<type<<" Golemina:"<<size<<"GB"<<endl;
    }
    bool ednakviSe(const OperativenSistem &os)
    {
        return strcmp(name,os.name)==0&&version==os.version&&type==os.type&&size==os.size;
    }
    int sporediVerzija(const OperativenSistem &os)
    {
        if(version==os.version)
        {
            return 0;
        }
        else if(version<os.version)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    bool istaFamilija(const OperativenSistem &sporedba)
    {
        return strcmp(name,sporedba.name)==0&&type==sporedba.type;
    }
};

class Repozitorium
{
private:
    char name[20];
    OperativenSistem *os;
    int n;
    void copy(const Repozitorium &r)
    {
        strcpy(this->name,r.name);
        this->n=r.n;
        this->os=new OperativenSistem[n];
        for(int i=0;i<n;i++)
        {
            os[i]=r.os[i];
        }
    }
public:
    Repozitorium(const char *name)
    {
        strcpy(this->name,name);
        this->n=0;
        this->os=new OperativenSistem[0];
    }
    Repozitorium(const Repozitorium &r)
    {
        copy(r);
    }
    Repozitorium& operator=(const Repozitorium &r)
    {
        if(this!=&r)
        {
            delete [] os;
            copy(r);
        }
        return *this;
    }
    ~Repozitorium()
    {
        delete [] os;
    }
    void pecatiOperativniSistemi()
    {
        cout<<"Repozitorium: "<<name<<endl;
        for(int i=0;i<n;i++)
        {
            os[i].pecati();
        }
    }
    void izbrishi(const OperativenSistem &operativenSistem)
    {
        int j=0;
        for(int i=0;i<n;i++)
        {
            if(!os[i].ednakviSe(operativenSistem))
            {
                os[j++]=os[i];
            }
        }
        n=j;
    }
    void dodadi(const OperativenSistem &nov)
    {
        for(int i=0;i<n;i++)
        {
            if(os[i].istaFamilija(nov)&&os[i].sporediVerzija(nov)==-1)
            {
                os[i]=nov;
                return;
            }
        }
        OperativenSistem *tmp=new OperativenSistem[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=os[i];
        }
        tmp[n++]=nov;
        delete [] os;
        os=tmp;
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}