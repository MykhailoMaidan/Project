#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <winsock2.h>

#include <QDialog>
#include <QMessageBox>
#include <QMainWindow>
#include <QString>
#include <QMessageBox>


namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(SOCKET sock, QWidget *parent = 0 );
    ~Registration();

private slots:
    void on_can_reg_button_clicked();

    void on_Regis_button_clicked();

private:
    SOCKET reg_socket;
    Ui::Registration *ui;

};

#endif // REGISTRATION_H
