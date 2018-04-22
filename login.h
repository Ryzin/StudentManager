#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>

#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFileDialog>

extern bool loginFlag;

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();


public slots:
    void on_loginBtn_clicked();

private slots:
    void on_pushButton_clicked();

private:
    Ui::login *ui;
    QList<QString> User_lines;
    QImage *image;
};

#endif // LOGIN_H
