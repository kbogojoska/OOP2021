//
// Created by kbogojoska on 19.6.2022.
//

#include <iostream>
#include <cstring>

using namespace std;

//Vasiot kod tuka

class Pica
{
private:
    char name[15];
    int price;
    char *ingredients;
    int discount;
    void copy(const Pica &p)
    {
        this->price=p.price;
        this->discount=p.discount;
        strcpy(this->name,p.name);
        this->ingredients=new char[strlen(p.ingredients)+1];
        strcpy(this->ingredients,p.ingredients);
    }
public:
    Pica(char *name="", int price=0, char *ingredients="", int discount=0)
    {
        this->price=price;
        this->discount=discount;
        strcpy(this->name,name);
        this->ingredients=new char[strlen(ingredients)+1];
        strcpy(this->ingredients,ingredients);
    }
    Pica(const Pica &p)
    {
        copy(p);
    }
    Pica& operator=(const Pica &p)
    {
        if(this!=&p)
        {
            delete [] ingredients;
            copy(p);
        }
        return *this;
    }
    ~Pica()
    {
        delete [] ingredients;
    }
    void pecati()
    {
        cout<<name<<" - "<<ingredients<<", "<<price<<endl;
    }
    bool istiSe(Pica p)
    {
        if(strcmp(ingredients,p.ingredients))
        {
            return false;
        }
        return true;
    }
    friend class Picerija;
};

class Picerija
{
private:
    char name[15];
    Pica *pici;
    int n;
    void copy(const Picerija &pr)
    {
        this->n=pr.n;
        strcpy(this->name,pr.name);
        this->pici=new Pica[n];
        for(int i=0;i<n;i++)
        {
            pici[i]=pr.pici[i];
        }
    }
public:
    Picerija(char *name="")
    {
        this->n=0;
        strcpy(this->name,name);
        this->pici=new Pica[0];
    }
    Picerija(const Picerija &pr)
    {
        copy(pr);
    }
    Picerija& operator=(const Picerija &pr)
    {
        if(this!=&pr)
        {
            delete [] pici;
            copy(pr);
        }
        return *this;
    }
    ~Picerija()
    {
        delete [] pici;
    }
    bool check(Pica p)
    {
        for(int i=0;i<n;i++)
        {
            if(pici[i].istiSe(p))
            {
                return false;
            }
        }
        return true;
    }
    void dodadi(Pica p)
    {
        if(!check(p))
        {
            return;
        }
        Pica *tmp=new Pica[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=pici[i];
        }
        tmp[n++]=p;
        delete [] pici;
        pici=tmp;
    }
    void setIme(char *n)
    {
        strcpy(this->name,n);
    }
    int priceDiscounted(int p, int d)
    {

        return p-(p*d/100);
    }
    void piciNaPromocija()
    {
        for(int i=0;i<n;i++)
        {
            if(pici[i].discount!=0&&pici[i].discount>0&&pici[i].discount<100)
            {
                cout<<pici[i].name<<" - "<<pici[i].ingredients<<", "<<pici[i].price<<" "<<priceDiscounted(pici[i].price, pici[i].discount)<<endl;
            }
        }
    }
    char* getIme()
    {
        return name;
    }
};

int main () {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for(int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);

        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);

    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();

    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();

    return 0;
}
