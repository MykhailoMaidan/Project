#include "booksinfo.h"
#include "ui_booksinfo.h"
#include <QMessageBox>
#include <QSqlQuery>

BooksInfo::BooksInfo(QSqlDatabase* obj, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BooksInfo)
{
    db = obj;
    ui->setupUi(this);
}

BooksInfo::~BooksInfo()
{
    delete ui;
}

void BooksInfo::on_SaverecordBooks_clicked()
{
    int count = 0;
    if(ui->bookname_line->text() == "" || ui->Author_line->text() == "" || ui->Countris_line->text() == "" ||
            ui->Genres_line->text() == "" || ui->Number_of_stock_line->text() == "")
    {
        QMessageBox::information(this,"Message", "All fields must be filled!");
    }
    else{
    QSqlQuery *query = new QSqlQuery(*db);
    query->exec("select* from users_info where Book_Name = '" + ui->bookname_line->text() + "'");
    while(query->next())
    {
        count++;
    }
    if(count == 0)
    {


       query->prepare("INSERT INTO books_info (Book_Name, Author, Countris, Genres, Number_of_stock) "
              "VALUES (?, ?, ?, ?, ?)");
       query->addBindValue(ui->bookname_line->text());
       query->addBindValue(ui->Author_line->text());
       query->addBindValue(ui->Countris_line->text());
       query->addBindValue(ui->Genres_line->text());
       query->addBindValue(ui->Number_of_stock_line->text().toInt());
       query->exec();
       this->close();
    }
    else
        QMessageBox::information(this,"Message","This book is already written");
    }
}
