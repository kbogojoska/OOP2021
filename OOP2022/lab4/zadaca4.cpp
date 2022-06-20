//
// Created by kbogojoska on 19.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

enum zanr
{
    akcija, komedija, drama
};

class Film
{
private:
    char *name;
    int size;
    zanr z;
    void copy(const Film &f)
    {
        this->name=new char[strlen(f.name)+1];
        strcpy(this->name,f.name);
        this->size=f.size;
        this->z=f.z;
    }
public:
    Film(char *name="", int size=0, zanr z=akcija)
    {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->size=size;
        this->z=z;
    }
    Film(const Film &f)
    {
        copy(f);
    }
    Film& operator=(const Film &f)
    {
        if(this!=&f)
        {
            delete [] name;
            copy(f);
        }
        return *this;
    }
    ~Film()
    {
        delete [] name;
    }
    void pecati()
    {
        cout<<size<<"MB-\""<<name<<"\""<<endl;
    }
    friend class DVD;
};

class DVD
{
private:
    Film film[5];
    int n;
    int capacity;
public:
    DVD(int capacity=5)
    {
        this->n=0;
        this->capacity=capacity;
    }
    ~DVD(){}
    void dodadiFilm (Film f)
    {
        if(n<5)
        {
            int vk=f.size;
            for(int i=0;i<n;i++)
            {
                vk+=film[i].size;
            }
            if(vk<=capacity)
            {
                film[n++]=f;
            }
        }
    }
    Film getFilm(int a)
    {
        for(int i=0;i<n;i++)
        {
            if(a==i)
            {
                return film[i];
            }
        }
    }
    int getBroj()
    {
        return n;
    }
    void pecatiFilmoviDrugZanr(zanr z)
    {
        for(int i=0;i<n;i++)
        {
            if((int)z!=(int)film[i].z)
            {
                film[i].pecati();
            }
        }
    }
    int sum()
    {
        int vk=0;
        for(int i=0;i<n;i++)
        {
            vk+=film[i].size;
        }
        return vk;
    }
    float procentNaMemorijaOdZanr(zanr z)
    {
        int vk=0;
        for(int i=0;i<n;i++)
        {
            if((int)z==(int)film[i].z)
            {
                vk+=film[i].size;
            }
        }
        return (vk/(double)sum())*100.0;
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Film ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
        Film f(ime, memorija, (zanr) kojzanr);
        f.pecati();
    }
    else if (testCase == 2) {
        cout << "===== Testiranje na klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getFilm(i)).pecati();
    }
    else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiFilm() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getFilm(i)).pecati();
    }
    else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    }
    else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    }
    else if (testCase == 6){
        cout<<"===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata DVD =====" <<endl;
        DVD omileno(40);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        cout<<"Procent na filmovi od dadeniot zanr iznesuva: "<<omileno.procentNaMemorijaOdZanr((zanr) kojzanr)<<"%\n";

    }

    return 0;
}