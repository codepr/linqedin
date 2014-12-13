#ifndef LINQNET_H
#define LINQNET_H

#include <map>
#include "user.h"
#include "linqdb.h"

class LinQNet {
private:
    map<SPUser*, Account*> net;
    LinqDB* db;
public:
    LinQNet();
    void addUser(const User&, const Account&);
    void delUser(const User&);
};
#endif