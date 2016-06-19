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
}

void PicCache::run()
{//readCount是读取文件的总个数，newCount是当前循环新增文件的个数
    //fileList是文件信息的总列表，newFileList是当前循环的差量列表
    while (1)
    {
        int oldFileCount = 0;
        oldFileCount = dir->count();//刷新之前文件的个数
        dir->refresh();
        newFileList = dir->entryInfoList();
        fileList = newFileList;
        newFileList = newFileList.mid(oldFileCount);//从新列表中剔除旧的列表中的内容，增量修改
//        qDebug()<<"file:"<<fileList.count()<<"---"<<dir->count();
//        qDebug()<<"新文件"<<newFileList.count();
        readCount = picList->count();
        if(readCount < fileList.count())
        {//循环嵌套，大循环刷新文件夹， 小循环把这次刷新到的文件加入缓存
            int newCount;
            for(newCount = 0;newCount < newFileList.count();newCount++)
            {
                pic tmp;
                if(newFileList.at(newCount).fileName().contains("_"))
                {
//                    qDebug()<<"！检测到无人机";
                    tmp.flag = true;
                }
                else
                {
//                    qDebug()<<"添加图片到缓存"<<newCount;
                    tmp.flag = false;
                }
                while( tmp.pixmap.load(newFileList.at(newCount).filePath()) == false);
                picList->append(tmp);

//                newFileList.at(newCount);
//                qDebug()<<"before"<<tmp.pixmap.isNull();
//                qDebug()<<tmp.pixmap.size().height()<<"x"<<tmp.pixmap.size().width();

//                qDebug()<<"新存入了"<<newFileList.count();
            }
        }
//        else qDebug()<<"缓存快于文件生成";
    }
}



