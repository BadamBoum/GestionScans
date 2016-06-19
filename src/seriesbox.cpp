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

QString SeriesBox::GetSeriesFolder()
{
   QString folder = SeriesFolder;

   if(folder.right(1) != "\\")
   {
      folder+= "\\";
   }

   folder += SeriesName;

   return folder;
}

QString SeriesBox::GetChapterFolder()
{
   QString folder = SeriesFolder;

   if(folder.right(1) != "\\")
   {
      folder+= "\\";
   }

   folder += SeriesName;
   folder += "\\";
   folder += ChapterVal;

   return folder;
}

QString SeriesBox::GetImgFolder()
{
   QString folder = SeriesFolder;
   QString convertion;

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

   convertion.setNum(ImageVal);
   if (ImageVal < 10)
   {
      convertion.push_front("0");
   }

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

QString SeriesBox::GetURLjpg()
{
   QString imageURLjpg = this->GetURL();

   imageURLjpg.remove(imageURLjpg.size() - 3, 3);
   imageURLjpg += "jpg";

   return imageURLjpg;
}

QString SeriesBox::GetURLpng()
{
   QString imageURLpng = this->GetURL();

   imageURLpng.remove(imageURLpng.size() - 3, 3);
   imageURLpng += "png";

   return imageURLpng;
}

int SeriesBox::GetImageVal()
{
   return ImageVal;
}
