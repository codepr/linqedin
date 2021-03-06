#include "linqadmin.h"
#include "utils.h"
#include <sstream>

LinqAdmin::completeRemove::completeRemove(const Username& usr, int m) : rmusr(usr), mode(m) {}
LinqAdmin::completeRemove::completeRemove(Group* gr, int m) : g(gr), mode(m) {}
LinqAdmin::completeRemove::~completeRemove() { }
void LinqAdmin::completeRemove::operator()(const SmartPtr<User>& user) const {
    switch(mode) {
        case 0:
        {
            try {
                user->removeContact(rmusr);
            }catch(Error e){}
        }
        break;
        case 1:
        {
            if(BusinessUser* ex = dynamic_cast<BusinessUser*> (&(*user))) {
                list<Group*> lu = ex->groups();
                list<Group*>::iterator it = lu.begin();
                for(; it != lu.end(); ++it) {
                    if((**it) == *g)
                        ex->removeGroup(**it);
                }
            }
        }
        break;
    }
}

LinqAdmin::adminSearch::adminSearch(const string& w) : _wanted(w){}
void LinqAdmin::adminSearch::operator()(const SmartPtr<User>& user) {
    UserInfo* uf = dynamic_cast<UserInfo*> (user->account()->info());
    _wanted = utilities::Utils::toLowerCase(_wanted);
    if(!_wanted.empty() && _wanted.at(0) == ':') {
        if(uf) {
            vector<string> skills = uf->skills();
            vector<string>::iterator itr = skills.begin();
            for(; itr < skills.end(); ++itr)
                *itr = utilities::Utils::toLowerCase(*itr);
            vector<string> input;
            vector<string>::iterator it;
            bool found = false;
            _wanted.erase(_wanted.begin());
            std::string token;
            std::istringstream ss(_wanted);
            while(std::getline(ss, token, ',')) {
                token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
                input.push_back(token);
            }
            it = input.begin();
            for(; it < input.end() && !found; ++it)
                if(std::find(skills.begin(), skills.end(), *it) != skills.end())
                    found = false;
                else found = true;
            if(!found) _result.insert(std::pair<string, string>(user->account()->username().login(), user->showInfo() + "\n" + user->net()->printHtml()));
        }
    }
    else {
        if(uf) {
            vector<string> skills = uf->skills();
            vector<string>::iterator it = skills.begin();
            for(; it < skills.end(); ++it)
                *it = utilities::Utils::toLowerCase(*it);
            string fullName = utilities::Utils::toLowerCase(uf->name() + " " + uf->surname());
            if((utilities::Utils::toLowerCase(uf->name()) == _wanted || utilities::Utils::toLowerCase(uf->surname()) == _wanted || fullName == _wanted || std::find(skills.begin(), skills.end(), _wanted) != skills.end()))
                 _result.insert(std::pair<string, string>(user->account()->username().login(), user->showInfo() + "\n" + user->net()->printHtml()));
        }
    }
}
map<string,string> LinqAdmin::adminSearch::result() const {
    return _result;
}

LinqAdmin::LinqAdmin() : _db(new LinqDB()) {}
LinqAdmin::~LinqAdmin() { delete _db; }
void LinqAdmin::insertUser(User* newuser) {
    _db->addUser(newuser);
    save();
}
list<SmartPtr<User> > LinqAdmin::listUsers() const {
    return _db->db();
}
void LinqAdmin::insertUser(const string& username, const string& password, privLevel plevel, const map<string, string>& info, int t) throw(Error) {
    if(username.empty() || password.empty()) throw Error(missingField, "Username or password missing");
    string name = "", surname = "", address = "", phone = "", website = "", email = "", bio = "", birthdate = "";
    if(t == 0) {
        name = (info.find("name"))->second;
        surname = info.find("surname")->second;
        address = info.find("address")->second;
        phone = info.find("telephone")->second;
        website = info.find("website")->second;
        email = info.find("e-mail")->second;
        birthdate = info.find("birthdate")->second;
        bio = info.find("bio")->second;
    }
    else {
        name = (info.find("name"))->second;
        surname = info.find("surname")->second;
        birthdate = info.find("birthdate")->second;
    }
    try {
        Bio b(name, surname, email, address, phone, website, QDate::fromString(QString::fromStdString(birthdate), "dd.MM.yyyy"), bio);
        Username u(username, password);
        Subscription s(plevel);
        CreditCard cd("N/A", "N/A");
        Payment p(&u, &s, &cd, true);
        Account a(&b, u, plevel);
        a.addPayment(p);
        if(plevel == basic) {
            BasicUser nu(&a);
            this->insertUser(&nu);
        }
        else if(plevel == business) {
            BusinessUser nu(&a);
            this->insertUser(&nu);
        }
        else if(plevel == executive)  {
            ExecutiveUser nu(&a);
            this->insertUser(&nu);
        }
    }catch(Error e) {throw;}
}
void LinqAdmin::removeUser(const Username& user) {
    std::for_each(_db->begin(), _db->end(), completeRemove(user));
    _db->removeUser(user);
    save();
}
void LinqAdmin::upgradeSubscription(const Username& usr, privLevel newlevel) {
    User* current = _db->find(usr);
    current->account()->setPrLevel(newlevel);
    current->account()->lastPayment()->setApprovation(true);
    current->account()->lastPayment()->setAppDate(QDate::currentDate());
    Message m(Username("Linqedin",""), current->account()->username(), "Upgrade request", "Upgrade requested succesfully approved.",false);
    current->loadInMail(m);
    save();
}
map<string,string> LinqAdmin::find(const string& s) const {
    return std::for_each(_db->begin(), _db->end(), adminSearch(s)).result();
}
Group LinqAdmin::findGroup(const string& name) const {
    return _db->findGroupByName(name);
}
list<Group*> LinqAdmin::listGroups() const {
    return _db->allGroups();
}
list<Group*> LinqAdmin::listUserGroups(const Username& u) const {
    list<Group*> ret;
    User* x = _db->find(u);
    if(BusinessUser* bu = dynamic_cast<BusinessUser*> (x))
        ret = bu->groups();
    return ret;
}
list<Post*> LinqAdmin::listPostFromGroup(const Group& g) const {
    return _db->postsFromGroup(g);
}
void LinqAdmin::deleteGroup(const string& a) {
    Group g = _db->findGroupByName(a);
    std::for_each(_db->begin(), _db->end(), completeRemove(&g));
    _db->deleteGroup(g);
    save();
}
void LinqAdmin::save() const {
    _db->save();
}