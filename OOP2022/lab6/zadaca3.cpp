//
// Created by kbogojoska on 21.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class Lekar
{
protected:
    int fax;
    char name[20];
    char surname[20];
    double startSalary;

public:
    Lekar(int fax=0, char *name="", char *surname="", double startSalary=0)
    {
        strcpy(this->name,name);
        strcpy(this->surname,surname);
        this->fax=fax;
        this->startSalary=startSalary;
    }
    Lekar(const Lekar &l)
    {
        strcpy(this->name,l.name);
        strcpy(this->surname,l.surname);
        this->fax=l.fax;
        this->startSalary=l.startSalary;
    }
    ~Lekar(){}
    void pecati()
    {
        cout<<fax<<": "<<name<<" "<<surname<<endl;
    }
    double plata()
    {
        return startSalary;
    }
};

class MaticenLekar : public Lekar
{
private:
    int patients;
    double *fees;
public:
    MaticenLekar(int fax=0, char *name="", char *surname="", double startSalary=0, int patients=0, double *fees=0) : Lekar(fax,name,surname,startSalary)
    {
        this->patients=patients;
        this->fees=new double[patients];
        for(int i=0;i<patients;i++)
        {
            this->fees[i]=fees[i];
        }
    }
    MaticenLekar(const MaticenLekar &ml) : Lekar(ml)
    {
        this->patients=ml.patients;
        this->fees=new double[ml.patients];
        for(int i=0;i<patients;i++)
        {
            this->fees[i]=ml.fees[i];
        }
    }
    MaticenLekar(const Lekar &l, int patients=0, double *fees=0) : Lekar(l)
    {
        this->patients=patients;
        this->fees=new double[patients];
        for(int i=0;i<patients;i++)
        {
            this->fees[i]=fees[i];
        }
    }
    MaticenLekar& operator=(const MaticenLekar &ml)
    {
        if(this!=&ml)
        {
            strcpy(this->name,ml.name);
            strcpy(this->surname,ml.surname);
            this->fax=ml.fax;
            this->startSalary=ml.startSalary;
            delete [] fees;
            this->patients=ml.patients;
            this->fees=new double[ml.patients];
            for(int i=0;i<patients;i++)
            {
                this->fees[i]=ml.fees[i];
            }
        }
        return *this;
    }
    ~MaticenLekar()
    {
        delete [] fees;
    }
    int avg()
    {
        int vk=0;
        for(int i=0;i<patients;i++)
        {
            vk+=fees[i];
        }
        return vk/patients;
    }
    void pecati()
    {
        Lekar::pecati();
        cout<<"Prosek na kotizacii: "<<avg()<<endl;
    }
    double plata()
    {
        double d=Lekar::plata();
        return d+(avg()*0.3);
    }
};

int main() {
    int n;
    cin>>n;
    int pacienti;
    double kotizacii[100];
    int faksimil;
    char ime [20];
    char prezime [20];
    double osnovnaPlata;

    Lekar * lekari = new Lekar [n];
    MaticenLekar * maticni = new MaticenLekar [n];

    for (int i=0;i<n;i++){
        cin >> faksimil >> ime >> prezime >> osnovnaPlata;
        lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);
    }

    for (int i=0;i<n;i++){
        cin >> pacienti;
        for (int j=0;j<pacienti;j++){
            cin >> kotizacii[j];
        }
        maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
        for (int i=0;i<n;i++){
            lekari[i].pecati();
            cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
        }
    }
    else {
        cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
        for (int i=0;i<n;i++){
            maticni[i].pecati();
            cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
        }
    }

    delete [] lekari;
    delete [] maticni;

    return 0;
}