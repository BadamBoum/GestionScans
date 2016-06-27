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
//   ui->DigitValue->setValue(Datas.at(DIGIT).toInt());
   CurrentIdx = Index;
   Date       = Datas.at(DATE);
   Folder     = Datas.at(FOLDER);
   Digit      = Datas.at(DIGIT);
}

void Setting::slotOkButton()
{
   QStringList String;
   String.insert(NAME,    ui->LabelSerie->text());
   String.insert(CHAPTER, ui->ChapterValue->cleanText());
   String.insert(DATE,    Date);
   String.insert(VOLUME,  ui->VolumeValue->cleanText());
   String.insert(URL,     ui->TextURL->text());
   String.insert(FOLDER,  Folder);
   String.insert(DIGIT,   Digit);
   String.insert(EXT,     ui->TextURL->text().remove(0, ui->TextURL->text().size()));

   emit ModifySerie(String, CurrentIdx);

   this->close();
}

void Setting::slotCancelButton()
{
   this->close();
}
