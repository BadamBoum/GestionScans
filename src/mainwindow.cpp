#include <QDebug>
#include <QFile>
#include <QTableWidgetItem>

#include "mainwindow.h"
#include "add.h"
#include "ui_mainwindow.h"

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
//      QByteArrayList SeriesNames;
      QByteArrayList URLs;
      QByteArrayList Folders;
      QByteArrayList Tome;
      QByteArrayList Chapter;
      QByteArrayList Date;

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

      QTableWidgetItem WidgetName;/*
      WidgetName.setData(0, SeriesNames.at(0));*/
      //        ui->Tab2StatusTable->setItem(0,0,WidgetName);
   }
   else
   {
      Add *AddWindows = new Add;
      AddWindows->show();
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

   for(int i = 0; i < ui->Tab2StatusTable->rowCount(); i++)
   {
      for(int j = 0; j < ui->Tab2StatusTable->columnCount(); j++)
      {
         out << (*ui->Tab2StatusTable->takeItem(i,j)).text();

         if (j < ui->Tab2StatusTable->columnCount() - 1) out << ";";
      }
      if (i < ui->Tab2StatusTable->rowCount() - 1) out << "\n";
   }

   delete ui;
}

void MainWindow::slotTab1AddButton()
{
   ui->Tab1TextScreen->append("Add");
   Add *AddWindows = new Add;
   AddWindows->show();
   //    Ouvrir boite de dialogue Add
   //    if (statusReturn == OK)
   //    {
   //        ui->Tab1TextScreen->append("New Manga added",ligneSplitee.at(4));
   //    }
}

void MainWindow::slotTab1Setting()
{
   ui->Tab1TextScreen->append("Setting");
}

void MainWindow::slotTab1Delete()
{
   ui->Tab1TextScreen->append("");
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
   //    foreach(QByteArray ligne, listeDesLignes)
   //    {
   //        ui->Tab1TextScreen->append("Search",ligne);
   //        if (exist(URL(chapter+1,1)))
   //        {
   //            ligneSplitee.at(4)++;
   //            ligneSplitee.at(5) = CurrentDate;
   //            WriteFile();
   //            ui->Tab1TextScreen->append("New Chapter found",ligneSplitee.at(4));
   //            for (index=1;index<25;index++)
   //            {
   //                if (exist(URL(ligneSplitee.at(4),index)))
   //                {
   //                    ui->Tab1TextScreen->append("Save image",ligne);
   //                    SaveURL("folder"\chapter\[chapter]_[index].[3LastCharOfURL]);
   //                }
   //            }
   //        }
   //    }
}

