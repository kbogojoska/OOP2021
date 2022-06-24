//
// Created by kbogojoska on 22.6.2022.
//

#include <iostream>

using namespace std;

class Shape {
public:
    virtual void draw() {
        cout << "Drawing a shape.\n";
    }
};

// креирајте класа Rectangle која наследува од Shape
class Rectangle : public Shape
{
    // во неа препокријте ја функцијата draw() така што ќе се испечати: "Drawing a rectangle.\n"
    void draw() {
        cout << "Drawing a rectangle.\n";
    }
};

int main() {
    Shape* shape;

    // тука инстанцирајте објект од класата Shape и покажувачот shape нека покажува кон него
    shape=new Shape();
    shape->draw();
    delete shape;
    shape=0;

    // сега инстанцирајте објект од класата Rectangle и покажувачот shape нека покажува кон него
    // повторно повикајте ја функцијата draw() на shape
    shape=new Rectangle();
    shape->draw();
    delete shape;
    shape=0;

    return 0;
}