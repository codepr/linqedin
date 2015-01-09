#include "linqadmin.h"

LinqAdmin::completeRemove::completeRemove(const Username& usr) : rmusr(usr) {}
LinqAdmin::completeRemove::~completeRemove() { }
void LinqAdmin::completeRemove::operator()(const SmartPtr<User>& user) const {
    user->removeContact(rmusr);
}
LinqAdmin::LinqAdmin() : _db(new LinqDB()) {}
LinqAdmin::~LinqAdmin() { delete _db; }
void LinqAdmin::insertUser(User* newuser) {
    _db->addUser(newuser);
    save();
}
void LinqAdmin::removeUser(const Username& user) {
    std::for_each(_db->begin(), _db->end(), completeRemove(user));
    _db->removeUser(user);
    save();
}
void LinqAdmin::alterSubscription(const Username& usr, privLevel newlevel) {
    User* current = _db->find(usr);
    current->account()->setPrLevel(newlevel);
    save();
}
void LinqAdmin::find() const {}
void LinqAdmin::save() const {
    _db->save();
}