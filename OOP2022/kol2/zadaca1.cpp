//
// Created by kbogojoska on 25.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class Book
{
protected:
    char ISBN[20];
    char title[50];
    char author[30];
    double price;
public:
    Book(char *ISBN="", char *title="", char *author="", double price=0.0)
    {
        strcpy(this->ISBN,ISBN);
        strcpy(this->title,title);
        strcpy(this->author,author);
        this->price=price;
    }
    virtual double bookPrice() = 0;
    virtual ~Book(){}

    friend ostream& operator<<(ostream& out, Book &o)
    {
        out<<o.ISBN<<": "<<o.title<<", "<<o.author<<" "<<o.bookPrice()<<endl;
        return out;
    }
    void setISBN(char *isbn)
    {
        strcpy(this->ISBN,isbn);
    }

    bool operator>(Book &b)
    {
        return price>b.price;
    }
};

class OnlineBook : public Book
{
private:
    char *url;
    int mb;
public:
    OnlineBook(char *ISBN="", char *title="", char *author="", double price=0.0, char *url="", int mb=0) : Book(ISBN,title,author,price)
    {
        this->url=new char[strlen(url)+1];
        strcpy(this->url,url);
        this->mb=mb;
    }
    OnlineBook(const OnlineBook &o)
    {
        strcpy(this->ISBN,o.ISBN);
        strcpy(this->title,o.title);
        strcpy(this->author,o.author);
        this->price=o.price;
        this->url=new char[strlen(o.url)+1];
        strcpy(this->url,o.url);
        this->mb=o.mb;
    }
    OnlineBook& operator=(const OnlineBook &o)
    {
        if(this!=&o)
        {
            delete [] url;
            strcpy(this->ISBN,o.ISBN);
            strcpy(this->title,o.title);
            strcpy(this->author,o.author);
            this->price=o.price;
            this->url=new char[strlen(o.url)+1];
            strcpy(this->url,o.url);
            this->mb=o.mb;
        }
        return *this;
    }
    ~OnlineBook()
    {
        delete [] url;
    }
    double bookPrice()
    {
        if(mb>20)
        {
            return price*1.2;
        }
        else
        {
            return price;
        }
    }
};

class PrintBook : public Book
{
private:
    double weight;
    bool isAvailable;
public:
    PrintBook(char *ISBN="", char *title="", char *author="", double price=0.0, double weight=0.0, bool isAvailable=false) : Book(ISBN,title,author,price)
    {
        this->weight=weight;
        this->isAvailable=isAvailable;
    }
    double bookPrice()
    {
        if(weight>0.7)
        {
            return price*1.15;
        }
        else
        {
            return price;
        }
    }
};

void mostExpensiveBook (Book** books, int n)
{
    cout<<"FINKI-Education"<<endl;
    int onlineC=0, printC=0;
    for(int i=0;i<n;i++)
    {
        OnlineBook *online=dynamic_cast<OnlineBook*>(books[i]);
        if(online!=0)
        {
            onlineC++;
        }
        PrintBook *print=dynamic_cast<PrintBook*>(books[i]);
        if(print!=0)
        {
            printC++;
        }
    }
    cout<<"Total number of online books: "<<onlineC<<endl;
    cout<<"Total number of print books: "<<printC<<endl;

    int idx=0;

    for(int i=1;i<n;i++)
    {
        if(books[i]->bookPrice()>books[idx]->bookPrice())
        {
            idx=i;
        }
    }
    cout<<"The most expensive book is:"<<endl;
    cout<< (*books[idx]);
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
