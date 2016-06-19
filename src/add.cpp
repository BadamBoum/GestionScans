#include <QDate>
#include "add.h"
#include "ui_add.h"
#include "mainwindow.h"

Add::Add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
    connect(ui->AddOK, SIGNAL(clicked(bool)), this, SLOT(slotAddOkButton()));
    connect(ui->AddCancel, SIGNAL(clicked(bool)), this, SLOT(slotAddCancelButton()));
}

Add::~Add()
{
    delete ui;
}

void Add::slotAddOkButton()
{
   QStringList String;
   QString temp;
   String.insert(NAME,    ui->TextSeriesName->text());
   String.insert(CHAPTER, ui->ChapterValue->cleanText());
   String.insert(DATE,    QDate::currentDate().toString("dd.MM.yyyy"));
   String.insert(VOLUME,  ui->VolumeValue->cleanText());
   String.insert(URL,     ui->TextURL->text());

   if(ui->AddCreateFolder->checkState() == 2)
   {
      temp.append(ui->TextFolder->text());
      if (temp.right(1) != "\\")
      {
         temp.append("\\");
      }
      temp.append(ui->TextSeriesName->text());
      String.insert(FOLDER, temp);
   }
   else
   {
      String.insert(FOLDER,  ui->TextFolder->text());
   }

   emit addNewSerie(String);

   this->close();
}

void Add::slotAddCancelButton()
{
   this->close();
}
