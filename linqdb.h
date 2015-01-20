#ifndef LINQDB_H
#define LINQDB_H

#include <iostream>
#include <vector>
#include <list>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>
#include <string>
#include "user.h"
#include "linqnet.h"
#include "privlevel.h"
#include "smartptr.h"

using std::list;
using std::vector;
using std::string;

class LinqDB {
private:
    list<SmartPtr<User> > _db;

    bool readJson();
    void read(const QJsonArray&);
    void readNet(const QJsonArray&);
    vector<QJsonObject> writeJson() const;
    void write(const vector<QJsonObject>&) const;
    vector<Message*> readMessageDb(const string&);
    void writeMessageDb(const string&) const;
public:
    LinqDB();
    ~LinqDB();
    void load();
    void save() const;
    void addUser(User*);
    void removeUser(const Username&);
    int size() const;
    User* find(const Username&) const;
    list<SmartPtr<User> >::const_iterator begin() const;
    list<SmartPtr<User> >::const_iterator end() const;
    // SmartPtr<User> operator[](const int&) const;
};
#endif