#ifndef ADDUSER_H
#define ADDUSER_H

#include <QSqlDatabase>
#include <QDialog>

namespace Ui {
class adduser;
}

class adduser : public QDialog
{
    Q_OBJECT

public:
    explicit adduser(QSqlDatabase* obj, QWidget *parent = 0);
    ~adduser();

private slots:
    void on_SaveData_clicked();

private:
    Ui::adduser *ui;
    QSqlDatabase* db;
};

#endif // ADDUSER_H
