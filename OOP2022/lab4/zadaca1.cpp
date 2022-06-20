//
// Created by kbogojoska on 19.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class List
{
private:
    int *numbers;
    int n;
    void copy(const List &l)
    {
        this->n=l.n;
        this->numbers=new int[this->n];
        for(int i=0;i<n;i++)
        {
            this->numbers[i]=l.numbers[i];
        }
    }
public:
    List()
    {
        n=0;
        this->numbers=new int[0];
    }
    List(int *numbers, int n)
    {
        this->n=n;
        this->numbers=new int[this->n];
        for(int i=0;i<n;i++)
        {
            this->numbers[i]=numbers[i];
        }
    }
    List(const List &l)
    {
        copy(l);
    }
    List &operator=(const List &l)
    {
        if(this!=&l)
        {
            delete [] numbers;
            copy(l);
        }
        return *this;
    }
    ~List()
    {
        delete [] numbers;
    }
    void print()
    {
        cout<<n<<": ";
        for(int i=0;i<n;i++)
        {
            cout<<numbers[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" ";
        cout<<"average: "<<average()<<endl;
    }
    int sum()
    {
        int sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=numbers[i];
        }
        return sum;
    }
    double average()
    {
        return sum()/(double)n;
    }
    friend class ListContainer;
};

class ListContainer
{
private:
    List *lists;
    int n;
    int attempts;
    void copy(const ListContainer &lc)
    {
        this->attempts=lc.attempts;
        this->n=lc.n;
        this->lists=new List[n];
        for(int i=0;i<n;i++)
        {
            this->lists[i]=lc.lists[i];
        }
    }
public:
    ListContainer()
    {
        attempts=0;
        n=0;
        lists=new List[0];
    }
    ListContainer(const ListContainer &lc)
    {
        copy(lc);
    }
    ListContainer& operator=(const ListContainer &lc)
    {
        if(this!=&lc)
        {
            delete [] lists;
            copy(lc);
        }
        return *this;
    }
    ~ListContainer()
    {
        delete [] lists;
    }
    void print()
    {
        if(n==0)
        {
            cout<<"The list is empty"<<endl;
            return;
        }
        for(int i=0;i<n;i++)
        {
            cout<<"List number: "<<i+1<<" List info: ";
            lists[i].print();
        }
        cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
        allAttempts();
    }
    void addNewList(List l)
    {
        for(int i=0;i<n;i++)
        {
            if(lists[i].sum()==l.sum())
            {
                attempts++;
                return;
            }
        }

        List *tmp=new List[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=lists[i];
        }
        tmp[n++]=l;
        delete [] lists;
        lists=tmp;
    }
    int sum()
    {
        int sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=lists[i].sum();
        }
        return sum;
    }
    int sumOfN()
    {
        int sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=lists[i].n;
        }
        return sum;
    }
    double average()
    {
        return sum()/(double)sumOfN();
    }
    void allAttempts()
    {
        cout<<"Successful attempts: "<<n<<" Failed attempts: "<<attempts<<endl;
    }
};

int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();
    }
    else {
        lc.print();
    }
}