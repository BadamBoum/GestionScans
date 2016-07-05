#include <QDebug>
#include <QDir>
#include <QFile>
#include <QDate>
#include <QTableWidgetItem>
#include <QtNetwork>
#include <QProcess>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add.h"
#include "pdf.h"
#include "setting.h"
#include "seriesbox.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   bool firstLine = false;
   QFile Datafile("datafile.txt");
   Datafile.open(QIODevice::ReadWrite);
   QByteArray DatafileContent = Datafile.readAll();

   if(DatafileContent.isEmpty() == false)
   {
      ui->Tab1TextScreen->append("Database found");
      QByteArrayList DatafileLine = DatafileContent.split('\n');

      foreach(QByteArray line, DatafileLine)
      {
         if(line.isEmpty() == false)
         {
             QByteArrayList ligneSplitee = line.split(';');
            if (firstLine == false)
            {
               GeneralFolder = ligneSplitee.at(0);
               ui->Tab3ScanFolderText->setText(GeneralFolder);
               if(ligneSplitee.at(1) == "AutoSearch=True")
               {
                   ui->Tab3AutoSearch->setChecked(true);
               }
               if(ligneSplitee.at(2) == "Debug=True")
               {
                   ui->DebugBox->setChecked(true);
               }
               firstLine = true;
            }
            else
            {
               QString String = ligneSplitee.at(NAME);
               ui->Tab2StatusTable->insertRow(ui->Tab2StatusTable->rowCount());

               ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, NAME, new QTableWidgetItem(String));
               ui->Tab1SelectedSerie->addItem(ligneSplitee.at(0));

               String = ligneSplitee.at(URL);
               ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, URL, new QTableWidgetItem(String));
               String = ligneSplitee.at(FOLDER);
               ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, FOLDER, new QTableWidgetItem(String));
               String = ligneSplitee.at(VOLUME);
               ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, VOLUME, new QTableWidgetItem(String));
               String = ligneSplitee.at(CHAPTER);
               ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, CHAPTER, new QTableWidgetItem(String));
               String = ligneSplitee.at(DATE);
               ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, DATE, new QTableWidgetItem(String));
               String = ligneSplitee.at(DIGIT);
               ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, DIGIT, new QTableWidgetItem(String));
               String = ligneSplitee.at(EXT);
               ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, EXT, new QTableWidgetItem(String));
               String = ligneSplitee.at(WEEKLY);
               ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, WEEKLY, new QTableWidgetItem(String));
            }
         }
      }
   }

   connect(ui->Tab1AddButton, SIGNAL(clicked(bool)), this, SLOT(slotTab1AddButton()));
   connect(ui->Tab1Setting, SIGNAL(clicked(bool)), this, SLOT(slotTab1Setting()));
//   connect(ui->Tab1PDF, SIGNAL(clicked(bool)), this, SLOT(slotTab1Pdf()));
   connect(ui->Tab1Search, SIGNAL(clicked(bool)), this, SLOT(slotTab1Search()));
   connect(ui->Tab1Delete, SIGNAL(clicked(bool)), this, SLOT(slotTab1Delete()));
   connect(ui->Tab1SearchOne, SIGNAL(clicked(bool)), this, SLOT(slotTab1SearchOne()));
   connect(ui->Tab1OpenFolder, SIGNAL(clicked(bool)), this, SLOT(slotTab1OpenFolder()));
   connect(ui->Tab1SpecificFolder, SIGNAL(clicked(bool)), this, SLOT(slotTab1OpenSeriesFolder()));
   connect(ui->Tab1PDF, SIGNAL(clicked(bool)), this, SLOT(slotTab1PrintPdf()));
   connect(ui->Tab3Save, SIGNAL(clicked(bool)), this, SLOT(slotUpdateFolder()));
   connect(ui->Tab3OpenFold, SIGNAL(clicked(bool)), this, SLOT(slotOpenFolder()));

   if (ui->Tab3AutoSearch->isChecked()) slotTab1Search();
}

