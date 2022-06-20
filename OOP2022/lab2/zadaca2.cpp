//
// Created by kbogojoska on 19.6.2022.
//

#include <iostream>
using namespace std;

class Krug {
private:
    float radius;
    const float pi;
public:
    Krug(float radius=0.0):pi(3.14)
    {
        this->radius=radius;
    }
    float plostina()
    {
        return radius*radius*pi;
    }
    float perimetar()
    {
        return 2*radius*pi;
    }
    int ednakvi()
    {
        if(perimetar()==plostina())
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
};

int main() {
    float r;
    cin >> r;
    //instanciraj objekt od klasata Krug cij radius e vrednosta procitana od tastatura
    Krug k(r);
    cout << k.perimetar() << endl;
    cout << k.plostina() << endl;
    cout << k.ednakvi() <<endl;
    //instanciraj objekt od klasata Krug cij radius ne e definiran
    Krug z;
    return 0;
}