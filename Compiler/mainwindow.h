#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>
#include <string>
#include<QStringList>


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
    void on_actionNew_file_triggered();

    void on_actionOpen_fiel_triggered();

    void on_actionClose_triggered();

    void on_actionBild_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<std::string> text_program;
    QString patch;

};

#endif // MAINWINDOW_H
