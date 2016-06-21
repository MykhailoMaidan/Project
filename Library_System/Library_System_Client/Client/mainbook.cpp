#include "mainbook.h"
#include "ui_mainbook.h"
#include <string>
#include <QStringList>

MainBook::MainBook(SOCKET sock_book,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainBook)
{
    ui->setupUi(this);
    this->setWindowTitle("Book");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->Counter_spinBox->setEnabled(false);
    this->setFixedSize(650,310);
    sock_books = sock_book;
    ui->TableForCatalog->setColumnCount(1);
    keyEnter = new QShortcut(this);
    keyEnter->setKey(Qt::Key_Enter);
    ui->SearchLine_edit->hide();
    ui->Author_checkBox->hide();
    labelmain = ui->username_label;
    spin_main = ui->Counter_spinBox;
    spin_main->hide();
    ui->username_label->hide();
    buy = ui->Buy_button;
    count_spin = 0;
    msg_cancel = new QMessageBox(this);
    msg_cancel->setText("Message");
    msg_cancel->setInformativeText("If you exit, you order will be destroyed");
    msg_cancel->setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msg_cancel->hide();
    ui->Buy_button->hide();
    ui->TableForCatalog->heightForWidth(200);



}

MainBook::~MainBook()
{
    if(send(sock_books,"close_menu",20,0) < 0)
    {}
    delete ui;
}

void MainBook::AddAuthoronTable(char * buff_books)
{
    int count_author = 0;
    for(int i = 0; i < strlen(buff_books); i++)
    {
        if(buff_books[i] == '-')
          {
            count_author++;
          }
    }
    item = new QTableWidgetItem[count_author];
    ui->TableForCatalog->setRowCount(count_author);
    char* pint_str = strtok(buff_books, "-");
    int i = 0;
    while(pint_str != NULL)
    {
        item[i].setText(pint_str);
        ui->TableForCatalog->setItem(i,0,&item[i]);
        item[i].setFlags(item[i].flags() ^ Qt::ItemIsEditable);
        pint_str = strtok(NULL,"-");
        i++;

    }
}

void MainBook::AddGenresTable(char *buff_genres)
{
    int count_genres = 0;
    for(int i = 0; i < strlen(buff_genres); i++)
    {
        if(buff_genres[i] == '-')
          {
            count_genres++;
          }
    }
    item = new QTableWidgetItem[count_genres];
    ui->TableForCatalog->setRowCount(count_genres);
    char* pint_str = strtok(buff_genres, "-");
    int i = 0;
    int k =0;
    while(pint_str != NULL)
    {
        item[k].setText(pint_str);
        ui->TableForCatalog->setItem(i,0,&item[k]);
        item[i].setFlags(item[i].flags() ^ Qt::ItemIsEditable);
        pint_str = strtok(NULL,"-");
        i++;
        k++;
    }
}

void MainBook::AddBooktoTable(char* str)
{
    int count = 0;
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] == '/')
            count++;
    }
    item_book = new QTableWidgetItem[count*2];
    ui->Books_info->setRowCount(count);
    ui->Books_info->setColumnCount(2);
    char* point = strtok(str, "/*");
    int i = 0;
    int k = 0;
    int j = 0;
    while(point != NULL)
    {
        item_book[i].setText(point);
        if(i % 2 == 0)
        {
        ui->Books_info->setItem(j,0,&item_book[i]);
        item_book[i].setFlags(item_book[i].flags() ^ Qt::ItemIsEditable);
        j++;
        }
        else
        {
            ui->Books_info->setItem(k,1,&item_book[i]);
            item_book[i].setFlags(item_book[i].flags() ^ Qt::ItemIsEditable);
            k++;
        }
        point = strtok(NULL,"/*");
        i++;

    }
}

void MainBook::on_CancleButton_clicked()
{

    if((ui->Counter_spinBox->value()) >0 )
    {
        int ret = msg_cancel->exec();
        if(ret == QMessageBox::Cancel)
        {
            msg_cancel->hide();
        }
        else
        {
            this->close();
        }

    }
    else
    {

        if(send(sock_books,"close_menu",15,0) < 0)
          {
            qDebug() << "error send close menu;";
        }
        this->close();
    }


}

void MainBook::on_AuthorButton_clicked()
{
        ui->SearchLine_edit->clear();
        ui->Author_checkBox->setChecked(false);
        ui->Books_info->clear();
        ui->Books_info->setColumnCount(0);
        ui->Books_info->setRowCount(0);
        ui->TableForCatalog->setHorizontalHeaderLabels(QStringList() << "Author");
        if(send(sock_books,"author",8,0) < 0)
        {
            qDebug() << "send search author error";
        }
        memset(buff_info_catalog,0, sizeof(buff_info_catalog));
        if(recv(sock_books,buff_info_catalog,1000,0) < 0)
        {
            qDebug() << "recv book athour error";
        }
        AddAuthoronTable(buff_info_catalog);





}

