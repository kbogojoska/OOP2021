//
// Created by kbogojoska on 22.6.2022.
//

#include<iostream>
using namespace std;
//вашиот код треба да биде тука

class Vozilo
{
protected:
    double mass;
    int height;
    int width;
public:
    Vozilo(double mass=0, int width=0, int height=0)
    {
        this->mass=mass;
        this->width=width;
        this->height=height;
    }
    void setMass(double m)
    {
        this->mass=m;
    }
    double getMass()
    {
        return mass;
    }
    void setWidth(int w)
    {
        this->width=w;
    }
    int getWidth()
    {
        return width;
    }
    void setHeight(int h)
    {
        this->height=h;
    }
    int getHeight()
    {
        return height;
    }
    virtual int vratiDnevnaCena()=0;
};

class Avtomobil : public Vozilo
{
private:
    int doors;
public:
    Avtomobil(double mass=0, int width=0, int height=0, int doors=0) : Vozilo(mass,width,height)
    {
        this->doors=doors;
    }
    void setDoors(int d)
    {
        this->doors=d;
    }
    int getDoors()
    {
        return doors;
    }
    int vratiDnevnaCena()
    {
        if(doors<5)
        {
            return 100;
        }
        else
        {
            return 130;
        }
    }
};

class Avtobus : public Vozilo
{
private:
    int passengers;
public:
    Avtobus(double mass=0, int width=0, int height=0, int passengers=0) : Vozilo(mass,width,height)
    {
        this->passengers=passengers;
    }
    void setPassengers(int p)
    {
        this->passengers=p;
    }
    int getPassengers()
    {
        return passengers;
    }
    int vratiDnevnaCena()
    {
        return passengers*5;
    }
};

class Kamion : public Vozilo
{
private:
    int maxMass;
public:
    Kamion(double mass=0, int width=0, int height=0, int maxMass=0) : Vozilo(mass,width,height)
    {
        this->maxMass=maxMass;
    }
    void setMax(int max)
    {
        this->maxMass=max;
    }
    int getMax()
    {
        return maxMass;
    }
    int vratiDnevnaCena()
    {
        return (mass+maxMass)*0.02;
    }
};

class ParkingPlac
{
private:
    Vozilo **vehicles;
    int n;
public:
    ParkingPlac()
    {
        n=0;
        vehicles=new Vozilo*[0];
    }
    ~ParkingPlac()
    {
        delete [] vehicles;
    }
    ParkingPlac& operator+=(Vozilo *v)
    {
        Vozilo **tmp=new Vozilo*[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=vehicles[i];
        }
        tmp[n++]=v;
        delete [] vehicles;
        vehicles=tmp;
        return *this;
    }
    float presmetajVkupnaMasa()
    {
        float sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=vehicles[i]->getMass();
        }
        return sum;
    }
    int brojVozilaPoshirokiOd(int l)
    {
        int count=0;
        for(int i=0;i<n;i++)
        {
            if(vehicles[i]->getWidth()>l)
            {
                count++;
            }
        }
        return count;
    }
    int countAuto()
    {
        int count=0;
        for(int i=0;i<n;i++)
        {
            Avtomobil *tmp=dynamic_cast<Avtomobil*>(vehicles[i]);
            if(tmp!=0)
            {
                count++;
            }
        }
        return count;
    }
    int countBus()
    {
        int count=0;
        for(int i=0;i<n;i++)
        {
            Avtobus *tmp=dynamic_cast<Avtobus*>(vehicles[i]);
            if(tmp!=0)
            {
                count++;
            }
        }
        return count;
    }
    int countKamion()
    {
        int count=0;
        for(int i=0;i<n;i++)
        {
            Kamion *tmp=dynamic_cast<Kamion*>(vehicles[i]);
            if(tmp!=0)
            {
                count++;
            }
        }
        return count;
    }
    void pecati()
    {
        cout<<"Brojot na avtomobili e "<<countAuto()<<", brojot na avtobusi e "<<countBus()<<" i brojot na kamioni e "<<countKamion()<<"."<<endl;
    }
    int pogolemaNosivostOd(Vozilo& v)
    {
        int count=0;
        for(int i=0;i<n;i++)
        {
            Kamion *tmp=dynamic_cast<Kamion*>(vehicles[i]);
            if(tmp!=0)
            {
                if(tmp->getMax()>v.getMass())
                {
                    count++;
                }
            }
        }
        return count;
    }
    int vratiDnevnaZarabotka()
    {
        int sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=vehicles[i]->vratiDnevnaCena();
        }
        return sum;
    }
};

int main(){
    ParkingPlac p;

    int n;
    cin>>n;
    int shirina,visina, broj;
    float masa,nosivost;
    for (int i=0;i<n;i++){
        int type;
        cin>>type;
        if(type==1){
            cin>>masa>>shirina>>visina>>broj;
            Avtomobil *a=new Avtomobil(masa,shirina,visina,broj);
            p+=a;
        }
        if(type==2){
            cin>>masa>>shirina>>visina>>broj;
            p+=new Avtobus(masa,shirina,visina,broj);
        }
        if(type==3){
            cin>>masa>>shirina>>visina>>nosivost;
            p+=new Kamion(masa,shirina,visina,nosivost);
        }
    }

    p.pecati();

    cout<<"\nZarabotkata e "<<p.vratiDnevnaZarabotka()<<endl;
    cout<<"Vkupnata masa e "<<p.presmetajVkupnaMasa()<<endl;
    cout<<"Brojot poshiroki od 5 e "<<p.brojVozilaPoshirokiOd(5)<<endl;
    Avtomobil a(1200,4,3,5);
    cout<<"Brojot na kamioni so nosivost pogolema od avtomobilot e "<<p.pogolemaNosivostOd(a)<<endl;


}
