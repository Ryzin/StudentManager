#include "mycreate.h"//创建通讯录信息
#include "ui_mycreate.h"

mycreate::mycreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mycreate)
{
    ui->setupUi(this);
    this->ui->rbtn_male->setChecked(true);//默认为男
}

mycreate::~mycreate()
{
    delete ui;
}

void mycreate::on_btn_ok_clicked()
{
    QString name = this->ui->le_name->text();
    QString id = this->ui->le_id->text();
    QString pnum = this->ui->le_pnum->text();
    QString sex = this->ui->sexGroup->checkedButton()->text();
    QString school = this->ui->cbb_school->currentText();
    QString yx = this->ui->cbb_yx->currentText();
    QString zy = this->ui->cbb_zy->currentText();
    QString bz = this->ui->te_other->toPlainText();

    //qDebug()<<name;
    //qDebug()<<id;
    //qDebug()<<pnum;

//    QMessageBox msgBox;
//      msgBox.setWindowTitle(u8"请确认信息");
//      msgBox.setInformativeText(u8"姓名 "+name+'\n'+u8"学号 "+id+'\n'+u8"电话 "+pnum+'\n');
//      msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);//static
//      QPushButton *cbtn = msgBox.addButton(u8"确定",QMessageBox::AcceptRole);
//      msgBox.setDefaultButton(cbtn);//default Button
//      msgBox.addButton(u8"取消",QMessageBox::RejectRole);
    if(pnum.length()<1)
        pnum=u8"无";
    if(school==u8"请选择学校")
        school=u8"无";
    if(yx==u8"请选择学院")
        yx=u8"无";
    if(zy==u8"请选择专业")
        zy=u8"无";
    if(bz.length()<1)
        bz=u8"无";

    QString content = u8"姓名 "+name+'\n'+u8"学号 "+id+'\n'+u8"性别 "+sex+'\n'+u8"电话 "+pnum+'\n'+u8"学校 "+school+'\n'+u8"学院 "+yx+'\n'+u8"专业 "+zy+'\n'+u8"备注 "+bz+'\n';
    QString cnt = name+" "+id+" "+sex+" "+pnum+" "+school+" "+yx+" "+zy+" "+bz+'\n';//file content

    if(name.length()<1||id.length()<11||doQuert(id))
    {
        QMessageBox::critical(this,u8"错误",u8"信息填写不完整、信息格式错误或此学号已存在，请重新填写",u8"确定");
    }
    else
    {
        int ret = QMessageBox::question(this,u8"请确认信息",content,u8"确定",u8"取消");//return a type
        if(ret==0)
        {
            clearUserInterface();
            writeToFile(cnt);
        }

    }
}

void mycreate::clearUserInterface()
{
    this->ui->le_name->clear();
    this->ui->le_id->clear();
    this->ui->le_pnum->clear();
    this->ui->te_other->clear();
    this->ui->cbb_school->setCurrentIndex(0);
    this->ui->rbtn_male->setChecked(true);

    this->ui->le_name->setFocus();//reset name focus
}

void mycreate::writeToFile(QString cnt)
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

void mycreate::on_cbb_school_currentIndexChanged(int index)//一级cbb_school
{
    type = index;
    QFile file("yx.txt");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::critical(this,u8"错误",u8"二级菜单文件打开失败，请重试",u8"确认");
            this->close();
        }

        QTextStream in(&file);

        while(!in.atEnd())//文件末尾
        {
            QString line = in.readLine();//read a line
            yx_lines.append(line);//存放在QList的单独一行
        }

        file.close();

    ui->cbb_yx->clear();

    QString yx;
    QStringList subs;

    yx= yx_lines.at(index);//file each line
    yx = yx.trimmed();//delete line ending meanless space
    subs = yx.split(" ");//line content can be split into subs and use space to isolate
    for(int i=0;i<subs.count();++i)
       ui->cbb_yx->addItem(subs.at(i));
}

void mycreate::on_cbb_yx_currentIndexChanged(int index)//二级cbb_zy
{
//    if (sender() == ui->cbb_yx)
//        {
//            ui->cbb_zy->clear();
//            ui->cbb_zy->blockSignals(true);
//            ui->cbb_zy->setCurrentIndex(index);
//            ui->cbb_zy->blockSignals(false);
//        }
//    else if (sender() == ui->cbb_zy)
//        {
//            ui->cbb_yx->blockSignals(true);
//            ui->cbb_yx->setCurrentIndex(index);
//            ui->cbb_yx->blockSignals(false);
//        }

    QFile file("zy.txt");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::critical(this,u8"错误",u8"三级菜单文件打开失败，请重试",u8"确认");
            this->close();
        }

        QTextStream in(&file);

        while(!in.atEnd())//文件末尾
        {
            QString line = in.readLine();//read a line
            zy_lines.append(line);//存放在QList的单独一行
        }

        file.close();

       ui->cbb_zy->clear();
     if(ui->cbb_yx->currentText()==u8"其它")
          ui->cbb_zy->addItem(u8"其它");
     else
      {
       QString zy;
       QStringList subs;

       switch(type)
       {
        case 0:
           ui->cbb_zy->addItem(u8"请选择专业");
           break;
        case 1:
           zy = zy_lines.at(index+1);//file each line
           zy = zy.trimmed();//delete line ending meanless space
           subs = zy.split(" ");//line content can be split into subs and use space to isolate
           for(int i=0;i<subs.count();++i)
              ui->cbb_zy->addItem(subs.at(i));
           break;
       case 2:
           zy = zy_lines.at(index+12+1);//file each line
           zy = zy.trimmed();//delete line ending meanless space
           subs = zy.split(" ");//line content can be split into subs and use space to isolate
           for(int i=0;i<subs.count();++i)
              ui->cbb_zy->addItem(subs.at(i));
           break;
       case 3:
           zy = zy_lines.at(index+23+1);//file each line
           zy = zy.trimmed();//delete line ending meanless space
           subs = zy.split(" ");//line content can be split into subs and use space to isolate
           for(int i=0;i<subs.count();++i)
              ui->cbb_zy->addItem(subs.at(i));
           break;
       default:
           ui->cbb_zy->addItem(u8"其它");
           break;
       }
      }
}

int mycreate::readFromFile()
{
    QFile file("stu.txt");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return -1;
        }

        QTextStream in(&file);

        stu_lines.clear();//reset stu_lines first

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


bool mycreate::doQuert(QString cnt)
{
    if(readFromFile()==-1)
       {
           QMessageBox::critical(this,u8"错误",u8"文件打开失败或通讯录为空，请重试",u8"确认");
           this->close();
       }

        int i=0;
        for(i=0;i<stu_lines.length();i++)
        {
            QString line= stu_lines.at(i);//file each line
            line = line.trimmed();//delete line ending meanless space
            QStringList subs = line.split(" ");//line content can be split into subs and use space to isolate
            if(cnt==subs.at(1))//has id existed?
            {
                qDebug()<<"wa";
                return true;
            }
        }
        qDebug()<<"van";
           return false;
}

