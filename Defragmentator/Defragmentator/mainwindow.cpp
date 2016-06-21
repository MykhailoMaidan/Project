#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(500);
    ui->progressBar->setValue(0);
    this->setFixedSize(910,670);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::GetBitMap(QString tom) // Взяття бітової мапи всього пристрою
{
    QString temp = "\\\\.\\" + tom;
    HANDLE handledisk = CreateFileA(temp.toStdString().c_str() ,
                                   GENERIC_READ,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                   NULL,
                                   OPEN_EXISTING,
                                   NULL,
                                   NULL
                                   );
    STARTING_LCN_INPUT_BUFFER StartingLCN; // містить початок бітової мапи
    Bitmap = NULL;
    StartingLCN.StartingLcn.QuadPart = 0;
    unsigned long long BitMap_Size;
    DWORD ByteReturned;
    bool result;
    BitMap_Size = sizeof(VOLUME_BITMAP_BUFFER)+4;
    Bitmap = (VOLUME_BITMAP_BUFFER*) malloc(BitMap_Size);
    result = DeviceIoControl(
                handledisk,
                FSCTL_GET_VOLUME_BITMAP, // керуючий код для отримання бітової мапи
                &StartingLCN,
                sizeof(StartingLCN),
                Bitmap,
                BitMap_Size,
                &ByteReturned,
                NULL);
        if ( (!result) && GetLastError() == ERROR_MORE_DATA )
            {
               ULONG ClusterCountVolume = Bitmap->BitmapSize.QuadPart - Bitmap->StartingLcn.QuadPart;

               BitMap_Size = sizeof(VOLUME_BITMAP_BUFFER) + (ClusterCountVolume/8) + 1;
                   Bitmap = (VOLUME_BITMAP_BUFFER*) realloc (Bitmap,BitMap_Size);
               Bitmap->StartingLcn.QuadPart = 0;;
               int temp = (BitMap_Size/500) + 1;
                     ui->tableWidget->setColumnCount(BitMap_Size/500);
                result = DeviceIoControl(
                        handledisk,
                        FSCTL_GET_VOLUME_BITMAP,
                        &StartingLCN,
                        sizeof(StartingLCN),
                        Bitmap,
                        BitMap_Size,
                        &ByteReturned,
                        NULL);

           }
}

bool MainWindow::GetFreeSizeBitMapDisk() // Знаходження вільного місця для файла який дефрагментується
{
    ULONG FreeCluster = 0;
    int BitMapMask = 1;
    int tempLNC = 0;
    int ClusterInUse = 0;
for(ULONG i = 0; i < (Bitmap->BitmapSize.QuadPart/8) - 1; i++ )
  {
      if(Bitmap->Buffer[i] == 255)
      {
          BeginLNC+= 8;
          FreeCluster = 0;
          continue;
      }

        while(BitMapMask != 256)
       {
           if(!FreeCluster)
           {
               tempLNC = BeginLNC;
           }
           ClusterInUse = Bitmap->Buffer[i] & BitMapMask;
           if(!ClusterInUse)
           {
               FreeCluster++;
           }
           else
           {
               FreeCluster = 0;
           }
           BitMapMask <<= 1;
            BeginLNC++;
         }
        if(FreeCluster >= TotalNumberClusteForFile)
        {
            BeginLNC = tempLNC;
            break;
        }
        BitMapMask = 1;

  }
return true;
}

bool MainWindow::GetBitMapFile(QString file_bit_map, int key) // Знаходження кластерів файла на диску
{
    handle_file = CreateFileA(file_bit_map.toStdString().c_str(),
                              FILE_READ_ATTRIBUTES,
                              FILE_SHARE_READ |
                             FILE_SHARE_WRITE |
                              FILE_SHARE_DELETE,
                             NULL,OPEN_EXISTING,
                             0,0);

    if(handle_file == INVALID_HANDLE_VALUE)
    {
        ui->Information_text->append("File not open");
        return false;
    }
        Size_File = GetFileSize(handle_file,NULL);
        ui->Information_text->append("Size of file in byte: " + QString::number(Size_File));
        BitMap_sizeFile = sizeof(RETRIEVAL_POINTERS_BUFFER) + (Size_File / SIZE_Cluster) *  sizeof(Buffer_file->Extents);
        ui->Information_text->append("The total size memmory for file:" + QString::number(BitMap_sizeFile));
        Buffer_file = new RETRIEVAL_POINTERS_BUFFER[BitMap_sizeFile];

        STARTING_VCN_INPUT_BUFFER BUFFIN;
        BUFFIN.StartingVcn.QuadPart = 0;

        DWORD ByteReturn;


        if(DeviceIoControl(handle_file,FSCTL_GET_RETRIEVAL_POINTERS, &BUFFIN, sizeof(BUFFIN),
                           Buffer_file, BitMap_sizeFile, &ByteReturn,NULL))
        {
            TotalNumberClusteForFile = (Size_File + SIZE_Cluster - 1) / SIZE_Cluster;
            ui->Information_text->append("Total size cluster for file:" + QString::number(TotalNumberClusteForFile));
        }
        else
        {
            return false;
        }
        if(key != 0)
               {
                    map_file.insert(Buffer_file->Extents[0].Lcn.QuadPart,handle_file);
                }

        VCNPrevCluster = Buffer_file->StartingVcn.QuadPart;
        ui->Information_text->append("Extend coutn is:" + QString::number(Buffer_file->ExtentCount));
        return true;
}

