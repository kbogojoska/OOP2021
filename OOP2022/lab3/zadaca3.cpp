//
// Created by kbogojoska on 19.6.2022.
//

#include<iostream>
#include<cstring>
using namespace std;

class Category
{
private:
    char name[20];
public:
    Category()
    {
        strcpy(this->name,"unnamed");
    }
    Category(char *name)
    {
        strcpy(this->name,name);
    }
    ~Category(){}
    void print()
    {
        cout<<"Category: "<<name<<endl;
    }
};

class NewsArticle
{
private:
    Category category;
    char title[30];
public:
    NewsArticle()
    {
        strcpy(this->title,"untitled");
    }
    NewsArticle(Category category, char *title="untitled")
    {
        this->category=category;
        strcpy(this->title,title);
    }
    ~NewsArticle(){}
    void print()
    {
        cout<<"Article title: "<<title<<endl;
        category.print();
    }
};

class FrontPage
{
private:
    NewsArticle cover;
    float price;
    int editionNumber;
public:
    FrontPage()
    {
        price=0;
        editionNumber=0;
    }
    FrontPage(NewsArticle cover, float price=0, int editionNumber=0)
    {
        this->cover=cover;
        this->price=price;
        this->editionNumber=editionNumber;
    }
    ~FrontPage(){}
    void print()
    {
        cout<<"Price: "<<price<<", Edition number: "<<editionNumber<<endl;
        cover.print();
    }
};

int main() {
    char categoryName[20];
    char articleTitle[30];
    float price;
    int editionNumber;

    int testCase;
    cin >> testCase;


    if (testCase == 1) {
        int iter;
        cin >> iter;
        while (iter > 0) {
            cin >> categoryName;
            cin >> articleTitle;
            cin >> price;
            cin >> editionNumber;
            Category category(categoryName);
            NewsArticle article(category, articleTitle);
            FrontPage frontPage(article, price, editionNumber);
            frontPage.print();
            iter--;
        }
    }
    else if (testCase == 2) {
        cin >> categoryName;
        cin >> price;
        cin >> editionNumber;
        Category category(categoryName);
        NewsArticle article(category);
        FrontPage frontPage(article, price, editionNumber);
        frontPage.print();
    }// test case 3
    else if (testCase == 3) {
        cin >> categoryName;
        cin >> articleTitle;
        cin >> price;
        Category category(categoryName);
        NewsArticle article(category, articleTitle);
        FrontPage frontPage(article, price);
        frontPage.print();
    }
    else {
        FrontPage frontPage = FrontPage();
        frontPage.print();
    }
    return 0;
}