#include <iostream>
// #include "account.h"
// #include "linqnet.h"
// #include "linqdb.h"
#include "linqclient.h"

using std::cout;
using std::endl;

int main() {
    LinqDB db; /*DB utenti*/
    // LinqNet* net = new LinqNet(); /*Rete amicizie*/
    // LinqNet* net2 = new LinqNet();
    // LinqNet* net3 = new LinqNet();
    // Username* usr = new Username("Baldaz", "password");
    // Info* uf = new UserInfo(1, "Andrea", "Baldan", "08-10-1988", "a.g.baldan@gmail.com", "via 4 novembre 12", "3450515048");
    // Username* usr2 = new Username("Pablito", "maurisio");
    // Info* uf2 = new UserInfo(1, "Pablos", "Escobar", "15-12-1923", "escobar@cartello.cb", "calle de la muerte 1", "9873478233");
    // Username* usr3 = new Username("Atilio", "piovra");
    // Info* uf3 = new UserInfo(1, "Atos", "Bierta", "15-10-1973", "atos@bierta.es", "calle de la muerte 2", "4872474213");
    // Account* acc = new Account(uf, usr, basic);
    // Account* acc2 = new Account(uf2, usr2, basic);
    // Account* acc3 = new Account(uf3, usr3, basic);
    // // cout << acc.getInfo()->getName() << endl;
    // User* s3 = new BasicUser(acc3, net3);
    // User* s2 = new BasicUser(acc2, net2);
    // User* s = new BasicUser(acc, net);
    // net->addUser(s2); /*inserisco pablo negli amici di andrea*/
    // net->addUser(s3);
    // net2->addUser(s3);
    // net3->addUser(s2);
    // db.addUser(s);
    // db.addUser(s2);
    // db.addUser(s3);
    // cout<<endl;
    // cout<<db;
    // net.delUser(s3);
    // cout << "*******" << endl;
    // cout << s->account()->username()->login().toStdString() << endl << uf->print().toStdString() << " >> " << net << endl;
    // cout << "*******" << endl;
    // cout << s2->account()->username()->login().toStdString() << endl << uf2->print().toStdString() << " >> " << net2 << endl;
    // cout << "*******" << endl;
    // cout << s3->account()->username()->login().toStdString() << endl << uf3->print().toStdString() << " >> " << net3 << endl;
    // cout << "*******" << endl;
    // db.save();
    db.load();
    cout << db;
    // Username* a = new Username("Baldaz", "password");
    // User* s = db.find(a);
    // cout << s->account()->username()->login().toStdString() << endl;
    Username* user = new Username("Baldaz", "password");
    LinqClient client(user);
    // client.displayProfile();
    return 0;
}