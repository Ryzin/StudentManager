#include "myprint.h"//主界面信息
#include "ui_myprint.h"
#include "login.h"
#include "mycreate.h"
#include "myedit.h"

Address::Address(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Address)
{
    ui->setupUi(this);

    //Address::update();//update ui when ui is changed

    //QDialog *login=new QDialog(this);//login setting
    //
    //login->show();

    if(loginFlag==1)
        ui->label_loginMode->setText(u8"登陆状态：已登陆");
    else
        ui->label_loginMode->setText(u8"登陆状态：未登陆");

    QObject::connect(ui->action_L,SIGNAL(triggered()),this,SLOT(Login_clicked()));//trigger触发
    QObject::connect(ui->action_1,SIGNAL(triggered()),this,SLOT(mycreate_clicked()));
    QObject::connect(ui->action_V1_0_A,SIGNAL(triggered()),this,SLOT(help_about()));
    QObject::connect(ui->action_H,SIGNAL(triggered()),this,SLOT(help_detail()));
    QObject::connect(ui->action_R,SIGNAL(triggered()),this,SLOT(reset_file()));
//    QObject::connect(ui->action_L_2,SIGNAL(triggered()),this,SLOT(language_setting()));

}

Address::~Address()
{
    delete ui;
}

void Address::Login_clicked()
{
    //login *login_windows = new login(this);//点击次数多会造成内存泄漏
    //login_windows->setModal(true);//Modal Windows
    //login_windows->show();
    login l;
    l.exec();
    if(loginFlag==1)
        ui->label_loginMode->setText(u8"登陆状态：已登陆");
    else
        ui->label_loginMode->setText(u8"登陆状态：未登陆");
}

void Address::mycreate_clicked()
{
    if(loginFlag!=1)
        QMessageBox::critical(this,u8"错误",u8"还未登录账户，无法进行操作",u8"确认");
    else
    {
        mycreate a;
        a.exec();//模态窗口
    }
}

void Address::on_action_2_triggered()
{
    if(loginFlag!=1)
        QMessageBox::critical(this,u8"错误",u8"还未登录账户，无法进行操作",u8"确认");
    else
    {
        myedit q;
        q.exec();
    }
}


void Address::help_about()
{
    QMessageBox::about(this,tr(u8"关于小型学生通讯录管理系统V1.0"),
                       tr(u8"小型学生通讯录管理系统V1.0\n\n"
                          "基于Qt 5.10.1(MSVC 2017,64 bit)\t\t\t\n\n"
                          "软件最后更新于20180319\n\n"
                          "2017级 计科2班 罗佳海 吴梓祺 彭旭睿"));
}

void Address::help_detail()
{
    QMessageBox::information(this,tr(u8"帮助说明"),
    tr(u8"1.1 账户\n"
       "1.1.1 登陆。账号默认为admin，密码默认为admin\n"
       "1.1.2 注销。账号（未登录状态）后将无法进行相关操作\n"
       "1.1.3 修改密码。仅能在登陆状态下修改密码\n"
       "\n2.1 编辑\n"
       "2.1.1 添加。添加个人信息，姓名与学号在确认保存后将\n"
       "无法修改；学校、学院与专业是多级逻辑关联菜单\n"
       "2.1.2 查看。支持模糊搜索；点击表头进行升序与降序操\n"
       "作；双击单元格进行修改操作；修改后可选择是否保存；单\n"
       "击列内任一单元格，再点击“隐藏列”按钮可以隐藏当前状态\n"
       "的列;单击行内任一单元格，再点击“删除”按钮，可以删除\n"
       "行\n"
       "\n3.1 选项\n"
       "3.1.1 初始化通讯录。可以直接进行通讯录文件的初始化\n"
       "\n3.1 帮助\n"
       "3.1.1 如何使用。提供基本的帮助说明手册\n"
       "3.1.2 关于小型学生通讯录管理系统。提供版权声明与作者\n"
       "简介\n"),QMessageBox::Ok);
}

