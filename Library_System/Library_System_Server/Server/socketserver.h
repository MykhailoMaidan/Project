#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <winsock2.h>

#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QString>


class SocketServer
{
private:
    SOCKET ServerSocket;
    SOCKET ClientSocket;
    SOCKADDR_IN ServerAddr;
    WSADATA wsdata;
    QSqlDatabase* db;
    QSqlQuery *query_socket;
    char buf_data_user[600];
    QString book_info;

public:
    SocketServer();
    void InitializeSocket();
    void BindSocket();
    void ListhenSocket();
    void AcceptSocket();
    void ProcessingClient();
    void AddNewUser(char * str);
    void CheckLog_user(char* log_str);
    void DBtoSock(QSqlDatabase* obj);
    void SearchAuthor();
    void SearchGenres();
    void ChoiseBooks();
    void SearchBook();
    void SearchBookGenres();
    void AddOrderToDB();
};

#endif // SOCKETSERVER_H