MainWindow::~MainWindow()
{
   QFile Datafile("datafile.txt");
   Datafile.open(QIODevice::WriteOnly);
   QTextStream out(&Datafile);
   QString temp;

   temp.append(ui->Tab3ScanFolderText->text());
   temp.append( ";" );
   if (ui->Tab3AutoSearch->isChecked())
   {
       temp.append( "AutoSearch=True" );
   }
   else
   {
       temp.append( "AutoSearch=False" );
   }
   temp.append( ";" );
   if (ui->DebugBox->isChecked())
   {
       temp.append( "Debug=True" );
   }
   else
   {
       temp.append( "Debug=False" );
   }
   temp.append( "\n" );

   for(int i = 0; i < ui->Tab2StatusTable->rowCount(); i++)
   {
      for(int j = 0; j < ui->Tab2StatusTable->columnCount(); j++)
      {
         temp.append( (*ui->Tab2StatusTable->item(i,j)).text() );

         if (j < ui->Tab2StatusTable->columnCount() - 1)
         {
             temp.append( ";" );
         }
      }
      if (i < ui->Tab2StatusTable->rowCount() - 1)
      {
          temp.append( "\n" );
      }
   }

   out << temp;
   out.flush();
   Datafile.flush();
   Datafile.close();

   delete ui;
}

void MainWindow::slotTab1PrintPdf()
{
    PDF *Pdf = new PDF;
    Pdf->show();
}

void MainWindow::slotUpdateFolder()
{
    QString NewFolder = ui->Tab3ScanFolderText->text();
    QString TempTxt;

    for(int i = 0; i < ui->Tab2StatusTable->rowCount(); i++)
    {
        TempTxt = ui->Tab2StatusTable->item(i, FOLDER)->text();
        TempTxt.replace(GeneralFolder, NewFolder);
        ui->Tab2StatusTable->setItem(i, FOLDER, new QTableWidgetItem (TempTxt));
    }

    GeneralFolder = NewFolder;

    ui->Tab1TextScreen->append("");
    ui->Tab1TextScreen->append("Save folder Updated");
}

void MainWindow::slotTab1AddButton()
{
   Add *AddWindows = new Add;
   AddWindows->show();

   connect(AddWindows, SIGNAL(addNewSerie(QStringList)), this, SLOT(AddLineStatusTable(QStringList)));
}

void MainWindow::slotOpenFolder()
{
    ui->Tab3ScanFolderText->setText(QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly));
}

void MainWindow::slotTab1OpenFolder()
{
   QProcess::startDetached("explorer.exe", QStringList() << "/e,/root,"+ui->Tab3ScanFolderText->text());
}

void MainWindow::slotTab1OpenSeriesFolder()
{
   QString folder = "/e,/root,";
   CurrentSerie.SetSeries(GetLineInfos(ui->Tab1SelectedSerie->currentIndex()));
   folder += " \"";
   folder += CurrentSerie.GetSeriesFolder();
   folder += "\"";
   QProcess::startDetached("explorer.exe", QStringList() << folder);
}

void MainWindow::AddLineStatusTable(QStringList NewLine)
{
    ui->Tab1SelectedSerie->addItem(NewLine.at(NAME));

    ui->Tab2StatusTable->insertRow(ui->Tab2StatusTable->rowCount());

    NewLine.removeAt(FOLDER);
    NewLine.insert(FOLDER, GeneralFolder + "\\" + NewLine.at(NAME));

    ModifyStatusTable(NewLine, ui->Tab2StatusTable->rowCount() - 1);

    ui->Tab1TextScreen->append("Series ");
    ui->Tab1TextScreen->insertPlainText(NewLine.at(NAME));
    ui->Tab1TextScreen->insertPlainText(" added");
}

void MainWindow::slotTab1Setting()
{
   Setting *SettingWindows = new Setting;

   connect(this, SIGNAL(SeriesInfo(QStringList, int)), SettingWindows, SLOT(FillWindow(QStringList, int)));
   emit SeriesInfo(GetLineInfos(ui->Tab1SelectedSerie->currentIndex()), ui->Tab1SelectedSerie->currentIndex());

   SettingWindows->show();

   connect(SettingWindows, SIGNAL(ModifySerie(QStringList, int)), this, SLOT(ModifyStatusTable(QStringList, int)));
}

