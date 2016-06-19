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

void Setting::FillWindow(QStringList Datas, int Index)
{
   ui->LabelSerie->setText(Datas.at(NAME));
   ui->TextURL->setText(Datas.at(URL));
   ui->VolumeValue->setValue(Datas.at(VOLUME).toInt());
   ui->ChapterValue->setValue(Datas.at(CHAPTER).toInt());
   ui->DigitValue->setValue(Datas.at(DIGIT).toInt());
   CurrentIdx = Index;
}

void Setting::slotOkButton()
{
   QStringList String;
   String.insert(NAME,    ui->LabelSerie->text());
   String.insert(CHAPTER, ui->ChapterValue->cleanText());
   String.insert(DATE,    "");
   String.insert(VOLUME,  ui->VolumeValue->cleanText());
   String.insert(URL,     ui->TextURL->text());
   String.insert(FOLDER,  "");
   String.insert(DIGIT,   ui->DigitValue->cleanText());

   emit ModifySerie(String, CurrentIdx);

   this->close();
}

void Setting::slotCancelButton()
{
   this->close();
}
