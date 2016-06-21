#include "buy_books.h"
#include "ui_buy_books.h"

Buy_Books::Buy_Books ( QString  point, SOCKET sock, QString user, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Buy_Books)
{
    ui->setupUi(this);
    this->setWindowTitle("Order");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    QRegExp login("[0-9]{1,13}");
    ui->PhoneNumber_lineEdit->setValidator(new QRegExpValidator(login,this));
    point_book_order = point;
    count_item = 0;
    name_user = user;
    total_price = 0;
    ui->nameuser_label->setText(name_user);
    sock_order = sock;
    for(int i = 0; i < point_book_order.length(); i++)
    {
    if(point_book_order[i] == '-')
    {
        count_item++;
    }
    }
    item_order = new QTableWidgetItem[count_item];
    ui->Books_ordertable->setRowCount(count_item/2);
    point_str = new char [point_book_order.length()+1];
    strcpy(point_str,point_book_order.toStdString().c_str());
    ui->Books_ordertable->setColumnCount(2);
    ui->Books_ordertable->setHorizontalHeaderLabels(QStringList() << "Book" << "Price $");
    char* po_str = strtok(point_str,"-");
    int i = 0;
    int j = 0;
    int k = 0;
    while(po_str != NULL)
    {
        item_order[i].setText(po_str);
        if(i % 2 == 0)
        {
            ui->Books_ordertable->setItem(j,0,&item_order[i]);
            item_order[i].setFlags(item_order[i].flags() ^ Qt::ItemIsEditable);
            j++;
        }
        else
        {
            ui->Books_ordertable->setItem(k,1,&item_order[i]);
            item_order[i].setFlags(item_order[i].flags() ^ Qt::ItemIsEditable);
            k++;
        }
        i++;
        po_str = strtok(NULL,"-");
    }

}
Buy_Books::~Buy_Books()
{
    if(send(sock_order,"close_menu",20,0) < 0)
    {}
    delete ui;
}

void Buy_Books::on_Books_ordertable_itemClicked(QTableWidgetItem *item)
{

        row_item = item->row();

}

void Buy_Books::on_Delete_button_clicked() // if you want delete book of list books, you have to delete
{
    ui->Books_ordertable->removeRow(row_item);
}

void Buy_Books::on_Buy_button_clicked()
{
    if(ui->Address_line->text().isEmpty() || ui->PhoneNumber_lineEdit->text().isEmpty() ||
            (ui->Books_ordertable->rowCount() == 0))
    {
        QMessageBox::information(this,"Information", "You must enter all lineEdit");
    }
    else
    {
        if(send(sock_order,"buy", 5,0) < 0 )
        {

        }
        int row = ui->Books_ordertable->rowCount();
        data_order = ui->nameuser_label->text() + '-' + ui->PhoneNumber_lineEdit->text() + '-' +
                ui->Address_line->text() + '-';
        for(int i = 0; i < row; i++)
        {
            data_order += ui->Books_ordertable->item(i,0)->text() + ';';
            QTableWidgetItem* item_price = ui->Books_ordertable->item(i,1);
            total_price += atoi(item_price->text().toStdString().c_str());
        }
        data_order += '-' + QString::number(total_price) + '-';

        if(send(sock_order,data_order.toStdString().c_str(),data_order.length(),0) <0)
        {

        }
        memset(buff_status,0,sizeof(buff_status));
        if(recv(sock_order,buff_status,15,0) < 0)
        {}
            if(strcmp(buff_status,"OK_buy") == false)
            {
                QMessageBox::information(this,"Information","Sent your order");
                this->close();
            }
            else
            {
                QMessageBox::information(this,"Information","Your order dont sent");
            }
    }
}

void Buy_Books::on_Cancel_order_clicked()
{
    if(send(sock_order,"close_menu",20,0) < 0)
    {}
    this->close();
}
