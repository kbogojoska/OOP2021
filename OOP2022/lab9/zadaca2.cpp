//
// Created by kbogojoska on 24.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class ArrayFullException
{
public:
    void message()
    {
        cout<<"The array is full. Increase the capacity"<<endl;
    }
};

class NumbersNotDivisibleException
{
private:
    int n;
public:
    NumbersNotDivisibleException(int n)
    {
        this->n=n;
    }
    void message()
    {
        cout<<"Division by "<<n<<" is not supported"<<endl;
    }
};

class ArithmeticException
{
public:
    void message()
    {
        cout<<"Division by zero is not allowed"<<endl;
    }
};

class IndexOutOfBoundsException
{
private:
    int i;
public:
    IndexOutOfBoundsException(int i)
    {
        this->i=i;
    }
    void message()
    {
        cout<<"Index "<<i<<" is out of bounds"<<endl;
    }
};

class NumberIsNotPositiveException
{
private:
    int n;
public:
    NumberIsNotPositiveException(int n)
    {
        this->n=n;
    }
    void message()
    {
        cout<<"Number "<<n<<" is not positive integer"<<endl;
    }
};

class PositiveIntegers
{
private:
    int *numbers;
    int n;
    int maxCapacity;
public:
    PositiveIntegers(int maxCapacity=5)
    {
        this->maxCapacity=maxCapacity;
        numbers=new int[0];
        n=0;
    }
    PositiveIntegers(const PositiveIntegers &p)
    {
        this->maxCapacity=p.maxCapacity;
        this->n=p.n;
        this->numbers=new int[n];
        for(int i=0;i<n;i++)
        {
            this->numbers[i]=p.numbers[i];
        }
    }
    PositiveIntegers& operator=(const PositiveIntegers &p)
    {
        if(this!=&p)
        {
            delete [] numbers;
            this->maxCapacity=p.maxCapacity;
            this->n=p.n;
            this->numbers=new int[n];
            for(int i=0;i<n;i++)
            {
                this->numbers[i]=p.numbers[i];
            }
        }
        return *this;
    }
    ~PositiveIntegers()
    {
        delete [] numbers;
    }
    void increaseCapacity(int c)
    {
        this->maxCapacity+=c;
    }
    PositiveIntegers& operator+=(int a)
    {
        if(n==maxCapacity)
        {
            throw ArrayFullException();
        }
        if(a<0||a==0)
        {
            throw NumberIsNotPositiveException(a);
        }
        int *tmp=new int[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=numbers[i];
        }
        tmp[n++]=a;
        delete [] numbers;
        numbers=tmp;
        return *this;
    }
    PositiveIntegers operator*(int a)
    {
        PositiveIntegers tmp(*this);
        for(int i=0;i<n;i++)
        {
            tmp.numbers[i]*=a;
        }
        return tmp;
    }
    PositiveIntegers operator/(int a)
    {
        PositiveIntegers tmp(*this);
        if(a==0)
        {
            throw ArithmeticException();
        }
        for(int i=0;i<n;i++)
        {
            if(tmp.numbers[i]%a!=0)
            {
                throw NumbersNotDivisibleException(a);
            }
            tmp.numbers[i]/=a;
        }
        return tmp;
    }
    int operator[](int idx)
    {
        if(idx<0||idx>n)
        {
            throw IndexOutOfBoundsException(idx);
        }
        return numbers[idx];
    }
    void print()
    {
        cout<<"Size: "<<n<<" Capacity: "<<maxCapacity<<" Numbers: ";
        for(int i=0;i<n;i++)
        {
            cout<<numbers[i]<<" ";
        }
        cout<<endl;
    }
};

int main() {

    int n,capacity;
    cin >> n >> capacity;
    PositiveIntegers pi (capacity);
    for (int i=0;i<n;i++){
        int number;
        cin>>number;
        try
        {
            pi+=number;
        }
        catch(ArrayFullException af)
        {
            af.message();
        }
        catch(NumberIsNotPositiveException np)
        {
            np.message();
        }
    }
    cout<<"===FIRST ATTEMPT TO ADD NUMBERS==="<<endl;
    pi.print();
    int incCapacity;
    cin>>incCapacity;
    pi.increaseCapacity(incCapacity);
    cout<<"===INCREASING CAPACITY==="<<endl;
    pi.print();

    int n1;
    cin>>n1;
    for (int i=0;i<n1;i++){
        int number;
        cin>>number;
        try
        {
            pi+=number;
        }
        catch(ArrayFullException af)
        {
            af.message();
        }
        catch(NumberIsNotPositiveException np)
        {
            np.message();
        }
    }


    cout<<"===SECOND ATTEMPT TO ADD NUMBERS==="<<endl;

    pi.print();
    PositiveIntegers pi1;

    cout<<"===TESTING DIVISION==="<<endl;
    try
    {
        pi1 = pi/0;
        pi1.print();
    }
    catch(ArithmeticException a)
    {
        a.message();
    }
    catch(NumbersNotDivisibleException e)
    {
        e.message();
    }


    try
    {
        pi1 = pi/1;
        pi1.print();
    }
    catch(ArithmeticException a)
    {
        a.message();
    }
    catch(NumbersNotDivisibleException e)
    {
        e.message();
    }


    try
    {
        pi1 = pi/2;
        pi1.print();
    }
    catch(ArithmeticException a)
    {
        a.message();
    }
    catch(NumbersNotDivisibleException e)
    {
        e.message();
    }


    cout<<"===TESTING MULTIPLICATION==="<<endl;
    pi1 = pi*3;
    pi1.print();


    cout<<"===TESTING [] ==="<<endl;
    try
    {
        cout<<"PositiveIntegers[-1] = "<<pi[-1]<<endl;
    }
    catch(IndexOutOfBoundsException ob)
    {
        ob.message();
    }
    try
    {
        cout<<"PositiveIntegers[2] = "<<pi[2]<<endl;
    }
    catch(IndexOutOfBoundsException ob)
    {
        ob.message();
    }
    try
    {
        cout<<"PositiveIntegers[3] = "<<pi[3]<<endl;
    }
    catch(IndexOutOfBoundsException ob)
    {
        ob.message();
    }
    try
    {
        cout<<"PositiveIntegers[12] = "<<pi[12]<<endl;
    }
    catch(IndexOutOfBoundsException ob)
    {
        ob.message();
    }

    return 0;
}