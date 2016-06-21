#include "adduser.h"
#include "ui_adduser.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
adduser::adduser(QSqlDatabase* obj,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adduser)
{
    ui->setupUi(this);
    db = obj;
}

adduser::~adduser()
{
    delete ui;
}

void adduser::on_SaveData_clicked()
{
    int count = 0;
    if(ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "" || ui->lineEdit_3->text() == "" ||
            ui->lineEdit_4->text() == "" || ui->lineEdit_5->text() == "")
    {
        QMessageBox::information(this,"Message", "All fields must be filled!");
    }
    else{
    QSqlQuery *query = new QSqlQuery(*db);
    query->exec("select* from users_info where Login = '" + ui->lineEdit_3->text() + "' or Email = '" + ui->lineEdit_4->text() + "'" );
    while(query->next())
    {
        count++;
    }
    if(count == 0)
    {


       query->prepare("INSERT INTO users_info (Name, Surname, Login, Email, Passvord) "
              "VALUES (?, ?, ?, ?, ?)");
       query->addBindValue(ui->lineEdit->text());
       query->addBindValue(ui->lineEdit_2->text());
       query->addBindValue(ui->lineEdit_3->text());
       query->addBindValue(ui->lineEdit_4->text());
       query->addBindValue(ui->lineEdit_5->text());
       query->exec();
       this->close();
    }
    else
        QMessageBox::information(this,"Message","The user of such data is already. Please try again");
    }


}
