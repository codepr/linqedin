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
#include "error.h"

using std::list;
using std::vector;
using std::string;

class LinqDB {
private:
    list<SmartPtr<User> > _db;
    list<Group*> _grp;

    bool readJson() throw (Error);
    void read(const QJsonArray&);
    void readNet(const QJsonArray&);
    vector<QJsonObject> writeJson() const;
    void write(const vector<QJsonObject>&, const vector<QJsonObject>&) const throw(Error);
    void readInfo(Info*, const QJsonObject&) const;
    void readGroups(const QJsonArray&) const;
    vector<QJsonObject> writeGroups() const;
    void initGroups(const QJsonArray&);
public:
    LinqDB();
    ~LinqDB();
    void load();
    void save() const;
    void addUser(User*) throw(Error);
    void removeUser(const Username&) throw(Error);
    int size() const;
    int postNumberFromGroup(const Group&) const;
    void deleteGroup(const Group&) throw(Error);
    void addGroup(const Group&) throw(Error);
    void addMemberToGroup(const Group&, const Username&);
    void removeMemberFromGroup(Group&, const Username&);
    void addPostToGroup(const Group&, const Post&);
    Username getAdmin() const throw(Error);
    list<SmartPtr<User> > db() const;
    list<Group*> allGroups() const;
    list<Post*> postsFromGroup(const Group&) const;
    const Group& findGroupByName(const string&) const throw(Error);
    Group& findGroupByName(const string&) throw(Error);
    User* find(const Username&) const;
    list<SmartPtr<User> >::const_iterator begin() const;
    list<SmartPtr<User> >::const_iterator end() const;
};
#endif
