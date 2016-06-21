#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
   Q_OBJECT

public:
   explicit Setting(QWidget *parent = 0);
   ~Setting();

signals:
    void ModifySerie(QStringList, int);

public slots:
    void FillWindow(QStringList Datas, int Index);

private slots:
    void slotOkButton();
    void slotCancelButton();

private:
   Ui::Setting *ui;
   int CurrentIdx = 0;
   QString Date;
   QString Folder;
};

#endif // SETTING_H
