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
        QByteArrayList SeriesNames;
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
                SeriesNames.append(ligneSplitee.at(0));//Series Name
                URLs.append(ligneSplitee.at(1));//URL
                Folders.append(ligneSplitee.at(2));//Folder
                Tome.append(ligneSplitee.at(3));//Tome
                Chapter.append(ligneSplitee.at(4));//Chapter
                Date.append(ligneSplitee.at(5));//Date
            }
        }

        QTableWidgetItem WidgetName;
        WidgetName.setData(0, SeriesNames.at(0));
//        ui->Tab2StatusTable->setItem(0,0,WidgetName);
    }

    connect(ui->Tab1AddButton, SIGNAL(clicked(bool)), this, SLOT(slotTab1AddButton()));
    connect(ui->Tab1Setting, SIGNAL(clicked(bool)), this, SLOT(slotTab1Setting()));
    connect(ui->Tab1PDF, SIGNAL(clicked(bool)), this, SLOT(slotTab1Pdf()));
    connect(ui->Tab1Search, SIGNAL(clicked(bool)), this, SLOT(slotTab1Search()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTab1AddButton()
{
    ui->Tab1TextScreen->append("Add");
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

