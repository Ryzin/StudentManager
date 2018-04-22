#ifndef ADDRESS_H
#define ADDRESS_H

#include <QMainWindow>
#include <QDialog>
#include <QMessageBox>
#include "login.h"
//#include <QComboBox>
//#include <QtGui/QIcon>
//#include <QTranslator>
#include <QPainter>
#include <QBrush>
#include <QPaintEvent>
#include <QDebug>
#include <QPixmap>
#include <QBitmap>

extern bool loginFlag;

namespace Ui {
class Address;//Address=myprint
}

class Address : public QMainWindow
{
    Q_OBJECT

public:
    explicit Address(QWidget *parent = 0);
    ~Address();

public slots:
    void Login_clicked();
    void mycreate_clicked();
    void help_about();
    void help_detail();
    void reset_file();
   // void paintEvent(QPaintEvent *);
    //void language_setting();

private slots:
    void on_action_2_triggered();
    void on_action_Q_triggered();
    void on_action_O_4_triggered();
//    void changeLanguage(int index);

private:
    Ui::Address *ui;
//    QComboBox *cbb_language;
//    QTranslator *m_translator;

};

#endif // ADDRESS_H
