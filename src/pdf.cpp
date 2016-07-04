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

void PDF::FillPdfWindow(/*SeriesBox Datas*/)
{
    //   ui->LabelSerie->setText(Datas.GetSeriesName());
    //   ui->VolNum->setValue(Datas.GetVolume().toInt() + 1);
    //   ui->EndChap->setValue(Datas.GetChapter().toInt());

    //   while(QDir(Datas.GetChapterFolder()).exists() == true))
    //   {
    //      Datas.DecreaseChapterVal();
    //   }

    //   ui->StartChap->setValue(i);
}

void PDF::slotPrintButton()
{
    QString Folder = "C:\\Users\\jlequerl\\Documents\\Database\\Fairy Tail\\490";
    QPdfWriter printpdf("C:\\Users\\jlequerl\\Documents\\Database\\test.pdf");
    printpdf.setPageSize(QPagedPaintDevice::A4);
    printpdf.setPageOrientation(QPageLayout::Portrait);
    const qreal horizontalMarginMM = 10.0;
    const qreal verticalMarginMM = 10.0;
    QPagedPaintDevice::Margins margins;
    margins.left = margins.right = horizontalMarginMM;
    margins.top = margins.bottom = verticalMarginMM;
    printpdf.setMargins(margins);

    //   //Render the QTableWidget in a QPixmap
    //   QPixmap tempPixmap(ui->tableWidget->size());
    //   //QPixmap tempPixmap(QSize(1920,1080));
    //   ui->tableWidget->render(&tempPixmap);

    //   //Rotate the QPixmap
    //   QTransform t;
    //   QPixmap pixmap(ui->tableWidget->size().transposed());
    //   pixmap = tempPixmap.transformed(t.rotate(90),Qt::SmoothTransformation);


    //Draw the QPixmap with a QPainter
    //   QPainter painter;
    //   painter.begin(&printpdf);
    //   painter.drawPixmap(QRectF(0, 0, test.width(), test.height()), pixmap, QRectF(0, 0,pixmap.width(), pixmap.height()));
    //   painter.end();


    bool allImageFounded = false;
    int i = 0;
    QString chapterTxt = Folder;
    chapterTxt.remove(0, chapterTxt.size()-3);
    //   QPrinter printer;
    //   printer.setOutputFormat(QPrinter::PdfFormat);
    //   printer.setFullPage(true);
    //   printer.setPageSize(QPrinter::A4);
    //   printer.setOutputFileName(Folder + ".pdf");
    //   printer.setOrientation(QPrinter::Portrait);
    //   printer.setPrinterName(printer.printerName());
    //   printer.setResolution(600);

    QPainter chapter;

    chapter.begin(&printpdf);

    QMatrix matrix;
    matrix.rotate(270);
    QRect rect = chapter.viewport();

    while(allImageFounded == false)
    {
        QString imageFolder = Folder;
        imageFolder += "\\";
        imageFolder += chapterTxt;
        imageFolder += "_";

        QString convertion;
        convertion.setNum(i);

        if (i < 10)
        {
            convertion.push_front("0");
        }

        imageFolder += convertion;
        imageFolder += ".";
        imageFolder += "jpg";

        QFile ImageFile(imageFolder);

        if(ImageFile.exists() == false)
        {
            imageFolder.remove(imageFolder.size()-3, imageFolder.size());
            imageFolder += "png";
            ImageFile.setFileName(imageFolder);
            if(ImageFile.exists() == false)
            {
                if(i > 5)
                {
                    allImageFounded = true;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                if(i > 0)
                {
                    //                if(!printer.newPage()) return;
                    printpdf.newPage();
                }

                QImage image(imageFolder);
                QPixmap Pix;
                Pix.load(imageFolder);
                QSize size = image.size();

                if(size.width() > size.height())
                {
                    image = image.transformed(matrix);
                    size = image.size();
                }

                size.scale(rect.size(), Qt::KeepAspectRatio);
                int x = rect.x() + ((rect.size().width() - size.width())/2);
                int y = rect.y() + ((rect.size().height() - size.height())/2);

                //          chapter.setViewport(x, y, size.width(), size.height());
                //          chapter.setWindow(image.rect());
                //          chapter.drawImage(0, 0, image);
                chapter.drawPixmap(rect, Pix);
                i++;
            }
        }
        else
        {
            if(i > 0)
            {
                printpdf.newPage();
            }

            QImage image(imageFolder);
            QSize size = image.size();
            QPixmap Pix;
            Pix.load(imageFolder);

            if(size.width() > size.height())
            {
                image = image.transformed(matrix);
                size = image.size();
            }

            size.scale(rect.size(), Qt::KeepAspectRatio);
            int x = rect.x() + ((rect.size().width() - size.width())/2);
            int y = rect.y() + ((rect.size().height() - size.height())/2);

            //          chapter.setViewport(x, y, size.width(), size.height());
            //          chapter.setWindow(image.rect());
            //          chapter.drawImage(0, 0, image);
            chapter.drawPixmap(rect, Pix);
            i++;
        }
    }

    chapter.end();
    this->close();
}

void PDF::slotCancelButton()
{
    QString imagePath = "C:/Users/jlequerl/Desktop/01.jpg";
    //QString imagePath = "./jpeg-home.jpg";
    QPdfWriter pdfWriter("C:/Users/jlequerl/Documents/Database/test.pdf");
    pdfWriter.setPageSize(QPagedPaintDevice::A4);
    const qreal horizontalMarginMM = 10.0;     // 10 mm margin on each side
    const qreal verticalMarginMM = 10.0;
    QPagedPaintDevice::Margins margins;
    margins.left = margins.right = horizontalMarginMM;
    margins.top = margins.bottom = verticalMarginMM;
    pdfWriter.setMargins(margins);

    //Open PNG image in a QPixmap
    QPixmap pixmap(imagePath);

    QImage image(imagePath);

    //Rotate the QPixmap
    //QTransform t;
    //QPixmap pixmap(ui->tableWidget->size().transposed());
    //pixmap = tempPixmap.transformed(t.rotate(90),Qt::SmoothTransformation);


    //Draw the QPixmap with a QPainter
    QPainter painter;
    painter.begin(&pdfWriter);
    painter.drawPixmap(QRectF(0, 0, pdfWriter.width(), pdfWriter.height()), pixmap, QRectF(0, 0,pixmap.width(), pixmap.height()));
    painter.end();
    this->close();
}
