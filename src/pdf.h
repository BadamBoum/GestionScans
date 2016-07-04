#ifndef PDF_H
#define PDF_H

#include <QWidget>

namespace Ui {
class PDF;
}

class PDF : public QWidget
{
   Q_OBJECT

public:
   explicit PDF(QWidget *parent = 0);
   ~PDF();

signals:
    void PrintSerie(/*SeriesBox*/);

public slots:
    void FillPdfWindow(/*SeriesBox Datas*/);

private slots:
    void slotPrintButton();
    void slotCancelButton();

private:
   Ui::PDF *ui;
};

#endif // PDF_H
