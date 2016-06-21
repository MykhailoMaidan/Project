#ifndef BUY_BOOKS_H
#define BUY_BOOKS_H

#include <winsock2.h>

#include <QDialog>
#include <QString>
#include <QTableWidgetItem>
#include <QStringList>
#include <QMessageBox>
#include <QRegExp>



namespace Ui {
class Buy_Books;
}

class Buy_Books : public QDialog
{
    Q_OBJECT

public:
    explicit Buy_Books( QString, SOCKET, QString , QDialog *parent = 0);
    ~Buy_Books();


private slots:
    void on_Books_ordertable_itemClicked(QTableWidgetItem *item);

    void on_Delete_button_clicked();

    void on_Buy_button_clicked();

    void on_Cancel_order_clicked();

private:
    Ui::Buy_Books *ui;
    QString point_book_order;
    QTableWidgetItem* item_order;
    int count_item;
    char* point_str;
    int row_item;
    QString name_user;
    SOCKET sock_order;
    QString data_order;
    char buff_status[20];
    int total_price;
};

#endif // BUY_BOOKS_H
