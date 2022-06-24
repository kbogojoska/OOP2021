//
// Created by kbogojoska on 22.6.2022.
//

//Vasiot kod ovde:
#include<iostream>
#include<cstring>

using namespace std;

class ZicanInstrument
{
protected:
    char name[20];
    int strings;
    int price;
public:
    ZicanInstrument(char *name="", int strings=0, int price=0)
    {
        strcpy(this->name,name);
        this->strings=strings;
        this->price=price;
    }
    virtual double cena()=0;
    bool operator==(ZicanInstrument &zi)
    {
        return strings==zi.strings;
    }
    friend ostream& operator<<(ostream& out, ZicanInstrument &zi)
    {
        return out<<zi.name<<" "<<zi.strings<<" "<<zi.price<<endl;
    }
};

class Mandolina : public ZicanInstrument
{
private:
    char shape[20];
public:
    Mandolina(char *name="", int strings=0, int price=0, char *shape="") : ZicanInstrument(name,strings,price)
    {
        strcpy(this->shape,shape);
    }
    double cena()
    {
        if(strcmp(shape,"Neapolitan")==0)
        {
            return price+(price*0.15);
        }
        else
        {
            return price;
        }
    }
};

class Violina : public ZicanInstrument
{
private:
    double size;
public:
    Violina(char *name="", int strings=0, int price=0, double size=0) : ZicanInstrument(name,strings,price)
    {
        this->size=size;
    }
    double cena()
    {
        if(size==0.25)
        {
            return price+(price*0.1);
        }
        else if(size==1.00)
        {
            return price+(price*0.2);
        }
        else
        {
            return price;
        }
    }
};

void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **inst, int n)
{
    for(int i=0;i<n;i++)
    {
        if(*inst[i]==zi)
        {
            cout<<inst[i]->cena()<<endl;
        }
    }
}

int main() {
    char ime[20];
    int brojZici;
    float cena;
    char forma[20];
    cin >> ime >> brojZici >> cena >> forma;
    Mandolina m(ime, brojZici, cena, forma);
    int n;
    cin >> n;
    ZicanInstrument **zi = new ZicanInstrument*[2 * n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> brojZici >> cena >> forma;
        zi[i] = new Mandolina(ime, brojZici, cena, forma);
    }
    for(int i = 0; i < n; ++i) {
        float golemina;
        cin >> ime >> brojZici >> cena >> golemina;
        zi[n + i] = new Violina(ime, brojZici, cena, golemina);
    }
    pecatiInstrumenti(m, zi, 2 * n);
    for(int i = 0; i < 2 * n; ++i) {
        delete zi[i];
    }
    delete [] zi;
    return 0;
}