bool MainWindow::StrTokFileDisk() // Розбиття списку файлів  і взяття кожно файла окремо
{
        buff_file_path = new char[file_list.length() + 1];
        strcpy(buff_file_path,file_list.toStdString().c_str());
        char* pointer = strtok(buff_file_path,"*");
        while(pointer != NULL)
        {
            if(!GetBitMapFile(QString(pointer),0))
            {
                ui->statusBar->showMessage("Error BitMap file didnt create!");
                return false;
            }
            if(Buffer_file->ExtentCount == 1)
            {

            }
            else
            {
           GetFreeSizeBitMapDisk();
            if(!Defrag_File(QString(pointer)))
            {
                ui->statusBar->showMessage("Error file name incorrect");
                return false;
            }
            }
                        pointer = strtok(NULL, "*");

        }
        return true;
}

bool MainWindow::Defrag_File(QString file_defrag) // Процес дефрагментації
{
    HANDLE handle_disk = 0;
    HANDLE handle_file = 0;
    MOVE_FILE_DATA buf_in; // структура для переміщення
    DWORD nBytes = 0;
    QString temp = "\\\\.\\" + QString::fromStdString(file_defrag.toStdString().substr(0,2));
    handle_file = CreateFileA(file_defrag.toStdString().c_str(),
                              FILE_READ_ATTRIBUTES,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                NULL, OPEN_EXISTING,
                              FILE_FLAG_NO_BUFFERING, NULL);
        handle_disk = CreateFileA(temp.toStdString().c_str(),
                                  GENERIC_READ,
                                  FILE_SHARE_READ |
                                  FILE_SHARE_WRITE,
                                  NULL,
                                  OPEN_EXISTING,
                                  0, 0);
        if(handle_file == INVALID_HANDLE_VALUE || handle_disk == INVALID_HANDLE_VALUE)
        {
            ui->Information_text->append("invalid handle value!");
            return false;
        }
        buf_in.FileHandle = handle_file;
        buf_in.StartingLcn.QuadPart = BeginLNC;

        for(unsigned int i = 0; i < Buffer_file->ExtentCount; i++)
        {
            buf_in.StartingVcn.QuadPart = VCNPrevCluster;
            buf_in.ClusterCount = Buffer_file->Extents[i].NextVcn.QuadPart - VCNPrevCluster;
            int result = DeviceIoControl(handle_disk, FSCTL_MOVE_FILE, &buf_in, sizeof(buf_in),
                                         NULL, 0 , &nBytes, NULL);
            result = GetLastError();
            ui->Information_text->append("Defrag:" + QString::number(result));
            buf_in.StartingLcn.QuadPart += buf_in.ClusterCount;
            VCNPrevCluster = Buffer_file->Extents[i].NextVcn.QuadPart;
        }
}

bool MainWindow::GetListDir(QString  path) // Рекурсивний спуск по директоріях для знаходження всіх файлів
{

    if(stoped==false){
        QDir dir( path);
        QString szFileName;
     foreach( QFileInfo fi, dir.entryInfoList())
     {
         if(fi.isDir())
         {
            szFileName = fi.absoluteFilePath();
         }
         else
         {
        file_list += fi.absoluteFilePath() + '*';
         }
        if( fi.isDir())
        {
            if( fi.fileName()=="." || fi.fileName()=="..")continue;
            GetListDir(szFileName);
        }

     }}
    return true;

}

