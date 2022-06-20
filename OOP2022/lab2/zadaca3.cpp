//
// Created by kbogojoska on 19.6.2022.
//

#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde
class Film
{
private:
    char name[100];
    char rezhiser[50];
    char zhanr[50];
    int year;
public:
    Film(char *name="", char *rezhiser="", char *zhanr="", int year=1900)
    {
        strcpy(this->name, name);
        strcpy(this->rezhiser, rezhiser);
        strcpy(this->zhanr, zhanr);
        this->year=year;
    }
    void print()
    {
        cout<<"Ime: "<<name<<endl;
        cout<<"Reziser: "<<rezhiser<<endl;
        cout<<"Zanr: "<<zhanr<<endl;
        cout<<"Godina: "<<year<<endl;
    }
    void setName(char *n)
    {
        strcpy(name,n);
    }
    void setRezhiser(char *n)
    {
        strcpy(rezhiser,n);
    }
    void setZhanr(char *n)
    {
        strcpy(zhanr,n);
    }
    void setYear(int n)
    {
        year=n;
    }
    int getYear()
    {
        return year;
    }
    ~Film(){}
};

void pecati_po_godina(Film *f, int n, int godina)
{
    for(int i=0;i<n;i++)
    {
        if(f[i].getYear()==godina)
        {
            f[i].print();
        }
    }
}

int main() {
    int n;
    cin >> n;
    //da se inicijalizira niza od objekti od klasata Film
    Film filmovi[n];
    for(int i = 0; i < n; ++i) {
        char ime[100];
        char reziser[50];
        char zanr[50];
        int godina;
        cin >> ime;
        cin >> reziser;
        cin >> zanr;
        cin >> godina;
        //da se kreira soodveten objekt
        filmovi[i].setName(ime);
        filmovi[i].setRezhiser(reziser);
        filmovi[i].setZhanr(zanr);
        filmovi[i].setYear(godina);
    }
    int godina;
    cin >> godina;
    //da se povika funkcijata pecati_po_godina
    pecati_po_godina(filmovi,n,godina);
    return 0;
}