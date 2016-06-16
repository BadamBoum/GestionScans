#include "add.h"
#include "ui_add.h"

Add::Add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
    connect(ui->AddOK, SIGNAL(clicked(bool)), this, SLOT(slotAddOkButton()));
}

Add::~Add()
{
    delete ui;
}

void Add::slotAddOkButton()
{
//    Ajouter une ligne
}