void MainWindow::on_disk_listViev_pressed(const QModelIndex &index) // Вибираємо пристрій
{

    long lpSectorsPerCluster;
    long lpBytesPerSector;
    long lpNumberOfFreeClusters;

    unsigned long long size_disk;
    double disk_size_Gbyte;
    int drive_type;
         tom_disk = index.data().toString();
        drive_type = GetDriveTypeA(LPCSTR(index.data().toString().toStdString().c_str()));
        if (drive_type == DRIVE_UNKNOWN) ui->Information_text->setText( " UNKNOWN");
        if (drive_type == DRIVE_NO_ROOT_DIR) ui->Information_text->setText (" DRIVE NO ROOT DIR");
        if (drive_type == DRIVE_REMOVABLE) ui->Information_text->setText(" REMOVABLE");
        if (drive_type == DRIVE_FIXED) ui->Information_text->setText(" FIXED");
        if (drive_type == DRIVE_REMOTE) ui->Information_text->setText(" REMOTE");
        if (drive_type == DRIVE_CDROM) ui->Information_text->setText(" CDROM" );
        if (drive_type == DRIVE_RAMDISK) ui->Information_text->setText(" RAMDISK");
        GetDiskFreeSpaceA(LPCSTR(index.data().toString().toStdString().c_str()),
                          (LPDWORD)&lpSectorsPerCluster, (LPDWORD)&lpBytesPerSector,
                         (LPDWORD)&lpNumberOfFreeClusters, (LPDWORD)&lpTotalNumberOfClusters);
        size_disk = (DWORD64)lpTotalNumberOfClusters * (DWORD64)lpSectorsPerCluster *
                (DWORD64)lpBytesPerSector;
        str.str("");
        str << lpTotalNumberOfClusters;
        ui->Information_text->append(QString::fromStdString("The total number clusters on disk: "
                                                             + str.str()));
        str.str("");
        str << lpNumberOfFreeClusters;
        ui->Information_text->append(QString::fromStdString("The total number free clusters on disk: "
                                                            + str.str()));
        str.str("");
        str << lpSectorsPerCluster;
        ui->Information_text->append(QString::fromStdString("The total number sectors per cluster: "
                                                            + str.str()));
        str.str("");
        str << lpBytesPerSector;
        ui->Information_text->append(QString::fromStdString("The total number byte per sectors: "
                                                             + str.str()));

        str.str("");
        disk_size_Gbyte = size_disk / 1024.0 / 1024.0/1024.0;
        str << disk_size_Gbyte;
        ui->Information_text->append(QString::fromStdString("Memmory dick in Gbyte: "
                                                             + str.str()));
        size_disk = (DWORD64)lpNumberOfFreeClusters * (DWORD64)lpSectorsPerCluster *
                (DWORD64)lpBytesPerSector;
         str.str("");
         disk_size_Gbyte = size_disk / 1024.0 / 1024.0 /1024.0;
         str << disk_size_Gbyte;
         SIZE_Cluster = lpBytesPerSector*lpSectorsPerCluster;
         ui->Information_text->append(QString::fromStdString("Free Memmory dick in Gbyte: "
                                                       + str.str()));
}

void MainWindow::on_actionGetBitMapDevice_triggered() // Малюємо бітову мапу диску
{
        PaintingBitMap();
}

void MainWindow::on_actionFind_Device_triggered() //Шукаємо пристрої на комп'ютері
{
    model = new QStringListModel(this);
    QStringList temp;
    wchar_t disks[256];
    wchar_t *disk;
    DWORD sizebuf = 256;
    GetLogicalDriveStringsW(sizebuf, disks);
    disk = disks;
    while (*disk)
        {
            temp << QString(*disk)+ ":\\";
            disk = disk + wcslen(disk) + 1;
        }
    model->setStringList(temp);
    ui->disk_listViev->setModel(model);
}

void MainWindow::on_actionDefragmentation_triggered() //Запускаємо процес дефрагментації
{
        ProccessDefragmentation();

}

void MainWindow::PaintingBitMap() // ф-ція яка малює бітову мапу
{
    int count_buff = 0;
       GetBitMap(QString::fromStdString(tom_disk.toStdString().substr(0,2)));
       ui->progressBar->setMaximum(ui->tableWidget->rowCount()-1);
       for(int i = 0; i < 500; i++)
       {
           if(count_buff >= lpTotalNumberOfClusters/8)
           {
               break;
           }
           for(int j = 0; j < ui->tableWidget->columnCount(); j++)
               {
               if(count_buff >= lpTotalNumberOfClusters/8)
               {
                   break;
               }
               if(Bitmap->Buffer[count_buff] > 0 && Bitmap->Buffer[count_buff] < 255)
               {
               ui->tableWidget->setItem(i, j, new QTableWidgetItem);
               ui->tableWidget->item(i, j)->setBackground(Qt::red);
               }
               else if(Bitmap->Buffer[count_buff] == 255)
               {
                   ui->tableWidget->setItem(i, j, new QTableWidgetItem);
                   ui->tableWidget->item(i, j)->setBackground(Qt::blue);
               }
               else
               {
                   ui->tableWidget->setItem(i, j, new QTableWidgetItem);
                   ui->tableWidget->item(i, j)->setBackground(Qt::white);
               }
               count_buff++;

               }
           ui->progressBar->setValue(i);
       }


}

