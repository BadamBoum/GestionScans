#include <QDebug>

#include "seriesbox.h"

SeriesBox::SeriesBox() : SeriesName("No Series"), ChapterVal("001"), SeriesFolder("C:\\ScanManager\\NoFolder"), SeriesURL(""), ImageVal(0)
{
}

void SeriesBox::SetSeries(QStringList Datas)
{
   SeriesName   = Datas.at(NAME);
   ChapterVal   = Datas.at(CHAPTER);
   SeriesFolder = Datas.at(FOLDER);
   SeriesURL    = Datas.at(URL);
   ImageVal     = 1;
}

void SeriesBox::UpdateImageVal()
{
   ImageVal++;
}

void SeriesBox::UpdateChapterVal()
{
   long value = ChapterVal.toLong();

   value++;

   ChapterVal.setNum(value);
}

QString SeriesBox::GetSeriesName()
{
   return SeriesName;
}

QString SeriesBox::GetChapter()
{
   return ChapterVal;
}

QString SeriesBox::GetImgFolder()
{
   QString folder = SeriesFolder;
   QString convertion;

   convertion.setNum(ImageVal);
   if (ImageVal < 10)
   {
      convertion.push_front("0");
   }

   if(folder.right(1) != "\\")
   {
      folder+= "\\";
   }

   folder += SeriesName;
   folder += "\\";
   folder += ChapterVal;
   folder += "\\";
   folder += ChapterVal;
   folder += "_";
   folder += convertion;
   folder += ".";
   folder += SeriesURL.right(3);

   return folder;
}

QString SeriesBox::GetURL()
{
   QString imageURL = SeriesURL;
   QString convertion;

   convertion.setNum(ImageVal);
   if (ImageVal < 10)
   {
      convertion.push_front("0");
   }

   imageURL.replace("[Chapter]", ChapterVal);
   imageURL.replace("[Image]", convertion);

   return imageURL;
}

int SeriesBox::GetImageVal()
{
   return ImageVal;
}
