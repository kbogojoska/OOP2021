//
// Created by kbogojoska on 24.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class RegistrationException
{
public:
    void message()
    {
        cout<<"Pogresno vnesena registracija"<<endl;
    }
};

class ImaMasa
{
public:
    virtual double vratiMasa() = 0;
    virtual void pecati() = 0;
};

class PaketPijalok : public ImaMasa
{
protected:
    double volumenEden;
    int kolicina;
    static double GUSTINA;
    static double MASA_AMBALAZHA;
public:
    PaketPijalok(double volumenEden=0.0, int kolicina=0)
    {
        this->volumenEden=volumenEden;
        this->kolicina=kolicina;
    }
    double vratiMasa()
    {
        return kolicina*(volumenEden*GUSTINA+MASA_AMBALAZHA);
    }
    void pecati()
    {
        cout<<"kolicina "<<kolicina;
    }
    int getKolicina()
    {
        return kolicina;
    }
};

double PaketPijalok::GUSTINA=0.8;
double PaketPijalok::MASA_AMBALAZHA=0.2;


class PaketSok : public PaketPijalok
{
private:
    bool daliGaziran;
public:
    PaketSok(double volumenEden=0.0, int kolicina=0, bool daliGaziran=false) : PaketPijalok(volumenEden,kolicina)
    {
        this->daliGaziran=daliGaziran;
    }
    double vratiMasa()
    {
        if(daliGaziran)
        {
            PaketPijalok::vratiMasa();
        }
        else
        {
            return kolicina*(volumenEden*GUSTINA+MASA_AMBALAZHA+0.1);
        }
    }
    void pecati()
    {
        cout<<"Paket sok"<<endl;
        PaketPijalok::pecati();
        cout<<", so po "<<volumenEden*GUSTINA<<" l(dm3)"<<endl;
    }
};

class PaketVino : public PaketPijalok
{
private:
    double procentAlkohol;
public:
    PaketVino(double volumenEden=0.0, int kolicina=0, double procentAlkohol=0.0) : PaketPijalok(volumenEden,kolicina)
    {
        this->procentAlkohol=procentAlkohol;
    }
    double vratiMasa()
    {
        return kolicina*(volumenEden*GUSTINA+MASA_AMBALAZHA)*(0.9+procentAlkohol);
    }
    void pecati()
    {
        cout<<"Paket vino"<<endl;
        PaketPijalok::pecati();
        cout<<", "<<getProcentAlkohol()<<"% alkohol od po "<<volumenEden*GUSTINA<<" l(dm3)"<<endl;
    }
    double getProcentAlkohol()
    {
        return procentAlkohol*100;
    }
};

