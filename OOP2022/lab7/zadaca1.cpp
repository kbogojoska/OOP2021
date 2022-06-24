//
// Created by kbogojoska on 22.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class Employee
{
protected:
    char name[50];
    int years;
    int age;
public:
    Employee(char *name="", int age=0, int years=0)
    {
        strcpy(this->name,name);
        this->age=age;
        this->years=years;
    }
    virtual double plata()=0;
    virtual double bonus()=0;
    bool operator==(const Employee &e)
    {
        return this->age==e.age;
    }
    virtual ~Employee(){}
    int getAge()
    {
        return age;
    }
};

class SalaryEmployee : public Employee
{
private:
    int baseSalary;
public:
    SalaryEmployee(char *name="", int age=0, int years=0, int baseSalary=0) : Employee(name,age,years)
    {
        this->baseSalary=baseSalary;
    }
    double plata()
    {
        return baseSalary+bonus();
    }
    double bonus()
    {
        return baseSalary*(years/100.0);
    }
    ~SalaryEmployee(){}
};

class HourlyEmployee  : public Employee
{
private:
    int hourly;
    int worked;
public:
    HourlyEmployee(char *name="", int age=0, int years=0, int worked=0, int hourly=0) : Employee(name,age,years)
    {
        this->worked=worked;
        this->hourly=hourly;
    }
    double plata()
    {
        return worked*hourly+bonus();
    }
    double bonus()
    {
        if(worked>320)
        {
            return (worked-320)*hourly*0.5;
        }
        else
        {
            return 0.0;
        }
    }
    ~HourlyEmployee(){}
};

class Freelancer  : public Employee
{
private:
    int projects;
    double projectprofit[10];
public:
    Freelancer(char *name="", int age=0, int years=0, int projects=0, double *projectprofit=0) : Employee(name,age,years)
    {
        this->projects=projects;
        for(int i=0;i<projects;i++)
        {
            this->projectprofit[i]=projectprofit[i];
        }
    }
    double sum()
    {
        double d=0;
        for(int i=0;i<projects;i++)
        {
            d+=projectprofit[i];
        }
        return d;
    }
    double plata()
    {
        return sum()+bonus();
    }
    double bonus()
    {
        if(projects>5)
        {
            return (projects-5)*1000;
        }
        else
        {
            return 0.0;
        }
    }
    ~Freelancer(){}
};

class Company
{
private:
    char name[50];
    int n;
    Employee **employees;
public:
    Company(char *name="")
    {
        strcpy(this->name,name);
        this->n=0;
        this->employees=new Employee*[0];//nizata e employees ne treba *employees deka ne stavame samo eden pokazuvac
    }
    Company& operator+=(Employee *e)
    {
        Employee **tmp=new Employee*[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=employees[i];
        }
        tmp[n++]=e;
        delete [] employees;
        employees=tmp;
        return *this;
    }
    double vkupnaPlata()
    {
        double d=0;
        for(int i=0;i<n;i++)
        {
            d+=employees[i]->plata();
        }
        return d;
    }
    double filtriranaPlata(Employee * emp)
    {
        double d=0;
        for(int i=0;i<n;i++)
        {
            if(*emp==*employees[i])//ovde mora * za da se zeme vrednosta od pokazuvacot (da se derefencira)
            {
                d+=employees[i]->plata();
            }
        }
        return d;
    }
    void pecatiRabotnici()
    {
        int salary=0,hourly=0,frees=0;
        cout<<"Vo kompanijata "<<name<<" rabotat:"<<endl;
        for(int i=0;i<n;i++)
        {
            SalaryEmployee *s=dynamic_cast<SalaryEmployee *>(employees[i]);
            HourlyEmployee *h=dynamic_cast<HourlyEmployee *>(employees[i]);
            Freelancer *f=dynamic_cast<Freelancer *>(employees[i]);
            if(s!=0)
            {
                salary++;
            }
            if(h!=0)
            {
                hourly++;
            }
            if(f!=0)
            {
                frees++;
            }
        }
        cout<<"Salary employees: "<<salary<<endl;
        cout<<"Hourly employees: "<<hourly<<endl;
        cout<<"Freelancers: "<<frees<<endl;
    }
};

int main() {

    char name[50];
    cin >> name;
    Company c(name);

    int n;
    cin >> n;

    char employeeName[50];
    int age;
    int experience;
    int type;

    for (int i=0; i <n; ++i) {
        cin >> type;
        cin >> employeeName >> age >> experience;

        if (type == 1) {
            int basicSalary;
            cin >> basicSalary;
            c += new SalaryEmployee(employeeName, age, experience, basicSalary);
        }

        else if (type == 2) {
            int hoursWorked;
            int hourlyPay;
            cin >> hoursWorked >> hourlyPay;
            c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
        }

        else {
            int numProjects;
            cin >> numProjects;
            double projects[10];
            for (int i=0; i < numProjects; ++i) {
                cin >> projects[i];
            }
            c += new Freelancer(employeeName, age, experience, numProjects, projects);
        }
    }

    c.pecatiRabotnici();
    cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
    Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
    cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

    delete emp;
}