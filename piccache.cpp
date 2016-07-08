#include "piccache.h"

PicCache::PicCache(QDir *dirInput)
{
    dir = dirInput;
    dir->setFilter(QDir::Files|QDir::Hidden|QDir::NoSymLinks);
    dir->setSorting(QDir::Time|QDir::Reversed);
    QStringList filters;
    filters << "*.jpg";
    dir->setNameFilters(filters);
    fileList = dir->entryInfoList();
    picList = new QList<struct pic>;
    readCount = 0;
    uavCount = 0;
    oldFileCount = 0;
    picHeight = 0;
    picWidth = 0;
}

void PicCache::run()
{   //readCount是读取文件的总个数，newCount是当前循环新增文件的个数
    //fileList是文件信息的总列表，newFileList是当前循环的差量列表
    while (1)
    {
        oldFileCount = dir->count();//刷新之前文件的个数
        dir->refresh();
        newFileList = dir->entryInfoList();
        fileList = newFileList;
        newFileList = newFileList.mid(oldFileCount);//从新列表中剔除旧的列表中的内容，增量修改
        readCount = picList->count();
        if(readCount < fileList.count())
        {//循环嵌套，大循环刷新文件夹， 小循环把这次刷新到的文件加入缓存
            int newCount;
            for(newCount = 0;newCount < newFileList.count();newCount++)
            {
                pic tmp;
                if(newFileList.at(newCount).fileName().contains("_"))
                {
                    tmp.uavFlag = true;

                    tmp.uavNum = uavCount;
                    uavCount ++;
                }
                else
                {
                    tmp.uavFlag = false;
                    tmp.uavNum = -1;
                }
                while( tmp.pixmap.load(newFileList.at(newCount).filePath()) == false)
                    msleep(50);
                picWidth = tmp.pixmap.width();
                picHeight = tmp.pixmap.height();
                tmp.uavFlag = -1;
                picList->append(tmp);

            }
        }
//        else qDebug()<<"缓存快于文件生成";
    }
}



