//
// Created by kbogojoska on 19.6.2022.
//

#include<iostream>
#include<cstring>
using namespace std;

class Date
{
private:
    int year;
    int month;
    int day;
public:
    Date(int year=0, int month=0, int day=0)
    {
        this->year=year;
        this->month=month;
        this->day=day;
    }
    Date(const Date &d)
    {
        this->year=d.year;
        this->month=d.month;
        this->day=d.day;
    }
    ~Date(){}
    void print()
    {
        cout<<year<<"."<<month<<"."<<day<<endl;
    }
};

class Person
{
private:
    char name[20];
    char surname[20];
public:
    Person(char *name="not specified", char *surname="not specified")
    {
        strcpy(this->name,name);
        strcpy(this->surname,surname);
    }
    ~Person(){}
    void print()
    {
        cout<<name<<" "<<surname<<endl;
    }
};

class Car
{
private:
    Person owner;
    Date date;
    float price;
public:
    Car()
    {
        price=0;
    }
    Car(Person owner, Date date, float price)
    {
        this->owner=owner;
        this->date=date;
        this->price=price;
    }
    ~Car(){}
    void print()
    {
        owner.print();
        date.print();
        cout<<"Price: "<<price<<endl;
    }
    friend void cheaperThan(Car *cars, int numCars, float price);
};

void cheaperThan(Car *cars, int numCars, float price)
{
    for(int i=0;i<numCars;i++)
    {
        if(cars[i].price<price)
        {
            cars[i].print();
        }
    }
}

int main() {
    char name[20];
    char lastName[20];
    int year;
    int month;
    int day;
    float price;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);

        cin >> year;
        cin >> month;
        cin >> day;
        Date date(year, month, day);

        cin >> price;
        Car car(lik, date,  price);

        car.print();
    }
    else if (testCase == 2) {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);

        cin >> year;
        cin >> month;
        cin >> day;
        Date date(Date(year, month, day));

        cin >> price;
        Car car(lik, date,  price);
        car.print();
    }
    else {
        int numCars;
        cin >> numCars;

        Car cars[10];
        for (int i = 0; i < numCars; i++) {
            cin >> name;
            cin >> lastName;
            Person lik(name, lastName);

            cin >> year;
            cin >> month;
            cin >> day;
            Date date(year, month, day);

            cin >> price;
            cars[i] = Car(lik, date,  price);
        }
        float priceLimit;
        cin >> priceLimit;
        cheaperThan(cars, numCars, priceLimit);
    }


    return 0;
}