# picturePlayer
本项目是为数模竞赛所做的客户端。其题目是在视频中识别无人机并将其标出。本程序所做功能为，不断查询某文件夹内是否有新的图片生成，若有，则缓存至内存，并按时在界面中刷新。此外带有帧回溯和显示无人机信息的功能。原本是使用openCV读取视频，但发现对于一个正在写入的视频，openCV无法获取其总帧数，于是改为读视频分解出的图片。
界面截图：
![](https://raw.githubusercontent.com/azure42/picturePlayer/master/snap.png)
