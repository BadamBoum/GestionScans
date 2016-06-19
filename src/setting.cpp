#include "setting.h"
#include "ui_setting.h"
#include "mainwindow.h"

Setting::Setting(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::Setting)
{
   ui->setupUi(this);

   connect(ui->OK, SIGNAL(clicked(bool)), this, SLOT(slotOkButton()));
   connect(ui->Cancel, SIGNAL(clicked(bool)), this, SLOT(slotCancelButton()));
}

Setting::~Setting()
{
   delete ui;
}

void Setting::FillWindow(QStringList Datas)
{
   ui->LabelSerie->setText(Datas.at(NAME));
   ui->TextFolder->setText(Datas.at(FOLDER));
   ui->TextURL->setText(Datas.at(URL));
   ui->VolumeValue->setValue(Datas.at(VOLUME).toInt());
   ui->ChapterValue->setValue(Datas.at(CHAPTER).toInt());
}

void Setting::slotOkButton()
{
//   QStringList String;
//   String.insert(NAME,    ui->TextSeriesName->text());
//   String.insert(CHAPTER, ui->ChapterValue->cleanText());
//   String.insert(DATE,    QDate::currentDate().toString("dd.MM.yyyy"));
//   String.insert(VOLUME,  ui->VolumeValue->cleanText());
//   String.insert(URL,     ui->TextURL->text());
//   String.insert(FOLDER,  ui->TextFolder->text());

//   emit ModifySerie(String);

   this->close();
}

void Setting::slotCancelButton()
{
   this->close();
}
