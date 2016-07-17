#ifndef SERIESBOX_H
#define SERIESBOX_H

#include "qstring.h"

class SeriesBox
{
public:
   SeriesBox();
   void    SetSeries(QStringList Datas);
   void    SetVolume(int vol);
   void    SetChapter(int chapt);
   void    UpdateImageVal();
   void    DecreaseImageVal();
   void    UpdateChapterVal();
   void    DecreaseChapterVal();
   QString GetSeriesName();
   QString GetChapter();
   QString GetSeriesFolder();
   QString GetChapterFolder();
   QString GetVolume();
   QString GetImgFolder();
   QString GetURL(int NbOfDigit, QString ExtFile);
   QString GetURL(QString NbOfDigit, QString ExtFile);
   SeriesBox &operator=(SeriesBox *box);
   int     GetImageVal();

private:
   QString SeriesName;
   QString ChapterVal;
   QString VolumeVal;
   QString SeriesFolder;
   QString SeriesURL;
   int     ImageVal;
   enum Column
   {
      NAME, CHAPTER, DATE, VOLUME, FOLDER, URL
   };
};

#endif // SERIESBOX_H
