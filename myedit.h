#ifndef MYEDIT_H
#define MYEDIT_H

#include <QDialog>
#include <QFile>
#include <QList>//信息 容器
#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include <qDebug>
#include <QStandardItemModel>//内置表格
#include <QStandardItem>
#include <QTableView>
#include <QAbstractItemView>
#include "mycreate.h"

namespace Ui {
class myedit;
}

extern bool loginFlag;

class myedit : public QDialog
{
    Q_OBJECT

public:
    explicit myedit(QWidget *parent = 0);
    ~myedit();
    int readFromFile();
    void doQuert(QString cnt);
    void display(int raw,QStringList subs);
    void writeToFile(QString cnt);


private slots:

    void on_le_cnt_textChanged(const QString &arg1);

    void on_btn_del_clicked();

    void editItem();//槽需要实现 而信号是只需要声明 不需要实现的 实现会由MOC预处理在生成的 moc文件里去实现

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_btn_save_clicked();

    void on_myedit_finished(int result);

    void on_btn_hideColumn_clicked();

private:
    Ui::myedit *ui;
    QStandardItemModel * model;
    QList<QString> stu_lines;
    bool editFlag = 0;

};


#endif // MYEDIT_H
