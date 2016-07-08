#ifndef PICCACHE_H
#define PICCACHE_H
#include <QThread>
#include <QDir>
#include <QDebug>
#include <QPixmap>
#include <QList>
struct pic
{
    QPixmap pixmap;//jpg文件预先处理为位图，提高性能
    bool uavFlag;//该帧是否检测到无人机
    int uavNum;//第几次检测到无人机，无则为-1
};

class PicCache : public QThread
{
//    Q_OBJECT
public:
    PicCache(QDir *dir);
    QList<pic> *picList;
    int oldFileCount,picWidth,picHeight;
private:
    int uavCount;
    QDir *dir;
    int readCount;
    QFileInfoList fileList,newFileList;
    void run();
    QPixmap tmpPixmap;
};


#endif // PICCACHE_H
