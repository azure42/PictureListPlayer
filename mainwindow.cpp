#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    playFlag = false;
    updateCount = 0;

    videoTimer = new QTimer(this);
    msgTimer = new QTimer(this);
    connect(msgTimer,SIGNAL(timeout()),this,SLOT(msgUpdate()));
    connect(videoTimer,SIGNAL(timeout()),this,SLOT(imgUpdate()));

    ui->openButton->hide();

    dir = new QDir("C:/Windows/temp/temp_picture");
    picCache = new PicCache(dir);
    picCache->start();

    ui->detailList->addItem("已缓存帧数");
    ui->detailList->addItem("0");
    ui->detailList->addItem("当前帧数");
    ui->detailList->addItem("0");
    ui->detailList->addItem("无人机坐标");
    ui->detailList->addItem("");
    ui->detailList->addItem("");

    red.load(":/new/prefix1/img/light-red.png");
    gray.load(":/new/prefix1/img/light-gray.png");

    ui->flagLabel->setPixmap(gray);
    msgTimer->start(1000);
    //    QPixmap tmp;
    //    tmp.load("C:/Windows/Temp/temp_picture/00001.jpg");
    //    ui->imgLabel->setPixmap(tmp);
}

MainWindow::~MainWindow()
{
    delete ui;
    system("taskkill /im UAV_detection.exe /f");

}

void MainWindow::imgUpdate()
{
    if(updateCount < picCache->picList->count())
    {
        ui->imgLabel->setPixmap(picCache->picList->at(updateCount).pixmap); //刷新图像
        updateCount++;//刷新图像的编号，和list中的编号一一对应
        if(picCache->picList->at(updateCount -1).uavFlag == true)//若发现无人机，则在文件中寻找坐标信息
        {
            infoFile = new QFile("C:\\windows\\temp\\temp_picture\\position.txt");
            infoFile->open(QFile::ReadOnly | QFile::Truncate);
            ui->flagLabel->setPixmap(red);
            qDebug()<<picCache->picList->at(updateCount -1).uavNum;
            QTextStream in(infoFile);
            for(int i=0 ; i< picCache->picList->at(updateCount -1).uavNum ; i++)
            {
                matStr = in.readLine();
            }


        }
        else
            {
            ui->flagLabel->setPixmap(gray);
            matStr = "0 0 0 0";
            }

    }
    //        else qDebug()<<"缓存慢于界面刷新";

}

void MainWindow::msgUpdate()
{
    if(picCache->picList->count() != 0)
        ui->timeSlider->setValue(100.0*updateCount/picCache->picList->count());
    ui->detailList->item(1)->setText(QString::number(picCache->picList->count()));
    ui->detailList->item(3)->setText(QString::number(updateCount));
    ui->timeLabel->setText(QString::number(updateCount));
    QString str0 = matStr.section(' ',0,0);
    QString str1 = matStr.section(' ',1,1);
    QString str2 = matStr.section(' ',2,2);
    QString str3 = matStr.section(' ',3,3);
    QString tmp = "("+str0 + "," + str1 + ") ->";
    QString tmp2 = "("+str2 + "," + str3 + ")";
    ui->detailList->item(5)->setText(tmp);
    ui->detailList->item(6)->setText(tmp2);
}

void MainWindow::on_playButton_clicked()
{
    playFlag = !playFlag;
    if(playFlag)
    {
        ui->playButton->setIcon(QIcon(":/new/prefix1/img/play.png"));
        videoTimer->stop();
    }
    else
    {
        ui->playButton->setIcon(QIcon(":/new/prefix1/img/pause.png"));
        videoTimer->start(100);
    }
}


void MainWindow::on_timeSlider_sliderMoved(int position)
{
    updateCount = picCache->picList->count()/100.0*position;
    ui->timeLabel->setText(QString::number(updateCount));
    ui->playButton->setIcon(QIcon(":/new/prefix1/img/play.png"));
    videoTimer->stop();
    imgUpdate();
}

void MainWindow::on_detailButton_clicked()
{
    static bool flag = false;
    if(flag)
        ui->detailButton->setIcon(QIcon(":/new/prefix1/img/details.png"));
    else
        ui->detailButton->setIcon(QIcon(":/new/prefix1/img/details_gray.png"));
    flag = !flag;

}
