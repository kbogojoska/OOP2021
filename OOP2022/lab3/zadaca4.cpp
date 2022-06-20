//
// Created by kbogojoska on 19.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class Masa
{
private:
    int length;
    int width;
public:
    Masa(int width=0, int length=0)
    {
        this->length=length;
        this->width=width;
    }
    ~Masa(){}
    void pecati()
    {
        cout<<"Masa: "<<width<<" "<<length;
    }
};

class Soba
{
private:
    Masa table;
    int length;
    int width;
public:
    Soba()
    {
        length=0;
        width=0;
    }
    Soba(int width, int length, Masa table)
    {
        this->table=table;
        this->length=length;
        this->width=width;
    }
    ~Soba(){}
    void pecati()
    {

        cout<<"Soba: "<<width<<" "<<length<<" ";
        table.pecati();
    }
};

class Kukja
{
private:
    Soba room;
    char address[50];
public:
    Kukja(Soba room, char *address="")
    {
        this->room=room;
        strcpy(this->address,address);
    }
    ~Kukja(){}
    void pecati()
    {
        cout<<"Adresa: "<<address<<" ";
        room.pecati();
        cout<<endl;
    }
};

//ne smee da se menuva main funkcijata!
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int masaSirina,masaDolzina;
        cin>>masaSirina;
        cin>>masaDolzina;
        Masa m(masaSirina,masaDolzina);
        int sobaSirina,sobaDolzina;
        cin>>sobaSirina;
        cin>>sobaDolzina;
        Soba s(sobaSirina,sobaDolzina,m);
        char adresa[30];
        cin>>adresa;
        Kukja k(s,adresa);
        k.pecati();
    }

    return 0;
}