class Kamion
{
private:
    char registration[9];
    char name[20];
    ImaMasa **products;
    int n;
public:
    Kamion(char *registration="", char *name="")
    {
        strcpy(this->registration,registration);
        if(strlen(registration)!=8)
        {
            throw RegistrationException();
        }
        else
        {
            int flag=1;
            if(!(registration[0]>'A'&&registration[0]<'Z'||registration[0]>'a'&&registration[0]<'z'))
            {
                throw RegistrationException();
            }
            if(!(registration[1]>'A'&&registration[1]<'Z'||registration[1]>'a'&&registration[1]<'z'))
            {
                throw RegistrationException();
            }
            if(!(registration[6]>'A'&&registration[6]<'Z'||registration[6]>'a'&&registration[6]<'z'))
            {
                throw RegistrationException();
            }
            if(!(registration[7]>'A'&&registration[7]<'Z'||registration[7]>'a'&&registration[7]<'z'))
            {
                throw RegistrationException();
            }
        }
        strcpy(this->name,name);
        products=new ImaMasa*[0];
        n=0;
    }
    Kamion(const Kamion &k)
    {
        strcpy(this->registration,k.registration);
        strcpy(this->name,k.name);
        products=new ImaMasa*[k.n];
        n=k.n;
        for(int i=0;i<n;i++)
        {
            products[i]=k.products[i];
        }
    }
    Kamion& operator=(const Kamion &k)
    {
        if(this!=&k)
        {
            delete [] products;
            strcpy(this->registration,k.registration);
            strcpy(this->name,k.name);
            products=new ImaMasa*[k.n];
            n=k.n;
            for(int i=0;i<n;i++)
            {
                products[i]=k.products[i];
            }
            return *this;
        }
    }
    ~Kamion()
    {
        delete [] products;
    }
    void registriraj(char* n)
    {
        strcpy(registration,n);
    }
    void dodadiElement(ImaMasa *e)
    {
        ImaMasa **tmp=new ImaMasa*[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=products[i];
        }
        tmp[n++]=e;
        delete [] products;
        products=tmp;
    }
    double vratiVkupnaMasa()
    {
        double sum=0.0;
        for(int i=0;i<n;i++)
        {
            sum+=products[i]->vratiMasa();
        }
        return sum;
    }
    void pecati()
    {
        cout<<"Kamion so registracija "<<registration<<" i vozac "<<name<<" prenesuva:"<<endl;
        for(int i=0;i<n;i++)
        {
            products[i]->pecati();
        }
    }
    Kamion pretovar(char* r, char* na)
    {
        Kamion k(r,na);
        if(strlen(r)!=8)
        {
            throw RegistrationException();
        }
        else
        {
            int flag=1;
            if(!(r[0]>'A'&&r[0]<'Z'||r[0]>'a'&&r[0]<'z'))
            {
                throw RegistrationException();
            }
            if(!(r[1]>'A'&&r[1]<'Z'||r[1]>'a'&&r[1]<'z'))
            {
                throw RegistrationException();
            }
            if(!(r[6]>'A'&&r[6]<'Z'||r[6]>'a'&&r[6]<'z'))
            {
                throw RegistrationException();
            }
            if(!(r[7]>'A'&&r[7]<'Z'||r[7]>'a'&&r[7]<'z'))
            {
                throw RegistrationException();
            }
        }
        int idx=0;
        for(int i=0;i<n;i++)
        {
            if(products[i]->vratiMasa()>products[idx]->vratiMasa())
            {
                idx=i;
            }
        }
        for(int i=0;i<n;i++)
        {
            if(i!=idx)
            {
                k.dodadiElement(products[i]);
            }
        }
        return k;
    }
};

int main()
{
    char ime[20], reg[9];
    double vol;
    int kol;
    bool g;
    double proc;

    try
    {
        cin>>reg;
        cin>>ime;
        Kamion A(reg, ime);
        ImaMasa **d = new ImaMasa*[5];
        cin>>vol>>kol;
        cin>>g;
        d[0] = new PaketSok(vol, kol, g);
        cin>>vol>>kol;
        cin>>proc;
        d[1] = new PaketVino(vol, kol, proc);
        cin>>vol>>kol;
        cin>>proc;
        d[2] = new PaketVino(vol, kol, proc);
        cin>>vol>>kol;
        cin>>g;
        d[3] = new PaketSok(vol, kol, g);
        cin>>vol>>kol;
        cin>>proc;
        d[4] = new PaketVino(vol, kol, proc);
        A.dodadiElement(d[0]);
        A.dodadiElement(d[1]);
        A.dodadiElement(d[2]);
        A.dodadiElement(d[3]);
        A.dodadiElement(d[4]);
        A.pecati();
        cout<<"Vkupna masa: "<<A.vratiVkupnaMasa()<<endl;

        cin>>reg;
        cin>>ime;
        Kamion B = A.pretovar(reg, ime);
        B.pecati();
        cout<<"Vkupna masa: "<<B.vratiVkupnaMasa()<<endl;
    }
    catch(RegistrationException r)
    {
        r.message();
    }

}
