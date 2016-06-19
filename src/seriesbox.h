#ifndef SERIESBOX_H
#define SERIESBOX_H

#include "qstring.h"

class SeriesBox
{
public:
   SeriesBox();
   void    SetSeries(QStringList Datas);
   void    UpdateImageVal();
   void    UpdateChapterVal();
   QString GetSeriesName();
   QString GetChapter();
   QString GetImgFolder();
   QString GetURL();
   int     GetImageVal();

private:
   QString SeriesName;
   QString ChapterVal;
   QString SeriesFolder;
   QString SeriesURL;
   int     ImageVal;
   enum Column
   {
      NAME, CHAPTER, DATE, VOLUME, FOLDER, URL
   };
};

#endif // SERIESBOX_H
