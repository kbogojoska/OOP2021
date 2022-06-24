//
// Created by kbogojoska on 22.6.2022.
//

#include<iostream>
using namespace std;

class Number
{
public:
    //TODO da se deklariraat trite cisto virtuelni metodi
    virtual double doubleValue()=0;
    virtual int intValue()=0;
    virtual void print()=0;
    bool operator==(Number &n)
    {
        return doubleValue()==n.doubleValue()&&intValue()==n.intValue();
    }
};

//ТODO preoptovaruvanje na operatorot ==

class Integer : public Number
{ //TODO da se dodadi izraz za nasleduvanje od Number
private:
    //TODO da se deklariraat promenlivite
    int number;
public:
    //TODO konstruktor so eden argument
    Integer(int number=0)
    {
        this->number=number;
    }
    //TODO da se prepokrijat metodite od klasata Number
    double doubleValue()
    {
        return (double)number;
    }
    int intValue()
    {
        return number;
    }
    void print()
    {
        cout<<number<<endl;
    }
};

class Double : public Number
{ //TODO da se dodadi izraz za nasleduvanje od Number
private:
    //TODO da se deklariraat promenlivite
    double number;
public:
    //TODO konstruktor so eden argument
    Double(double number=0)
    {
        this->number=number;
    }
    //TODO da se prepokrijat metodite od klasata Number
    double doubleValue()
    {
        return number;
    }
    int intValue()
    {
        return (int)number;
    }
    void print()
    {
        cout<<number<<endl;
    }
};

class Numbers{
private:
    //TODO deklariranje na promenlivite
    Number **numbers;
    int n;
public:
    //TODO default konstruktor
    Numbers()
    {
        n=0;
        numbers=new Number*[0];
    }
    //TODO copy konstruktor
    Numbers(const Numbers &m)
    {
        this->n=m.n;
        numbers=new Number*[n];
        for(int i=0;i<n;i++)
        {
            this->numbers[i]=m.numbers[i];
        }
    }
    //TODO operator =
    Numbers& operator=(const Numbers &m)
    {
        if(this!=&m)
        {
            delete [] numbers;
            this->n=m.n;
            numbers=new Number*[n];
            for(int i=0;i<n;i++)
            {
                this->numbers[i]=m.numbers[i];
            }
        }
        return *this;
    }
    //TODO destruktor
    ~Numbers()
    {
        delete [] numbers;
    }
    bool check(Number *m)
    {
        for(int i=0;i<n;i++)
        {
            if(*numbers[i]==*m)
            {
                return false;
            }
        }
        return true;
    }
    //TODO operator += (operatorot da prima pointer od objekt od Number, a ne referenca)
    Numbers& operator+=(Number *m)
    {
        if(check(m))
        {
            Number **tmp=new Number*[n+1];
            for(int i=0;i<n;i++)
            {
                tmp[i]=numbers[i];
            }
            tmp[n++]=m;
            delete [] numbers;
            numbers=tmp;
        }
        return *this;
    }
    int countD()
    {
        int count=0;
        for(int i=0;i<n;i++)
        {
            Double *tmp=dynamic_cast<Double*>(numbers[i]);
            if(tmp!=0)
            {
                count++;
            }
        }
        return count;
    }
    int countI()
    {
        int count=0;
        for(int i=0;i<n;i++)
        {
            Integer *tmp=dynamic_cast<Integer*>(numbers[i]);
            if(tmp!=0)
            {
                count++;
            }
        }
        return count;
    }
    double sumD()
    {
        double count=0;
        for(int i=0;i<n;i++)
        {
            Double *tmp=dynamic_cast<Double*>(numbers[i]);
            if(tmp!=0)
            {
                count+=numbers[i]->doubleValue();
            }
        }
        return count;
    }
    int sumI()
    {
        int count=0;
        for(int i=0;i<n;i++)
        {
            Integer *tmp=dynamic_cast<Integer*>(numbers[i]);
            if(tmp!=0)
            {
                count+=numbers[i]->intValue();
            }
        }
        return count;
    }
    double sumAll()
    {
        return sumI()+sumD();
    }
    //TODO void statistics()
    void statistics()
    {
        cout<<"Count of numbers: "<<n<<endl;
        cout<<"Sum of all numbers: "<<sumAll()<<endl;
        cout<<"Count of integer numbers: "<<countI()<<endl;
        cout<<"Sum of integer numbers: "<<sumI()<<endl;
        cout<<"Count of double numbers: "<<countD()<<endl;
        cout<<"Sum of double numbers: "<<sumD()<<endl;
    }
    //TODO void integersLessThan (Integer n)
    void integersLessThan (Integer m)
    {
        int flag=0;
        for(int i=0;i<n;i++)
        {
            Integer *tmp=dynamic_cast<Integer*>(numbers[i]);
            if(tmp!=0)
            {
                if(numbers[i]->intValue()<m.intValue())
                {
                    flag=1;
                    cout<<"Integer: "<<numbers[i]->intValue()<<endl;
                }
            }
        }
        if(!flag)
        {
            cout<<"None"<<endl;
        }
    }
    //TODO void doublesBiggerThan (Double n)
    void doublesBiggerThan (Double m)
    {
        int flag=0;
        for(int i=0;i<n;i++)
        {
            Double *tmp=dynamic_cast<Double*>(numbers[i]);
            if(tmp!=0)
            {
                if(numbers[i]->doubleValue()>m.doubleValue())
                {
                    flag=1;
                    cout<<"Double: "<<numbers[i]->doubleValue()<<endl;
                }
            }
        }
        if(!flag)
        {
            cout<<"None"<<endl;
        }
    }
};

int main() {

    int n;
    cin>>n;
    Numbers numbers;
    for (int i=0;i<n;i++){
        int type;
        double number;
        cin>>type>>number;
        if (type==0){//Integer object
            Integer * integer = new Integer((int) number);
            numbers+=integer;
        }
        else {
            Double * doublee = new Double(number);
            numbers+=doublee;
        }
    }

    int lessThan;
    double biggerThan;

    cin>>lessThan;
    cin>>biggerThan;

    cout<<"STATISTICS FOR THE NUMBERS\n";
    numbers.statistics();
    cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
    numbers.integersLessThan(Integer(lessThan));
    cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
    numbers.doublesBiggerThan(Double(biggerThan));

    return 0;
}