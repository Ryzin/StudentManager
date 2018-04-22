#ifndef MYCREATE_H
#define MYCREATE_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QMessageBox>//输入信息提示窗
#include <QFile>
#include <QTextStream>
#include <QIODevice>

extern bool loginFlag;

namespace Ui {
class mycreate;
}

class mycreate : public QDialog
{
    Q_OBJECT

public:
    explicit mycreate(QWidget *parent = 0);
    ~mycreate();
    void clearUserInterface();//clear type in after saving imformation
    void writeToFile(QString cnt);
    bool doQuert(QString cnt);
    int readFromFile();

private slots:
    void on_btn_ok_clicked();

    void on_cbb_yx_currentIndexChanged(int index);

    void on_cbb_school_currentIndexChanged(int index);

private:
    Ui::mycreate *ui;
    int type=1;
    QList<QString> yx_lines;
    QList<QString> zy_lines;
    QList<QString> stu_lines;
};

#endif // MYCREATE_H
