#ifndef LOG_IN_H
#define LOG_IN_H

#include "clientsocket.h"


#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QRegExp>
#include <QLabel>
#include <QPushButton>
#include <QString>



namespace Ui {
class Log_in;
}

class Log_in : public QDialog
{
    Q_OBJECT

public:
    QLabel* linelabel;
    QPushButton* button;
    explicit Log_in(SOCKET log_sock , QWidget *parent = 0);
    ~Log_in();

    void LabelLOG_IN(QLabel*, QPushButton*);


private slots:
    void on_OK_button_clicked();

    void on_Cancle_button_clicked();

private:
    QString name_user;
    SOCKET log_socket;
    Ui::Log_in *ui;
};

#endif // LOG_IN_H
