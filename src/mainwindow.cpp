#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
}

void MainWindow::slotTab1Setting()
{
    ui->Tab1TextScreen->append("Setting");
}

void MainWindow::slotTab1Pdf()
{
    ui->Tab1TextScreen->append("PDF");
}

void MainWindow::slotTab1Search()
{
    ui->Tab1TextScreen->append("Search");
}