QStringList MainWindow::GetLineInfos(int Idx)
{
   QStringList StringRet;

   StringRet.insert(NAME,    ui->Tab2StatusTable->item(Idx, NAME)->text());
   StringRet.insert(CHAPTER, ui->Tab2StatusTable->item(Idx, CHAPTER)->text());
   StringRet.insert(DATE,    ui->Tab2StatusTable->item(Idx, DATE)->text());
   StringRet.insert(VOLUME,  ui->Tab2StatusTable->item(Idx, VOLUME)->text());
   StringRet.insert(URL,     ui->Tab2StatusTable->item(Idx, URL)->text());
   StringRet.insert(FOLDER,  GeneralFolder);
   StringRet.insert(DIGIT,   ui->Tab2StatusTable->item(Idx, DIGIT)->text());
   StringRet.insert(EXT,     ui->Tab2StatusTable->item(Idx, EXT)->text());
   StringRet.insert(WEEKLY,  ui->Tab2StatusTable->item(Idx, WEEKLY)->text());

   return StringRet;
}

void MainWindow::ModifyStatusTable(QStringList NewLine, int Index)
{
    if (NewLine.at(NAME) != "")
    {
        if (NewLine.at(URL) != "")
        {
            ui->Tab2StatusTable->setItem(Index, NAME,    new QTableWidgetItem(NewLine.at(NAME)));
            ui->Tab2StatusTable->setItem(Index, CHAPTER, new QTableWidgetItem(NewLine.at(CHAPTER)));
            ui->Tab2StatusTable->setItem(Index, DATE,    new QTableWidgetItem(NewLine.at(DATE)));
            ui->Tab2StatusTable->setItem(Index, VOLUME,  new QTableWidgetItem(NewLine.at(VOLUME)));
            ui->Tab2StatusTable->setItem(Index, FOLDER,  new QTableWidgetItem(NewLine.at(FOLDER)+ "\\" + NewLine.at(NAME)));
            ui->Tab2StatusTable->setItem(Index, URL,     new QTableWidgetItem(NewLine.at(URL)));
            ui->Tab2StatusTable->setItem(Index, DIGIT,   new QTableWidgetItem(NewLine.at(DIGIT)));
            ui->Tab2StatusTable->setItem(Index, EXT,     new QTableWidgetItem(NewLine.at(EXT)));
            ui->Tab2StatusTable->setItem(Index, WEEKLY,  new QTableWidgetItem(NewLine.at(WEEKLY)));

            ui->Tab1TextScreen->append("");
            ui->Tab1TextScreen->append("Database update for " + NewLine.at(NAME));
        }
        else
        {
            ui->Tab1TextScreen->append("Error. Missing URL");
        }
    }
    else
    {
        ui->Tab1TextScreen->append("Error. Missing series name");
    }
}

void MainWindow::slotTab1Delete()
{
   ui->Tab1TextScreen->append("Series ");
   ui->Tab1TextScreen->insertPlainText(ui->Tab1SelectedSerie->currentText());
   ui->Tab1TextScreen->insertPlainText(" deleted");
   ui->Tab2StatusTable->removeRow(ui->Tab1SelectedSerie->currentIndex());
   ui->Tab1SelectedSerie->removeItem(ui->Tab1SelectedSerie->currentIndex());
}

void MainWindow::slotTab1Pdf()
{
   ui->Tab1TextScreen->append("PDF");
   //    QPrinter printer;

   //    QPrintDialog *dialog = new QPrintDialog(&printer, this);
   //    dialog->setWindowTitle(tr("Print Document"));
   //    if (editor->textCursor().hasSelection())
   //        dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
   //    if (dialog->exec() != QDialog::Accepted)
   //        return;
   //    IndexOf(Tab1ListOfManga).ligneSplitee.at(3)++;
}

