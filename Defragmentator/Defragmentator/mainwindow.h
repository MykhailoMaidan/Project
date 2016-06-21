#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Windows.h>

#include <QMainWindow>
#include <QStringListModel>
#include <QStringList>
#include <QAbstractItemModel>
#include <sstream>
#include <QString>
#include <QDir>
#include <thread>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool GetBitMap(QString);

    bool GetBitMapFile(QString, int );

    bool StrTokFileDisk();

    bool Defrag_File(QString);

    bool GetListDir(QString);

    bool GetFreeSizeBitMapDisk();

    void PaintingBitMap();

    void ProccessDefragmentation();

    void FindStartFreeCluster();

    void FindStartClusterFile();

    bool MoveClusterBlock();




private slots:
    void on_disk_listViev_pressed(const QModelIndex &index);

    void on_actionGetBitMapDevice_triggered();

    void on_actionFind_Device_triggered();

    void on_actionDefragmentation_triggered();

    void on_actionClose_triggered();

    void on_actionMoveCluster_triggered();

private:
    Ui::MainWindow *ui;
    QStringListModel* model;
    QAbstractItemModel * item;
    ULONG StartLNC;
    long lpTotalNumberOfClusters;
    std::stringstream str;
    ULONG BeginLNC;
    ULONG TotalNumberClusteForFile;
    char* point_dir;
    HANDLE handle_file;
    ULONG Size_File;
    RETRIEVAL_POINTERS_BUFFER* Buffer_file; // структура яка мість інформація про кластери
    ULONG SIZE_Cluster;
    ULONG BitMap_sizeFile;
    ULONG VCNPrevCluster;
    VOLUME_BITMAP_BUFFER *Bitmap; // структура в якій міститься бітова мапа
    QDir mDir;
    QString file_list;
    bool stoped;
    QString tom_disk;
    char * buff_file_path;
    QMap <int, HANDLE> map_file;
    QMap <int,HANDLE>::iterator it;


};

#endif // MAINWINDOW_H
