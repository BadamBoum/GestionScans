#include "add.h"
#include "ui_add.h"

Add::Add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
}

Add::~Add()
{
    connect(ui->AddOK, SIGNAL(clicked(bool)), this, SLOT(slotAddOkButton()));
    delete ui;
}

void MainWindow::slotAddOkButton()
{
//    Ajouter une ligne
}