void MainWindow::slotTab1Search()
{
   ui->Tab1TextScreen->append("");
   ui->Tab1TextScreen->append("***Global Search Start***");
   ui->Tab1TextScreen->append("");

   DownloadSeriesIdx    = 0;
   NumberOfSeriesSearch = ui->Tab2StatusTable->rowCount();
   CurrentSerie.SetSeries(GetLineInfos(DownloadSeriesIdx));
   CurrentSerie.UpdateChapterVal();
   CurrentStatus.ExtJpg1   = false;
   CurrentStatus.ExtJpg2   = false;
   CurrentStatus.ExtJpg3   = false;
   CurrentStatus.ExtJpg4   = false;
   CurrentStatus.ExtPng1   = false;
   CurrentStatus.ExtPng2   = false;
   CurrentStatus.ExtPng3   = false;
   CurrentStatus.ExtPng4   = false;
   CurrentStatus.Double    = false;
   CurrentStatus.Np1       = false;
   CurrentStatus.SearchURL = false;

   ui->Tab1TextScreen->append("Searching chapter " + CurrentSerie.GetChapter() + " of " + CurrentSerie.GetSeriesName());
   TestUrl(CurrentSerie.GetURL(ui->Tab2StatusTable->item(0, DIGIT)->text(), ui->Tab2StatusTable->item(0, EXT)->text()));
}

void MainWindow::slotTab1SearchOne()
{
   ui->Tab1TextScreen->append("");
   ui->Tab1TextScreen->append("***Search Start***");
   ui->Tab1TextScreen->append("");

   DownloadSeriesIdx    = ui->Tab1SelectedSerie->currentIndex();
   NumberOfSeriesSearch = 1;
   CurrentSerie.SetSeries(GetLineInfos(DownloadSeriesIdx));
   CurrentSerie.UpdateChapterVal();
   CurrentStatus.ExtJpg1   = false;
   CurrentStatus.ExtJpg2   = false;
   CurrentStatus.ExtJpg3   = false;
   CurrentStatus.ExtJpg4   = false;
   CurrentStatus.ExtPng1   = false;
   CurrentStatus.ExtPng2   = false;
   CurrentStatus.ExtPng3   = false;
   CurrentStatus.ExtPng4   = false;
   CurrentStatus.Double    = false;
   CurrentStatus.Np1       = false;
   CurrentStatus.SearchURL = false;

   ui->Tab1TextScreen->append("Searching chapter " + CurrentSerie.GetChapter() + " of " + CurrentSerie.GetSeriesName());
   TestUrl(CurrentSerie.GetURL(ui->Tab2StatusTable->item(DownloadSeriesIdx, DIGIT)->text(), ui->Tab2StatusTable->item(DownloadSeriesIdx, EXT)->text()));
}

void MainWindow::TestUrl(QUrl url)
{
   erreurTrouvee = false;

   QNetworkRequest requete(url);
   QNetworkAccessManager *m = new QNetworkAccessManager;
   QNetworkReply *r = m->get(requete);

   if(ui->DebugBox->isChecked())
   {
      ui->Tab1TextScreen->append("URL tested :");
      ui->Tab1TextScreen->append(url.toString());
   }

   connect(r, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(messageErreur(QNetworkReply::NetworkError)));
   connect(r, SIGNAL(finished()), this, SLOT(enregistrer()));
}

void MainWindow::messageErreur(QNetworkReply::NetworkError)
{
   if(ui->DebugBox->isChecked())
   {
      ui->Tab1TextScreen->append("");
      ui->Tab1TextScreen->append("***Error Slot***");
   }
   erreurTrouvee = true;
   QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());

   if(ui->DebugBox->isChecked())
   {
      ui->Tab1TextScreen->append("URL return error :");
      ui->Tab1TextScreen->append(r->errorString());
   }

   r->deleteLater();
}