void MainBook::ChoiseCatalog(QTableWidgetItem* current)
{
    if(send(sock_books,"choise_catalog",30,0) < 0)
    {
        qDebug() << "send error choise catalog";
    }
    if(send(sock_books,current->text().toStdString().c_str(),40,0) < 0)
    {
        qDebug() << "send error choise catalog";
    }

}

void MainBook::on_GenresButton_clicked()
{
    ui->SearchLine_edit->clear();
    ui->Author_checkBox->setChecked(false);
    ui->Books_info->clear();
    ui->Books_info->setColumnCount(0);
    ui->Books_info->setRowCount(0);
    ui->TableForCatalog->setHorizontalHeaderLabels(QStringList() << "Genres");
    if(send(sock_books,"genres",8,0) < 0)
    {
        qDebug() << "send search author error";
    }
    memset(buff_info_catalog,0, sizeof(buff_info_catalog));
    if(recv(sock_books,buff_info_catalog,1000,0) < 0)
    {
        qDebug() << "recv book athour error";
    }
   AddGenresTable(buff_info_catalog);
}

void MainBook::on_TableForCatalog_itemClicked(QTableWidgetItem *item)
{

    if(ui->TableForCatalog->item(0,0)->text() == "empty")
    {

    }
    else
    {

    if(send(sock_books,"choise",12,0) < 0)
    {
        qDebug() << "send error choise catalog";
    }
    if(send(sock_books,item->text().toStdString().c_str(),item->text().length(),0) < 0)
    {
            qDebug() << "send error choise catalog";

    }
    memset(buff_info_catalog,0,sizeof(buff_info_catalog));
    if(recv(sock_books,buff_info_catalog,1000,0) < 0)
    {

    }
    AddBooktoTable(buff_info_catalog);
    ui->Books_info->setHorizontalHeaderLabels(QStringList() << "Book" << "Price $");
    }


}

void MainBook::on_Search_pushButton_clicked()
{
        ui->Author_checkBox->show();
        ui->SearchLine_edit->show();

}

void MainBook::on_SearchLine_edit_textChanged(const QString &arg1)
{
    ui->Books_info->clear();
    ui->Books_info->setColumnCount(0);
    ui->Books_info->setRowCount(0);
    if(ui->Author_checkBox->isChecked())
      {
          if(send(sock_books,"author_s",15,0) < 0)
          {

          }

          if(arg1.isEmpty())
          {
              if(send(sock_books,"NULL",
                      5,0) < 0)
              {

              }

          }
          else
          {
              if(send(sock_books,arg1.toStdString().c_str(),
                      arg1.length(),0) < 0)
              {

              }
              ui->TableForCatalog->setHorizontalHeaderLabels(QStringList() << "Author");

          }

          memset(buff_info_catalog,0,sizeof(buff_info_catalog));
          if(recv(sock_books,buff_info_catalog,1000,0) < 0)
          {

          }

          AddGenresTable(buff_info_catalog);

      }
      else
      {
          if(send(sock_books,"genres_s",15,0) < 0)
          {

          }
          if(arg1.isEmpty())
          {
              if(send(sock_books,"NULL",
                      5,0) < 0)
              {

              }

          }
          else
          {
              if(send(sock_books,arg1.toStdString().c_str(),
                      arg1.length(),0) < 0)
              {

              }
              ui->TableForCatalog->setHorizontalHeaderLabels(QStringList() << "Genres");
          }
          memset(buff_info_catalog,0,sizeof(buff_info_catalog));
          if(recv(sock_books,buff_info_catalog,1000,0) < 0)
          {

          }

          AddGenresTable(buff_info_catalog);

      }

}

void MainBook::on_Books_info_itemClicked(QTableWidgetItem *item)
{

    if(item->column() == 1)
    {

    }
    else
    {
    count_spin++;
    if(ui->username_label->isHidden())
    {
        QMessageBox::warning(this,"Warning", "To order the book must log");
    }
    else
    {
        if(item->column() != 0)
        {}
        else
        {
        ui->Counter_spinBox->setValue(count_spin);
            QTableWidgetItem* item_price =  ui->Books_info->item(item->row(),1);
            book_order +=item->text() + '-' + item_price->text() + '-';

        }

    }
    }
}

void MainBook::on_Buy_button_clicked()
{
            if(count_spin > 0)
            {
            order = new Buy_Books(book_order, sock_books,ui->username_label->text());
            this->hide();
            order->exec();
            delete order;
            //this->show();
            }
            else
            {
                QMessageBox::information(this,"Information", "Please choose anything");
            }
}
