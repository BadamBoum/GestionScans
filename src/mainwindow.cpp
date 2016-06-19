#include <QDebug>
#include <QFile>
#include <QDate>
#include <QTableWidgetItem>
#include <QtNetwork>

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
            }

         }
      }
   }

   connect(ui->Tab1AddButton, SIGNAL(clicked(bool)), this, SLOT(slotTab1AddButton()));
   connect(ui->Tab1Setting, SIGNAL(clicked(bool)), this, SLOT(slotTab1Setting()));
   connect(ui->Tab1PDF, SIGNAL(clicked(bool)), this, SLOT(slotTab1Pdf()));
   connect(ui->Tab1Search, SIGNAL(clicked(bool)), this, SLOT(slotTab1Search()));
   connect(ui->Tab1Delete, SIGNAL(clicked(bool)), this, SLOT(slotTab1Delete()));
}

MainWindow::~MainWindow()
{
   QFile Datafile("datafile.txt");
   Datafile.open(QIODevice::WriteOnly);
   QTextStream out(&Datafile);
   QString temp;

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

void MainWindow::AddLineStatusTable(QStringList NewLine)
{
    ui->Tab1SelectedSerie->addItem(NewLine.at(NAME));

    ui->Tab2StatusTable->insertRow(ui->Tab2StatusTable->rowCount());

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

   return StringRet;
}

void MainWindow::ModifyStatusTable(QStringList NewLine, int Index)
{
    ui->Tab2StatusTable->setItem(Index, NAME,    new QTableWidgetItem(NewLine.at(NAME)));
    ui->Tab2StatusTable->setItem(Index, CHAPTER, new QTableWidgetItem(NewLine.at(CHAPTER)));
//    ui->Tab2StatusTable->setItem(Index, DATE,    new QTableWidgetItem(NewLine.at(DATE)));
    ui->Tab2StatusTable->setItem(Index, VOLUME,  new QTableWidgetItem(NewLine.at(VOLUME)));
//    ui->Tab2StatusTable->setItem(Index, FOLDER,  new QTableWidgetItem(NewLine.at(FOLDER)));
    ui->Tab2StatusTable->setItem(Index, URL,     new QTableWidgetItem(NewLine.at(URL)));
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
   ui->Tab1TextScreen->append("***Search Start***");
   DownloadSeriesIdx = 0;
   CurrentSerie.SetSeries(GetLineInfos(DownloadSeriesIdx));
   CurrentSerie.UpdateChapterVal();

   erreurTrouvee = false;

   QUrl url = QUrl(CurrentSerie.GetURL());
   QNetworkRequest requete(url);
   QNetworkAccessManager *m = new QNetworkAccessManager;
   QNetworkReply *r = m->get(requete);

   if(ui->DebugBox->isChecked())
   {
      ui->Tab1TextScreen->append("URL tested :");
      ui->Tab1TextScreen->append(CurrentSerie.GetURL());
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

   if ((CurrentSerie.GetImageVal() < 25) && (lastStatus == true))
   {
      QUrl url = QUrl(CurrentSerie.GetURL());
      QNetworkRequest requete(url);
      QNetworkAccessManager *m = new QNetworkAccessManager;
      QNetworkReply *r = m->get(requete);

      if(ui->DebugBox->isChecked())
      {
         ui->Tab1TextScreen->append("URL tested :");
         ui->Tab1TextScreen->append(CurrentSerie.GetURL());
      }

      connect(r, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(messageErreur(QNetworkReply::NetworkError)));
      connect(r, SIGNAL(finished()), this, SLOT(enregistrer()));
   }
   else
   {
      if (DownloadSeriesIdx < ui->Tab2StatusTable->lineWidth())
      {
         DownloadSeriesIdx++;
         CurrentSerie.SetSeries(GetLineInfos(DownloadSeriesIdx));
         CurrentSerie.UpdateChapterVal();

         erreurTrouvee = false;

         QUrl url = QUrl(CurrentSerie.GetURL());
         QNetworkRequest requete(url);
         QNetworkAccessManager *m = new QNetworkAccessManager;
         QNetworkReply *r = m->get(requete);

         if(ui->DebugBox->isChecked())
         {
            ui->Tab1TextScreen->append("URL tested :");
            ui->Tab1TextScreen->append(CurrentSerie.GetURL());
         }

         connect(r, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(messageErreur(QNetworkReply::NetworkError)));
         connect(r, SIGNAL(finished()), this, SLOT(enregistrer()));
      }
   }
}
