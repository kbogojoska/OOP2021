//
// Created by kbogojoska on 25.6.2022.
//

#include <cstring>
#include <iostream>
using namespace std;

enum Size
{
    small, big, family
};

class Pizza
{
protected:
    char name[20];
    char ingredients[100];
    double thePrice;
public:
    Pizza(const char *name="", const char *ingredients="", double thePrice=0.0)
    {
        strcpy(this->name,name);
        strncpy(this->ingredients,ingredients,49);
        this->thePrice=thePrice;
    }
    virtual double price() = 0;
};

class FlatPizza : public Pizza
{
private:
    Size size;
public:
    FlatPizza(const char *name="", const char *ingredients="", double thePrice=0.0, Size size=small) : Pizza(name,ingredients,thePrice)
    {
        this->size=size;
    }
    double price()
    {
        if(size==0)
        {
            return thePrice*1.1;
        }
        if(size==1)
        {
            return thePrice*1.5;
        }
        if(size==2)
        {
            return thePrice*1.3;
        }
    }
    friend ostream& operator<<(ostream& out, FlatPizza &flat)
    {
        out<<flat.name<<": "<<flat.ingredients<<", ";
        switch(flat.size)
        {
            case 0:
                out<<"small";
                break;
            case 1:
                out<<"big";
                break;
            case 2:
                out<<"family";
                break;
        }
        out<<" - "<<flat.price()<<endl;
    }
};

class FoldedPizza : public Pizza
{
private:
    bool isWhite;
public:
    FoldedPizza(const char *name="", const char *ingredients="", double thePrice=0.0, bool isWhite=true) : Pizza(name,ingredients,thePrice)
    {
        this->isWhite=isWhite;
    }
    double price()
    {
        if(isWhite)
        {
            return thePrice*1.1;
        }
        else
        {
            return thePrice*1.3;
        }
    }
    friend ostream& operator<<(ostream& out, FoldedPizza &fold)
    {
        out<<fold.name<<": "<<fold.ingredients<<", ";
        if(fold.isWhite)
        {
            out<<"wf - ";
        }
        else
        {
            out<<"nwf - ";
        }
        out<<fold.price()<<endl;
        return out;
    }
    void setWhiteFlour(bool n)
    {
        isWhite=n;
    }
};

bool operator<(Pizza &p1, Pizza &p2)
{
    return p1.price()<p2.price();
}
// Testing

void expensivePizza(Pizza **pizzas, int n)
{
    int idx=0;
    for(int i=0;i<n;i++)
    {
        if(pizzas[i]->price()>pizzas[idx]->price())
        {
            idx=i;
        }
    }
    FlatPizza *flat=dynamic_cast<FlatPizza*>(pizzas[idx]);
    if(flat!=0)
    {
        cout<<*flat;
    }
    FoldedPizza *folded=dynamic_cast<FoldedPizza*>(pizzas[idx]);
    if(folded!=0)
    {
        cout<<*folded;
    }
}

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    }
    else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    }
    else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    }
    else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    }
    else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    }
    else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
