#include "login.h"//登陆信息
#include "ui_login.h"
#include <QInputDialog>
#include <QTextStream>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //ui->loginBtn->button(QDialogButtonBox::Ok)->setText(u8"确定");
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);//hide password
    ui->pwdLineEdit->setFocus();//将光标转到用户名输入框
    ui->loginBtn->setDefault(1);
    QObject::connect(ui->loginBtn,SIGNAL(triggered()),this,SLOT(on_loginBtn_clicked()));

    this->image = new QImage();//头像
    //QString fileName = QFileDialog::getOpenFileName(this, "open image file",".","Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
//        if(fileName != "")
//        {
            if(image->load("imageHead.gif"))
            {
                QGraphicsScene *scene = new QGraphicsScene;
                scene->addPixmap(QPixmap::fromImage(*image));
                ui->graphicsView->setScene(scene);
                //setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;");//圆角控件
                ui->graphicsView->setStyleSheet("background: transparent");//set background to transparent
                ui->graphicsView->resize(image->width(), image->height());
                //in ui designer,frame set
                ui->graphicsView->show();
            }
//        }
}

login::~login()
{
    delete image;
    delete ui;
}

void login::on_loginBtn_clicked()
{
    QFile file("User.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this,u8"错误",u8"账户文件丢失",u8"确定");
        return;
    }

    QTextStream in(&file);

    while(!in.atEnd())
    {
        QString Userlines = in.readLine();
        User_lines.append(Userlines);
    }

    file.close();

    QString line= User_lines.at(0);
    line = line.trimmed();
    QStringList subs = line.split(" ");
    QString usrn=subs.at(0);
    QString pwd=subs.at(1);


    if(ui->usrLineEdit->text().trimmed()==(usrn)&&ui->pwdLineEdit->text()==(pwd))//judget username and password. "text().trimmed()" to skip 'space' of the front or end of username
    {
        accept();
        loginFlag=1;
    }
    else
    {
        QMessageBox::warning(this,tr(u8"提示"),tr(u8"账户或密码错误！"),QMessageBox::Ok);//如果不正确，弹出警告对话框
        //ui->usrLineEdit->clear();//清空用户名输入框
        ui->pwdLineEdit->clear();//清空密码输入框
        ui->pwdLineEdit->setFocus();//将光标转到用户名输入框
        ui->loginBtn->setDefault(1);
    }
}

void login::on_pushButton_clicked()
{
    if(loginFlag!=1)
    {
        QMessageBox::critical(this,u8"错误",u8"还未登录账户，无法进行操作",u8"确认");
        ui->loginBtn->setDefault(1);
    }
    else
    {   bool OK=false;
        QString pwd = QInputDialog::getText(NULL,u8"密码",u8"请输新密码",QLineEdit::PasswordEchoOnEdit,NULL,&OK);
        if(OK&&pwd=="")
        {
            QMessageBox::critical(this,u8"错误",u8"密码不能为空！",u8"确定");
        }
        else if(OK)
        {
            QFile file("User.txt");
        if(!file.open(QIODevice::WriteOnly))
            {
            QMessageBox::critical(this,u8"错误",u8"账户文件丢失",u8"确定");
            ui->usrLineEdit->setFocus();
            ui->loginBtn->setDefault(1);
            return;
            }


        QTextStream out(&file);

        out<<"admin "+pwd;

        file.close();
        }

        ui->loginBtn->setDefault(1);
//        QMessageBox leBox;
//              leBox.setWindowTitle(u8"管理账户");
//              leBox.setInformativeText(u8"请输入新用户名");
        //      msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);//static
        //      QPushButton *cbtn = msgBox.addButton(u8"确定",QMessageBox::AcceptRole);
        //      msgBox.setDefaultButton(cbtn);//default Button
        //      msgBox.addButton(u8"取消",QMessageBox::RejectRole);
    }
}
