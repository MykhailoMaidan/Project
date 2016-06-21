#include "log_in.h"
#include "ui_log_in.h"

Log_in::Log_in(SOCKET log_sock, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Log_in)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    QRegExp login("{[a-zA-Z]{1,25}|[1-9]{1,10}}");
    //ui->lineEdit->setValidator(new QRegExpValidator(login,this));
    log_socket = log_sock;
    this->setWindowTitle("Log In");
    this->setFixedSize(480,300);


}

Log_in::~Log_in()
{
    if(send(log_socket,"close_l",20,0) < 0)
    {}
    delete ui;
}

void Log_in::LabelLOG_IN(QLabel* obj_label, QPushButton* button_obj)
{
    linelabel = obj_label;
    button = button_obj;
}

void Log_in::on_OK_button_clicked()
{
    QString temp_log_data;
    if(ui->lineEdit->text().length()== 0 || ui->lineEdit_2->text().length()== 0)
    {
        QMessageBox::warning(this,"Warning","Please fill in all fields!");
    }
    else
    {
        temp_log_data = ui->lineEdit->text() + "." + ui->lineEdit_2->text();
        if(send(log_socket,temp_log_data.toStdString().c_str(), temp_log_data.length(), 0) < 0)
        {
            qDebug() << "error send log";
        }
        char buff[20];
        memset(buff,0,sizeof(buff));
        if(recv(log_socket,buff,20,0) < 0)
        {
            qDebug() << "error recv log...";
        }
        if(strcmp(buff,"Log_ok") == false)
        {
            name_user = ui->lineEdit->text();
            linelabel->setText(ui->lineEdit->text());
            linelabel->show();
            button->show();
            this->close();
        }
        else
        {

            QMessageBox::warning(this, "error", "Please enter the corect Log or Passvord");
            if(send(log_socket,"log_in",10,0) < 0)
            {
                qDebug() << "error send log in again";
            }
        }
    }

}

void Log_in::on_Cancle_button_clicked()
{
    if(send(log_socket, "close_l",15,0) < 0)
       {

    }
    this->close();
}
