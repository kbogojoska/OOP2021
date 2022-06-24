//
// Created by kbogojoska on 24.6.2022.
//

#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

class Igrachka {
public:
    virtual float getVolumen() = 0;
    virtual float getMasa() = 0;
    //дополнително барање 1
    virtual float getPlostina() = 0;
};

class Forma {
protected:
    char boja[100];
    int gustina;
public:
    // да се имплементираат потребните методи
    Forma(char *boja="", int gustina=0)
    {
        strcpy(this->boja,boja);
        this->gustina=gustina;
    }
    ~Forma(){}
};

class Topka : public Igrachka, public Forma
{
private:
    int radius;
public:
    Topka(char *boja="", int gustina=0, int radius=0) : Forma(boja,gustina)
    {
        this->radius=radius;
    }
    float getVolumen()
    {
        return 4.0/3*3.14*pow(radius,3);
    }
    float getMasa()
    {
        return getVolumen()*gustina;
    }
    float getPlostina()
    {
        return pow(radius,2)*3.14*4.0;
    }
};

class Kocka : public Igrachka, public Forma
{
private:
    int height;
    int width;
    int depth;
public:
    Kocka(char *boja="", int gustina=0, int height=0, int width=0, int depth=0) : Forma(boja,gustina)
    {
        this->height=height;
        this->width=width;
        this->depth=depth;
    }
    float getVolumen()
    {
        return (float)height*width*depth;
    }
    float getMasa()
    {
        return getVolumen()*gustina;
    }
    float getPlostina()
    {
        if(height==width&&width==depth)
        {
            return 6.0*pow(height,2);
        }
        else
        {
            return 2.0*(height*depth+height*width+width*depth);
        }
    }
};

int main(){
    //vnesi informacii za kupche
    int n;
    cin>>n;
    Igrachka **kupche=new Igrachka *[n];

    int type,dense, r, h, w, d;
    char c[100];

    for(int i=0;i<n;i++)
    {
        cin>>type>>c>>dense;
        if(type==1)
        {
            cin>>r;
            kupche[i]=new Topka(c,dense,r);
        }
        else if(type==2)
        {
            cin>>h>>w>>d;
            kupche[i]=new Kocka(c,dense,h,w,d);
        }
    }

    //vnesi informacii za igrachkata na Petra
    cin>>c>>dense>>h>>w>>d;
    Igrachka *kockaPetra=new Kocka(c,dense,h,w,d);


    //baranje 1
    float total=0.0;
    for(int i=0;i<n;i++)
    {
        total+=kupche[i]->getMasa();
    }
    if(total>kockaPetra->getMasa())
    {
        cout<<"DA"<<endl;
    }
    else
    {
        cout<<"NE"<<endl;
    }

    //baranje 2
    int maxIdx=0;
    for(int i=1;i<n;i++)
    {
        if(kupche[i]->getVolumen()>kupche[maxIdx]->getVolumen())
        {
            maxIdx=i;
        }
    }
    cout<<"Razlikata e: "<<abs(kupche[maxIdx]->getVolumen()-kockaPetra->getVolumen())<<endl;

    //дополнително барање 2
    int minIdx=0;
    for(int i=1;i<n;i++)
    {
        if(kupche[i]->getPlostina()<kupche[minIdx]->getPlostina())
        {
            minIdx=i;
        }
    }
    cout<<"Razlikata e: "<<abs(kupche[minIdx]->getPlostina()-kockaPetra->getPlostina())<<endl;
    return 0;
}