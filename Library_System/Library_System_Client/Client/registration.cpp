#include "registration.h"
#include "ui_registration.h"
#include "clientsocket.h"




Registration::Registration(SOCKET sock, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    this->setWindowTitle("Registration");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setFixedSize(700,310);
    reg_socket = sock;
    QRegExp login("[a-zA-Z]{1,20}");
    ui->lineEdit_5->setValidator(new QRegExpValidator(login,this));



}

Registration::~Registration()
{
    if(send(reg_socket,"close_r",20,0) < 0)
    {}
    delete ui;
}

void Registration::on_can_reg_button_clicked()
{
    if(send(reg_socket,"close_r", 15,0) < 0)
    {

    }
    this->close();
}

void Registration::on_Regis_button_clicked()
{
    QString temp_data_user;
    if(ui->lineEdit->text().length()==0 || ui->lineEdit_2->text().length()==0 || ui->lineEdit_3->text().length()==0 ||
             ui->lineEdit_4->text().length()==0 || ui->lineEdit_5->text().length()==0)
    {
   QMessageBox::warning(this,"Warning","You shall be required to fill in all fields");
    }
    else
    {
       temp_data_user = ui->lineEdit->text() + "/" + ui->lineEdit_2->text() + "/" +
               ui->lineEdit_3->text() + "/" + ui->lineEdit_4->text() + "/" +
               ui->lineEdit_5->text() + "/";
      if(send(reg_socket,temp_data_user.toStdString().c_str(), temp_data_user.length(),0) < 0 )
      {
      qDebug() << "Error send registration data...";
    }
      else
      {
          char buff[10];
          if(recv(reg_socket,buff,10,0)<0)
          {
              qDebug() << "Error send registration data...";
          }
          if(strcmp(buff,"OK") == false)
          {
              QMessageBox::information(this,"Message", "Registration access");
              this->close();
          }
          else
          {
              QMessageBox::information(this,"Message", "Such Login or Email present. Please enter the "
                                                       "other Login or Email");
              ui->lineEdit_3->clear();
              ui->lineEdit_4->clear();
              if(send(reg_socket,"reg",4,0) < 0)
              {
                  qDebug() << "Error send reg ...";
              }

          }
      }
    }

}
