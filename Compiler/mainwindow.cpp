#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStringList>
#include <fstream>
#include "compiler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Error->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_file_triggered()
{
    patch = QFileDialog::getSaveFileName(this, "New file", "D:\\", "*.m12");
    std::ofstream fout;
    fout.open(patch.toStdString().c_str());

}

void MainWindow::on_actionOpen_fiel_triggered()
{

    std::string temp;
    std::ifstream fin;
    patch=QFileDialog::getOpenFileName(this, "Open file", "D:\\", "*.m12");
    fin.open(patch.toStdString().c_str());
    if(fin.is_open())
    {

        ui->Reader->clear();
    }
    while(!fin.eof())
    {
     std::getline(fin,temp);
     text_program.push_back(temp);
    }
    for(unsigned int i = 0; i<text_program.size(); i++)
    {
        ui->Reader->append(QString::fromStdString(text_program[i]));
    }
    fin.close();

}

void MainWindow::on_actionClose_triggered()
{
    this->close();
}

void MainWindow::on_actionBild_triggered()
{
    Compiler obj(text_program);
    obj.GetLexem();
    obj.Translator();
    QStringList list(obj.GetError());
        QString str_tmp;

        for(auto x : list)
            str_tmp.append(x);

        ui->Error->setPlainText(str_tmp);



}

void MainWindow::on_actionSave_triggered()
{
if(!patch.isEmpty())
{
    ofstream file;
    file.open(patch.toStdString().c_str());
    QString str_tmp;
            str_tmp += ui->Reader->toPlainText();
            file << str_tmp.toStdString(); //зберег
            file.close();
}
else
    return ;
}
