#ifndef BOOKSINFO_H
#define BOOKSINFO_H

#include <QDialog>
#include <QSqlDatabase>
namespace Ui {
class BooksInfo;
}

class BooksInfo : public QDialog
{
    Q_OBJECT

public:
    explicit BooksInfo(QSqlDatabase* obj, QWidget *parent = 0);
    ~BooksInfo();

private slots:
    void on_SaverecordBooks_clicked();

private:
    Ui::BooksInfo *ui;
    QSqlDatabase* db;
};

#endif // BOOKSINFO_H
