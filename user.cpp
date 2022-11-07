#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type) :
    name_(name), balance_(balance), type_(type)
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    std::string bal = std::to_string(int(balance_)) + ".";
    if (int(balance_*1000+0.001)%10 >= 5) bal += std::to_string((int(balance_*100+0.001)%100 + 1));
    else if (int(balance_*100+0.001)%100 == 0) bal += "00";
    else bal += std::to_string(int(balance_*100+0.001)%100);
    os << name_ << " "  << bal << " " << type_ << endl;
}
