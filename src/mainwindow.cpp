#include <QDebug>
#include <QDir>
#include <QFile>
#include <QDate>
#include <QTableWidgetItem>
#include <QtNetwork>
#include <QProcess>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add.h"
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
      ui->Tab1TextScreen->append("Database founded");
      QByteArrayList DatafileLine = DatafileContent.split('\n');

      foreach(QByteArray line, DatafileLine)
      {
         if(line.isEmpty() == false)
         {
            if (firstLine == false)
            {
               GeneralFolder = line;
               ui->Tab3ScanFolderText->setText(GeneralFolder);
               firstLine = true;
            }
            else
            {
               QByteArrayList ligneSplitee = line.split(';');
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
            }
         }
      }
   }

   connect(ui->Tab1AddButton, SIGNAL(clicked(bool)), this, SLOT(slotTab1AddButton()));
   connect(ui->Tab1Setting, SIGNAL(clicked(bool)), this, SLOT(slotTab1Setting()));
   connect(ui->Tab1PDF, SIGNAL(clicked(bool)), this, SLOT(slotTab1Pdf()));
   connect(ui->Tab1Search, SIGNAL(clicked(bool)), this, SLOT(slotTab1Search()));
   connect(ui->Tab1Delete, SIGNAL(clicked(bool)), this, SLOT(slotTab1Delete()));
   connect(ui->Tab1SearchOne, SIGNAL(clicked(bool)), this, SLOT(slotTab1SearchOne()));
   connect(ui->Tab1OpenFolder, SIGNAL(clicked(bool)), this, SLOT(slotTab1OpenFolder()));
   connect(ui->Tab1SpecificFolder, SIGNAL(clicked(bool)), this, SLOT(slotTab1OpenSeriesFolder()));
}

MainWindow::~MainWindow()
{
   QFile Datafile("datafile_out.txt");
   Datafile.open(QIODevice::WriteOnly);
   QTextStream out(&Datafile);
   QString temp;

   temp.append(ui->Tab3ScanFolderText->text());
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

void MainWindow::slotTab1AddButton()
{
   Add *AddWindows = new Add;
   AddWindows->show();

   connect(AddWindows, SIGNAL(addNewSerie(QStringList)), this, SLOT(AddLineStatusTable(QStringList)));
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

   return StringRet;
}

void MainWindow::ModifyStatusTable(QStringList NewLine, int Index)
{
    ui->Tab2StatusTable->setItem(Index, NAME,    new QTableWidgetItem(NewLine.at(NAME)));
    ui->Tab2StatusTable->setItem(Index, CHAPTER, new QTableWidgetItem(NewLine.at(CHAPTER)));
    ui->Tab2StatusTable->setItem(Index, DATE,    new QTableWidgetItem(NewLine.at(DATE)));
    ui->Tab2StatusTable->setItem(Index, VOLUME,  new QTableWidgetItem(NewLine.at(VOLUME)));
    ui->Tab2StatusTable->setItem(Index, FOLDER,  new QTableWidgetItem(NewLine.at(FOLDER)));
    ui->Tab2StatusTable->setItem(Index, URL,     new QTableWidgetItem(NewLine.at(URL)));
    ui->Tab2StatusTable->setItem(Index, DIGIT,   new QTableWidgetItem(NewLine.at(DIGIT)));
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

   DownloadSeriesIdx    = 0;
   NumberOfSeriesSearch = ui->Tab2StatusTable->rowCount();
   CurrentSerie.SetSeries(GetLineInfos(DownloadSeriesIdx));
   CurrentSerie.UpdateChapterVal();

   TestUrl(CurrentSerie.GetURL());
}

void MainWindow::slotTab1SearchOne()
{
   ui->Tab1TextScreen->append("");
   ui->Tab1TextScreen->append("***Search Start***");

   DownloadSeriesIdx    = ui->Tab1SelectedSerie->currentIndex();
   NumberOfSeriesSearch = 1;
   CurrentSerie.SetSeries(GetLineInfos(DownloadSeriesIdx));
   CurrentSerie.UpdateChapterVal();

   TestUrl(CurrentSerie.GetURL());
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
//      ui->Tab1TextScreen->append(url);
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
      QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());

      if(QDir(CurrentSerie.GetSeriesFolder()).exists() == false)
      {
         ui->Tab1TextScreen->append("");
         ui->Tab1TextScreen->append("CreateFolder :");
         ui->Tab1TextScreen->append(CurrentSerie.GetSeriesFolder());
         QDir().mkdir(CurrentSerie.GetSeriesFolder());
      }

      if(QDir(CurrentSerie.GetChapterFolder()).exists() == false)
      {
         ui->Tab1TextScreen->append("");
         ui->Tab1TextScreen->append("CreateFolder :");
         ui->Tab1TextScreen->append(CurrentSerie.GetChapterFolder());
         QDir().mkdir(CurrentSerie.GetChapterFolder());
      }

      QFile f(CurrentSerie.GetImgFolder());

      if (f.open(QIODevice::WriteOnly))
      {
         f.write(r->readAll());
         f.close();
         r->deleteLater();
      }

      if(ui->DebugBox->isChecked())
      {
         ui->Tab1TextScreen->append("URL saved :");
         ui->Tab1TextScreen->append(r->url().toString());
      }

      ui->Tab1TextScreen->append(CurrentSerie.GetImgFolder());
      downloadNextImage(true);
   }
   else
   {
      downloadNextImage(false);
   }

   erreurTrouvee = false;
}

void MainWindow::downloadNextImage(bool lastStatus)
{
   CurrentSerie.UpdateImageVal();

   if (  ((CurrentSerie.GetImageVal() < 100) && (lastStatus == true))
      || (CurrentSerie.GetImageVal() < 5))
   {
      TestUrl(CurrentSerie.GetURL());
   }
   else
   {
      if(QDir(CurrentSerie.GetChapterFolder()).exists() == true)
      {
         //ajouter un chapitre
         long chapterValue = ui->Tab2StatusTable->item(DownloadSeriesIdx, CHAPTER)->text().toLong();
         chapterValue++;
         QString ChapterTxt;
         ChapterTxt.setNum(chapterValue);
         ui->Tab2StatusTable->setItem(DownloadSeriesIdx, CHAPTER, new QTableWidgetItem(ChapterTxt));
      }

      DownloadSeriesIdx++;
      if (DownloadSeriesIdx < NumberOfSeriesSearch)
      {
         CurrentSerie.SetSeries(GetLineInfos(DownloadSeriesIdx));
         CurrentSerie.UpdateChapterVal();

         TestUrl(CurrentSerie.GetURL());
      }
      else
      {
         ui->Tab1TextScreen->append("");
         ui->Tab1TextScreen->append("***Search ended***");
      }
   }
}
