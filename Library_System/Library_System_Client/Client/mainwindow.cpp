#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <clientsocket.h>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->hide();
    this->setFixedSize(640,300);
    this->setWindowTitle("Menu");
    Client = new ClientSocket();
    Client->InitializeClient();
    Client->ConnectClient_to_Server();
    ui->user_name->hide();


}

MainWindow::~MainWindow()
{
    if(send(Client->SocketClient,"close",10,0) < 0)
    {
        qDebug() << "Error send destructor...";
    }
    delete ui;
}

void MainWindow::on_Log_in_button_clicked()
{
    char buff[10] = "log_in";
    if(send(Client->SocketClient,buff,strlen(buff),0) <0 )
    {
       qDebug() << "Error send log_in...";
    }

    log_in = new Log_in(Client->SocketClient, this);
    log_in->LabelLOG_IN(ui->user_name, ui->pushButton);
    this->hide();
    log_in->exec();
    delete log_in;
    this->show();

}

void MainWindow::on_Registratio_button_clicked()
{
    char buff[10] = "reg";
    if(send(Client->SocketClient, buff, strlen(buff),0) < 0)
    {
            qDebug() << "Send reg...";
    }


    regis = new Registration(Client->SocketClient,this);
    this->hide();
    regis->exec();
    delete regis;
    this->show();
}

void MainWindow::on_Menu_books_button_clicked()
{
    if(send(Client->SocketClient, "menubooks",11,0) < 0)
    {
        qDebug() << "send menubooks error...";
    }
    mainbook = new MainBook(Client->SocketClient,this);
    if(ui->user_name->isHidden())
    {

    }
    else
    {
        mainbook->labelmain->setText(ui->user_name->text());
        mainbook->labelmain->show();
        mainbook->spin_main->show();
        mainbook->buy->show();
    }
    this->hide();
    mainbook->exec();
    delete mainbook;
    this->show();
}

void MainWindow::on_pushButton_clicked()
{
    ui->user_name->clear();
    ui->user_name->hide();
    ui->pushButton->hide();
}
