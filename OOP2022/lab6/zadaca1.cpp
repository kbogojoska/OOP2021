//
// Created by kbogojoska on 20.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class NBAPlayer
{
protected:
    char *name;
    char team[40];
    double averagePts;
    double averageAssist;
    double averageRebounds;

    void copy(const NBAPlayer &p)
    {
        this->name=new char[strlen(p.name)+1];
        strcpy(this->name,p.name);
        strcpy(this->team,p.team);
        this->averagePts=p.averagePts;
        this->averageAssist=p.averageAssist;
        this->averageRebounds=p.averageRebounds;
    }
public:
    NBAPlayer(char *name="", char *team="", double averagePts=0, double averageAssist=0, double averageRebounds=0)
    {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->team,team);
        this->averagePts=averagePts;
        this->averageAssist=averageAssist;
        this->averageRebounds=averageRebounds;
    }
    NBAPlayer(const NBAPlayer &p)
    {
        copy(p);
    }
    NBAPlayer& operator=(const NBAPlayer &p)
    {
        if(this!=&p)
        {
            delete [] name;
            copy(p);
        }
        return *this;
    }
    ~NBAPlayer()
    {
        delete [] name;
    }
    double rating()
    {
        return this->averagePts*0.45+this->averageAssist*0.3+this->averageRebounds*0.25;
    }
    void print()
    {
        cout<<name<<" - "<<team<<endl;
        cout<<"Points: "<<averagePts<<endl;
        cout<<"Assists: "<<averageAssist<<endl;
        cout<<"Rebounds: "<<averageRebounds<<endl;
        cout<<"Rating: "<<rating()<<endl;
    }
};

class AllStarPlayer: public NBAPlayer
{
private:
    double avgASpts;
    double avgASassist;
    double avgASreb;

public:
    AllStarPlayer(char *name="", char *team="", double averagePts=0, double averageAssist=0, double averageRebounds=0, double avgASpts=0, double avgASassist=0, double avgASreb=0) : NBAPlayer(name,team,averagePts,averageAssist,averageRebounds)
    {
        this->avgASpts=avgASpts;
        this->avgASassist=avgASassist;
        this->avgASreb=avgASreb;
    }
    AllStarPlayer(const NBAPlayer &p, double avgASpts=0, double avgASassist=0, double avgASreb=0) : NBAPlayer(p)
    {
        this->avgASpts=avgASpts;
        this->avgASassist=avgASassist;
        this->avgASreb=avgASreb;
    }
    AllStarPlayer(const AllStarPlayer &asp) : NBAPlayer(asp)
    {
        this->avgASpts=asp.avgASpts;
        this->avgASassist=asp.avgASassist;
        this->avgASreb=asp.avgASreb;
    }
    AllStarPlayer& operator=(const AllStarPlayer &asp)
    {
        if(this!=&asp)
        {
            NBAPlayer tmp(asp);
            NBAPlayer::operator=(tmp);
            this->avgASpts=asp.avgASpts;
            this->avgASassist=asp.avgASassist;
            this->avgASreb=asp.avgASreb;
        }
        return *this;
    }
    ~AllStarPlayer(){}

    double allStarRating()
    {
        return this->avgASpts*0.3+this->avgASassist*0.4+this->avgASreb*0.3;
    }
    double rating()
    {
        double tmp=0;
        tmp=NBAPlayer::rating();
        return (tmp+allStarRating())/2;
    }
    void print()
    {
        NBAPlayer::print();
        cout<<"All Star Rating: "<<allStarRating()<<endl;
        cout<<"New Rating: "<<rating()<<endl;
    }
};

int main() {

    char name[50];
    char team[40];
    double points;
    double assists;
    double rebounds;
    double allStarPoints;
    double allStarAssists;
    double allStarRebounds;

    NBAPlayer * players = new NBAPlayer[5];
    AllStarPlayer * asPlayers = new AllStarPlayer[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            players[i].print();
        }
    }
    else if (n == 2) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
        }

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            players[i].print();

        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }
    else if (n == 3) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                         allStarPoints,allStarAssists,allStarRebounds);
        }
        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }

    delete [] players;
    delete [] asPlayers;
}
