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
//   ui->Tab2StatusTable->insertRow(ui->Tab2StatusTable->rowCount());
//   ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, NAME, new QTableWidgetItem(String));
   String = ui->TextURL->text();
//   ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, URL, new QTableWidgetItem(String));
   String = ui->TextFolder->text();
   if(ui->AddCreateFolder->checkState() == 2) ;
//   ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, FOLDER, new QTableWidgetItem(String));
//   String = ui->VolumeValue->value();
//   ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, VOLUME, new QTableWidgetItem(String));
//   ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, CHAPTER, new QTableWidgetItem(String));
//   ui->Tab2StatusTable->setItem(ui->Tab2StatusTable->rowCount() - 1, DATE, new QTableWidgetItem(String));
}

void Add::slotAddCancelButton()
{
   this->close();
}