void MainWindow::enregistrer()
{
   if(ui->DebugBox->isChecked())
   {
      ui->Tab1TextScreen->append("");
      ui->Tab1TextScreen->append("***Save Slot***");
   }

   if(!erreurTrouvee)
   {
      if (CurrentStatus.SearchURL == true)
      {
         if(ui->DebugBox->isChecked())
         {
            ui->Tab1TextScreen->append("New Type of URL founded");
         }

         if (CurrentStatus.Np1 == true)
         {
            if(ui->DebugBox->isChecked())
            {
               ui->Tab1TextScreen->append("Image Skip");
            }
         }
         else if (CurrentStatus.Double == true)
         {
            if(ui->DebugBox->isChecked())
            {
               ui->Tab1TextScreen->append("Double Image");
            }
         }
         else if (CurrentStatus.ExtPng4 == true)
         {
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, DIGIT,   new QTableWidgetItem("4"));
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, EXT,     new QTableWidgetItem("png"));

            if(ui->DebugBox->isChecked())
            {
               ui->Tab1TextScreen->append("4 Digit / png");
            }
         }
         else if (CurrentStatus.ExtPng3 == true)
         {
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, DIGIT,   new QTableWidgetItem("3"));
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, EXT,     new QTableWidgetItem("png"));

            if(ui->DebugBox->isChecked())
            {
               ui->Tab1TextScreen->append("3 Digit / png");
            }
         }
         else if (CurrentStatus.ExtPng2 == true)
         {
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, DIGIT,   new QTableWidgetItem("2"));
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, EXT,     new QTableWidgetItem("png"));

            if(ui->DebugBox->isChecked())
            {
               ui->Tab1TextScreen->append("2 Digit / png");
            }
         }
         else if (CurrentStatus.ExtPng1 == true)
         {
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, DIGIT,   new QTableWidgetItem("1"));
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, EXT,     new QTableWidgetItem("png"));

            if(ui->DebugBox->isChecked())
            {
               ui->Tab1TextScreen->append("1 Digit / png");
            }
         }
         else if (CurrentStatus.ExtJpg4 == true)
         {
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, DIGIT,   new QTableWidgetItem("4"));
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, EXT,     new QTableWidgetItem("jpg"));

            if(ui->DebugBox->isChecked())
            {
               ui->Tab1TextScreen->append("4 Digit / jpg");
            }
         }
         else if (CurrentStatus.ExtJpg3 == true)
         {
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, DIGIT,   new QTableWidgetItem("3"));
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, EXT,     new QTableWidgetItem("jpg"));

            if(ui->DebugBox->isChecked())
            {
               ui->Tab1TextScreen->append("3 Digit / jpg");
            }
         }
         else if (CurrentStatus.ExtJpg2 == true)
         {
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, DIGIT,   new QTableWidgetItem("2"));
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, EXT,     new QTableWidgetItem("jpg"));

            if(ui->DebugBox->isChecked())
            {
               ui->Tab1TextScreen->append("2 Digit / jpg");
            }
         }
         else if (CurrentStatus.ExtJpg1 == true)
         {
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, DIGIT,   new QTableWidgetItem("1"));
            ui->Tab2StatusTable->setItem(DownloadSeriesIdx, EXT,     new QTableWidgetItem("jpg"));

            if(ui->DebugBox->isChecked())
            {
               ui->Tab1TextScreen->append("1 Digit / jpg");
            }
         }
         else
         {
            if(ui->DebugBox->isChecked())
            {
               ui->Tab1TextScreen->append("Error when search new URL type");
            }
         }

         CurrentStatus.ExtJpg1   = false;
         CurrentStatus.ExtJpg2   = false;
         CurrentStatus.ExtJpg3   = false;
         CurrentStatus.ExtJpg4   = false;
         CurrentStatus.ExtPng1   = false;
         CurrentStatus.ExtPng2   = false;
         CurrentStatus.ExtPng3   = false;
         CurrentStatus.ExtPng4   = false;
         CurrentStatus.Double    = false;
         CurrentStatus.Np1       = false;
         CurrentStatus.SearchURL = false;
      }

      QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
      bool FolderExist = true;

      if(QDir(CurrentSerie.GetSeriesFolder()).exists() == false)
      {
         QDir().mkdir(CurrentSerie.GetSeriesFolder());

         if(QDir(CurrentSerie.GetSeriesFolder()).exists() == false)
         {
             ui->Tab1TextScreen->append("Error. Can't create new Folder");
             FolderExist = false;
         }
         else
         {
             ui->Tab1TextScreen->append("");
             ui->Tab1TextScreen->append("CreateFolder :");
             ui->Tab1TextScreen->append(CurrentSerie.GetSeriesFolder());
         }
      }

      if(QDir(CurrentSerie.GetChapterFolder()).exists() == false)
      {
         QDir().mkdir(CurrentSerie.GetChapterFolder());

         if(QDir(CurrentSerie.GetSeriesFolder()).exists() == false)
         {
             ui->Tab1TextScreen->append("Error. Can't create new Folder");
             FolderExist = false;
         }
         else
         {
             ui->Tab1TextScreen->append("");
             ui->Tab1TextScreen->append("CreateFolder :");
             ui->Tab1TextScreen->append(CurrentSerie.GetChapterFolder());
         }
      }

      if (FolderExist == true)
      {
          QString ImgName = CurrentSerie.GetImgFolder();

          ImgName.remove(ImgName.size() - 3, 3);
//          ImgName += ui->Tab2StatusTable->item(DownloadSeriesIdx, EXT)->text();
          QByteArray DatafileContent = r->readAll();
          if (  ((unsigned char)DatafileContent.at(0) == 0xFF)
             && ((unsigned char)DatafileContent.at(1) == 0xD8)
             && ((unsigned char)DatafileContent.at(2) == 0xFF))
          {
              ImgName += "jpg";
          }
          else
          {
              ImgName += "png";
          }

          QFile f(ImgName);

          if (f.open(QIODevice::WriteOnly))
          {
             f.write(DatafileContent);
             f.close();
             r->deleteLater();
          }

          if(ui->DebugBox->isChecked())
          {
             ui->Tab1TextScreen->append("URL saved :");
             ui->Tab1TextScreen->append(r->url().toString());
             ui->Tab1TextScreen->append(CurrentSerie.GetImgFolder());
          }
          downloadNextImage(true);
      }
   }
   else
   {
      CurrentStatus.SearchURL = true;

      if (CurrentStatus.ExtJpg2 == false)
      {
         CurrentStatus.ExtJpg2 = true;
         TestUrl(CurrentSerie.GetURL(2, "jpg"));
      }
      else if (CurrentStatus.ExtJpg3 == false)
      {
         CurrentStatus.ExtJpg3 = true;
         TestUrl(CurrentSerie.GetURL(3, "jpg"));
      }
      else if (CurrentStatus.ExtJpg4 == false)
      {
         CurrentStatus.ExtJpg4 = true;
         TestUrl(CurrentSerie.GetURL(4, "jpg"));
      }
      else if (CurrentStatus.ExtJpg1 == false)
      {
         CurrentStatus.ExtJpg1 = true;
         TestUrl(CurrentSerie.GetURL(1, "jpg"));
      }
      else if (CurrentStatus.ExtPng2 == false)
      {
         CurrentStatus.ExtPng2 = true;
         TestUrl(CurrentSerie.GetURL(2, "png"));
      }
      else if (CurrentStatus.ExtPng3 == false)
      {
         CurrentStatus.ExtPng3 = true;
         TestUrl(CurrentSerie.GetURL(3, "png"));
      }
      else if (CurrentStatus.ExtPng4 == false)
      {
         CurrentStatus.ExtPng4 = true;
         TestUrl(CurrentSerie.GetURL(4, "png"));
      }
      else if (CurrentStatus.ExtPng1 == false)
      {
         CurrentStatus.ExtPng1 = true;
         TestUrl(CurrentSerie.GetURL(1, "png"));
      }
      else if (CurrentStatus.Double == false)
      {
         CurrentStatus.Double = true;
         QString DoubleUrl = CurrentSerie.GetURL(2, "");
         DoubleUrl.remove(DoubleUrl.size() - 1, 1);
         CurrentSerie.UpdateImageVal();
         DoubleUrl += "-" + CurrentSerie.GetURL(2, "").remove(0, CurrentSerie.GetURL(2, "").size() - 3) + ui->Tab2StatusTable->item(DownloadSeriesIdx, EXT)->text();
         TestUrl(DoubleUrl);
      }
      else if (CurrentStatus.Np1 == false)
      {
          CurrentStatus.Np1 = true;
          TestUrl(CurrentSerie.GetURL(ui->Tab2StatusTable->item(DownloadSeriesIdx, DIGIT)->text(), ui->Tab2StatusTable->item(DownloadSeriesIdx, EXT)->text()));
      }
      else
      {
         if(ui->DebugBox->isChecked())
         {
            ui->Tab1TextScreen->append("URL not found");
         }

         CurrentStatus.ExtJpg1   = false;
         CurrentStatus.ExtJpg2   = false;
         CurrentStatus.ExtJpg3   = false;
         CurrentStatus.ExtJpg4   = false;
         CurrentStatus.ExtPng1   = false;
         CurrentStatus.ExtPng2   = false;
         CurrentStatus.ExtPng3   = false;
         CurrentStatus.ExtPng4   = false;
         CurrentStatus.Double    = false;
         CurrentStatus.Np1       = false;
         CurrentStatus.SearchURL = false;
         downloadNextImage(false);
      }
   }

   erreurTrouvee = false;
}

