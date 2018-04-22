#include "myedit.h"
#include "ui_myedit.h"
#include <qDebug>
#include <QCollator>
#include <QLocale>

myedit::myedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myedit)
{
    ui->setupUi(this);

    if(readFromFile()==-1)//在构造函数处读取 即一点击菜单栏的查询就提前读取文件
       {
           QMessageBox::critical(this,u8"错误",u8"文件打开失败或通讯录为空，请重试",u8"确认");
           this->close();
       }

       this->model=new QStandardItemModel;//Model View Control中的内容 Model

        doQuert("");

       //设置水平表头
       this->model->setHorizontalHeaderItem(0,new QStandardItem(u8"姓名"));
       this->model->setHorizontalHeaderItem(1,new QStandardItem(u8"学号"));
       this->model->setHorizontalHeaderItem(2,new QStandardItem(u8"性别"));
       this->model->setHorizontalHeaderItem(3,new QStandardItem(u8"电话"));
       this->model->setHorizontalHeaderItem(4,new QStandardItem(u8"学校"));
       this->model->setHorizontalHeaderItem(5,new QStandardItem(u8"学院"));
       this->model->setHorizontalHeaderItem(6,new QStandardItem(u8"专业"));
       this->model->setHorizontalHeaderItem(7,new QStandardItem(u8"备注"));

       this->ui->tableView->setModel(model);//View

       connect(this->model,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(editItem()));//connect after setmodel

       this->ui->tableView->setColumnWidth(0,100);
       this->ui->tableView->setColumnWidth(1,150);
       this->ui->tableView->setColumnWidth(2,50);
       this->ui->tableView->setColumnWidth(3,150);
       this->ui->tableView->setColumnWidth(4,250);
       this->ui->tableView->setColumnWidth(5,200);
       this->ui->tableView->setColumnWidth(6,300);
       this->ui->tableView->setColumnWidth(7,320);

       ui->tableView->setAlternatingRowColors(1);//隔行变色
       ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//点击选择行
       ui->tableView->setSortingEnabled(1);//表头排序 字典序
       editFlag = 0;
}

myedit::~myedit()
{
    delete ui;
}


int myedit::readFromFile()
{
    QFile file("stu.txt");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return -1;
        }

        QTextStream in(&file);

        while(!in.atEnd())//文件末尾
        {
            QString line = in.readLine();//read a line
            stu_lines.append(line);//存放在QList的单独一行
        }

        file.close();

    //    int i=0;
    //    for(i=0;i<stu_lines.length();i++)
    //    {
    //        qDebug()<<stu_lines.at(i);
    //    }

        return 0;

}

void myedit::doQuert(QString cnt)
{
        int i=0;
        int row=0;
        for(i=0;i<stu_lines.length();i++)
        {
            QString line= stu_lines.at(i);//file each line
            line = line.trimmed();//delete line ending meanless space
            QStringList subs = line.split(" ");//line content can be split into subs and use space to isolate
            if(line.contains(cnt,Qt::CaseSensitive))//返回true;
                display(row++,subs);//subs中符合的话 view行数row可加
        }
}

void myedit::display(int raw,QStringList subs)
{
    int i=0;
    for(i=0;i<8;i++)
    {
        this->model->setItem(raw,i,new QStandardItem(subs.at(i)));
    }

}

