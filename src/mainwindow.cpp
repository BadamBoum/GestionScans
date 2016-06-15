#include <QDebug>
#include <QFile>

#include "mainwindow.h"
#include "add.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file("datafile.txt");
    file.open(QIODevice::WriteOnly);
    QByteArray fileContent = file.readAll();
    QByteArrayList listeDesLignes = fileContent.split('\n');

    foreach(QByteArray ligne, listeDesLignes)
    {
        QByteArrayList ligneSplitee = ligne.split(';');
        ligneSplitee.at(0);//Series Name
        ligneSplitee.at(1);//URL
        ligneSplitee.at(2);//Folder
        ligneSplitee.at(3);//Tome
        ligneSplitee.at(4);//Chapter
        ligneSplitee.at(5);//Date
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

