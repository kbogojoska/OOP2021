//
// Created by kbogojoska on 19.6.2022.
//

#include <iostream>
#include <cstring>

using namespace std;

class Potpisuvac
{
    //vasiot kod ovde
private:
    char name[20];
    char surname[20];
    char embg[14];
public:
    Potpisuvac(char *name="", char *surname="", char* embg="")
    {
        strcpy(this->name,name);
        strcpy(this->surname,surname);
        strcpy(this->embg,embg);
    }
    Potpisuvac(const Potpisuvac &p)
    {
        strcpy(this->name,p.name);
        strcpy(this->surname,p.surname);
        strcpy(this->embg,p.embg);
    }
    friend class Dogovor;
};

class Dogovor
{
    //vasiot kod ovde
private:
    int number;
    char category[50];
    Potpisuvac signer[3];
public:
    Dogovor()
    {
        number=0;
        strcpy(this->category,"unknown");
    }
    Dogovor(int number, char *category, Potpisuvac *signer)
    {
        this->number=number;
        strcpy(this->category,category);
        for(int i=0;i<3;i++)
        {
            this->signer[i]=signer[i];
        }
    }
    bool proverka()
    {
        if(strcmp(signer[0].embg,signer[1].embg)==0||strcmp(signer[0].embg,signer[2].embg)==0||strcmp(signer[1].embg,signer[2].embg)==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};


//ne smee da se menuva main funkcijata
int main()
{
    char embg[14], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> embg >> ime >> prezime;
        Potpisuvac p1(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p2(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p3(ime, prezime, embg);
        cin >> broj >> kategorija;
        Potpisuvac p[3];
        p[0] = p1; p[1] = p2; p[2] = p3;
        Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl;
        if(d.proverka() == true)
            cout << "Postojat potpishuvaci so ist EMBG" << endl;
        else
            cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}