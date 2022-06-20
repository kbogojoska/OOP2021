//
// Created by kbogojoska on 20.6.2022.
//

#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class ComplexNumber
{
private:
    float real;
    float imag;
public:
    ComplexNumber(float real=0, float imag=0)
    {
        this->real=real;
        this->imag=imag;
    }
    ~ComplexNumber(){}
    double module()
    {
        return sqrt(pow(real, 2) + pow(imag, 2));
    }
    ComplexNumber& operator=(const ComplexNumber &c)
    {
        if(this!=&c)
        {
            this->real=c.real;
            this->imag=c.imag;
        }
        return *this;
    }
    friend ostream & operator<<(ostream& out, const ComplexNumber &c)
    {
        if(c.real==0)
        {
            out<<c.imag<<"i"<<endl;;
        }
        else if(c.imag==0)
        {
            out<<c.real<<endl;
        }
        else
        {
            out<<c.real<<"+"<<c.imag<<"i"<<endl;
        }

        return out;
    }
    ComplexNumber operator+(const ComplexNumber &c)
    {
        ComplexNumber tmp;
        tmp.real=this->real+c.real;
        tmp.imag=this->imag+c.imag;

        return tmp;
    }
    ComplexNumber operator-(const ComplexNumber &c)
    {
        ComplexNumber tmp=*this;
        tmp.real-=c.real;
        tmp.imag-=c.imag;

        return tmp;
    }
    ComplexNumber operator*(const ComplexNumber &c)
    {
        ComplexNumber tmp;
        tmp.real=this->real*c.real;
        tmp.imag=this->imag*c.imag;

        return tmp;
    }
    ComplexNumber operator/(const ComplexNumber &c)
    {
        ComplexNumber tmp;
        tmp.real=this->real/c.real;
        tmp.imag=this->imag/c.imag;

        return tmp;
    }
    bool operator==(const ComplexNumber &c)
    {
        return this->real==c.real&&this->imag==c.imag;
    }
    bool operator>(const ComplexNumber &c)
    {
        if(this->real!=c.real)
        {
            return this->real>c.real;
        }
        else if(this->real==c.real)
        {
            return this->imag>c.imag;
        }
    }
    bool operator<(const ComplexNumber &c)
    {
        if(this->real!=c.real)
        {
            return this->real<c.real;
        }
        else if(this->real==c.real)
        {
            return this->imag<c.imag;
        }
    }
};
class Equation
{
private:
    ComplexNumber *numbers;
    char *operations;
    int n, o;

public:
    Equation()
    {
        n=o=0;
        this->numbers=new ComplexNumber[0];
        this->operations=new char[0];
    }

    Equation& operator+=(const ComplexNumber &c)
    {
        ComplexNumber *tmp=new ComplexNumber[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=numbers[i];
        }
        tmp[n++]=c;
        delete [] numbers;
        numbers=tmp;
    }

    Equation& operator+=(const char &c)
    {
        char *tmp=new char[o+1];
        for(int i=0;i<o;i++)
        {
            tmp[i]=operations[i];
        }
        tmp[o++]=c;
        delete [] operations;
        operations=tmp;
    }

    friend istream& operator>>(istream& in, Equation &e)
    {
        float r,im;
        char c;
        for(int i=0;;i++)
        {
            in>>r;
            in>>im;
            ComplexNumber cn(r,im);
            e+=cn;
            in>>c;
            e+=c;
            if(c=='=')
            {
                return in;
            }
        }
    }

    ComplexNumber result()
    {
        ComplexNumber res = numbers[0];
        for(int i = 0, j = 1; i < o; i++, j++)
        {
            switch (operations[i])
            {
                case '+':
                    res = numbers[j] + res;
                    break;
                case '-':
                    res = res - numbers[j];
                    break;
                case '*':
                    res = res * numbers[j];
                    break;
                case '/':
                    res = res / numbers[j];
                    break;
                default:
                    break;
            }
        }
        return res;
    }

    double sumModules()
    {
        double vk = 0;
        for(int i = 0; i < n; i++)
        {
            vk += numbers[i].module();
        }
    }
};

int main() {
    int testCase;
    double real, imaginary;
    ComplexNumber first, second, result;

    cin >> testCase;

    if (testCase <= 8) {
        cin >> real;
        cin >> imaginary;
        first = ComplexNumber(real, imaginary);
        cin >> real;
        cin >> imaginary;
        second = ComplexNumber(real, imaginary);
    }

    if (testCase == 1) {
        cout << "===== OPERATOR + =====" << endl;
        result = first + second;
        cout << result;
    }
    else if (testCase == 2) {
        cout << "===== OPERATOR - =====" << endl;
        result = first - second;
        cout << result;
    }
    else if (testCase == 3) {
        cout << "===== OPERATOR * =====" << endl;
        result = first * second;
        cout << result;
    }
    else if (testCase == 4) {
        cout << "===== OPERATOR / =====" << endl;
        result = first / second;
        cout << result;
    }
    else if (testCase == 5) {
        cout << "===== OPERATOR == =====" << endl;
        cout << first;
        cout << second;
        if (first == second)
            cout << "EQUAL" << endl;
        else
            cout << "NOT EQUAL" << endl;
    }
    else if (testCase == 6) {
        cout << "===== OPERATOR > =====" << endl;
        cout << first;
        cout << second;
        if (first > second)
            cout << "FIRST GREATER THAN SECOND" << endl;
        else
            cout << "FIRST LESSER THAN SECOND" << endl;
    }
    else if (testCase == 7) {
        cout << "===== OPERATOR < =====" << endl;
        cout << first;
        cout << second;
        if (first < second)
            cout << "FIRST LESSER THAN SECOND" << endl;
        else
            cout << "FIRST GREATER THAN SECOND" << endl;
    }
    else if (testCase == 8) {
        cout << "===== MODULE =====" << endl;
        double module = first.module();
        cout << first;
        cout << "Module: " << module << endl;
        cout << second;
        module = second.module();
        cout << "Module: " << module << endl;
    }
    else if (testCase == 9) {
        cout << "===== OPERATOR >> & SUM OF MODULES =====" << endl;
        Equation equation;
        cin >> equation;
        cout << equation.sumModules();
    }
    else if (testCase == 10) {
        cout << "===== EQUATION RESULT =====" << endl;
        Equation equation;
        cin >> equation;
        result = equation.result();
        cout << result;
    }
    return 0;
}