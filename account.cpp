#include "account.h"

Account::Account() {}
Account::Account(Info* uf, Username* us, privLevel l = basic) : _info(uf), _user(us), _privilege(l) {}
Account::~Account() { delete _user; delete _info;}
Username* Account::username() const {
    return _user;
}
Info* Account::info() const {
    return _info;
}
privLevel Account::prLevel() const {
    return _privilege;
}
void Account::setInfo(Info* uf) {
    _info = uf;
}