#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QtCore/QFile>
#include <QTextStream>
#include <QIODevice>
#include <QMessageBox>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->t = 0;
    ui->logout->setEnabled(false);
    ui->tableWidget->setColumnWidth(0,198);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()
{
    ui->login->setEnabled(false);
    QString id;
    QString pssword;
    id = ui->username->text();
    pssword = ui->password->text();
    this->br = new QWebView();
    this->br->show();
    this->t=0;
    this->br->load(QUrl("http://academics.gndec.ac.in"));    //Deepak tere liye ah line jo tenu chahidi c
    connect(this->br,SIGNAL(loadFinished(bool)),this,SLOT(loadComplete()));

    ui->logout->setEnabled(true);
}

void MainWindow::loadComplete()
{
    this->t++;
    if(this->br->findText("Error: Authentication Failed. Wrong/Username Password."))
    {
        QMessageBox::information(this,"oops","Wrong username or password");
        ui->login->setEnabled(true);
        ui->logout->setEnabled(false);
        //delete br;
    }
    if(t==1)
    {

        this->br->page()->currentFrame()->evaluateJavaScript(QString("document.getElementById('username').value =\"%1\";").arg(ui->username->text()));
         this->br->page()->currentFrame()->evaluateJavaScript(QString("document.getElementById('password').value =\"%1\";").arg(ui->password->text()));
         this->br->page()->currentFrame()->evaluateJavaScript(QString("document.getElementsByTagName('button')[0].click();"));

    }
    if(t==2)
    {
        this->loadComplete2();
    }
    if(t==3)
    {
        this->loadComplete3();
    }
}
void MainWindow::loadComplete2()
{
    this->br->page()->currentFrame()->evaluateJavaScript(QString("document.getElementsByTagName('button')[2].click();"));
}

void MainWindow::loadComplete3()
{


    int n;
    QString temp = this->br->page()->currentFrame()->toHtml();

    struct record
    {
        int total;
            int attended;
            int deficit;
            QString name;
    };
    record stu[20];
    QString x="he";
    QChar ch;
    int ii=0;
    while(x != "<tr class=\"warning\"><td>1</td>")
    {
        x="";
        while(temp[ii]!='\n')
        {
            x+=temp[ii];
            ii++;
        }
        ii++;
    }
    //cout<<x.toStdString();
    for(int i=0;x[x.length()-2]=='d';i++)
    {
        ch = 'a';
        while(ch != '>')
        {
            ch = temp[ii];
            ii++;
        }
        //cout<<ch.toLatin1();
        ch=temp[ii];
        ii++;
        while(ch != '<')
        {
            stu[i].name+=ch;
            ch=temp[ii];
            ii++;
        }
        //cout<<stu.name.toStdString();
        while(temp[ii]!='\n')
        {
            ii++;
        }
       // cout<<"hey";
        ii++;
        while(temp[ii]!='\n')
        {
            ii++;
        }
        ii++;
        //cout<<"hey";
        while(temp[ii]!='\n')
        {
            ii++;
        }
        ii++;
        //cout<<"hey";
        while(ch != '>')
        {
            ch=temp[ii];
            ii++;
        }
        //cout<<ch.toLatin1();
        x="a";
        //stu.total=0;
        x=temp[ii];
        //cout<<x.toStdString();
        ii++;
        while(temp[ii]!='<')
        {
            x+=temp[ii];
            ii++;
        }
        //cout<<x.toStdString();
        stu[i].total=x.toInt();
        //cout<<stu.total;
        ch = 'a';
        while(ch != '>')
        {
            ch=temp[ii];
            ii++;
        }
        ch=temp[ii];
        ii++;
        while(ch != '>')
        {
            ch=temp[ii];
            ii++;
        }
        x="a";
        x=temp[ii];
        ii++;
        while(temp[ii]!='<')
        {
            x+=temp[ii];
            ii++;
        }
        stu[i].attended=x.toInt();
        //cout<<stu.attended;
        stu[i].deficit = 3*stu[i].total-4*stu[i].attended;
        if(stu[i].deficit <0)
        {
            stu[i].deficit = stu[i].deficit/3;
        }
        //cout<<stu.deficit;
        x="";
        while(temp[ii]!='\n')
        {
            x+=temp[ii];
            ii++;
        }
        ii++;
        n=i;
       // cout<<"hey"<<endl;
}
    //cout<<n<<endl;
    ui->tableWidget->clear();
    for(int i=0;i<=n;i++)
    {

                ui->tableWidget->insertRow(i);
                ui->tableWidget->setItem(i,0,new QTableWidgetItem(stu[i].name));
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(stu[i].total)));
                ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(stu[i].attended)));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(stu[i].deficit)));
                if(stu[i].deficit>0){
                    ui->tableWidget->item(i,1)->setTextColor(Qt::red);
                    ui->tableWidget->item(i,2)->setTextColor(Qt::red);
                    ui->tableWidget->item(i,3)->setTextColor(Qt::red);
                }
                else
                {
                    if(stu[i].deficit<=0){
                        ui->tableWidget->item(i,1)->setTextColor(Qt::green);
                        ui->tableWidget->item(i,2)->setTextColor(Qt::green);
                        ui->tableWidget->item(i,3)->setTextColor(Qt::green);
                    }
                }
        //ui->listWidget->addItem(stu[i].name+"\t"+QString::number(stu[i].total)+"\t"+QString::number(stu[i].attended)+"\t"+QString::number(stu[i].deficit));
        //cout<<"hey"<<endl;
        //cout<<stu[i].name.toStdString()<<stu[i].total<<"\t"<<stu[i].attended<<"\t"<<stu[i].deficit<<endl<<endl;
    }

    this->br->hide();
    //delete br;
    //ui->login->setEnabled(true);
    ui->logout->setEnabled(true);

}

void MainWindow::on_pushButton_clicked()
{
    this->br->page()->currentFrame()->evaluateJavaScript(QString("document.getElementsByTagName('button')[1].click();"));
    connect(this->br,SIGNAL(loadFinished(bool)),this,SLOT(loadComplete3()));
}

void MainWindow::on_logout_clicked()
{
    this->br->hide();
    delete this->br;
    ui->login->setEnabled(true);
}

void MainWindow::on_password_returnPressed()
{
    this->on_login_clicked();
}
