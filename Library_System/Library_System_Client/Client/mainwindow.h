#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "log_in.h"
#include "registration.h"
#include "mainbook.h"
#include "log_in.h"
#include <clientsocket.h>
#include <QDebug>
#include <QLineEdit>
#include <QSpinBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Log_in_button_clicked();

    void on_Registratio_button_clicked();

    void on_Menu_books_button_clicked();

    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    Log_in *log_in;
    Registration *regis;
    MainBook *mainbook;
    ClientSocket* Client;

};

#endif // MAINWINDOW_H