void myedit::on_le_cnt_textChanged(const QString &arg1)
{
    this->model->clear();//when search again

    this->model->setHorizontalHeaderItem(0,new QStandardItem(u8"姓名"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem(u8"学号"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem(u8"性别"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem(u8"电话"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem(u8"学校"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem(u8"学院"));
    this->model->setHorizontalHeaderItem(6,new QStandardItem(u8"专业"));
    this->model->setHorizontalHeaderItem(7,new QStandardItem(u8"备注"));

    this->ui->tableView->setColumnWidth(0,100);
    this->ui->tableView->setColumnWidth(1,150);
    this->ui->tableView->setColumnWidth(2,50);
    this->ui->tableView->setColumnWidth(3,150);
    this->ui->tableView->setColumnWidth(4,250);
    this->ui->tableView->setColumnWidth(5,200);
    this->ui->tableView->setColumnWidth(6,300);
    this->ui->tableView->setColumnWidth(7,320);
    //connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_sortByColumn(int)));
    //int index = this->ui->cbb_method->currentIndex();//search type
    QString cnt = this->ui->le_cnt->text();//search content
    doQuert(cnt);
}

void myedit::on_btn_del_clicked()
{
    editFlag = 1;

    int newRow = this->ui->tableView->currentIndex().row();//当前行
   // qDebug()<<newRow;
    QString newId = this->model->data(model->index(newRow,1)).toString();
    QString lastLine= stu_lines.at(stu_lines.length()-1);
    QStringList lastLineSubs = lastLine.split(" ");
//    qDebug()<<stu_lines.length();
//    qDebug()<<line;
//    qDebug()<<newId;
//    qDebug()<<subs.at(1);
    if(newId==lastLineSubs.at(1))//if the removedRow is the last Row
    {
        stu_lines.removeAt(stu_lines.length()-1);
    }
    else
    {
        int trueRow = 0;//the true row in file
        for(int i=0;i<stu_lines.length();++i)
        {
            QString line= stu_lines.at(i);
            line = line.trimmed();
            QStringList subs = line.split(" ");
            if(newId==subs.at(1))
            {
                trueRow = i;//find trueRow
            }
        }
        //qDebug()<<stu_lines.at(newRow);
        stu_lines.replace(trueRow,lastLine);//just let the last Row replace the removeRow
       // qDebug()<<stu_lines.at(newRow);
        stu_lines.removeAt(stu_lines.length()-1);
    }
    model->removeRow(newRow);
}

void myedit::editItem()
{
    editFlag = 1;
    int newRow = this->ui->tableView->currentIndex().row();
    int newColumn = this->ui->tableView->currentIndex().column();
    QString changedItem=model->data(model->index(newRow,newColumn)).toString();//the new item
    int i=0;

    //replace newline to line
    for(i=0;i<stu_lines.length();++i)
    {
        QString newId = this->model->data(model->index(newRow,1)).toString();
        QString line= stu_lines.at(i);
        line = line.trimmed();
        QStringList subs = line.split(" ");
        if(newId==subs.at(1))//返回true;
        {
            subs.replace(newColumn,changedItem);
            line = subs.join(" ");
            stu_lines.replace(i,line);
            break;
        }
    }
}

void myedit::writeToFile(QString cnt)
{
    QFile file("Stu.txt");
    if(!file.open(QIODevice::Append | QIODevice::Text))//can not open file successfully
    {
        QMessageBox::critical(this,u8"错误",u8"文件未能正确打开",u8"确定");
        return;
    }
    QTextStream out(&file);//out to file
    out<<cnt;
    file.close();
}

void myedit::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(this->ui->tableView->currentIndex().column()==0||this->ui->tableView->currentIndex().column()==1)
    {
        QMessageBox::critical(this,u8"错误",u8"姓名或学号不允许编辑\n如想修改，请重新添加此个人信息",u8"确定");
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
    else
         ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
}

void myedit::on_btn_save_clicked()
{
    int ret = QMessageBox::question(this,u8"保存",u8"是否保存当前内容？",u8"确定",u8"取消");
    if(ret==0)
      {
         editFlag = 0;
         QFile::remove("Stu.txt");
         int i=0;
         for(i=0;i<stu_lines.length();++i)
         {
             QString cnt = stu_lines.at(i)+'\n';//file content
             writeToFile(cnt);
         }
      }
}

void myedit::on_myedit_finished(int result)
{
    if(editFlag==1)
        on_btn_save_clicked();
}

void myedit::on_btn_hideColumn_clicked()
{
    int column = this->ui->tableView->currentIndex().column();
    ui->tableView->setColumnHidden(column,true);
}