void MainWindow::downloadNextImage(bool lastStatus)
{
   CurrentSerie.UpdateImageVal();

   if (  ((CurrentSerie.GetImageVal() < 100) && (lastStatus == true))
      || (CurrentSerie.GetImageVal() < 5))
   {
      TestUrl(CurrentSerie.GetURL(ui->Tab2StatusTable->item(DownloadSeriesIdx, DIGIT)->text(), ui->Tab2StatusTable->item(DownloadSeriesIdx, EXT)->text()));
   }
   else
   {
      if(QDir(CurrentSerie.GetChapterFolder()).exists() == true)
      {
         long chapterValue = ui->Tab2StatusTable->item(DownloadSeriesIdx, CHAPTER)->text().toLong();
         chapterValue++;
         QString ChapterTxt;
         ChapterTxt.setNum(chapterValue);
         ui->Tab2StatusTable->setItem(DownloadSeriesIdx, CHAPTER, new QTableWidgetItem(ChapterTxt));
         if(ui->Tab2StatusTable->item(DownloadSeriesIdx, WEEKLY)->text() == "true")
         {
            //slotTab1PrintPdf(CurrentSerie.GetChapterFolder());
         }

         ui->Tab1TextScreen->append("Chapter " + CurrentSerie.GetChapter() + " of " + CurrentSerie.GetSeriesName() + " store in \"" + CurrentSerie.GetChapterFolder() + "\"");
      }
      else
      {
         ui->Tab1TextScreen->append("Chapter " + CurrentSerie.GetChapter() + " of " + CurrentSerie.GetSeriesName() + " not found");
      }

      DownloadSeriesIdx++;
      if (DownloadSeriesIdx < NumberOfSeriesSearch)
      {
         CurrentSerie.SetSeries(GetLineInfos(DownloadSeriesIdx));
         CurrentSerie.UpdateChapterVal();

         ui->Tab1TextScreen->append("");
         ui->Tab1TextScreen->append("Searching chapter " + CurrentSerie.GetChapter() + " of " + CurrentSerie.GetSeriesName());
         TestUrl(CurrentSerie.GetURL(ui->Tab2StatusTable->item(DownloadSeriesIdx, DIGIT)->text(), ui->Tab2StatusTable->item(DownloadSeriesIdx, EXT)->text()));
      }
      else
      {
         ui->Tab1TextScreen->append("");
         ui->Tab1TextScreen->append("***Search ended***");

         if ((NumberOfSeriesSearch == 1) && (ui->LoopSearch->isChecked()))
         {
             if(QDir(CurrentSerie.GetChapterFolder()).exists() == true)
             {
                 slotTab1SearchOne();
             }
         }
      }
   }
}
