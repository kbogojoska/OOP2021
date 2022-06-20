//
// Created by kbogojoska on 19.6.2022.
//

#include <iostream>
using namespace std;

class Agol
{
private:
    int degrees;
    int minutes;
    int seconds;
public:
    Agol(int deg=0, int min=0, int sec=0)
    {
        degrees=deg;
        minutes=min;
        seconds=sec;
    }
    void set_stepeni(int n)
    {
        degrees=n;
    }
    int getDegrees()
    {
        return degrees;
    }
    void set_minuti(int n)
    {
        minutes=n;
    }
    int getMinutes()
    {
        return minutes;
    }
    void set_sekundi(int n)
    {
        seconds=n;
    }
    int getSekundi()
    {
        return seconds;
    }
    int to_sekundi()
    {
        int s=0;
        s+=seconds;
        s+=(degrees*60+minutes)*60;
        return s;
    }
};

bool proveri(int d, int m, int s)
{
    return d<=90&&d>=0&&m<=60&&m>=0&&s<=60&&s>=0;
}


bool changeOfSeconds(Agol a, int sec){
    return a.getSekundi()!=sec;
}

int main() {

    //da se instancira objekt od klasata Agol
    int deg, min, sec;
    cin >> deg >> min >> sec;
    Agol a1(deg,min,sec);
    if (proveri(deg, min, sec)) {

        a1.set_stepeni(deg);
        a1.set_minuti(min);
        a1.set_sekundi(sec);
        cout << a1.to_sekundi();
        if (changeOfSeconds(a1,sec))
            cout << "Ne smeete da gi menuvate sekundite vo ramkite na klasata!" << endl;

    }
    if (!proveri(deg, min, sec))
    {
        cout<<"Nevalidni vrednosti za agol"<<endl;
    }

    return 0;
}