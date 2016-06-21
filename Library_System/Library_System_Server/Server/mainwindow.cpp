#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <socketserver.h>
#include <windows.h>
#include "serverthread.h"

#include <QSqlQuery>
#include <QDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Passvord->setEchoMode(QLineEdit::Password);
    server = new SocketServer();
    server->InitializeSocket();
    server->BindSocket();
    server->ListhenSocket();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Connect_clicked()  // connect to database
{
        db =  QSqlDatabase::addDatabase("QMYSQL");
        db.setDatabaseName("ipz_user");
       //db.setHostName("127.0.0.0");
        //db.setPort(3306);
        db.setUserName("root");
        db.setPassword("root");
        if(db.open())
        {
                ui->Status->setText("Connect success;");
        }
        else
        {
            ui->Status->setText("Connect fail;");
        }
    }



void MainWindow::on_DataBaseUser_button_clicked() // show the database users
{
        model =  new QSqlTableModel(this,db);
        model->setTable("users_info");
        model->select();
        ui->Table->setModel(model);

}



void MainWindow::on_ShowDataBaseBook_button_clicked() //show database books
{
    model =  new QSqlTableModel(this,db);
    model->setTable("books_info");
    model->select();
    ui->Table->setModel(model);
}



void MainWindow::on_Authorization_button_clicked()
{
    int count = 0;
    QSqlQuery * query = new QSqlQuery(db);
    query->exec("select* from users_info where Login = '" + ui->Login->text()+ "' and Passvord = '" + ui->Passvord->text() + "'");
    while(query->next())
    {
        count++;
    }
    if(count != 0)
    {
        QMessageBox::information(this,"Message", "Authorization successful");
    }
    else
        QMessageBox::information(this,"Message", "Invalid password or username");
}

void MainWindow::on_Start_Server_button_clicked() // server start working
{
    server->DBtoSock(&db);
    ServerThread* Thread = new ServerThread(server);
    Thread->start();

}

void MainWindow::on_add_new_user_push_button_clicked()
{
    adduser *add =  new adduser(&db,this);
    this->close();
    add->exec();
    this->show();
}

void MainWindow::on_add_book_pushButton_clicked()
{
    BooksInfo* books = new BooksInfo(&db,this);
    this->close();
    books->exec();
    this->show();

}
