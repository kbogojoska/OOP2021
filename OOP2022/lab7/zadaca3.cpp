//
// Created by kbogojoska on 22.6.2022.
//

#include <iostream>
#include <cmath>
using namespace std;

//TODO: konstruiraj ja abstraknata klasa Shape
class Shape
{
protected:
    int a;
public:
    Shape(int a=0)
    {
        this->a=a;
    }
    virtual double plostina()=0;
    virtual void pecati()=0;
    virtual int getType()=0;
};

//TODO: konstruiraj ja klasata Kvadrat
class Square : public Shape
{
public:
    Square(int a=0):Shape(a){}
    double plostina()
    {
        return (double)a*a;
    }
    void pecati()
    {
        cout<<"Kvadrat so plostina = "<<plostina()<<endl;
    }
    int getType()
    {
        return 1;
    }
};

//TODO: konstruiraj ja klasata Krug
class Circle : public Shape
{
public:
    Circle(int a=0):Shape(a){}
    double plostina()
    {
        return a*a*3.14;
    }
    void pecati()
    {
        cout<<"Krug so plostina = "<<plostina()<<endl;
    }
    int getType()
    {
        return 2;
    }
};

//TODO: konstruiraj ja klasata Triagolnik
class Triangle : public Shape
{
public:
    Triangle(int a=0):Shape(a){}
    double plostina()
    {
        return (sqrt(3)/4) * (double)a * a;
    }
    void pecati()
    {
        cout<<"Triagolnik so plostina = "<<plostina()<<endl;
    }
    int getType()
    {
        return 3;
    }
};

// nema potreba od ovie dolu bidejki ima getType() ama ako nemashe togash vaka kje beshe kako dolu

// int Squares(Shape** niza, int n)
// {
//     for(int i=0;i<n;i++)
//     {
//         Square *tmp=dynamic_cast<Square*>(niza[i])
//         if(tmp!=0)
//         {
//             count++;
//         }
//     }
//     return count;
// }

// int Circles(Shape** niza, int n)
// {
//     for(int i=0;i<n;i++)
//     {
//         Circle *tmp=dynamic_cast<Circle*>(niza[i])
//         if(tmp!=0)
//         {
//             count++;
//         }
//     }
//     return count;
// }

// int Triangles(Shape** niza, int n)
// {
//     for(int i=0;i<n;i++)
//     {
//         Triangle *tmp=dynamic_cast<Triangle*>(niza[i])
//         if(tmp!=0)
//         {
//             count++;
//         }
//     }
//     return count;
// }

//TODO: definiraj go metodot void checkNumTypes(Shape** niza, int n)
void checkNumTypes(Shape** niza, int n)
{
    int s,c,t;
    s=c=t=0;
    for(int i=0;i<n;i++)
    {
        if(niza[i]->getType()==1)
        {
            s++;
        }
        else if(niza[i]->getType()==2)
        {
            c++;
        }
        else if(niza[i]->getType()==3)
        {
            t++;
        }
    }
    cout<<"Broj na kvadrati vo nizata = "<<s<<endl;
    cout<<"Broj na krugovi vo nizata = "<<c<<endl;
    cout<<"Broj na triagolnici vo nizata = "<<t<<endl;
}

int main(){


    int n;
    cin >> n;

    //TODO: inicijaliziraj niza od pokazuvachi kon klasata Shape
    //TODO: alociraj memorija so golemina n za prethodno navedenata niza
    Shape **niza=new Shape*[n];

    int classType;
    int side;

    //TODO: konstruiraj for ciklus so chija pomosh ke ja popolnish nizata
    for(int i = 0; i < n; ++i){

        cin >> classType;
        cin >> side;
        if(classType==1)
        {
            niza[i]=new Square(side);
        }
        else if(classType==2)
        {
            niza[i]=new Circle(side);
        }
        else if(classType==3)
        {
            niza[i]=new Triangle(side);
        }
    }


    for(int i = 0; i < n; ++i){

        niza[i]->pecati();
    }

    checkNumTypes(niza, n);


    return 0;
}