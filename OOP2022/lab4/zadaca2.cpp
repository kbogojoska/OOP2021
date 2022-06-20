//
// Created by kbogojoska on 19.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

enum Extension
{
    pdf, txt, exe
};

class File
{
private:
    char *name;
    Extension ext;
    char *owner;
    int size;
    void copy(const File &f)
    {
        this->name=new char[strlen(f.name)+1];
        strcpy(this->name, f.name);
        this->ext=f.ext;
        this->owner=new char[strlen(f.owner)+1];
        strcpy(this->owner, f.owner);
        this->size=f.size;
    }
public:
    File(char *name="", char *owner="", int size=0, Extension ext=pdf)
    {
        this->name=new char[strlen(name)+1];
        strcpy(this->name, name);
        this->ext=ext;
        this->owner=new char[strlen(owner)+1];
        strcpy(this->owner, owner);
        this->size=size;
    }
    File(const File &f)
    {
        copy(f);
    }
    File& operator=(const File &f)
    {
        if(this!=&f)
        {
            delete [] name;
            delete [] owner;
            copy(f);
        }
        return *this;
    }
    ~File()
    {
        delete [] name;
        delete [] owner;
    }
    void print()
    {
        cout<<"File name: "<<name<<".";
        switch(ext)
        {
            case 0:
                cout<<"pdf"<<endl;
                break;
            case 1:
                cout<<"txt"<<endl;
                break;
            case 2:
                cout<<"exe"<<endl;
                break;
        }
        cout<<"File owner: "<<owner<<endl;
        cout<<"File size: "<<size<<endl;
    }
    bool equals(const File & that)
    {
        return strcmp(this->name,that.name)==0&&strcmp(this->owner,that.owner)==0&&this->ext==that.ext;
    }
    bool equalsType(const File & that)
    {
        return strcmp(this->name,that.name)==0&&this->ext==that.ext;
    }
};

class Folder
{
private:
    char *directorium;
    int n;
    File *files;
public:
    Folder(const char* name)
    {
        this->directorium=new char[strlen(name)+1];
        strcpy(this->directorium,name);
        this->n=0;
        this->files=new File[0];
    }
    ~Folder()
    {
        delete [] directorium;
        delete [] files;
    }
    void print()
    {
        cout<<"Folder name: "<<directorium<<endl;
        for(int i=0;i<n;i++)
        {
            files[i].print();
        }
    }
    void add(const File & file)
    {
        File *tmp=new File[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=files[i];
        }
        tmp[n++]=file;
        delete [] files;
        files=tmp;
    }
    void remove(const File & file)
    {
        int j=0;
        File *tmp=new File[n-1];
        for(int i=0;i<n;i++)
        {
            if(!files[i].equals(file))
            {
                tmp[j++]=files[i];
            }
        }
        delete [] files;
        files=tmp;
        n=j;
    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS AND EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}