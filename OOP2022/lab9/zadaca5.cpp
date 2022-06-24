//
// Created by kbogojoska on 24.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class InvalidDateException
{
private:
    int d,m,y;
public:
    InvalidDateException(int d, int m, int y)
    {
        this->d=d;
        this->m=m;
        this->y=y;
    }
    void message()
    {
        cout<<"Invalid Date "<<d<<"/"<<m<<"/"<<y<<endl;
    }
};

class NotSupportedCurrencyException
{
private:
    char c[4];
public:
    NotSupportedCurrencyException(char *c)
    {
        strcpy(this->c,c);
    }
    void message()
    {
        cout<<c<<" is not a supported currency"<<endl;
    }
};

class Transakcija
{
protected:
    int day;
    int month;
    int year;
    double iznos;
    static double EUR;
    static double USD;
public:
    Transakcija(int day=1, int month=1, int year=2000, double iznos=0)
    {
        this->day=day;
        this->month=month;
        this->year=year;
        if(day<1||day>31||month<1||month>12)
        {
            throw InvalidDateException(day,month,year);
        }
        this->iznos=iznos;
    }
    virtual double voDenari() = 0;
    virtual double voEvra() = 0;
    virtual double voDolari() = 0;
    virtual void pecati() = 0;
    static void setEUR(double n)
    {
        EUR=n;
    }
    static void setUSD(double n)
    {
        USD=n;
    }
    static double getEUR()
    {
        return EUR;
    }
    static double getUSD()
    {
        return USD;
    }
};

double Transakcija::EUR=61;
double Transakcija::USD=50;

class DenarskaTransakcija : public Transakcija
{
public:
    DenarskaTransakcija(int day=1, int month=1, int year=2000, double iznos=0) : Transakcija(day,month,year,iznos)
    {

    }
    double voDenari()
    {
        return iznos;
    }
    double voEvra()
    {
        return iznos/EUR;
    }
    double voDolari()
    {
        return iznos/USD;
    }
    void pecati()
    {
        cout<<day<<"/"<<month<<"/"<<year<<" "<<iznos<<" MKD"<<endl;
    }
};

class DeviznaTransakcija : public Transakcija
{
private:
    char currency[4];
public:
    DeviznaTransakcija(int day=1, int month=1, int year=2000, double iznos=0, char *currency="") : Transakcija(day,month,year,iznos)
    {
        strcpy(this->currency,currency);
        if(strcmp(currency,"USD")!=0&&strcmp(currency,"EUR")!=0)
        {
            throw NotSupportedCurrencyException(currency);
        }
    }
    double voDenari()
    {
        if(strcmp(currency,"USD")==0)
        {
            return iznos*USD;
        }
        if(strcmp(currency,"EUR")==0)
        {
            return iznos*EUR;
        }
    }
    double voEvra()
    {
        if(strcmp(currency,"USD")==0)
        {
            return (iznos*USD)/EUR;
        }
        if(strcmp(currency,"EUR")==0)
        {
            return iznos;
        }
    }
    double voDolari()
    {
        if(strcmp(currency,"USD")==0)
        {
            return iznos;
        }
        if(strcmp(currency,"EUR")==0)
        {
            return (iznos*EUR)/USD;
        }
    }
    void pecati()
    {
        if(strcmp(currency,"USD")==0)
        {
            cout<<day<<"/"<<month<<"/"<<year<<" "<<iznos<<" USD"<<endl;
        }
        if(strcmp(currency,"EUR")==0)
        {
            cout<<day<<"/"<<month<<"/"<<year<<" "<<iznos<<" EUR"<<endl;
        }
    }
};

class Smetka
{
private:
    Transakcija **transactions;
    int n;
    char id[15];
    double start;
public:
    Smetka(char *id="", double start=0.0)
    {
        strcpy(this->id,id);
        this->start=start;
        n=0;
        transactions=new Transakcija*[0];
    }
    Smetka(const Smetka &s)
    {
        strcpy(this->id,s.id);
        this->start=s.start;
        n=s.n;
        transactions=new Transakcija*[n];
        for(int i=0;i<n;i++)
        {
            transactions[i]=s.transactions[i];
        }
    }
    Smetka& operator=(const Smetka &s)
    {
        if(this!=&s)
        {
            delete [] transactions;
            strcpy(this->id,s.id);
            this->start=s.start;
            n=s.n;
            transactions=new Transakcija*[n];
            for(int i=0;i<n;i++)
            {
                transactions[i]=s.transactions[i];
            }
        }
        return *this;
    }
    ~Smetka()
    {
        delete [] transactions;
    }
    Smetka& operator+=(Transakcija *t)
    {
        Transakcija **tmp=new Transakcija*[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=transactions[i];
        }
        tmp[n++]=t;
        delete [] transactions;
        transactions=tmp;
        return *this;
    }
    void izvestajVoDenari()
    {
        double sum=0.0;
        sum+=start;
        cout<<"Korisnikot so smetka: "<<id<<" ima momentalno saldo od ";
        for(int i=0;i<n;i++)
        {
            sum+=transactions[i]->voDenari();
        }
        //ima greshka vo eden test primer:)
        cout<<sum<<" MKD"<<endl;
    }
    void izvestajVoDolari()
    {
        double sum=0.0;
        cout<<"Korisnikot so smetka: "<<id<<" ima momentalno saldo od ";
        for(int i=0;i<n;i++)
        {
            sum+=transactions[i]->voDolari();
        }
        sum+=start/Transakcija::getUSD();
        cout<<sum<<" USD"<<endl;
    }
    void izvestajVoEvra()
    {
        double sum=0.0;
        cout<<"Korisnikot so smetka: "<<id<<" ima momentalno saldo od ";
        for(int i=0;i<n;i++)
        {
            sum+=transactions[i]->voEvra();
        }
        sum+=start/Transakcija::getEUR();
        cout<<sum<<" EUR"<<endl;
    }
    void pecatiTransakcii()
    {
        for(int i=0;i<n;i++)
        {
            transactions[i]->pecati();
        }
    }
};

int main () {

    Smetka s ("300047024112789",1500);

    int n, den, mesec, godina, tip;
    double iznos;
    char valuta [3];

    cin>>n;
    cout<<"===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI==="<<endl;
    for (int i=0;i<n;i++){
        cin>>tip>>den>>mesec>>godina>>iznos;
        if (tip==2){
            cin>>valuta;
            try
            {
                Transakcija * t = new DeviznaTransakcija(den,mesec,godina,iznos,valuta);
                s+=t;
            }
            catch(NotSupportedCurrencyException e)
            {
                e.message();
            }
            catch(InvalidDateException i)
            {
                i.message();
            }
            //delete t;
        }
        else {
            try
            {
                Transakcija * t = new DenarskaTransakcija(den,mesec,godina,iznos);
                s+=t;
            }
            catch(NotSupportedCurrencyException e)
            {
                e.message();
            }
            catch(InvalidDateException i)
            {
                i.message();
            }
            //delete t;
        }

    }
    cout<<"===PECHATENJE NA SITE TRANSAKCII==="<<endl;
    s.pecatiTransakcii();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();


    cout<<"\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n"<<endl;


    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();




    return 0;
}