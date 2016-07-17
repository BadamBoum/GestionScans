#ifndef PDF_H
#define PDF_H

#include <QWidget>
#include "seriesbox.h"

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
    void UpdateVolume(int);

public slots:
    void FillPdfWindow(QStringList Datas, int Index);

private slots:
    void slotPrintButton();
    void slotCancelButton();

private:
   Ui::PDF *ui;
   SeriesBox SeriesInfos;
   int CurrentIdx = 0;
};

#endif // PDF_H
