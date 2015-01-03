#ifndef GUI_LINKS_H
#define GUI_LINKS_H

#include <QStringList>
#include <QString>
#include <QListWidget>
#include "../username.h"
#include "../user.h"
#include "../linqnet.h"
#include "../linqclient.h"

class Gui_Links : public QListWidget {
    Q_OBJECT
public:
    Gui_Links(LinqClient*, QWidget* parent = 0);
    void refresh();
signals:

public slots:
    void viewContact();
private:
    LinqClient* _client;
    QString _selected;
    void createList();
};
#endif