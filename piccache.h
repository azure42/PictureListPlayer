#ifndef PICCACHE_H
#define PICCACHE_H
#include <QThread>
#include <QDir>
#include <QDebug>
#include <QPixmap>
#include <QList>
struct pic
{
    QPixmap pixmap;
    bool flag;
};

class PicCache : public QThread
{
//    Q_OBJECT
public:
    PicCache(QDir *dir);
    QList<pic> *picList;

private:
    QDir *dir;
    int readCount;
    QFileInfoList fileList,newFileList;
    void run();
    QPixmap tmpPixmap;
};


#endif // PICCACHE_H
