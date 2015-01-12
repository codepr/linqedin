#ifndef GUI_USERWINDOW_H
#define GUI_USERWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include "gui_overview.h"

class Gui_UserWindow : public QWidget {
    Q_OBJECT
public:
    Gui_UserWindow(QWidget* parent = 0);

private:
    QGroupBox* horizontalGroupBox;
    QGroupBox* gridGroupBox;
    enum {NumButtons = 5};
    QPushButton* buttons[NumButtons];
    Gui_Overview* layout;

    void createHorizontalGroupBox();
    void createGridGroupBox();

signals:

public slots:
    void overview();

};

#endif