#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <adduser.h>
#include <booksinfo.h>
#include <socketserver.h>

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
    void on_Connect_clicked();

    void on_DataBaseUser_button_clicked();

    void on_pushButton_clicked();

    void on_ShowDataBaseBook_button_clicked();

    void on_pushButton_2_clicked();

    void on_Authorization_button_clicked();

    void on_Start_Server_button_clicked();

    void StartServer();

    void on_add_new_user_push_button_clicked();

    void on_add_book_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel* model;
    SocketServer* server;


};

#endif // MAINWINDOW_H
