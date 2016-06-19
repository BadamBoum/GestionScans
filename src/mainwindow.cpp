#include <QDebug>
#include <QFile>
#include <QDate>
#include <QTableWidgetItem>
#include <QtNetwork>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add.h"
#include "setting.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
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
         temp.append( (*ui->Tab2StatusTable->takeItem(i,j)).text() );

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

    ModifyStatusTable(NewLine);

    ui->Tab1TextScreen->append("Series ");
    ui->Tab1TextScreen->insertPlainText(NewLine.at(NAME));
    ui->Tab1TextScreen->insertPlainText(" added");
}

void MainWindow::slotTab1Setting()
{
   Setting *SettingWindows = new Setting;

   connect(this, SIGNAL(SeriesInfo(QStringList)), SettingWindows, SLOT(FillWindow(QStringList)));
   emit SeriesInfo(GetLineInfos(ui->Tab1SelectedSerie->currentIndex()));

   SettingWindows->show();

   connect(SettingWindows, SIGNAL(ModifySerie(QStringList)), this, SLOT(ModifyStatusTable(QStringList)));
}

QStringList MainWindow::GetLineInfos(int Idx)
{
   QStringList StringRet;

   StringRet.insert(NAME,    ui->Tab2StatusTable->takeItem(Idx, NAME)->text());
   StringRet.insert(CHAPTER, ui->Tab2StatusTable->takeItem(Idx, CHAPTER)->text());
   StringRet.insert(DATE,    ui->Tab2StatusTable->takeItem(Idx, DATE)->text());
   StringRet.insert(VOLUME,  ui->Tab2StatusTable->takeItem(Idx, VOLUME)->text());
   StringRet.insert(URL,     ui->Tab2StatusTable->takeItem(Idx, URL)->text());
   StringRet.insert(FOLDER,  ui->Tab2StatusTable->takeItem(Idx, FOLDER)->text());

   return StringRet;
}

void MainWindow::ModifyStatusTable(QStringList NewLine)
{
    ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, NAME,    new QTableWidgetItem(NewLine.at(NAME)));
    ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, CHAPTER, new QTableWidgetItem(NewLine.at(CHAPTER)));
    ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, DATE,    new QTableWidgetItem(NewLine.at(DATE)));
    ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, VOLUME,  new QTableWidgetItem(NewLine.at(VOLUME)));
    ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, FOLDER,  new QTableWidgetItem(NewLine.at(FOLDER)));
    ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, URL,     new QTableWidgetItem(NewLine.at(URL)));
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
   QString TextDirectory;
   QString TextChapter;
   QString TextUrlSrc;
   QString TextUrl;
   long NumChapter;

//   for(int i = 0; i < ui->Tab2StatusTable->rowCount(); i++)
//   {
      TextUrlSrc    = ui->Tab2StatusTable->takeItem(0,URL)->text();
      TextDirectory = ui->Tab2StatusTable->takeItem(0,FOLDER)->text();
      TextChapter   = ui->Tab2StatusTable->takeItem(0,CHAPTER)->text();
      NumChapter    = TextChapter.toLong();
      NumChapter++;
      TextChapter.setNum(NumChapter);

      TextUrlSrc.replace("[Chapter]", TextChapter);
      TextUrl = TextUrlSrc;
      TextUrl.replace("[Image]","01");

      erreurTrouvee = false;

      QUrl url = QUrl(TextUrl); //On récupère l'URL
      QNetworkRequest requete(url); //On crée notre requête
      QNetworkAccessManager *m = new QNetworkAccessManager; //On crée le QNetworkAccessManager qui va traiter la requête
      /*Ensuite, on utilise la méthode get() pour télécharger le contenu de notre requête.
      On récupère un pointeur de QNetworkReply.*/
      QNetworkReply *r = m->get(requete);

      connect(r, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(messageErreur(QNetworkReply::NetworkError)));
      connect(r, SIGNAL(finished()), this, SLOT(enregistrer()));

//      if(TempUrl.isValid())
//      {
//         for(int j = 1; j < 25; j++)
//         {
//            TextUrl = TextUrlSrc;
//            if (j < 10)
//            {
//               TextUrl.replace("[Image]","0[Image]");
//            }
//            TextUrl.replace("[Image]",Text.setNum(j));
//         }
//         ui->Tab1TextScreen->append("Series ");
//         ui->Tab1TextScreen->insertPlainText(ui->Tab1SelectedSerie->currentText());
//         ui->Tab1TextScreen->insertPlainText(" downloaded");
//         ui->Tab2StatusTable->setItem(i, CHAPTER, new QTableWidgetItem(TextChapter));
//      }
//   }
}

void MainWindow::messageErreur(QNetworkReply::NetworkError)
{
    erreurTrouvee = true; //On indique qu'il y a eu une erreur au slot enregistrer
    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
    ui->Tab1TextScreen->append(r->errorString());
}

void MainWindow::enregistrer()
{
   //On vérifie qu'il n'y a pas eu d'erreur.
   if(!erreurTrouvee)
   {
      QNetworkReply *r = qobject_cast<QNetworkReply*>(sender()); //On récupère la réponse du serveur
      QFile f("reponse.txt"); //On ouvre le fichier

      if ( f.open(QIODevice::WriteOnly) )
      {
         f.write(r->readAll()); ////On lit la réponse du serveur que l'on met dans un fichier
         f.close(); //On ferme le fichier
         r->deleteLater(); //IMPORTANT : on emploie la fonction deleteLater() pour supprimer la réponse du serveur.
         //Si vous ne le faites pas, vous risquez des fuites de mémoire ou autre.
      }
   }
}

void MainWindow::loadImage()
{
 QPixmap buttonImage;
// buttonImage.loadFromData(m_pImgCtrl->downloadedData());
}
