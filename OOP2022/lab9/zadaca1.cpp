//
// Created by kbogojoska on 24.6.2022.
//

#include<iostream>
#include<cstring>

using namespace std;

class InvalidPasswordException
{
public:
    void message()
    {
        cout<<"Password is too weak."<<endl;
    }
};

class InvalidEmailException
{
public:
    void message()
    {
        cout<<"Mail is not valid."<<endl;
    }
};

class MaximumSizeLimitException
{
private:
    int n;
public:
    MaximumSizeLimitException(int n)
    {
        this->n=n;
    }
    void message()
    {
        cout<<"You can't add more than "<<n<<" users."<<endl;
    }
};

class User
{
protected:
    char username[50];
    char password[50];
    char email[50];
public:
    User(char *username="", char *password="",char *email="")
    {
        strcpy(this->username,username);

        int bigLetter=0;
        int smallLetter=0;
        int isNumber=0;
        for(int i=0; i<strlen(password); i++)
        {
            if(password[i]>='0'&&password[i]<='9')
            {
                isNumber=1;
            }
            if(password[i]>='a'&&password[i]<='z')
            {
                smallLetter=1;
            }
            if(password[i]>='A'&&password[i]<='Z')
            {
                bigLetter=1;
            }
        }
        if(!bigLetter||!smallLetter||!isNumber)
        {
            throw InvalidPasswordException();
        }
        strcpy(this->password,password);

        int atCount=0;
        for(int i=0; i<strlen(email); i++)
        {
            if(email[i]=='@')
            {
                atCount++;
            }
        }
        if(atCount!=1)
        {
            throw InvalidEmailException();
        }
        strcpy(this->email,email);
    }
    virtual double popularity() = 0;
};

class FacebookUser : public User
{
private:
    int friends;
    int likes;
    int comments;
    static double LIKE_COEF;
    static double COMMENT_COEF;
public:
    FacebookUser(char *username="", char *password="",char *email="", int friends=0, int likes=0, int comments=0) : User(username,password,email)
    {
        this->friends=friends;
        this->likes=likes;
        this->comments=comments;
    }
    double popularity()
    {
        return friends+likes*LIKE_COEF+comments*COMMENT_COEF;
    }
};

double FacebookUser::LIKE_COEF=0.1;
double FacebookUser::COMMENT_COEF=0.5;

class TwitterUser : public User
{
private:
    int followers;
    int tweets;
    static double TWEET_COEF;
public:
    TwitterUser(char *username="", char *password="",char *email="", int followers=0, int tweets=0) : User(username,password,email)
    {
        this->followers=followers;
        this->tweets=tweets;
    }
    double popularity()
    {
        return followers+tweets*TWEET_COEF;
    }
};

double TwitterUser::TWEET_COEF=0.5;

class SocialNetwork
{
private:
    User **users;
    int n;
    static int MAX_USERS;
public:
    SocialNetwork()
    {
        users=new User*[0];
        n=0;
    }
    SocialNetwork(const SocialNetwork &s)
    {
        n=s.n;
        users=new User*[n];
        for(int i=0; i<n; i++)
        {
            users[i]=s.users[i];
        }

    }
    ~SocialNetwork()
    {
        delete [] users;
    }
    SocialNetwork& operator+=(User *u)
    {
        if(n==MAX_USERS)
        {
            throw MaximumSizeLimitException(n);
        }
        User **tmp=new User*[n+1];
        for(int i=0; i<n; i++)
        {
            tmp[i]=users[i];
        }
        tmp[n++]=u;
        delete [] users;
        users=tmp;
        return *this;
    }
    double avgPopularity()
    {
        double sum=0.0;
        for(int i=0; i<n; i++)
        {
            sum+=users[i]->popularity();
        }
        return sum/n;
    }
    void changeMaximumSize(int number)
    {
        MAX_USERS=number;
    }
};

int SocialNetwork::MAX_USERS=5;

int main() {

    SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i=0; i < n; ++i) {
        cin >> username;
        cin >> password;
        cin >> email;
        cin >> userType;
        if (userType == 1) {
            int friends;
            int likes;
            int comments;
            cin >> friends >> likes >> comments;

            // TODO: Try-catch
            try
            {
                User * u = new FacebookUser(username,password,email,friends,likes,comments);
                network += u;
            }
            catch(InvalidPasswordException i)
            {
                i.message();
            }
            catch(InvalidEmailException e)
            {
                e.message();
            }
            catch(MaximumSizeLimitException &s)
            {
                s.message();
            }


        }
        else {
            int followers;
            int tweets;
            cin >> followers >> tweets;

            // TODO: Try-catch
            try
            {
                User * u= new TwitterUser(username,password,email,followers,tweets);
                network += u;
            }
            catch(InvalidPasswordException i)
            {
                i.message();
            }
            catch(InvalidEmailException e)
            {
                e.message();
            }
            catch(MaximumSizeLimitException &s)
            {
                s.message();
            }

        }

    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;

    // TODO: Try-catch
    try
    {
        User * u= new TwitterUser(username,password,email,followers,tweets);
        network += u;
    }
    catch(InvalidPasswordException i)
    {
        i.message();
    }
    catch(InvalidEmailException e)
    {
        e.message();
    }
    catch(MaximumSizeLimitException &s)
    {
        s.message();
    }


    cout << network.avgPopularity();

}
