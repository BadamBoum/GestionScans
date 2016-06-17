#include <QDate>
#include "add.h"
#include "ui_add.h"

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
   QString String = ui->TextSeriesName->text();
   String.append(";");
   String.append(ui->ChapterValue->cleanText());
   String.append(";");
   String.append(QDate::currentDate().toString(0));//dd.MM.yyyy));
   String.append(";");
   String.append(ui->VolumeValue->cleanText());
   String.append(";");
   String.append(ui->TextFolder->text());
   if(ui->AddCreateFolder->checkState() == 2)
   {
       String.append(ui->TextSeriesName->text());
   }
   String.append(";");
   String.append(ui->TextURL->text());

   emit addNewSerie(String);

   this->close();
}

void Add::slotAddCancelButton()
{
   this->close();
}
