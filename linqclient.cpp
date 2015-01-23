#include "linqclient.h"

using std::map;

LinqClient::LinqClient() : _db(new LinqDB()), _avatar(STANDARD_AVATAR) {}
LinqClient::LinqClient(const Username& usr) : _db(new LinqDB), _avatar(STANDARD_AVATAR)  {
    _usr = _db->find(usr);
}
LinqClient::~LinqClient() {delete _db;}
void LinqClient::addContact(const Username& usr) {
    _usr->addContact(_db->find(usr));
}
void LinqClient::removeContact(const Username& usr) {
    _usr->removeContact(usr);
}
string LinqClient::displayProfile() const {
    std::string profile = "";
    std::ostringstream o, o2;
    o << _usr->account()->prLevel();
    o2 << *_usr->net();
    profile += "Account type >> " + o.str() + "\n";
    profile += "Credentials >> user: " + _usr->account()->username().login() + "  password: " + _usr->account()->username().password() + "\n";
    profile += "Account info >> " + _usr->account()->info()->print() + "\n";
    profile += "Friend list >> ";
    profile += o2.str() + "\n";
    profile += "inMail >> ";
    list<Message*> inm = _usr->inMail();
    list<Message*> outm = _usr->outMail();
    list<Message*>::const_iterator it = inm.begin();
    for(; it != inm.end(); ++it)
        profile += "Sender: " + (*it)->sender().login() + " Receiver: " + (*it)->receiver().login() + "\n";
    return profile;
}
string LinqClient::displayHtmlInfo() const {
    return _usr->account()->info()->printHtml();
}
string LinqClient::displayHtmlPayments() const {
    vector<SmartPtr<Payment> > v = _usr->account()->history();
    return "<html><table><tr><th style='padding:10px;'>Subscription</th><th style='padding:10px;'>Method</th><th style='padding:10px'>Amount</th></tr></table></html>";
}
string LinqClient::displayHtmlSettings() const {
    string html = "";
    html = "<html>";
    html += "<h3> Username</h3><p style='font-weight:400;'>" + _usr->account()->username().login() + "</p>";
    html += "<h3> Account type</h3><p style='font-weight:400;'>" + utilities::Utils::levelToString(_usr->account()->prLevel()) + "</p></html>";
    return html;
}
string LinqClient::displayHtmlMessages() const {
    return "<html><table><tr><th style='padding:10px;'>Subject</th><th style='padding:10px;'>Body</th><th style='padding:10px'>From</th></tr></table></html>";
}
int LinqClient::netSize() const {
    return _usr->net()->size();
}
vector<SmartPtr<User> > LinqClient::similarity() const {
    // ExecutiveUser* eu = dynamic_cast<ExecutiveUser*> (_usr);
    return _usr->listPossibleLinks(*_db);
}
bool LinqClient::linked(const Username& usr) const {
   return _usr->linked(usr);
}
vector<string> LinqClient::skills() const {
    vector<string> ret;
    if(UserInfo* p = dynamic_cast<UserInfo*> (_usr->account()->info()))
        ret = p->skills();
    return ret;
}
vector<string> LinqClient::interests() const {
    vector<string> ret;
    if(UserInfo* p = dynamic_cast<UserInfo*> (_usr->account()->info()))
        ret = p->interests();
    return ret;
}
vector<string> LinqClient::displayHtmlNet() const {
    vector<string> ret;
    string html = "";
    std::ostringstream o;
    o << _usr->net()->size();
    UserInfo* info;
    string name, surname;
    vector<Username> vec = _usr->net()->username();
    vector<Username>::const_iterator it = vec.begin();
    for(; it < vec.end(); ++it) {
        info = dynamic_cast<UserInfo*> ((_db->find(*it))->account()->info());
        if(info) {
            name = info->name();
            surname = info->surname();
        }
        html = name + " " + surname;
        ret.push_back(html);
    }
    return ret;
}
vector<SmartPtr<User> > LinqClient::contactsInfo() const {
    vector<SmartPtr<User> > ret;
    vector<Username> vec = _usr->net()->username();
    vector<Username>::const_iterator it = vec.begin();
    User* acc;
    for(; it < vec.end(); ++it) {
        acc = _db->find(*it);
        ret.push_back(SmartPtr<User>(acc));
    }
    return ret;
}
map<string, string> LinqClient::find(const string& wanted = "") const {
    return _usr->userSearch(*_db, wanted);
}
map<string, int> LinqClient::keywordFrequency() const {
    ExecutiveUser* tmp = dynamic_cast<ExecutiveUser*> (_usr);
    map<string, int> ret;
    if(tmp) {
        ret = tmp->keywordPercent();
        // std::sort(ret.begin(), ret.end(), value_compare);
        return ret;
    }
}
void LinqClient::addExperience(const Experience& xp) {
    UserInfo* uf = dynamic_cast<UserInfo*> (_usr->account()->info());
    if(uf) uf->addExperience(xp);
}
void LinqClient::addVisitTo(const Username& usr) {
    User* u = _db->find(usr);
    u->addVisit();
}
void LinqClient::save() const {
    _db->save();
}
string LinqClient::avatar() const {
    return _avatar;
}
void LinqClient::setAvatar(const string& path) {
    _avatar = path;
}
int LinqClient::visitCount() const {
    return _usr->visitCount();
}