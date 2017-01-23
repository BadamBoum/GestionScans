#include <QDir>
#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>
#include <QPainter>

#include <QPixmap>
#include <QImage>

#include "mainwindow.h"
#include "pdf.h"
#include "ui_pdf.h"

PDF::PDF(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PDF)
{
    ui->setupUi(this);

    connect(ui->Print, SIGNAL(clicked(bool)), this, SLOT(slotPrintButton()));
    connect(ui->Cancel, SIGNAL(clicked(bool)), this, SLOT(slotCancelButton()));
}

PDF::~PDF()
{
    delete ui;
}

void PDF::FillPdfWindow(QStringList Datas, int Index)
{
   SeriesInfos.SetSeries(Datas);
   ui->LabelSerie->setText(SeriesInfos.GetSeriesName());
   ui->VolNum->setValue(SeriesInfos.GetVolume().toInt());
   ui->EndChap->setValue(SeriesInfos.GetChapter().toInt());

   while(QDir(SeriesInfos.GetChapterFolder()).exists() == true)
   {
      SeriesInfos.DecreaseChapterVal();
   }

   SeriesInfos.UpdateChapterVal();

   CurrentIdx = Index;
   ui->StartChap->setValue(SeriesInfos.GetChapter().toInt());
}

void PDF::slotPrintButton()
{
    QDir monRepertoire;
    bool firstpage = true;
    SeriesInfos.SetChapter(ui->StartChap->value());
    monRepertoire.setPath(SeriesInfos.GetChapterFolder());

    if (monRepertoire.exists())
    {
        QPdfWriter pdfWriter(SeriesInfos.GetSeriesFolder() + "/" + SeriesInfos.GetSeriesName() + " Tome " + SeriesInfos.GetVolume() + ".pdf");
        pdfWriter.setPageSize(QPagedPaintDevice::A4);
        const qreal horizontalMarginMM = 10.0;     // 10 mm margin on each side
        const qreal verticalMarginMM = 10.0;
        QPagedPaintDevice::Margins margins;
        margins.left = margins.right = horizontalMarginMM;
        margins.top = margins.bottom = verticalMarginMM;
        pdfWriter.setMargins(margins);
        QPixmap pixmap;
        QPainter painter;

        while ((monRepertoire.exists()) && (ui->EndChap->value() >= SeriesInfos.GetChapter().toInt()))
        {
            QStringList listOfFiles = monRepertoire.entryList();
            for (int i = 2; i < listOfFiles.size(); i++)
            {
                QString imagePath = monRepertoire.absolutePath() + "/" + listOfFiles.at(i);
                if ((imagePath.contains("jpg")) || (imagePath.contains("png")))
                {
                    pixmap.load(imagePath);
                    if (pixmap.width() >  pixmap.height())
                    {
                        if (ui->Vertical->isChecked())
                        {
                            if (firstpage == false)
                            {
                                pdfWriter.newPage();
                            }
                            else
                            {
                                painter.begin(&pdfWriter);
                            }
                            QTransform t;
                            pixmap = pixmap.transformed(t.rotate(90),Qt::SmoothTransformation);
                            painter.drawPixmap(QRectF(0, 0, pdfWriter.width(), pdfWriter.height()), pixmap, QRectF(0, 0, pixmap.width(), pixmap.height()));
                        }
                        else
                        {
                            pdfWriter.setPageOrientation(QPageLayout::Landscape);
                            if (firstpage == false)
                            {
                                pdfWriter.newPage();
                            }
                            else
                            {
                                painter.begin(&pdfWriter);
                            }
                            painter.drawPixmap(QRectF(0, 0, pdfWriter.width(), pdfWriter.height()), pixmap, QRectF(0, 0, pixmap.width(), pixmap.height()));
                            pdfWriter.setPageOrientation(QPageLayout::Portrait);
                        }
                    }
                    else
                    {
                        if (firstpage == false)
                        {
                            pdfWriter.newPage();
                        }
                        else
                        {
                            painter.begin(&pdfWriter);
                        }
                        painter.drawPixmap(QRectF(0, 0, pdfWriter.width(), pdfWriter.height()), pixmap, QRectF(0, 0, pixmap.width(), pixmap.height()));
                    }
                    firstpage = false;
                }
            }
            SeriesInfos.UpdateChapterVal();
            monRepertoire.setPath(SeriesInfos.GetChapterFolder());
        }

        emit UpdateVolume(CurrentIdx);

        painter.end();
    }
    this->close();
}

void PDF::slotCancelButton()
{
    this->close();
}
