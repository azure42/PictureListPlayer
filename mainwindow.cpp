#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    playFlag = false;
    tmpTime = QTime::currentTime();
    timeCount = 0;
    updateCount = 0;
    flagCount = 0;

    videoTimer = new QTimer(this);
    msgTimer = new QTimer(this);
    connect(msgTimer,SIGNAL(timeout()),this,SLOT(msgUpdate()));
    connect(videoTimer,SIGNAL(timeout()),this,SLOT(imgUpdate()));



    ui->openButton->hide();
    //    ui->timeLabel->hide();


    dir = new QDir("C:/Windows/temp/temp_picture");
    picCache = new PicCache(dir);
    picCache->start();

    ui->detailList->addItem("已缓存帧数");
    ui->detailList->addItem("0");
    ui->detailList->addItem("当前帧数");
    ui->detailList->addItem("0");
    ui->detailList->addItem("无人机坐标");
    ui->detailList->addItem("0 0 0 0");

    red.load(":/new/prefix1/img/light-red.png");
    gray.load(":/new/prefix1/img/light-gray.png");

    ui->flagLabel->setPixmap(gray);

    //    QPixmap tmp;
    //    tmp.load("C:/Windows/Temp/temp_picture/00001.jpg");
    //    ui->imgLabel->setPixmap(tmp);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::imgUpdate()
{
    if(updateCount < picCache->picList->count())
    {
//        if(picCache->picList->at(updateCount).pixmap.isNull() == false)
            ui->imgLabel->setPixmap(picCache->picList->at(updateCount).pixmap);

            QPixmap tmp = picCache->picList->at(updateCount).pixmap;

//            qDebug()<<tmp.isNull();
//            qDebug()<<tmp.size().height()<<"x"<<tmp.size().width();


//        qDebug()<<"缓存:"<<picCache->picList->count();
//        qDebug()<<"刷新界面:"<<updateCount;
        updateCount++;
        if(picCache->picList->at(updateCount -1).flag == true)
        {
            infoFile = new QFile("C:\\windows\\temp\\temp_picture\\position.txt");
            infoFile->open(QFile::ReadOnly | QFile::Truncate);

            ui->flagLabel->setPixmap(red);
            flagCount ++;


                QTextStream in(infoFile);
                QString str;
                for(int i=0;i<flagCount;i++)
                {
                    str = in.readLine();
//                    qDebug()<<flagCount<<"\t"<<str;

                }
                ui->detailList->item(5)->setText(str);

        }
        else  ui->flagLabel->setPixmap(gray);

    }
//    else qDebug()<<"缓存慢于界面刷新"<<"cache:"<<picCache->picList->count();
}

void MainWindow::msgUpdate()
{
    if(picCache->picList->count() != 0)
        ui->timeSlider->setValue(100.0*updateCount/picCache->picList->count());
    ui->detailList->item(1)->setText(QString::number(picCache->picList->count()));
    ui->detailList->item(3)->setText(QString::number(updateCount));
    ui->timeLabel->setText(QString::number(updateCount));


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
        videoTimer->start(40);

    }

}


void MainWindow::on_timeSlider_sliderMoved(int position)
{
    updateCount = picCache->picList->count()/100.0*position;
    ui->timeLabel->setText(QString::number(updateCount));
    ui->playButton->setIcon(QIcon(":/new/prefix1/img/pause.png"));
    videoTimer->stop();
}
