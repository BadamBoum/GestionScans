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
   String.insert(NAME,    ui->TextSeriesName->text());
   String.insert(CHAPTER, ui->ChapterValue->cleanText());
   String.insert(DATE,    QDate::currentDate().toString("dd.MM.yyyy"));
   String.insert(VOLUME,  ui->VolumeValue->cleanText());
   String.insert(URL,     ui->TextURL->text());
   String.insert(FOLDER,  "");
   String.insert(DIGIT,   "2");
   String.insert(EXT,     ui->TextURL->text().remove(0, ui->TextURL->text().size()));

   if (ui->BoxWeeklyPDF->isChecked() == true)
   {
      String.insert(WEEKLY, "true");
   }
   else
   {
      String.insert(WEEKLY, "false");
   }

   emit addNewSerie(String);

   this->close();
}

void Add::slotAddCancelButton()
{
   this->close();
}