void MainWindow::ProccessDefragmentation() // ф-ція яка містить всі ф-ція для дефрагментації
{
    ui->progressBar->setMaximum(1);
    if(!GetListDir(tom_disk))
    {
        ui->statusBar->showMessage("Error, List dir didn create!");
        return;
    }
    if(!StrTokFileDisk())
    {
        ui->statusBar->showMessage("Error. Defragmentation fault");
        return;
    }
    ui->progressBar->setValue(1);
}

void MainWindow::on_actionClose_triggered()
{
    this->close();
}

void MainWindow::FindStartFreeCluster()
{
     GetBitMap(QString::fromStdString(tom_disk.toStdString().substr(0,2)));
     ULONG FreeCluster = 0;
     StartLNC = 0;
     int BitMapMask = 1;
     int tempLNC = 0;
     int ClusterInUse = 0;
 for( long long iteration = 0; iteration < (Bitmap->BitmapSize.QuadPart/8) - 1; iteration++ )
   {
       if(Bitmap->Buffer[iteration] == 255)
       {
           FreeCluster = 0;
           StartLNC+= 8;
           continue;
       }

         while(BitMapMask != 256)
        {
          if(!FreeCluster)
          {
              tempLNC = StartLNC;
            }
            ClusterInUse = Bitmap->Buffer[iteration] & BitMapMask;
            if(!ClusterInUse)
            {
                FreeCluster++;
            }
            else
            {
                FreeCluster = 0;
            }
            BitMapMask <<= 1;
             StartLNC++;
          }
         if(FreeCluster >= 1 )
         {
            StartLNC = tempLNC;
             break;
         }
         BitMapMask = 1;
   }
 }

void MainWindow::FindStartClusterFile()
{
    int size_number; // зміння в якій буде зберігатися номер початково кластера для файла.
    for (long long iteration = StartLNC/8 + 1; iteration< Bitmap->BitmapSize.QuadPart-1; iteration++)
    {
        if(Bitmap->Buffer[iteration] > 0)
        {
            size_number = iteration*8;
            while(1)
            {
                it = map_file.find(size_number);
                if(size_number == it.key())
                {
                    break;
                }
                 size_number++;
            }
            break;
        }
    }
}
bool MainWindow::MoveClusterBlock()
{
    MOVE_FILE_DATA buf_in; // структура для переміщення
    DWORD nBytes = 0;
    HANDLE handle_disk;
    QString temp = "\\\\.\\" + QString::fromStdString(tom_disk.toStdString().substr(0,2));
    handle_disk = CreateFileA(temp.toStdString().c_str() ,
                                   GENERIC_READ,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                   NULL,
                                   OPEN_EXISTING,
                                   NULL,
                                   NULL
                                   );
        if(handle_file == INVALID_HANDLE_VALUE || handle_disk == INVALID_HANDLE_VALUE)
        {
            ui->Information_text->append("invalid handle value!");
        }
        ULONG start_cluster = StartLNC;
        ULONG size_cluster = 0;
        ULONG cluster_file = 0;
        int file_size = GetFileSize(it.value(),NULL);
        buf_in.FileHandle = it.value();
        int send_size = it.key() - start_cluster;
        if(file_size == -1)
        {
            return false;
        }
        else{
        while(size_cluster <= file_size)
        {
            buf_in.StartingLcn.QuadPart = start_cluster;
            buf_in.StartingVcn.QuadPart =cluster_file;
            buf_in.ClusterCount = send_size;
            int result = DeviceIoControl(handle_disk, FSCTL_MOVE_FILE, &buf_in, sizeof(buf_in),
                                         NULL, 0 , &nBytes, NULL);
            result = GetLastError();
            ui->Information_text->append("Defrag:" + QString::number(result));
            start_cluster+= cluster_file + start_cluster;
            if(start_cluster > (it.key() + file_size))
            {break;}
            else
            {

            if((file_size - size_cluster) < (cluster_file - start_cluster))
            {
            cluster_file += cluster_file + start_cluster;
            size_cluster += cluster_file - start_cluster;
            }
            else
            {
                send_size = file_size -size_cluster;
                size_cluster += send_size;
            }
        }
        }
        }
        return true;
}


void MainWindow::on_actionMoveCluster_triggered()
{
    buff_file_path = new char[file_list.length() + 1];
        strcpy(buff_file_path,file_list.toStdString().c_str());
        char* pointer = strtok(buff_file_path,"*");
        while(pointer != NULL)
        {
            GetBitMapFile(pointer,2);
            pointer = strtok(NULL,"*");
        }
        bool exit = true;
        while (exit != false)
        {

        FindStartFreeCluster();
        FindStartClusterFile();
        exit = MoveClusterBlock();
        }
}
