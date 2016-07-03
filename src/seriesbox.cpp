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
   VolumeVal    = Datas.at(VOLUME);
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

void SeriesBox::DecreaseChapterVal()
{
   long value = ChapterVal.toLong();

   value--;

   ChapterVal.setNum(value);
}

QString SeriesBox::GetSeriesName()
{
   return SeriesName;
}

QString SeriesBox::GetVolume()
{
   return VolumeVal;
}

QString SeriesBox::GetChapter()
{
   return ChapterVal;
}

int SeriesBox::GetImageVal()
{
   return ImageVal;
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

QString SeriesBox::GetURL(int NbOfDigit, QString ExtFile)
{
   QString imageURL = SeriesURL;
   QString convertion;

   convertion.setNum(ImageVal);

   if ((ImageVal < 10) && (NbOfDigit >= 2))
   {
      convertion.push_front("0");
   }
   if ((ImageVal < 100) && (NbOfDigit >= 3))
   {
      convertion.push_front("0");
   }
   if ((ImageVal < 1000) && (NbOfDigit >= 4))
   {
      convertion.push_front("0");
   }

   imageURL.replace("[Chapter]", ChapterVal);
   imageURL.replace("[Image]", convertion);

   imageURL.remove(imageURL.size() - 3, 3);
   imageURL += ExtFile;

   return imageURL;
}

QString SeriesBox::GetURL(QString NbOfDigit, QString ExtFile)
{
   return GetURL(NbOfDigit.toInt(), ExtFile);
}
