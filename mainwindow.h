#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "piccache.h"
#include "QTimer"
#include <QTime>
#include <QLabel>
#include <QDir>
#include <QDebug>
#include <QPixmap>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int fpsCount;

private slots:
//    void on_openButton_clicked();
    void imgUpdate();
    void msgUpdate();
//    void on_openButton_clicked();
    void on_playButton_clicked();
    void on_timeSlider_sliderMoved(int position);

private:
    QTime tmpTime;
    Ui::MainWindow *ui;
    QTimer *videoTimer;
    QTimer *msgTimer;
    PicCache *picCache;
    int updateCount;//当前显示的帧数编号，和缓存列表里的一一对应
    QDir *dir;
    QFile *infoFile;
    bool playFlag,endFlag;//playFlag表示暂停/播放，endflag表示是否到达文件末尾（逐帧播放功能）
    QPixmap red,gray;
    int timeCount,flagCount;
    QLabel newLabel;
};

#endif // MAINWINDOW_H
