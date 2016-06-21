#include "socketserver.h"
#include <QString>


SocketServer::SocketServer()
{


}
void SocketServer::InitializeSocket() // start initialize socket
{
    if(WSAStartup(MAKEWORD(2,2), &wsdata)<0)
    {
        qDebug() << "Initialize error...";
    }

}

void SocketServer::BindSocket() // bind socket
{
    if((ServerSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
    {
        qDebug() << "Socket error...";
    }
     ServerAddr.sin_family = AF_INET;
     ServerAddr.sin_port = htons(7777);
     ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
     if(bind(ServerSocket, (LPSOCKADDR) &ServerAddr, sizeof(ServerAddr))<0)
     {
         qDebug() << "Bind error...";
     }
}

void SocketServer::ListhenSocket() // socket starts lithen
{
    if(listen(ServerSocket,SOMAXCONN)<0)
    {
        qDebug() << "Listhen error...";
    }
}

void SocketServer::AcceptSocket() // sokcet begin accept
{
    int sizeServerAddr = sizeof(ServerAddr);
while(1){
        if((ClientSocket = accept(ServerSocket,(struct sockaddr*)&ServerAddr, &sizeServerAddr))<0)
        {
        qDebug() << "Accept error...";
        }
        if(ClientSocket <= 0)
        {

               qDebug() << "Client not connect...";

        }
        else
         ProcessingClient();

}
}

void SocketServer::ProcessingClient()
{
     char buff[100];
     while(1)
     {
     memset(buff,0,sizeof(buff));
     if(recv(ClientSocket,buff, sizeof(buff),0) < 0)
     {
         qDebug() << "recv error";
     }
     qDebug() << buff;
    if(strcmp(buff,"reg") == false)
    {


        memset(buf_data_user , 0 , sizeof(buf_data_user));
        if(recv(ClientSocket,buf_data_user,200,0) <0 )
        {
            qDebug() << "recv error...";
        }
        if(strcmp(buf_data_user,"close_r") == false )
        {
            continue;
        }
        else
        {
        AddNewUser(buf_data_user);
        }


    }
    else if(strcmp(buff,"log_in") == false)
    {
         memset(buff,0,sizeof(buff));
         memset(buf_data_user , 0 , sizeof(buf_data_user));
         if(recv(ClientSocket,buf_data_user,200,0) < 0 )
         {
             qDebug() << "recv error...";
         }
         if(strcmp(buf_data_user,"close_l") == false )
         {
             continue;
         }
         else
         {
         CheckLog_user(buf_data_user);
         }
    }
    else if(strcmp(buff,"menubooks") == false)
    {
        while(1)
     {
        memset(buff,0,sizeof(buff));
        if(recv(ClientSocket,buff,50,0) < 0)
        {
            qDebug() << "recv author error";
        }
        else if(strcmp(buff,"author") == false)
        {
                    SearchAuthor();
        }
        else if(strcmp(buff,"genres") == false)
        {
                    SearchGenres();
        }
        else if(strcmp(buff,"choise") == false)
        {
                    ChoiseBooks();
        }
        else if(strcmp(buff,"author_s") == false)
        {
                    SearchBook();
        }
        else if(strcmp(buff,"genres_s") == false)
        {
                    SearchBookGenres();
        }
        else if(strcmp(buff,"buy") == false)
        {
                    AddOrderToDB();
        }

        else if(strcmp(buff, "close_menu") == false)
        {
            break;
        }
        }
    }

        else if(strcmp(buff,"close") == false)
        {

        break;
        }
       }
    }

void SocketServer::AddNewUser(char * str)
{
    char* point[5];
    char* point_str = strtok(str,"/");
    int i = 0;
    int count = 0;
    while(point_str != NULL)
    {
        point[i] = point_str;
        point_str = strtok(NULL,"/");
        i++;
    }
    query_socket->exec("select* from users_info where Login = '" +   QString(point[2]) + "' or Email = '" + QString(point[3]) + "'" );
    while(query_socket->next())
    {
        count++;
    }
    if(count == 0)
    {


        query_socket->prepare("INSERT INTO users_info (Name, Surname, Login, Email, Passvord) "
               "VALUES (?, ?, ?, ?, ?)");
        query_socket->addBindValue(point[0]);
        query_socket->addBindValue(point[1]);
        query_socket->addBindValue(point[2]);
        query_socket->addBindValue(point[3]);
        query_socket->addBindValue(point[4]);
        query_socket->exec();
        if(send(ClientSocket,"OK", 3 , 0) < 0)
        {
            qDebug() << "error dsas";
        }
    }
    else
       {
        if(send(ClientSocket,"nok", 4 , 0) < 0)
        {
            qDebug() << "error dsas";
        }
    }


}

void SocketServer::CheckLog_user(char *log_str)
{
    char* point_log[2];
    int i = 0;
    int count = 0;
    char* point_str = strtok(log_str,".");
    while(point_str != NULL)
    {
        point_log[i] = point_str;
        point_str = strtok(NULL,".");
        i++;
    }
    query_socket->exec("select* from users_info where Login = '" +   QString(point_log[0]) +
            "' and Passvord = '" + QString(point_log[1]) + "'" );
    while(query_socket->next())
    {
        count++;
    }
    if(count > 0)
    {
        if(send(ClientSocket,"Log_ok", 20,0) <0)
        {
            qDebug() << "error send log_ok...";
        }
    }
    else
    {
        if(send(ClientSocket,"Log_error", 20, 0) <0)
        {
            qDebug() << "error send log_error...";
        }
    }

}

void SocketServer::DBtoSock(QSqlDatabase *obj)
{
    db = obj;
    query_socket = new QSqlQuery(*db);
}

void SocketServer::SearchAuthor()
{
    book_info.clear();
    query_socket->exec("select distinct Author from books_info");
    while(query_socket->next())
    {
        book_info += query_socket->value(0).toString() + '-';
        qDebug () << query_socket->value(0).toString();
        qDebug () << book_info;
    }
    if(send(ClientSocket, book_info.toStdString().c_str(),book_info.length(),0) < 0)
    {
        qDebug() << "error send author";
    }
}

void SocketServer::SearchGenres()
{
    book_info.clear();
    query_socket->exec("select distinct Genres from books_info");
    while(query_socket->next())
    {
        book_info += query_socket->value(0).toString() + '-';
        qDebug () << query_socket->value(0).toString();
        qDebug () << book_info;
    }
    if(send(ClientSocket, book_info.toStdString().c_str(),book_info.length(),0) < 0)
    {
        qDebug() << "error send genres";
    }
}

void SocketServer::ChoiseBooks()
{

    book_info.clear();
    memset(buf_data_user,0,sizeof(buf_data_user));
    if(recv(ClientSocket,buf_data_user,50,0) < 0)
    {

    }
      QString name_book(buf_data_user);
   query_socket->exec("select Book_Name, Price from books_info where Author = '"
                       + name_book + "' or Genres = '" + name_book + "'" );
    while(query_socket->next())
    {
        book_info += query_socket->value(0).toString() + "/";
        book_info += query_socket->value(1).toString() + "*";
        qDebug() << book_info;
    }
    if(send(ClientSocket,book_info.toStdString().c_str(),book_info.length(),0))
    {

    }
}

void SocketServer::SearchBook()
{
    book_info.clear();
    memset(buf_data_user,0, sizeof(buf_data_user));
    if(recv(ClientSocket,buf_data_user,1000,0) < 0)
    {

    }
    int count = 0;
    QString temp(buf_data_user);
    query_socket->exec("select distinct Author from books_info where Author like \""
                       + temp + "%\"");
    while(query_socket->next())
    {
        book_info += '-' + query_socket->value(0).toString();
        count++;
    }
    if(count == 0)
    {
        if(send(ClientSocket,"-empty", 15,0) < 0)
        {

        }
    }
    else
    {
    if(send(ClientSocket,book_info.toStdString().c_str(), book_info.length(),0) < 0)
    {

    }
    }
}

void SocketServer::SearchBookGenres()
{
    book_info.clear();
    memset(buf_data_user,0, sizeof(buf_data_user));
    if(recv(ClientSocket,buf_data_user,1000,0) < 0)
    {

    }
    int count = 0;
    QString temp(buf_data_user);
    query_socket->exec("select distinct Genres from books_info where Genres like \""
                       + temp + "%\"");
    while(query_socket->next())
    {
        book_info += '-' + query_socket->value(0).toString();
        count++;
    }
    if(count == 0)
    {
        if(send(ClientSocket,"-empty", 15,0) < 0)
        {

        }
    }
    else
    {
    if(send(ClientSocket,book_info.toStdString().c_str(), book_info.length(),0) < 0)
    {

    }
    }
}

void SocketServer::AddOrderToDB()
{
    memset(buf_data_user,0,sizeof(buf_data_user));
    if(recv(ClientSocket,buf_data_user,500,0) < 0)
    {

    }
    query_socket->prepare("INSERT INTO order_book (User_login, Number_phone, Address, Books, Price_books) "
                   "VALUES (?, ?, ?, ?, ?)");
    char* point = strtok(buf_data_user, "-");
    while(point != NULL)
    {
        query_socket->addBindValue(point);
        point = strtok(NULL,"-");
    }

     if(query_socket->exec())
     {
            if(send(ClientSocket,"OK_buy",10,0) < 0)
            {
            }
     }else
     {
         if(send(ClientSocket,"error_buy",15,0) < 0)
         {
         }
     }


}
