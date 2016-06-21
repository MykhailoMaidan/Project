#ifndef MAINBOOK_H
#define MAINBOOK_H

#include <winsock2.h>
#include <buy_books.h>

#include <QDialog>
#include <QDebug>
#include <QTableWidgetItem>
#include <QShortcut>
#include <QLabel>
#include <QSpinBox>
#include <QMessageBox>

namespace Ui {
class MainBook;
}

class MainBook : public QDialog
{
    Q_OBJECT

public:
    explicit MainBook(SOCKET sock_book,QWidget *parent = 0);
    ~MainBook();
    void AddAuthoronTable(char*buff_books);
    void AddGenresTable(char* buff_genres);
    void AddBooktoTable(char* str);
    QLabel* labelmain;
    QSpinBox* spin_main;
    QPushButton* buy;
private slots:
    void on_CancleButton_clicked();

    void on_AuthorButton_clicked();

    void ChoiseCatalog(QTableWidgetItem *current);

    void on_GenresButton_clicked();

    void on_TableForCatalog_itemClicked(QTableWidgetItem *item);

    void on_Search_pushButton_clicked();

    void on_SearchLine_edit_textChanged(const QString &arg1);

    void on_Books_info_itemClicked(QTableWidgetItem *item);


    void on_Buy_button_clicked();

private:
    Ui::MainBook *ui;
    SOCKET sock_books;
    QTableWidgetItem* item;
    QTableWidgetItem* item_book;
    char buff_info_catalog[1000];
    QShortcut* keyEnter;
    int count_spin;
    QMessageBox* msg_cancel;
    QString book_order;
    QString name_user;
    Buy_Books * order;
};

#endif // MAINBOOK_H