void Address::on_action_Q_triggered()
{
    close();
}

void Address::on_action_O_4_triggered()
{
    loginFlag=0;
    if(loginFlag==1)
        ui->label_loginMode->setText(u8"登陆状态：已登陆");
    else
        ui->label_loginMode->setText(u8"登陆状态：未登陆");
    QMessageBox::information(this,u8"注销",u8"该账户已注销",u8"确认");
}

void Address::reset_file()
{
    int ret = QMessageBox::question(this,u8"初始化通讯录",u8"确定要初始化通讯录吗？（该操作无法还原）",u8"确定",u8"取消");
    if(ret==0)
        QFile::remove("Stu.txt");
}

//void Address::language_setting()
//{
//    QDialog a;
//    cbb_language = new QComboBox(this);
//    cbb_language->resize(100, 20);
//    cbb_language->addItem(u8"简体中文 \ Simplified Chinese");
//    cbb_language->addItem(u8"English \ American English");
//    m_translator = new QTranslator(this);
//    connect(cbb_language, SIGNAL(activated(int)), this, SLOT(changeLanguage(int index)));
//    a.exec();
//    delete m_translator;

//    comboBox = new QComboBox(this);
//     comboBox->resize(100, 20);
//     QIcon icon1(":/new/ico/images/ftp.ico");
//     comboBox->addItem(icon1, "ftp");

//     QIcon icon2(":/new/ico/images/www.ico");
//     comboBox->addItem("www");
//     //设置列表框中选项的图标
//     comboBox->setItemIcon(1, icon2);
//     //当下拉列表框中的项重新选择时 产生一个currentIndexChanged(int index)信号 弹出一个消息框提示你重新选择了哪一项
//     connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onChanged(int)));
//     this->resize(100, 100);
//     this->setWindowTitle("QComboBoxDemo");
//}

//void Address::changeLanguage(int index)
//{
//    switch(index)
//    {
//    case 0:
//        m_translator->load("CN.qm");
//    }
//}

//void Address::paintEvent(QPaintEvent *)
//{
//    //==========实现上边角圆弧==========
//        //setWindowFlags(Qt::FramelessWindowHint);
//        QBitmap bmp(this->size());
//        bmp.fill();
//        QPainter p(&bmp);
//    //    p.setPen(Qt::NoPen);
//    //    p.setBrush(Qt::black);
//        p.setRenderHint(QPainter::Antialiasing);    //抗锯齿
//        p.drawRoundedRect(bmp.rect(), 20, 20); //四个角都是圆弧
//        //只要上边角圆弧
//        int arcR = 10;    //弧度
//        QRect rect = this->rect();
//        QPainterPath path;
//        //逆时针
//        path.moveTo(arcR, 0);
//        path.arcTo(0, 0, arcR * 2, arcR * 2, 90.0f, 90.0f);
//        path.lineTo(0, rect.height());
//        path.lineTo(rect.width(), rect.height());
//        path.lineTo(rect.width(), arcR);
//        path.arcTo(rect.width() - arcR * 2, 0, arcR * 2, arcR * 2, 0.0f, 90.0f);
//        path.lineTo(arcR, 0);
//        p.drawPath(path);
//        p.fillPath(path, QBrush(Qt::black)); //arm和windows平台没有这行代码将显示一个透明的空空的框
//        setMask(bmp);

//    //==========实现下边角圆弧==========
//    QPainter painter(this);
//    QBrush brush;
//    QImage background;
//    background.load("background_myprint.jpg");
//    brush.setTextureImage(QImage(background)); //背景图片
//    painter.setBrush(brush);
//    painter.setPen(Qt::transparent);  //边框色
//    painter.setRenderHint(QPainter::Antialiasing);//抗锯齿
//    painter.drawRoundedRect(this->rect(), arcR, arcR); //圆角像素



//}
